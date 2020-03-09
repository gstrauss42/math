all:
	gcc -c calc.c
	ar rc calc.a calc.o
	rm calc.o

test: all
	gcc calc.a main.c

clean:
	rm calc.a