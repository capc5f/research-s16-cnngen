#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <cudnn.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <cublas.h>

#include <iostream>
#include <string>
#include <vector>
#include "..//ece8270project/ImageBatch.h"
#include "../layers/InputLayer.h"
#include "../layers/ConvolutionLayer.h"
#include "../layers/PoolingLayer.h"
#include "../layers/ReLULayer.h"
#include "../layers/LRNLayer.h"
#include "../layers/InnerProductLayer.h"
#include "../layers/SoftmaxLayer.h"
#include "../prototxt/Prototxt.h"
#include "../utils/UserInput.h"
#include "../utils/GenerateLayers.h"
#include "../layers/LayerBase.h"
#include "../utils/Utilities.h"

//#include "../layers/layer_helpers/LayerEnums.h"
//#include "../layers/layer_helpers/LayerTypes.h"
//#include "../layers/layer_helpers/Param.h"

#define ITERS 10
#define OMP_NUM_THREADS 16
#define BATCH_SIZE LayerBase::getBatchSize()

cudnnHandle_t cudnnHandle;			//global handler for cudnn library API
// BATCHSIZE = LayerBase::getBatchSize() 

//\/\/\/\/\/\/ function checks the status of the cuDNN API call and returns error string //\\//\\/\/\/\/ 
void cudnnErrorCheck(cudnnStatus_t status){
    const char * x;
     if (status!=CUDNN_STATUS_SUCCESS){
        x = cudnnGetErrorString(status);
        printf("%s\n",x);
   }
}

//\/\/\/\/\/ function initializes a tensor, filter, conv layer with random floating point values between 0 and 1 /\/\/\/\/\/\/
void initializeMatrix(float * entity,int size){
    int i = 0;
    #pragma omp parallel for    
       for (i=0;i<size;i++){
            entity[i]= (float)((float) rand() / (float)RAND_MAX);
       }

}

//\/\/\/\/// function prints if allocation fails ///\/\/\/\///
void allocCheck(float * x){
    if (x==NULL)
        puts("memory allocation failure");
}

//\/\/\/\/// makes sure cudamemcpy works ///\/\/\/\///
void cudaErrCheck(cudaError_t err){
    if (err!= cudaSuccess){
        printf("%s\n",cudaGetErrorString(err));
    }
}


///\/\/\/\/\/\\/\/\/\/ Tensor Superclass ///\/\/\/\/\/\/\/\/// 
class Tensor {
	public: 
		~Tensor();
		cudnnTensorDescriptor_t tensorDesc;
		cudnnTensorFormat_t tensFormat;
		cudnnDataType_t dataType;
		float *h_tensor,*d_tensor;
		size_t size;
		int height, width, depth, n, c, h, w;
		LayerType type;
		Tensor(int, int ,int, int);
		Tensor();
		virtual void doAction(cudnnTensorDescriptor_t tensorDesc2, float *d_tensor2){};
};

										///\/\/\/\/ Default Constructor ///\/\/\/\/
Tensor::Tensor(){
	d_tensor = NULL;
	h_tensor = NULL;
}

										///\/\/\/\/ Constructor ///\/\/\/\/
Tensor::Tensor(int n,int c,int h,int w){
	printf("Tensor vals: n = %d c = %d h = %d w = %d\t", n, c ,h, w);
	d_tensor = NULL;
	h_tensor = NULL;
	this->n = n;
	this->c = c;
	this->h = h;
	this->w = w;
	size = n*c*h*w;  

	h_tensor = (float *)malloc(sizeof(float)*size);			
	cudaMalloc((void **)&(d_tensor),sizeof(float)*(size));
	allocCheck(h_tensor);
	allocCheck(d_tensor);

    initializeMatrix(h_tensor,size);				
	cudaErrCheck(cudaMemcpy(d_tensor,h_tensor,(sizeof(float)*size),cudaMemcpyHostToDevice)); //copy initial weights

    cudnnErrorCheck(cudnnCreateTensorDescriptor(&tensorDesc));
    tensFormat = CUDNN_TENSOR_NCHW;
    dataType = CUDNN_DATA_FLOAT;
    cudnnErrorCheck(cudnnSetTensor4dDescriptor(tensorDesc, tensFormat, dataType, n, c, h, w));
	puts("Tensor Created");
}

										///\/\/\/\/\/ Destructor ///\/\/\/\/\/\/\/\//
