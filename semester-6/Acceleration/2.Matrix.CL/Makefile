CXX = g++
CXXFLAGS = -Wall -std=c++17 -DCL_TARGET_OPENCL_VERSION=300 -MMD -MP

LDFLAGS = -lOpenCL

BUILD_DIR = build
TARGET = matrix_mul
SRCS = matrix_mul.cpp matrix_mul_naive_NN.cpp opencl_helper.cpp
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.o))
DEPS = $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
