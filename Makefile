all:
	make -C libft
	gcc -c calc.c
	ar rc calc.a calc.o
	rm calc.o
	make -C libft clean

test: all
	gcc calc.a libft/libft.a main.c
	rm calc.a
	make -C libft clean

clean:
	rm calc.a

tclean:
	rm a.out