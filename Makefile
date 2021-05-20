all: terminal

biblio.o: biblio.c biblio.h
	gcc -c biblio.c -o biblio.o

biblio: biblio.o
	gcc biblio.o -o biblio #./biblio ne peut pas être executable car biblio.c n'as pas de main.

terminal.o: terminal.c terminal.h
		gcc -c terminal.c -o terminal.o

fsprint.o: fsprint.c fsprint.h
					gcc -c fsprint.c -o fsprint.o

terminal: terminal.o biblio.o fsprint.o
		gcc terminal.o biblio.o fsprint.o -o terminal

clean:
	rm -f *.o biblio terminal
