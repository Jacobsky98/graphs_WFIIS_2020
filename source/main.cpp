#include "headers/graphs.hpp"
#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include <fstream>

void project_1() {
    std::ofstream file("output.dat");
    Graph *graph;


    AdjacencyMatrix adjacencyMatrix = AdjacencyMatrix::loadFromFile("input/p1/adjMat.txt");
    adjacencyMatrix.print(std::cout);
    std::cout << "\n\n";

    AdjacencyList adjacencyList = AdjacencyList::loadFromFile("input/p1/adjList.txt");
    adjacencyList.print(std::cout);
    std::cout << "\n\n";

    IncidenceMatrix incidenceMatrix = IncidenceMatrix::loadFromFile("input/p1/incMat.txt");
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
}

void project_2() {
    // zadanie 1
    
    std::vector<int> A1 = {3,2,1,0}; // nie
    AdjacencyList::constuctGraphFromDegreeSequence(A1);
    std::vector<int> A2 = {3,3,3,3}; // tak
    AdjacencyList::constuctGraphFromDegreeSequence(A2);
    std::vector<int> A3 = {4,4,3,1,2}; // nie
    AdjacencyList::constuctGraphFromDegreeSequence(A3);
    std::vector<int> A4 = {3,3,3,2,2,1}; // tak
    AdjacencyList adjacencyList = Graph::constuctGraphFromDegreeSequence(A4);
    std::ofstream file("output-p2-z1.dat");
    Graph *graph;
    graph = &adjacencyList;
    graph -> printToFile(file);

    // zadanie 3
    // AdjacencyMatrix adjacencyMatrix(
    //                     1, 4, 4, 4, 4, 3, 3, 1, 
    //                     2, 1, 1, 4, 3, 3, 1, 1, 
    //                     3, 2, 1, 1, 2, 3, 2, 1, 
    //                     3, 3, 2, 1, 2, 2, 2, 2, 
    //                     3, 1, 3, 1, 1, 4, 4, 4, 
    //                     1, 1, 3, 1, 1, 4, 4, 4);
    // Graph::largestComponent(adjacencyMatrix);

}

int main()
{
    project_2();
    return 0;
}