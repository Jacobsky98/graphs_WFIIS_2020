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
    
    // std::vector<int> A1 = {3,2,1,0}; // nie
    // AdjacencyList::constuctGraphFromDegreeSequence(A1);
    // std::vector<int> A2 = {3,3,3,3}; // tak
    // AdjacencyList::constuctGraphFromDegreeSequence(A2);
    // std::vector<int> A3 = {4,4,3,1,2}; // nie
    // AdjacencyList::constuctGraphFromDegreeSequence(A3);
    // std::vector<int> A4 = {4,2,2,3,2,1,4,2,2,2,2}; // tak
    // AdjacencyList adjacencyList = Graph::constuctGraphFromDegreeSequence(A4);
    // std::ofstream file("output.dat");
    // Graph *graph = & adjacencyList;
    // graph -> printToFile(file);

    // zadanie 2
    
    // std::ofstream file1("output-p2-z2-1.dat"); //Zmienić gnuplot.sh przy pokazywaniu!
    // std::ofstream file2("output-p2-z2-2.dat");
    // AdjacencyList adjacencyList = AdjacencyList::loadFromFile("input/p1/adjList.txt");
    // Graph *graph = &adjacencyList;
    // graph -> printToFile(file1);
    // adjacencyList.print(std::cout);
    // std::cout << std::endl;
    // adjacencyList = Graph::randomizeEdges(10, adjacencyList);
    // graph -> printToFile(file2);
    // adjacencyList.print(std::cout);
    // std::cout << std::endl;

    // zadanie 3
    
    // std::vector<int> A4 = {4,2,2,3,2,1,4,2,2,2,2}; // tak
    // AdjacencyList adjacencyList = Graph::constuctGraphFromDegreeSequence(A4);
    // Graph::largestComponent(adjacencyList);
    // adjacencyList.print(std::cout);
    // std::ofstream file("output.dat");
    // Graph *graph = & adjacencyList;
    // graph -> printToFile(file);

    // zadanie 4

    // AdjacencyMatrix g1(
    // 0, 1, 1, 1, 1,
    // 1, 0, 1, 1, 0,
    // 1, 1, 0, 1, 0,
    // 1, 1, 1, 0, 1,
    // 1, 0, 0, 1, 0);
    // g1.convertToList().print(std::cout);
    // std::cout << std::endl;
    // Graph *graph = &g1;
    // std::ofstream file("output.dat");
    // graph -> printToFile(file);
    // g1.print(std::cout);
    // Graph::findEulerCycle(g1); 
    // Graph::randomEuler(10);

    // zadanie 5
    // std::ofstream file("output.dat");
    // Graph *graph;
    // AdjacencyList g1=    Graph::generateKRegularGraph(7, 2);
    // graph = &g1;
    // graph -> printToFile(file);

    // zadanie 6
    // przykladowy wejsciowy graf z rysunku 4
    // AdjacencyMatrix z6(
    //     0,1,0,1,1,0,0,0,
    //     1,0,1,0,1,1,0,0,
    //     0,1,0,1,0,0,1,0,
    //     1,0,1,0,0,1,1,0,
    //     1,1,0,0,0,0,0,1,
    //     0,1,0,1,0,0,0,1,
    //     0,0,1,1,0,0,0,1,
    //     0,0,0,0,1,1,1,0
    //                     );
    // Graph::hamiltonCycleFind(z6);
    
}

void project_3() 
{

    // Zadanie 1

    AdjacencyList adjList = Graph::createRandomWeightedConnectedGraph(10, 0.2);
    adjList.print(std::cout);
    Graph *gr = &adjList;
    std::ofstream file("output.dat");
    gr->printToFile(file);

    //Zadanie 2

    Graph::dijkstraAlgorithm(*gr, 0, true);

    //Zadanie 3

    for(int vertex = 0; vertex < gr -> getVertexAmount(); vertex++)
    {
        std::vector<int> result = Graph::dijkstraAlgorithm(*gr, vertex, false);
        for(auto i: result)
            std::cout << i <<"\t";
        std::cout << std::endl;
    }
}

int main()
{
    // AdjacencyMatrix adjMat = {  0, 1, 0, 1, 0,
    //                             1, 0, 1, 1, 0,
    //                             0, 1, 0, 1, 0,
    //                             1, 1, 1, 0, 0,
    //                             0, 0, 0, 0, 0};
    // project_1();
    // project_2();
    project_3();
    return 0;
}