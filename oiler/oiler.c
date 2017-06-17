#include <stdio.h>
#include <stdlib.h>

#include "language/globals.h"
#include "language/oiler_parser.h"
#include "language/oiler_lexer.h"

void* ParseAlloc(void* (*allocProc)(size_t)); // For some reason, avoids a compiler warning about an integer conversion

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

    // Stores data relative to the Operating System
    OS os;
    os.task_count = 0;
    os.resource_count = 0;

    // create a instance of the parser
    void* l_parser = ParseAlloc( malloc );

    int l_token_id = yylex();
    while( l_token_id != 0 ) {
        // printf( "LEXER: Got token %i\n", l_token_id );
        // Parses the current token
        Parse( l_parser, l_token_id, yylval, &os );        
        // get the next token
        l_token_id = yylex();
    }

    // Finishes the parser giving it an EOF token
    Parse( l_parser, 0, yylval, NULL );
    // frees the parser
    ParseFree( l_parser, free );
    // and closes the file
    fclose( l_file );

    printf( "\n" );
    int i;
    for( i = 0; i < os.task_count; i++ ) {
        Task* l_task = &os.tasks[i];
        printf( "Task %i: %s\n", i+1, l_task->name );
        printf( "\tPriority = %d\n", l_task->priority );
        printf( "\tSchedule = %d\n", l_task->schedule );
        printf( "\tActivation = %d\n", l_task->activation );
        printf( "\tAutoStart = %d\n", l_task->autostart );
        printf( "\tResources: " );
        int j;
        for( j = 0; j < l_task->resource_count; j++ ) {
            printf( "%s", l_task->resources[j]->name );
            printf( j != l_task->resource_count -1 ? ", " : ";\n" );
        }
        if( l_task->resource_count == 0 ) {
            printf( "\n" );
        }
    }
    printf( "\n" );
    for( i = 0; i < os.resource_count; i++ ) {
        printf( "Resource %i: %s[%d]\n", i+1, os.resources[i].name, os.resources[i].type );
    }
    printf( "\n" );
    printf( "TASKS_TOTAL = %i\n", os.task_count );
    printf( "RESOURCE_TOTAL = %i\n", os.resource_count );

    // Create the output file in the oiler directory
    char * oiler_cmd = a_arguments[0];
    char l_filename_out[256] = { '\0' };
    char * l_slash = strrchr( oiler_cmd,'/' );
    memcpy( l_filename_out, oiler_cmd, (int)(l_slash - oiler_cmd) );
    strcat( l_filename_out, "/initial.d" );

    l_file = fopen( l_filename_out, "w" );    
    // Generating the source file
    // Total # of Tasks
    fprintf( l_file, "const uint8_t TASKS_TOTAL = %i;\n\n", os.task_count );
    // Creating constants for the tasks, function headers & setting the allocated resource a initial value for its priority
    for( i = 0; i < os.task_count; i++ ) {
        Task* l_task = &os.tasks[i];
        fprintf( l_file, "const TaskType %s = %i;\n", l_task->name, i+1 );
        fprintf( l_file, "TASK(%s);\n", l_task->name );
        int j;
        for( j = 0; j < l_task->resource_count; j++ ) {
            // Resources used by tasks should have higher priority than the calling task
            Resource* l_resource = l_task->resources[j];
            if( l_resource->priority <= l_task->priority ) {
                l_resource->priority = l_task->priority + 1;
            }
        }
    }
    fprintf( l_file, "\n" );
    // Creating constants for the resources
    for( i = 0; i < os.resource_count; i++ ) {
        fprintf( l_file, "const ResourceType ResourceType_%s = %i;\n", os.resources[i].name, i+1 );
    }
    if( os.resource_count != 0 ) {
        fprintf( l_file, "\n" );
    }
    // Writing the initialization code for tasks
    fprintf( l_file, "void TASK_FUNC_IDLE() {\n\twhile( TRUE ) { NOP(); }\n}\n\n" );
    fprintf( l_file, "void InitializeTasks() {\n" );
    fprintf( l_file, "\tInitializeTaskData( g_idle, TASK_ID_IDLE, 0, READY, TASK_FUNC_IDLE );\n" );
    for( i = 0; i < os.task_count; i++ ) {
        Task* l_task = &os.tasks[i];
        fprintf( l_file, "\tInitializeTaskData( &g_tasks[%i], %s, %i, %s, TASK_FUNC_%s );\n",
            i, l_task->name, l_task->priority, l_task->autostart == 0 ? "SUSPENDED" : "READY", l_task->name
        );
    }
    fprintf( l_file, "\tGroupTasksSamePriority();\n" );
    fprintf( l_file, "}\n\n" ); // InitializeTasks    
    // Writing the initialization code for the resources
    if( os.resource_count > 0 ) {
        fprintf( l_file, "ResourceDataType g_res[%i];\n", os.resource_count );
    }
    fprintf( l_file, "void InititializeResources() {\n" );
    for( i = 0; i < os.resource_count; i++ ) {
        // Part 1: Fixing the priorities values
        Resource* l_resource = &os.resources[i];
        int ok;
        do {
            ok = 1;
            int j;
            for( j = 0; j < os.task_count; j++ ) {
                if( l_resource->priority == os.tasks[j].priority ) {
                    l_resource->priority++;
                    ok = 0;
                    break;
                }
            }
        } while( ok != 1 );        
        // Generating the initialization code
        fprintf( l_file, "\tAddResourceDataToResources( &g_res[%i], ResourceType_%s, %i );\n",
            i, l_resource->name, l_resource->priority
        );
    }
    fprintf( l_file, "}\n\n" ); // InititializeResources
    // Register functions
    fprintf( l_file, "asm(\"GLOBAL _TASK_FUNC_IDLE" );
    for( i = 0; i < os.task_count; i++ ) {
        fprintf( l_file, ", _TASK_FUNC_%s", os.tasks[i].name );
    }
    fprintf( l_file, "\" );\n" );
    
    fclose( l_file );

	return 0;
}
