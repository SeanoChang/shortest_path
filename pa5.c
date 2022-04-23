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
    short** graphMatrix = readGraph(argv[1], &row, &col);
    Node** graph = buildGraph(graphMatrix, row, col);

    if(!writeOutput1(argv[2], graphMatrix, row, col)){
        fprintf(stderr, "Error writing output file 1\n");
        return EXIT_FAILURE;
    }


    int fastestPath = writeOutput2(argv[3], graph, row, col);

    if(fastestPath = -1){
        fprintf(stderr, "Error writing output file 2\n");
        return EXIT_FAILURE;
    }

    if(!writeOutput3(argv[4], graph, fastestPath)){
        fprintf(stderr, "Error writing output file 3\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
