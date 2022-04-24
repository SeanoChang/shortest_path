#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "build_graph.h"
#include "write_output.h"

int main(int argc, char** argv){
    if(argc != 5){
        fprintf(stderr,"pa5.c Invalid number of files\n");
        return EXIT_FAILURE;
    }

    Graph* graph = readGraph(argv[1]);
    short row = graph->row;
    short col = graph->col;

    if(writeOutput1(argv[2], graph, row, col)){
        fprintf(stderr, "pa5.c Error writing output file 1\n");
        return EXIT_FAILURE;
    }

    Path* fastestPath = writeOutput2(argv[3], graph, row, col);
    
    if(fastestPath == NULL){
        fprintf(stderr, "pa5.c Error writing output file 2\n");
        return EXIT_FAILURE;
    }

    if(writeOutput3(argv[4], fastestPath)){
        fprintf(stderr, "pa5.c Error writing output file 3\n");
        return EXIT_FAILURE;
    }

    destroyGraph(graph);
    return EXIT_SUCCESS;
}
