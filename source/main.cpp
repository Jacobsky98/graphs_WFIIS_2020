#include "headers/graphs.hpp"
#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include <fstream>

int main()
{
    std::ofstream file("output.dat");
    Graph *graph;


    AdjacencyMatrix adjacencyMatrix = AdjacencyMatrix::loadFromFile("adjMat.txt");
    adjacencyMatrix.print(std::cout);
    std::cout << "\n\n";

    AdjacencyList adjacencyList = AdjacencyList::loadFromFile("adjList.txt");
    adjacencyList.print(std::cout);
    std::cout << "\n\n";

    IncidenceMatrix incidenceMatrix = IncidenceMatrix::loadFromFile("incMat.txt");
    incidenceMatrix.print(std::cout);
    std::cout << "\n\n";

    graph = &adjacencyMatrix;

    AdjacencyList testAdjacencyList({{},{}});
    IncidenceMatrix testIncidenceMatrix({{},{}});

    Graph::convert(*graph, testIncidenceMatrix);
    Graph::convert(*graph, testAdjacencyList);

    testAdjacencyList.print(std::cout);
    std::cout << "\n\n";
    testIncidenceMatrix.print(std::cout);
    std::cout << "\n\n";
    
    adjacencyList = Graph::randomByEdges(6, 9);
    adjacencyList = Graph::randomByProbability(6, 0.3);
    graph = &adjacencyList;
    graph -> printToFile(file);
    std::cout << graph;
    return 0;
}