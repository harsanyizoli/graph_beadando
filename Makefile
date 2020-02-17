CXX := g++
TARGET := beadando
LDFLAGS := -lstdc++fs -lSOIL -lGL -lGLU -lglut -lm
INCLUDE := -I$(shell pwd)/include/
CXXFLAGS := -std=c++17
SRC	:= src/*.cpp src/Game/*.cpp src/Graphics/*.cpp src/Graphics/*.c

all:
	$(CXX) $(SRC) $(LDFLAGS) $(INCLUDE) -o $(TARGET) $(CXXFLAGS)