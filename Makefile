CC=g++

rope: rope.cpp
	$(CC) -g3 -o $@ $<

all: rope

run: rope
	./rope