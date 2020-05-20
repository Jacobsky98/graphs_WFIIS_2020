#include "headers/graphs.hpp"
#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <queue>

void project_1()
{
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

    AdjacencyList testAdjacencyList({{}, {}});
    IncidenceMatrix testIncidenceMatrix({{}, {}});

    Graph::convert(*graph, testIncidenceMatrix);
    Graph::convert(*graph, testAdjacencyList);

    testAdjacencyList.print(std::cout);
    std::cout << "\n\n";
    testIncidenceMatrix.print(std::cout);
    std::cout << "\n\n";

    adjacencyList = Graph::randomByEdges(6, 9);
    adjacencyList = Graph::randomByProbability(6, 0.3);
    graph = &adjacencyList;
    graph->printToFile(file);
    std::cout << graph;
}

void project_2()
{
    // zadanie 1

    std::vector<int> A1 = {3, 2, 1, 0}; // nie
    AdjacencyList::constuctGraphFromDegreeSequence(A1);
    std::vector<int> A2 = {3, 3, 3, 3}; // tak
    AdjacencyList::constuctGraphFromDegreeSequence(A2);
    std::vector<int> A3 = {4, 4, 3, 1, 2}; // nie
    AdjacencyList::constuctGraphFromDegreeSequence(A3);
    std::vector<int> A4 = {4, 2, 2, 3, 2, 1, 4, 2, 2, 2, 2}; // tak
    AdjacencyList adjacencyList = Graph::constuctGraphFromDegreeSequence(A4);
    std::ofstream file("output.dat");
    Graph *graph = &adjacencyList;
    graph->printToFile(file);

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
    // 1, 0, 0, 1, 0,
    // 1, 0, 0, 1, 0,
    // 1, 1, 1, 0, 1,
    // 1, 0, 0, 1, 0);
    // g1.convertToList().print(std::cout);
    // std::cout << std::endl;
    // Graph *graph = &g1;
    // std::ofstream file("output.dat");
    // graph -> printToFile(file);
    // g1.print(std::cout);
    // Graph::findEulerCycle(g1);
    // std::cout<<std::endl;
    // Graph::randomEuler(6);

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
    std::cout << std::endl;

    //Zadanie 2

    Graph::dijkstraAlgorithm(*gr, 0, true);
    std::cout << std::endl;

    //Zadanie 3

    for (int vertex = 0; vertex < gr->getVertexAmount(); vertex++)
    {
        std::vector<int> result = Graph::dijkstraAlgorithm(*gr, vertex, false);
        for (auto i : result)
            std::cout << i << "\t";
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //Zadanie 4
    struct ve
    {
        ve(int v, int w) : v(v), w(w){};
        int v, w;
        bool operator>(ve a) { return w > a.w; }
    };
    std::priority_queue<ve, std::vector<ve>, std::greater<>> min_sums;
    std::priority_queue<ve, std::vector<ve>, std::greater<>> minmax;
    std::cout << "\n\nSumy wag wierzchłków:" << std::endl;
    for (int vertex = 0; vertex < gr->getVertexAmount(); vertex++)
    {
        std::vector<int> result = Graph::dijkstraAlgorithm(*gr, vertex, false);
        int sum = 0;
        int max = 0;
        for (auto i : result)
        {
            sum += i;
            if (i > max)
            {
                max = i;
            }
        }
        min_sums.push(ve(vertex, sum));
        minmax.push(ve(vertex, max));
        std::cout << vertex << ": " << sum << std::endl; //show all sums
    }
    std::cout << "Najmniejsza suma wag: " << std::endl;
    std::cout << min_sums.top().v << ": " << min_sums.top().w << std::endl;
    std::cout << "Centrum minmax: " << std::endl;
    std::cout << minmax.top().v << ": " << minmax.top().w << std::endl
              << std::endl
              << std::endl;

    //zadanie 5
    adjList.primsAlgorithm().print(std::cout);
}

void directedTests()
{
    Graph *graph;

    AdjacencyList adjacencyList = AdjacencyList::loadFromFile("input/p4/adjList.txt");
    adjacencyList.print(std::cout);
    std::cout << "\n\n";

    graph = &adjacencyList;

    AdjacencyMatrix testAdjacencyMatrix;
    IncidenceMatrix testIncidenceMatrix;

    Graph::convert(*graph, testIncidenceMatrix);
    Graph::convert(*graph, testAdjacencyMatrix);

    testAdjacencyMatrix.print(std::cout);
    std::cout << "\n\n";
    testIncidenceMatrix.print(std::cout);
    std::cout << "\n\n";

    std::cout << adjacencyList.getVertexAmount() << " " << testAdjacencyMatrix.getVertexAmount() << " " << testIncidenceMatrix.getVertexAmount() << std::endl;
    std::cout << adjacencyList.doesEdgeExists(0, 1) << " " << testAdjacencyMatrix.doesEdgeExists(0, 1) << " " << testIncidenceMatrix.doesEdgeExists(0, 1) << std::endl;
    std::cout << adjacencyList.doesEdgeExists(3, 2) << " " << testAdjacencyMatrix.doesEdgeExists(3, 2) << " " << testIncidenceMatrix.doesEdgeExists(3, 2) << std::endl;
    std::cout << adjacencyList.isVertexIsolated(4) << " " << testAdjacencyMatrix.isVertexIsolated(4) << " " << testIncidenceMatrix.isVertexIsolated(4) << std::endl;
    std::cout << adjacencyList.dimOfVertex(2) << " " << testAdjacencyMatrix.dimOfVertex(2) << " " << testIncidenceMatrix.dimOfVertex(2) << std::endl;
    std::cout << adjacencyList.isDirectedGraph() << " " << testAdjacencyMatrix.isDirectedGraph() << " " << testIncidenceMatrix.isDirectedGraph() << std::endl;
}

void project_4()
{
    // zadanie 1
    // AdjacencyList adjacencyList = Graph::createRandomDigraph(10, 0.5);
    // adjacencyList.print(std::cout);
    // std::cout << "\n\n";

    // zadanie 2
    AdjacencyList adjacencyList1 = AdjacencyList::loadFromFile("input/p4/adjList_ad1.txt");
    Graph::kosarajuAlgorithm(adjacencyList1);

    AdjacencyList adjacencyList2 = AdjacencyList::loadFromFile("input/p4/adjList_ad2.txt");
    Graph::kosarajuAlgorithm(adjacencyList2);

    AdjacencyList adjacencyList3 = AdjacencyList::loadFromFile("input/p4/adjList_ad3.txt");
    adjacencyList3.addVertex();
    Graph::kosarajuAlgorithm(adjacencyList3);

    // std::cout << "Zadanie 2: losowy graf\n\n";
    AdjacencyList randomAdjacencyList = Graph::createRandomDigraph(7);
    Graph::kosarajuAlgorithm(randomAdjacencyList);
    std::ofstream file("output.dat");
    Graph *graph;
    graph = &randomAdjacencyList;
    graph->printToFile(file);

    // zadanie 3
    std::cout << "\nZadanie 3: Bellman-Ford Algorytm\n\n";
    std::vector<int> result;
    AdjacencyList coherentGraph;
    bool isCoherent = false;
    while (true)
    {
        coherentGraph = Graph::createRandomDigraph(5, 0.3, -5, 10);
        Graph::kosarajuAlgorithm(coherentGraph, false, &isCoherent);
        if (isCoherent)
            break;
    }
    Graph::kosarajuAlgorithm(coherentGraph);

    std::cout << std::endl;
    if (!Graph::bellmanFordAlgorithm(coherentGraph, 0, result, true))
    {
        std::cout << "W grafie jest cykl ujemny" << std::endl;
    }

    //zad4
    std::cout << "\nZadanie 4: Algorytm Johnsona\n\n";

    Graph *gr = &coherentGraph;
    Graph::johnsonAlgorithm(*gr, 1);
}

void project_5()
{
    FlowNetwork flowNet(2);
    flowNet.print();


    std::ofstream file("output_python.txt");
    flowNet.printToFile(file);

    std::cout << std::endl;
    FlowNetwork maxFlow = flowNet.fordFulkersonAlgorithm();
    maxFlow.print();

}

int main()
{
    srand(time(NULL));
    // AdjacencyMatrix adjMat = {  0, 1, 0, 1, 0,
    //                             1, 0, 1, 1, 0,
    //                             0, 1, 0, 1, 0,
    //                             1, 1, 1, 0, 0,
    //                             0, 0, 0, 0, 0};
    // project_1();
    // project_2();
    // project_3();
    // directedTests();
    // project_4();
    project_5();
    return 0;
}