all: main

main: main.c
	${CC} `pkg-config --cflags glib-2.0` $^ `pkg-config --libs glib-2.0` -o $@

clean: 
	rm -rf main
