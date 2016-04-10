all: game



game: game.cpp
	g++  -lm -o game game.cpp -lGL -lGLU -lGLEW -lglut 
clean:
	rm game

