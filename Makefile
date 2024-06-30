build:
	gcc -Wall ./src/*.c -lm -o test
run:
	./test
clean:
	rm ./test
