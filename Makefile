# files to compile
OBJS = main.o player.o screen.o timer.o object.o items.o math.o

# compiler
CC = g++

# additional paths
INCLUDE = -IC:\Code\SDL\x86_64-w64-mingw32\include\SDL2 -ID:\Code\Game-Test\include
LIBRARIES = -LC:\Code\SDL\x86_64-w64-mingw32\lib

# flags
COMPILER = -w -Wl,-subsystem,windows -Wall -Wextra
LINKER = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

# actual commands
all: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE) $(LIBRARIES) $(COMPILER) $(LINKER) -o program

main.o: main.cpp
	$(CC) $(INCLUDE) $(LIBRARIES) $(COMPILER) $(LINKER) -c main.cpp
player.o: player.cpp
	$(CC) $(INCLUDE) $(LIBRARIES) $(COMPILER) $(LINKER) -c player.cpp
timer.o: timer.cpp
	$(CC) $(INCLUDE) $(LIBRARIES) $(COMPILER) $(LINKER) -c timer.cpp
screen.o: screen.cpp
	$(CC) $(INCLUDE) $(LIBRARIES) $(COMPILER) $(LINKER) -c screen.cpp
object.o: object.cpp
	$(CC) $(INCLUDE) $(LIBRARIES) $(COMPILER) $(LINKER) -c object.cpp
items.o: items.cpp
	$(CC) $(INCLUDE) $(LIBRARIES) $(COMPILER) $(LINKER) -c items.cpp
math.o: math.cpp
	$(CC) $(INCLUDE) $(LIBRARIES) $(COMPILER) $(LINKER) -c math.cpp

clean:
	rm $(OBJS)