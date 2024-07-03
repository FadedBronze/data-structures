OUT=./dist
CC=gcc
CFLAGS=-Wall -g

build:
	mkdir -p $(OUT)
	$(CC) -c $(CFLAGS) ./src/*.c -lm -o $(OUT)/data_structures.o
test:
	make
	$(CC) -c $(CFLAGS) ./main.c -o $(OUT)/main.o
	$(CC) $(CFLAGS) $(OUT)/main.o $(OUT)/data_structures.o -lm -o $(OUT)/test
run-test:
	$(OUT)/test
clean:
	rm $(OUT) -rf
