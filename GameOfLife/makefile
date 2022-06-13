CC = gcc
life: main.o game.o file.o
	$(CC) -o life -Wall -ansi -pedantic -Werror main.o game.o file.o 

main.o: main.c main.h game.c game.h
	$(CC) -c -Wall -ansi -pedantic -Werror main.c -o main.o

game.o: game.c game.h file.c file.h
	$(CC) -c -Wall -ansi -pedantic -Werror game.c -o game.o

file.o: file.c file.h
	$(CC) -c -Wall -ansi -pedantic -Werror file.c -o file.o
