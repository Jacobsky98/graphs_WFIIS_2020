#include "headers/graphs.hpp"
#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include <fstream>

int main()
{
    Graph *graph;
    std::vector<std::vector<int>> matrix = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0}};

    AdjacencyMatrix adjacencyMatrix(matrix);
    graph = &adjacencyMatrix;
    *graph = graph->convertToList();

    IncidenceMatrix incidenceMatrix;

    Graph::convert(*graph, incidenceMatrix);

    graph = &incidenceMatrix;

    std::ofstream file("output.dat");
    AdjacencyList adjacencyList = Graph::randomByEdges(6, 9);
    adjacencyList = Graph::randomByProbability(6, 0.1);
    graph = &adjacencyList;
    file << graph;


    return 0;
}