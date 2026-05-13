all: exec

exec: main.o user.o livre.o emprunt.o affichage.o rendre.o
	gcc main.o user.o livre.o emprunt.o affichage.o rendre.o -o exec

main.o: main.c
	gcc -c main.c

user.o: user.c
	gcc -c user.c

livre.o: livre.c
	gcc -c livre.c

emprunt.o: emprunt.c
	gcc -c emprunt.c

affichage.o: affichage.c
	gcc -c affichage.c

rendre.o: rendre.c
	gcc -c rendre.c

clean:
	rm -f *.o exec