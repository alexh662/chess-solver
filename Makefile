# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

# Source files
SRC = main.cpp board.cpp evaluate.cpp # minimax.cpp

# Header files (optional, for dependency tracking)
HEADERS = board.h evaluate.h # minimax.h

# Executable name
TARGET = main

# Build target
all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean build files
clean:
	rm -f $(TARGET) *.o

# Run
run: $(TARGET)
	./$(TARGET)
