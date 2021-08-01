#OBJS specifies which files to compile as part of the project
OBJS =LTexture.cpp Tile.cpp grid.cpp app.cpp pacman.cpp main.cpp level.cpp play.cpp ghost.cpp sounds.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w #-g -fsanitize=address -fsanitize=undefined -Wshadow

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_gfx -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main.o

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)