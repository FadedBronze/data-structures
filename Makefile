OUT=./dist
CC=gcc
CFLAGS=-Wall

build:
	mkdir -p $(OUT)
	$(CC) -c $(CFLAGS) -g ./src/*.c -lm -o $(OUT)/data_structures.o
test:
	make
	$(CC) -c $(CFLAGS) -g ./main.c -o $(OUT)/main.o
	$(CC) $(OUT)/main.o $(OUT)/data_structures.o -lm -o $(OUT)/test
run-test:
	$(OUT)/test
clean:
	rm $(OUT) -rf
