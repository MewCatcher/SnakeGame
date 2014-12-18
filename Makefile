CC = g++
CFLAGS = -Wall -O2 -I/usr/include/freetype2 -I/usr/include/freetype -c

default: SnakeGame

SnakeGame: main.o gameworld.o freetype.o snake.o snakeai.o
	rm -rf build
	mkdir build
	cp src/comic.ttf build/comic.ttf
	g++ src/main.o src/gameworld.o src/freetype.o src/snake.o src/snakeai.o -o build/SnakeGame -lfreetype -lGL -lGLU -lglut

snake.o: src/snake.cpp src/snake.h src/gameworld.h
	$(CC) $(CFLAGS) -o src/snake.o src/snake.cpp

snakeai.o: src/snakeai.cpp src/snakeai.h src/gameworld.h src/snake.h
	$(CC) $(CFLAGS) -o src/snakeai.o src/snakeai.cpp

freetype.o: src/freetype.cpp src/freetype.h
	$(CC) $(CFLAGS) -o src/freetype.o src/freetype.cpp

gameworld.o: src/gameworld.cpp src/gameworld.h src/main.h src/freetype.h src/snakeai.h
	$(CC) $(CFLAGS) -o src/gameworld.o src/gameworld.cpp

main.o: src/main.cpp src/main.h src/gameworld.h src/snake.h src/snakeai.h
	$(CC) $(CFLAGS) -o src/main.o src/main.cpp

clean:
	rm -f src/*.o
	rm -f build/SnakeGame
	rm -f build/comic.ttf
	rmdir build

