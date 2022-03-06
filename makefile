

build: clear
	mkdir dist
	gcc -o ./dist/app.o -I ./src/includes ./src/main.c 

clear:
	rm -r dist