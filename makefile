# Define the compiler
CXX = g++

# Compiler flags
# -g adds debugging information to the executable file
# -Wall turns on most, but not all, compiler warnings
CXXFLAGS = -g -Wall -std=c++11

# Define the target executable
TARGET = testLL

# Define source files
SOURCES = testLL.cpp

# The build target executable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

# Phony target for cleaning up compiled files
.PHONY: clean

clean:
	rm -f $(TARGET) $(TARGET).o
