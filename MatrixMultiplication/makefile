all : matrix-mult

clean :
	-rm matrix-mult 2> /dev/null

matrix-mult : matrix-mult.c
	gcc matrix-mult.c -pthread -fno-stack-protector -lm -o matrix-mult
