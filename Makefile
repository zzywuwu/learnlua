
all:
	rm -rf test
	gcc -o test test.c -L /usr/lib -llua
	./test

