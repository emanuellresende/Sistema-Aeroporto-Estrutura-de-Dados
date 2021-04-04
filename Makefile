main:	main.o	ferramentas.o	Grafo.o
		gcc	 main.o	ferramentas.o	Grafo.o	-o main.exe -lm
		rm *.o

main.o:
		gcc -c main.c

ferramentas.o:
		gcc -c	ferramentas.c

Grafo.o:
		gcc -c	Grafo.c