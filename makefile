SRC=.
CC=g++

all: $(SRC)/*.cpp
	$(CC) $(SRC)/*.cpp -lGL -lglfw3 -lX11 -lGLEW

clean:
	rm -rf a.out