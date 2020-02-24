CXX := gcc
TARGET := beadando
LDFLAGS :=-lSOIL -lGL -lGLU -lglut -lm
INCLUDE := -I$(shell pwd)/include/
CXXFLAGS :=
SRC	:= src/*.c

all:
	$(CXX) $(SRC) $(LDFLAGS) $(INCLUDE) -o $(TARGET) $(CXXFLAGS)