Tensor::~Tensor(){
	free(h_tensor);
	cudaFree(d_tensor);
	cudnnErrorCheck(cudnnDestroyTensorDescriptor(tensorDesc));
}

///\/\/\/\/\/\/\/\/\/ Filter Class ///\/\/\/\/\/\///
class Filter{
	public:
		~Filter();
    	int fn,fc,fh,fw;
		size_t filterSize;
		cudnnDataType_t dType;
    	float *h_filter, *d_filter;	
		cudnnFilterDescriptor_t filterDesc;
    	Filter(ConvolutionLayer *);
		void doAction(cudnnTensorDescriptor_t, float *){};
};

										///\/\/\/\/\/\/ Filter Constructor ///\/\/\/\/\/\/
Filter::Filter(ConvolutionLayer* convolutionLayer) {
	fn = BATCH_SIZE;
	fc = convolutionLayer->getFilterDepth();
	fh = convolutionLayer->getFilterSize();
	fw = convolutionLayer->getFilterSize();	
	filterSize = fn*fc*fh*fw;
	dType = CUDNN_DATA_FLOAT;

	h_filter = (float *)malloc(sizeof(float)*filterSize);
    cudaMalloc((void **)&(d_filter),sizeof(float)*(filterSize));
    allocCheck(h_filter);
    allocCheck(d_filter);

    initializeMatrix(h_filter,filterSize);                
    cudaErrCheck(cudaMemcpy(d_filter,h_filter,(sizeof(float)*filterSize),cudaMemcpyHostToDevice)); //copy initial weights	
    cudnnErrorCheck(cudnnCreateFilterDescriptor(&filterDesc));
    cudnnErrorCheck(cudnnSetFilter4dDescriptor(filterDesc,dType,fn,fc,fh,fw)); 
}

										///\/\/\/\/\/\/ Destructor ///\/\/\/\/\/
Filter::~Filter(){
	free(h_filter);
	cudaFree(d_filter);
	cudnnErrorCheck(cudnnDestroyFilterDescriptor(filterDesc));
}

///\/\/\/\/\/\/\/\/\/ Convolution Layer Class ///\/\/\/\/\/\///
class ConvLayer: public Tensor{
	public:
		~ConvLayer();
		size_t workspaceSize;
		float * d_space;
		const void *alpha,*beta;
		cudnnConvolutionDescriptor_t convLayer;
		
		Filter *filter;
		cudnnConvolutionMode_t mode;
		cudnnConvolutionFwdAlgo_t convAlgorithm;	

		ConvLayer(LayerBase *);
		void doAction(cudnnTensorDescriptor_t,float *);
};

										///\/\/\/\/\/\/ Convolution Constructor ///\/\/\/\/\/\/
ConvLayer::ConvLayer(LayerBase *baseLayer) : Tensor(BATCH_SIZE,baseLayer->getInputDepth(),baseLayer->getInputHeight(),baseLayer->getInputWidth()){
	alpha = ((ConvolutionLayer *)baseLayer)->getAlpha();
	beta = ((ConvolutionLayer *)baseLayer)->getBeta();
	workspaceSize = 0;
	d_space = NULL;	
    mode = CUDNN_CONVOLUTION;
    convAlgorithm = CUDNN_CONVOLUTION_FWD_ALGO_GEMM;
	cudnnErrorCheck(cudnnCreateConvolutionDescriptor(&convLayer));

	filter = new Filter((ConvolutionLayer *)baseLayer);

    cudnnErrorCheck(cudnnSetConvolution2dDescriptor(convLayer,((ConvolutionLayer *)baseLayer)->getPadding(),((ConvolutionLayer *)baseLayer)->getPadding(),((ConvolutionLayer *)baseLayer)->getStride(),((ConvolutionLayer *)baseLayer)->getStride(),((ConvolutionLayer *)baseLayer)->getUpscaleX(),((ConvolutionLayer *)baseLayer)->getUpscaleY(),mode));
}

										///\/\/\/\/\/\/ Convolution Action ///\/\/\/\/\///
