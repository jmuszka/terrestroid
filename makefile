SRC=.
CC=g++

all: $(SRC)/*.cpp
	$(CC) $(SRC)/*.cpp -lGL -lglfw3 -lGLEW -lm

clean:
	rm -rf a.out