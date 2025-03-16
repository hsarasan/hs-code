# Compiler and flags
CXX = g++
CXXFLAGS = -O2 -march=native -Wall -pthread
LDFLAGS = -lnuma

# Source and output
SRC = numa_benchmark.cpp
OUT = numa_benchmark

# Default target: Compile
all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

# Run the program
run: $(OUT)
	sudo ./$(OUT)

# Clean build files
clean:
	rm -f $(OUT)

# Rebuild the project
rebuild: clean all

