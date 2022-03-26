CFiles = ./src/includes/c/*.c

build: clear
	mkdir dist
	gcc -o ./dist/Apollo ./src/main.c ${CFiles}

test:

	gcc -o ./dist/test ./src/Test.c ./src/includes/c/readfile.c
	./dist/test

clear:
	rm -r dist