#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "build_graph.h"
#include "write_output.h"

int main(int argc, char** argv){
    if(argc != 5){
        fprintf(stderr,"Invalid number of files\n");
        return EXIT_FAILURE;
    }

    short row;
    short col;
    Graph* graph = readGraph(argv[1], &row, &col);

    if(!writeOutput1(argv[2], graph, row, col)){
        fprintf(stderr, "Error writing output file 1\n");
        return EXIT_FAILURE;
    }


    Path* fastestPath = writeOutput2(argv[3], graph, row, col);

    if(fastestPath == NULL){
        fprintf(stderr, "Error writing output file 2\n");
        return EXIT_FAILURE;
    }

    if(!writeOutput3(argv[4], fastestPath)){
        fprintf(stderr, "Error writing output file 3\n");
        return EXIT_FAILURE;
    }

    destroyGraph(graph);
    return EXIT_SUCCESS;
}
