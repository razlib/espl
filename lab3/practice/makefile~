%.o: %.c
	gcc -c -o $@ $<

all:xsum

clean:
	rm -f *.o

fortune: xsum.o
	cc -o $@ $^