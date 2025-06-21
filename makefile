CC=g++
libs= -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm
deps= glad.c

all: *.cpp *.hpp
	$(CC) *.cpp $(deps) $(libs)

clean:
	rm a.out