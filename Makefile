CXX = g++
CXX_FLAGS = -std=c++20 -fno-rtti

INCLUDES = -I$(HALIDE_ROOT)/include -I$(HALIDE_ROOT)/tools
LIBS = -L$(HALIDE_ROOT)/lib 
LIB_FLAGS = -lHalide -lpthread -ldl -lz -ltinfo
IMAGE_IO_FLAGS = -ljpeg `libpng-config --cflags --ldflags`

ifndef PATH_IN1
	PATH_IN1=inputs/mandrill.png
endif

ifndef PATH_IN2
	PATH_IN2=inputs/peppers2.png
endif

ifndef ALPHA
	ALPHA=0.3
endif

ifndef BETA
	BETA=0.7
endif

ifndef GAMMA
	GAMMA=0
endif

ifndef PATH_OUT
	PATH_OUT=outputs/result.png
endif

all: outputs

clean:
	@rm -rf bin outputs

bin/main: src/main.cpp
	@mkdir -p $(@D)
	@$(CXX) $^ $(CXX_FLAGS) $(INCLUDES) $(LIBS) $(LIB_FLAGS) $(IMAGE_IO_FLAGS) -o $@

outputs: bin/main
	@mkdir -p $@
	@$^ $(PATH_IN1) $(ALPHA) $(PATH_IN2) $(BETA) $(GAMMA) $(PATH_OUT)

.PHONY: all clean