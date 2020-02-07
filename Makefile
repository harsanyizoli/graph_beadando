output := beadando

all:
	gcc -Iinclude src/*  -lSOIL -lGL -lGLU -lglut -lm -o $(output)