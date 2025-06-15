CC=g++
libs= -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm
deps= glad.c

all: main.cpp
	$(CC) main.cpp $(deps) $(libs)

clean:
	rm a.out