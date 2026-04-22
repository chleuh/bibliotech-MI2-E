all: exec

exec: main.o user.o livre.o emprunt.o affichage.o
	gcc main.o user.o livre.o emprunt.o affichage.o -o exec

main.o: main.c user.h livre.h emprunt.h affichage.h
	gcc -c main.c

user.o: user.c user.h
	gcc -c user.c

livre.o: livre.c livre.h
	gcc -c livre.c

emprunt.o: emprunt.c emprunt.h
	gcc -c emprunt.c

affichage.o: affichage.c affichage.h user.h livre.h emprunt.h
	gcc -c affichage.c

clean:
	rm -f *.o exec