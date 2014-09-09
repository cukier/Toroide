CC=ccsc
CFLAGS=+FH +LN -T -A -M -Z +DF +Y=9 +STDOUT

all: toroide

toroide: toroide.c
	$(CC) $(CFLAGS) toroide.c

clean:
	rm *.cof *.err *.esym *.hex *.lst