PYTHON := python3
PYBIND11_INCLUDES := $(shell $(PYTHON) -m pybind11 --includes)
EXT_SUFFIX := $(shell $(PYTHON)-config --extension-suffix)
CXX := c++
CXXFLAGS := -O3 -Wall -shared -std=c++17 -fPIC

TARGET := example$(EXT_SUFFIX)
SRC := example.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(PYBIND11_INCLUDES) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

