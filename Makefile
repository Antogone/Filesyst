all: biblio terminal

biblio.o: biblio.c biblio.h
	gcc -c biblio.c -o biblio.o

biblio: biblio.o
	gcc biblio.o -o biblio

terminal.o: terminal.c terminal.h
		gcc -c terminal.c -o terminal.o

terminal: terminal.o
		gcc terminal.o -o terminal

clean:
	rm -f *.o biblio terminal
