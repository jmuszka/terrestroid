SRC=.
CC=g++

all: $(SRC)/*.cpp
	$(CC) $(SRC)/*.cpp -lGL -lglut -lglfw3 -lGLEW

clean:
	rm -rf a.out