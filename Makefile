main:	main.o	leitura.o	Grafo.o
		gcc	 main.o	leitura.o	Grafo.o	-o main.exe
		rm *.o

main.o:
		gcc -c main.c

util.o:
		gcc -c	leitura.c

tadGrafo.o:
		gcc -c	Grafo.c