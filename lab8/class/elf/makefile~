 
CC=gcc
CFLAGS=-O -g -m32

#%.o: %.c
#	$(CC) $(CFLAGS) -c -o $@ $<

all: decbc encbc

#test: decbc encbc testbc
#	./testbc
#	if [ "`./encbc shalom olam|./decbc`" != "shalom olam" ]; then\
#	exit 1;\
#	fi

decbc: secret-elf-a secret-elf-c
	$(CC) $(CFLAGS) -o $@ $^

encbc: secret-elf-b secret-elf-c
	$(CC) $(CFLAGS) -o $@ $^

#testbc: bclib.c
#	$(CC) $(CFLAGS) -o $@ -DTESTBC=1 $^

#decbc.o: decbc.c bclib.h
#encbc.o: encbc.c bclib.h
#bclib.o: bclib.c bclib.h

clean:
	rm -f *.o encbc decbc testbc