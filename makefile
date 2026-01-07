main: main.c
	gcc -O3 -march=native -Wall -Wextra main.c -lm -o main

run:
	make
	@echo " "
	./main

	
