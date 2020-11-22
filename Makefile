all: game

game: main.c game.o
	gcc -o game main.c game.o -no-pie

game.o: game.asm
	nasm -f elf64 -F dwarf -g game.asm

clean: all
	rm *.o game
