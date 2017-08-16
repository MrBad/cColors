#DFLAGS=
INCLUDE=.
LIBS=-lSDL2 -lGL -lGLEW
CC=gcc
OFLAGS=-c
CFLAGS=-g -Wall -Wextra -std=c99 -pedantic-errors -I$(INCLUDE)

TARGET=colors
OBJECTS=main.o window.o error.o sprite.o vertex.o gl_program.o file_buf.o upng/upng.o texture.o

all: $(OBJECTS) Makefile
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

%o: %.c Makefile *.h
	$(CC) $(CFLAGS) $(OFLAGS) -o $@ $<
clean:
	rm $(OBJECTS) $(TARGET)
