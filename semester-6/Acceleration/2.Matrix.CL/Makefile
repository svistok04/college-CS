CC = gcc
CFLAGS = -Wall -std=c11 -DCL_TARGET_OPENCL_VERSION=300 -MMD -MP

LDFLAGS = -lOpenCL -lrt -lm

BUILD_DIR = build
TARGET = matrix_mul
SRCS = matrix_mul.c matrix_mul_naive_NN.c opencl_helper.c
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
