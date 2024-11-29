CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Files
SRCS = main.cpp parser.cpp
OBJS = main.o parser.o
TARGET = turing

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp parser.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

parser.o: parser.cpp parser.hpp
	$(CXX) $(CXXFLAGS) -c parser.cpp

clean:
	rm -f $(OBJS) $(TARGET)