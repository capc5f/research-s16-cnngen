NVCC = nvcc
NV_FLAGS = --compiler-options -fopenmp
LINK = -lcublas -lcudnn
CC = g++
LAYER_DIR = ../layers/
LAYER_HELP_DIR = ../layers/layer_helpers/

all:	main

clean:
	rm nn_setup

main: LayerBase ConvolutionLayer InnerProductLayer InputLayer PoolingLayer ReLULayer Param
	$(NVCC) $(LINK) -o nn_setup NNsetup.cu LayerBase.o ConvolutionLayer.o InnerProductLayer.o InputLayer.o PoolingLayer.o ReLULayer.o Param.o

LayerBase:
	$(CC) -c $(LAYER_DIR)LayerBase.cpp

ConvolutionLayer:
	$(CC) -c $(LAYER_DIR)ConvolutionLayer.cpp

InnerProductLayer:
	$(CC) -c $(LAYER_DIR)InnerProductLayer.cpp

InputLayer:
	$(CC) -c $(LAYER_DIR)InputLayer.cpp

PoolingLayer:
	$(CC) -c $(LAYER_DIR)PoolingLayer.cpp

ReLULayer:
	$(CC) -c $(LAYER_DIR)ReLULayer.cpp

Param:
	$(CC) -c $(LAYER_HELPER_DIR)Param.cpp