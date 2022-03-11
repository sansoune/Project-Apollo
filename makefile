CFiles = ./src/includes/*.c

build: clear
	mkdir dist
	gcc -o ./dist/app.o ./src/main.c ${CFiles}

clear:
	rm -r dist