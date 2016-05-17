NVCC = nvcc
NV_FLAGS = --compiler-options -fopenmp
LINK = -lcublas -lcudnn
CC = g++
C_FLAGS = -std=c++11
LAYER_DIR = ../layers/
LAYER_HELPER_DIR = ../layers/layer_helpers/
UTILS = ../utils/
ECE_PROJ_DIR = ../ece8270project/
DEBUG = -D DEBUG

all:	main

clean:
	rm nn_setup

debug: LayerBase ConvolutionLayer InnerProductLayer InputLayer PoolingLayer ReLULayer Param Utilities UserInputDebug GenerateLayers LRNLayer SoftmaxLayer Image ImageBatch
	$(NVCC) $(LINK) $(C_FLAGS) $(DEBUG) -o nn_setup NNsetup.cu LayerBase.o ConvolutionLayer.o InnerProductLayer.o InputLayer.o PoolingLayer.o ReLULayer.o Param.o Utilities.o UserInput.o GenerateLayers.o LRNLayer.o SoftmaxLayer.o Image.o ImageBatch.o

main: LayerBase ConvolutionLayer InnerProductLayer InputLayer PoolingLayer ReLULayer Param Utilities UserInput GenerateLayers LRNLayer SoftmaxLayer Image ImageBatch
	$(NVCC) $(LINK) $(C_FLAGS) -o nn_setup NNsetup.cu LayerBase.o ConvolutionLayer.o InnerProductLayer.o InputLayer.o PoolingLayer.o ReLULayer.o Param.o Utilities.o UserInput.o GenerateLayers.o LRNLayer.o SoftmaxLayer.o Image.o ImageBatch.o

LayerBase:
	$(CC) $(C_FLAGS) -c $(LAYER_DIR)LayerBase.cpp

ConvolutionLayer:
	$(CC) $(C_FLAGS) -c $(LAYER_DIR)ConvolutionLayer.cpp

InnerProductLayer:
	$(CC) $(C_FLAGS) -c $(LAYER_DIR)InnerProductLayer.cpp

InputLayer:
	$(CC) $(C_FLAGS) -c $(LAYER_DIR)InputLayer.cpp

PoolingLayer:
	$(CC) $(C_FLAGS) -c $(LAYER_DIR)PoolingLayer.cpp

ReLULayer:
	$(CC) $(C_FLAGS) -c $(LAYER_DIR)ReLULayer.cpp

Param:
	$(CC) $(C_FLAGS) -c $(LAYER_HELPER_DIR)Param.cpp

Utilities:
	$(CC) $(C_FLAGS) -c $(UTILS)Utilities.cpp

UserInputDebug:
	$(CC) $(C_FLAGS) $(DEBUG) -c $(UTILS)UserInput.cpp

UserInput:
	$(CC) $(C_FLAGS) -c $(UTILS)UserInput.cpp

GenerateLayers:
	$(CC) $(C_FLAGS) -c $(UTILS)GenerateLayers.cpp

LRNLayer:
	$(CC) $(C_FLAGS) -c $(LAYER_DIR)LRNLayer.cpp

SoftmaxLayer:
	$(CC) $(C_FLAGS) -c $(LAYER_DIR)SoftmaxLayer.cpp

Image:
	$(CC) $(C_FLAGS) -c $(ECE_PROJ_DIR)Image.cpp

ImageBatch:
	$(CC) $(C_FLAGS) -c $(ECE_PROJ_DIR)ImageBatch.cpp