.PHONY: all clean

all: main

main.exe: main.o
	gcc -flto -o $@ $^
	strip $@

%.o: %.c
	gcc -c -flto -O3 $<

clean:
	rm -f main
