# Variables
CXX = g++
CXXFLAGS = -Wall -std=c++17
MYPROGRAM = myprogram

# Source files
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

# Default rule to build the myprogram executable
all: $(MYPROGRAM)

# Rule to build only the myprogram executable
myprogram: $(MYPROGRAM)

# Link object files to create the myprogram executable
$(MYPROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS)

cleanall: clean
	rm -f $(MYPROGRAM)

.PHONY: all clean myprogram