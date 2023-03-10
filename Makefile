
all: build
build: 
	gcc tema1.c -o tema1 -lm

clean:
	-rm -f tema1

