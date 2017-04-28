all: oiler_parser oiler_lexer

includes: globals.h

oiler_parser: includes oiler_parser.lemon
	../lemon/lemon oiler_parser.lemon
	$(CC) -c -o oiler_parser.o oiler_parser.c

oiler_lexer: includes oiler_lexer.flex
	flex --outfile=oiler_lexer.c --header-file=oiler_lexer.h oiler_lexer.flex
	$(CC) -c -o oiler_lexer.o oiler_lexer.c

clean:
	rm -f *.out *.o *.c oiler_lexer.h oiler_parser.h

.PHONY: clean