void ConvLayer::doAction(cudnnTensorDescriptor_t tensorDesc2, float *d_tensor2){
	cudnnErrorCheck(cudnnGetConvolutionForwardWorkspaceSize(cudnnHandle,tensorDesc,filter->filterDesc,convLayer,tensorDesc2,convAlgorithm,&workspaceSize)); 
    cudaMalloc((void**) &d_space, workspaceSize);
    allocCheck(d_space);
	cudnnConvolutionForward(cudnnHandle,alpha,tensorDesc, d_tensor, filter->filterDesc,filter->d_filter , convLayer, convAlgorithm,d_space,workspaceSize,beta,tensorDesc2,d_tensor2);
	cudaFree(d_space);
}

										///\/\/\/\/\/\/ Destructor ///\/\/\/\/\/\/												
ConvLayer::~ConvLayer(){
//	cudaFree(d_space);
	cudnnErrorCheck(cudnnDestroyConvolutionDescriptor(convLayer));
}

///\/\/\/\/\/\/\/\/\/\/ Pooling Layer Class ///\/\/\/\/\/\/\///
class PoolLayer: public Tensor{
	public:
		~PoolLayer();
		cudnnDataType_t dataType;
		cudnnPoolingDescriptor_t poolDesc;
		cudnnPoolingMode_t poolMode;
		int poolHeight,poolWidth,vertPad,horizPad,vertStride,horizStride;
		float a,b;
        const void *alpha,*beta;
		PoolLayer(LayerBase *);
		void doAction(cudnnTensorDescriptor_t,float *);
};

										///\/\/\/\/ Constructor ///\/\/\/\/
PoolLayer::PoolLayer(LayerBase *baseLayer) : Tensor(BATCH_SIZE,baseLayer->getInputDepth(),baseLayer->getInputHeight(),baseLayer->getInputWidth()){
	
	a=0.0; b=0.0;
	alpha = &a;
	beta = &b;													
	poolWidth = (baseLayer)->getInputWidth();
	poolHeight = (baseLayer)->getInputHeight();
	vertPad = ((PoolingLayer *)baseLayer)->getPadding();
	horizPad = ((PoolingLayer *)baseLayer)->getPadding();
	vertStride = ((PoolingLayer *)baseLayer)->getStride();
	horizStride = ((PoolingLayer *)baseLayer)->getStride();
	poolMode = CUDNN_POOLING_MAX;
	
	cudnnErrorCheck(cudnnCreatePoolingDescriptor(&poolDesc)); 
    cudnnErrorCheck(cudnnSetPooling2dDescriptor(poolDesc, poolMode, poolHeight, poolWidth, vertPad, horizPad, vertStride, horizStride));
	
}

										///\/\/\/\/\/\/ Pooling Action ///\/\/\/\/\/
void PoolLayer::doAction(cudnnTensorDescriptor_t tensorDesc2, float *d_tensor2){
	cudnnErrorCheck(cudnnPoolingForward(cudnnHandle,poolDesc,alpha,tensorDesc,d_tensor,beta,tensorDesc2, d_tensor2));
}

										///\/\/\/\/\/\/ Destructor ///\/\/\/\/\/
PoolLayer::~PoolLayer(){
	cudnnErrorCheck(cudnnDestroyPoolingDescriptor(poolDesc));	
}

///\/\/\/\/\/\/\/\/ Activation Layer Class ///\/\/\/\/\//\/\/\////
class ActivationLayer: public Tensor{
	public:
		~ActivationLayer();
		float a,b;
		const void *alpha, *beta;
		cudnnActivationMode_t activMode;
		ActivationLayer(LayerBase *);
		void doAction(cudnnTensorDescriptor_t, float*);	
};
											///\/\/\/\/ Constructor ///\/\/\/\/
ActivationLayer::ActivationLayer(LayerBase *baseLayer) : Tensor(BATCH_SIZE,baseLayer->getInputDepth(),baseLayer->getInputHeight(),baseLayer->getInputWidth()){
	activMode = CUDNN_ACTIVATION_RELU;
    a=0.0; b=0.0;
    alpha = &a;
    beta = &b;
}

											///\/\/\// Activation Action ///\/\///
void ActivationLayer::doAction(cudnnTensorDescriptor_t tensorDesc2, float *d_tensor2){
	cudnnErrorCheck(cudnnActivationForward(cudnnHandle,activMode,alpha,tensorDesc,d_tensor,beta,tensorDesc2,d_tensor2));
//	cudnnErrorCheck(cudnnActivationForward(cudnnHandle,activMode,alpha,tensorDesc2,d_tensor2,beta,tensorDesc,d_tensor));
}

											///\/\/\/\/ Destructor ///\/\/\/\/\/\/\/
