.PHONY: all clean
.SUFFIXES: .c .o .h .asm
CFLAGS=-g -m32 -O0 -Wall
LDFLAGS=$(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -m32 -g -c -o $@ $<

%.o: %.asm
	nasm -g -f elf -o $@ $<

all: bsplit

bsplit: bsplit.o
	gcc -m32 -o $@ $^

#bsplit.o: bsplit.asm

clean:
	rm -f *.o 

distclean: clean
	rm -f bsplit
    
