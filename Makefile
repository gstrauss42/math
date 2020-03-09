all:
	gcc -c calc.c
	ar rc calc.a calc.o
	rm calc.o

clean:
	rm calc.a