ActivationLayer::~ActivationLayer(){

}

///\/\/\/\/\/\/\/\/ Fully Connected Filter ///\/\/\/\/\/\/\/\/////
class FCFilter{
    public:
        ~FCFilter();
        int fn,fc,fh,fw;
        size_t filterSize;
        cudnnDataType_t dType;
        float *h_filter, *d_filter; 
        cudnnFilterDescriptor_t filterDesc;
        FCFilter(InnerProductLayer *);
        void doAction(cudnnTensorDescriptor_t, float *){};
};

                                        	///\/\/\/\/\/ FCFilter Constructor ///\/\/\/\/\/\/
FCFilter::FCFilter(InnerProductLayer *fullyConnectedLayer){
    fn = BATCH_SIZE;
    fc = fullyConnectedLayer->getInputDepth();
    fh = fullyConnectedLayer->getInputHeight();
    fw = fullyConnectedLayer->getInputWidth();
    filterSize = fn*fc*fh*fw;
    dType = CUDNN_DATA_FLOAT;

    h_filter = (float *)malloc(sizeof(float)*filterSize);
    cudaMalloc((void **)&(d_filter),sizeof(float)*(filterSize));
    allocCheck(h_filter);
    allocCheck(d_filter);

    initializeMatrix(h_filter,filterSize);                
    cudaErrCheck(cudaMemcpy(d_filter,h_filter,(sizeof(float)*filterSize),cudaMemcpyHostToDevice));    
    cudnnErrorCheck(cudnnCreateFilterDescriptor(&filterDesc));
    cudnnErrorCheck(cudnnSetFilter4dDescriptor(filterDesc,dType,fn,fc,fh,fw)); 
}

											///\/\/\/\/\/ Destructor ///\/\/\/\/\////
FCFilter::~FCFilter(){
    free(h_filter);
    cudaFree(d_filter);
	cudnnErrorCheck(cudnnDestroyFilterDescriptor(filterDesc));
}

///\/\/\/\/\/\/\/\/ Fully Connected Layer ///\/\/\/\/\/\/\/\////
class FCLayer: public Tensor{
    public:
        ~FCLayer();
        size_t workspaceSize;
        float * d_space;
        const void *alpha,*beta;
        cudnnConvolutionDescriptor_t convLayer;     
        FCFilter *filter;
        cudnnConvolutionMode_t mode;
        cudnnConvolutionFwdAlgo_t convAlgorithm;
        FCLayer(LayerBase *);
        void doAction(cudnnTensorDescriptor_t,float *);
};

                                        	///\/\/\/\/\/\/ FC Constructor ///\/\/\/\/\/\/
FCLayer::FCLayer(LayerBase *baseLayer) : Tensor(BATCH_SIZE,baseLayer->getInputDepth(),baseLayer->getInputHeight(),baseLayer->getInputWidth()){
    alpha = ((InnerProductLayer *)baseLayer)->getAlpha();
    beta = ((InnerProductLayer *)baseLayer)->getBeta();
    workspaceSize = 0;
    d_space = NULL;
    mode = CUDNN_CONVOLUTION;
    convAlgorithm = CUDNN_CONVOLUTION_FWD_ALGO_GEMM;
    cudnnErrorCheck(cudnnCreateConvolutionDescriptor(&convLayer));
    filter = new FCFilter((InnerProductLayer *)baseLayer); 					
	cudnnErrorCheck(cudnnSetConvolution2dDescriptor(convLayer,0,0,1,1,1,1,mode));
}

                                        	///\/\/\/\/\/\/ FC Action ///\/\/\/\/\///
void FCLayer::doAction(cudnnTensorDescriptor_t tensorDesc2, float *d_tensor2){
   cudnnErrorCheck(cudnnGetConvolutionForwardWorkspaceSize(cudnnHandle,tensorDesc,filter->filterDesc,convLayer,tensorDesc2,convAlgorithm,&workspaceSize)); 
   cudaMalloc((void**) &d_space, workspaceSize);
   allocCheck(d_space);
   cudnnConvolutionForward(cudnnHandle,alpha,tensorDesc, d_tensor, filter->filterDesc,filter->d_filter , convLayer, convAlgorithm,d_space,workspaceSize,beta,tensorDesc2,d_tensor2);
	cudaFree(d_space);
}

											///\/\/\//\/\/\/ Destructor ///\/\/\/\/\/\////
