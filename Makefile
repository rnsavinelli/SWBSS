# Makefile for SWBSS to automate its compilation
# Created by Roberto Nicolás Savinelli

CC= gcc
LIBS= -L ./lib/ar/ -lal_handler -lallegro -lallegro_image -lallegro_primitives -lallegro_ttf -lallegro_dialog -lallegro_font -lallegro_audio -lallegro_acodec
CFLAGS=-Wall -g
INCLUDES=-I ./inc -I ./lib/inc/
SOURCES=./src/*.c ./src/menues/*.c ./src/drawing/*.c ./src/logic/*.c
EXE=exe

compile:
	$(CC) $(SOURCES) $(INCLUDES) -o $(EXE) $(CFLAGS) $(LIBS)

execute:
	./$(EXE)

clean:
	rm ./$(EXE)
