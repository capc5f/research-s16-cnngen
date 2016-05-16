NVCC = nvcc
NV_FLAGS = --compiler-options -fopenmp
LINK = -lcublas -lcudnn
CC = g++
C_FLAGS = -std=c++11
LAYER_DIR = ../layers/
LAYER_HELPER_DIR = ../layers/layer_helpers/
UTILS = ../utils/

all:	main

clean:
	rm nn_setup

main: LayerBase ConvolutionLayer InnerProductLayer InputLayer PoolingLayer ReLULayer Param Utilities UserInput GenerateLayers
	$(NVCC) $(LINK) $(C_FLAGS) -o nn_setup NNsetup.cu LayerBase.o ConvolutionLayer.o InnerProductLayer.o InputLayer.o PoolingLayer.o ReLULayer.o Param.o Utilities.o UserInput.o GenerateLayers.o

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

UserInput:
	$(CC) $(C_FLAGS) -c $(UTILS)UserInput.cpp

GenerateLayers:
	$(CC) $(C_FLAGS) -c $(UTILS)GenerateLayers.cpp