FCLayer::~FCLayer(){
//    cudaFree(d_space);
	cudnnErrorCheck(cudnnDestroyConvolutionDescriptor(convLayer));
}
//////////////////////////////////////////////   MAIN PROGRAM \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
int main(){
	//define and instantiate number of layers recieved

	cudnnErrorCheck(cudnnCreate(&cudnnHandle));
	int i;
	UserInput in(false);
	if ( !in.isValidInput() ) {
		std::cout << "Exiting program.." << std::endl;
		return EXIT_FAILURE;
	}	
	GenerateLayers gen(in);
	std::vector <LayerBase *> layers;
	layers = gen.getLayerList();		//layers = alexnet now
	displayPrototxtOutput(in, layers, true);
	LayerType layerType; 

	Tensor * layerArray[layers.size()+1];			//to allow for output tensor
	#pragma omp parallel for						//////////layer and tensor setup, build network 
		for (i=0;i<layers.size();i++){				
			//generate array of cudnn layers
			layerType = (layers.at(i))->getLayerType();
			switch (layerType){
				case INPUT:
						layerArray[i] = new Tensor(BATCH_SIZE,layers.front()->getInputDepth(),layers.front()->getInputHeight(),layers.front()->getInputWidth());
						puts("input skipped");
						break;
				case CONVOLUTION:
						layerArray[i] = new ConvLayer(layers.at(i));
						puts("conv created ");
						break;
				case POOLING:
						
						layerArray[i] = new PoolLayer(layers.at(i));
						puts("pool created ");
						break;
				case RELU:
						layerArray[i] = new ActivationLayer(layers.at(i));
						puts("relu created ");
						break;
				case INNER_PRODUCT:
						layerArray[i] = new FCLayer(layers.at(i));
						puts("fc created ");
						break;
				default:
						puts("error");
						break;
			}

		}
		puts("before layerArray");
		layerArray[i] = new Tensor(BATCH_SIZE,layers.back()->getOutputDepth(),layers.back()->getOutputHeight(),layers.back()->getOutputWidth());
		puts("After layerArray, before ImageBatch vec init");
	//std::vector <ImageBatch *> batchList = buildBatchList(in,BATCH_SIZE);
		puts("After batc vec init");
	int x = 0,y=0;
	for(y=0;y<10;y++){
	std::vector <ImageBatch *> batchList = buildBatchList(in, BATCH_SIZE);
	
	for(x=0;x<batchList.size();x++){		
		printf("Batch number %d \n",x);
		ImageBatch *newBatch = batchList.at(x);
		for (i=0;i<layers.size();i++){
            //generate array of cudnn layers
            layerType = (layers.at(i))->getLayerType();
            switch (layerType){
                case INPUT: 
						//set convolution input descriptors as the input images		
						cudaErrCheck(cudaMemcpy(layerArray[i+1]->d_tensor,newBatch->get(),(sizeof(float)*newBatch->length()),cudaMemcpyHostToDevice));	
                        //create convolution layer for input image
  
                        puts("input finished");
                        break;
                case CONVOLUTION:
//						puts("b4");
                        layerArray[i]->doAction(layerArray[i+1]->tensorDesc,layerArray[i+1]->d_tensor);
                        puts("conv finished ");
                        break;
                case POOLING:
//						puts("b4");
						layerArray[i]->doAction(layerArray[i+1]->tensorDesc,layerArray[i+1]->d_tensor);                        
                        puts("pool finished ");
                        break;
                case RELU:
//						puts("b4");
                        layerArray[i]->doAction(layerArray[i+1]->tensorDesc,layerArray[i+1]->d_tensor);
                        puts("relu finished ");
                        break;
                case INNER_PRODUCT:
//						puts("b4");
                        layerArray[i]->doAction(layerArray[i+1]->tensorDesc,layerArray[i+1]->d_tensor);
                        puts("fc finished ");
                        break;
                default:
                        puts("error");
                        break;
			}
         }
		newBatch->clean();
	}
	
		destroyBatchList(batchList);
	}
	//destroyBatchList(batchList);
	layers.clear();
	
	return 0;
}
