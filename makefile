CP=python3
CC=gcc
CB=bash
data:
	$(CB) menu.sh
rand:
	$(CC) -Wall *.c -lm -o main.out
	./main.out --help
clean:
	@clear
	@rm *.out