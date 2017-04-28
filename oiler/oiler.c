#include <stdio.h>
#include <stdlib.h>

#include "language/globals.h"
#include "language/oiler_parser.h"
#include "language/oiler_lexer.h"

// For some reason, avoids a compiler warning about an integer conversion
void* ParseAlloc(void* (*allocProc)(size_t));

int main( int a_argument_count, char** a_arguments ) {
    // see if the user is calling the function correctly
    if( a_argument_count != 2 ) {
        printf("Usage: oiler file.oil\n");
        return -1;
    }
    // recovers the filename
    char* l_filename = a_arguments[1];

    // opens the oil file in read-only mode.
    FILE* l_file = fopen( l_filename, "r" );
    if( l_file == NULL ) {
        printf("File %s not found!", l_filename );
        return -1;        
    }
    // sets the lexer to get its input from the file
    yyin = l_file;

    // create a instance of the parser
    void* l_parser = ParseAlloc( malloc );

    int l_token_id = yylex();
    while( l_token_id != 0 ) {
        // printf( "LEXER: Got token %i\n", l_token_id );
        // Parses the current token
        Parse( l_parser, l_token_id, yylval );        
        // get the next token
        l_token_id = yylex();
    }

    // Finishes the parser giving it an EOF token
    Parse( l_parser, 0, yylval );
    // frees the parser
    ParseFree( l_parser, free );
    // and closes the file
    fclose( l_file );

	return 0;
}
