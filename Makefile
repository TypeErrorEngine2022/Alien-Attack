all:
	g++ -Iinclude -Llib src/*.cpp src/Entity/*.cpp src/Gamestate/*.cpp src/Levels/*.cpp src/Utils/*.cpp -o main -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lz