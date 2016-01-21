CC=gcc

all: romsplit
romsplit: romsplit.c
	$(CC) romsplit.c -std=c89 -pedantic -o romsplit

clean:
	rm -f romsplit
