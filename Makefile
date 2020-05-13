CXX := gcc
TARGET := beadando
LDFLAGS := -lGL -lGLU -lglut -lm -lSOIL
INCLUDE := -I$(shell pwd)/include/
CXXFLAGS :=
SRC	:= src/*.c

all:
	$(CXX) $(SRC) $(LDFLAGS) $(INCLUDE) -o $(TARGET) $(CXXFLAGS)