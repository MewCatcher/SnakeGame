default: SnakeGame

SnakeGame: src/main.o src/gameworld.o src/freetype.o src/snake.o src/snakeai.o
	mkdir build
	cp src/comic.ttf build/comic.ttf
	g++ src/main.o src/gameworld.o src/freetype.o src/snake.o src/snakeai.o \
		-o build/SnakeGame -lfreetype -lGL -lGLU -lglut

snake.o: snake.cpp snake.h gameworld.h
	g++ -c src/snake.cpp -o src/snake.o

snakeai.o: snakeai.cpp snakeai.h gameworld.h snake.h
	g++ -c src/snakeai.cpp -o src/snakeai.o

freetype.o: freetype.cpp freetype.h
	g++ -c src/freetype.cpp -o src/freetype.o

gameworld.o: gameworld.cpp gameworld.h main.h freetype.h snakeai.h
	g++ -c src/gameworld.cpp -o src/gameworld.o

main.o: main.cpp main.h gameworld.h snake.h snakeai.h
	g++ -c src/main.cpp -o src/main.o

clean:
	rm -f src/*.o
	rm -f build/SnakeGame
	rm -f build/comic.ttf
	rmdir build

