%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.man: %.1
	nroff -man $< > $@

all: bsplit

bsplit: bsplit.o xsum.o
	$(CC) $(LDFLAGS) -o $@ $^


bsplit.o: bsplit.c xsum.h
xsum.o: xsum.c xsum.h

clean:
	rm -f *.o 

distclean: clean
	rm -f bsplit
