all: lemon 

lemon: lemon.c template
	$(CC) -o lemon lemon.c

template: lempar.c

clean:
	-rm -rf lemon lemon.old

.PHONY: clean