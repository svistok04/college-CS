CXX = g++
CXXFLAGS = -Wall -std=c++17 -D CL_TARGET_OPENCL_VERSION=300
LDFLAGS = -lOpenCL

TARGET = matrix_mul
SRC = matrix_mul.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)
