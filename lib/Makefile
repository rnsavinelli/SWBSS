# Makefile for libal_handler to automate its compilation
# Created by Roberto Nicolás Savinelli

SOURCES = $(wildcard ./src/*.c)
OBJS = $(subst /src/,/obj/,$(SOURCES:.c=.o))

./ar/libal_handler.a: $(OBJS)
	ar rcs $@ $^

./obj/%.o: ./src/%.c
	gcc -c $< -o $@ -I./inc/

clean:
	rm ./obj/*.o
