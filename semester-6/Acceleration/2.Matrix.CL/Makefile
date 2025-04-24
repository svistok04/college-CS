CXX = g++
CXXFLAGS = -Wall -std=c++17
LDFLAGS = -lOpenCL

TARGET = VectorAdd
SRC = VectorAdd.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)
