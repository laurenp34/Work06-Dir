all: main.o
	gcc -o rand main.o

dwstring.o: main.c
	gcc -c main.c

run:
	./rand

clean:
	rm *.o
	rm *~
