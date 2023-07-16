# files to compile
OBJS = main.o math.o screen.o input.o collision.o object.o player.o items.o timer.o

# compiler
CC = g++

# additional paths
INCLUDE = -IC:\Code\SDL\x86_64-w64-mingw32\include\SDL2 -ID:/Code/Game-Test/include
LIBRARIES = -LC:\Code\SDL\x86_64-w64-mingw32\lib

# flags
COMPILER = -Wall -Wextra -w -Wl,-subsystem,windows
LINKER = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

# actual commands
all: program

program: ${OBJS}
	$(CC) $(OBJS) $(INCLUDE) $(LIBRARIES) $(COMPILER) $(LINKER) -o program

main.o: main.cpp
	$(CC) $(INCLUDE) $(LIBRARIES) $(COMPILER) $(LINKER) -c main.cpp -o main.o
math.o: math.cpp
	$(CC) $(INCLUDE) $(LIBRARIES) $(COMPILER) $(LINKER) -c math.cpp -o math.o
screen.o: screen.cpp
	$(CC) $(INCLUDE) $(LIBRARIES) $(COMPILER) $(LINKER) -c screen.cpp -o screen.o
input.o: input.cpp
	$(CC) $(INCLUDE) $(LIBRARIES) $(COMPILER) $(LINKER) -c input.cpp -o input.o
collision.o: collision.cpp
	$(CC) $(INCLUDE) $(LIBRARIES) $(COMPILER) $(LINKER) -c collision.cpp -o collision.o
object.o: object.cpp
	$(CC) $(INCLUDE) $(LIBRARIES) $(COMPILER) $(LINKER) -c object.cpp -o object.o
player.o: player.cpp
	$(CC) $(INCLUDE) $(LIBRARIES) $(COMPILER) $(LINKER) -c player.cpp -o player.o
items.o: items.cpp
	$(CC) $(INCLUDE) $(LIBRARIES) $(COMPILER) $(LINKER) -c items.cpp -o items.o
timer.o: timer.cpp
	$(CC) $(INCLUDE) $(LIBRARIES) $(COMPILER) $(LINKER) -c timer.cpp -o timer.o

clean:
	rm $(OBJS)