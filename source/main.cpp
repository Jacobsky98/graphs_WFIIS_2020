#include "headers/graphs.hpp"
#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <queue>

#include <algorithm>
#include <array>
#include <random> // std::default_random_engine
#include <math.h>
#include <iomanip> // std::setprecision
#include <fstream>
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

// constexpr int N = 2;
// constexpr int iter = 1000011;
// constexpr int iter2 = 111;
// constexpr float teleport = 0.15;

// void project_6()
// {
//     std::string names[8] = {"A", "B", "C", "D", "E", "F", "G"};
//     int PageRank1[N] = {};
//     //  A, B, C, D, E, F
//     float repr1[N][N] = {
//         {0, 1},
//         {1, 0}
//     };

constexpr int N = 6;
constexpr int iter = 1000011;
constexpr int iter2 = 20;
constexpr float teleport = 0.15;

void project_6()
{
    std::cout << std::setprecision(2) << std::fixed;
    {

        std::string names[8] = {"A", "B", "C", "D", "E", "F", "G"};
        int PageRank1[N] = {};
        //  A, B, C, D, E, F
        float repr1[N][N] = {
            {0, 1, 0, 1, 1, 0},  //A
            {0, 0, 1, 0, 1, 0},  //B
            {0, 1, 0, 1, 0, 1},  //C
            {0, 1, 0, 0, 0, 0},  //D
            {0, 1, 0, 1, 0, 1},  //E
            {0, 1, 0, 0, 0, 0}}; //F
        //itera
        int poz = rand() % N;
        for (size_t i = 0; i < iter; i++)
        {
            PageRank1[poz]++;

            //testing dead end
            bool empty = 1;
            for (size_t j = 0; j < N; j++)
            {
                if (repr1[poz][j] == 1)
                {
                    empty = 0;
                }
            }
            if (empty)
            {
                std::cout << poz;

                poz = rand() % N;
                continue;
            }
            //
            float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

            if (r < teleport)
            {
                poz = rand() % N;
            }
            else
            {
                int gues = rand() % N;
                while (repr1[poz][gues] == 0)
                {
                    gues = rand() % N;
                    // std::cout << "Vertex " << gues << " Page rank: " <<repr1[poz][gues] << "\n";
                }
                poz = gues;
            }
        }

        struct Rank
        {

            std::string name;
            float v;
            Rank(std::string name, float v) : name(name), v(v){};
            bool operator>(Rank a) { return v > a.v; }
            bool operator<(Rank a) { return v < a.v; }
        };
        // std::priority_queue<Rank, std::vector<Rank>, std::greater<>> sorted_ranking;
        std::priority_queue<Rank, std::vector<Rank>, std::less<>> sorted_ranking;
        std::priority_queue<Rank, std::vector<Rank>, std::less<>> sorted_ranking2;

        for (size_t i = 0; i < N; i++)
        {
            //   std::cout << "Vertex " << names[i] << " Page rank: " << (float)PageRank1[i] / (float)iter << "\n";
            sorted_ranking.push(Rank(names[i], (float)PageRank1[i] / (float)iter));
        }
        for (size_t i = 0; i < N; i++)
        {
            std::cout << "Vertex " << sorted_ranking.top().name << " Page rank: " << sorted_ranking.top().v << "\n";
            sorted_ranking.pop();
        }

        //metoda 2
        float obs[N] = {};
        float obs_hist[10][N] = {};

        for (auto &i : obs)
        {
            i = 1.0 / (float)N;
        }

        float P[N][N] = {};
        int d[N] = {};
        for (size_t i = 0; i < N; i++)
        {
            for (size_t j = 0; j < N; j++)
            {
                d[i] += repr1[i][j];
            }
        }
        for (size_t i = 0; i < N; i++)
        {
            for (size_t j = 0; j < N; j++)
            {
                P[i][j] = ((1 - teleport) * (repr1[i][j] / (float)d[i])) + (teleport / (float)N);
            }
        }

        float sum[N] = {};
        for (size_t t = 0; t < iter2; t++)
        {
            for (size_t i = 0; i < N; i++)
            {
                sum[i] = 0;
                for (size_t j = 0; j < N; j++)
                {
                    sum[i] += obs[j] * P[j][i];
                }
            }
            for (size_t i = 0; i < N; i++)
            {
                obs[i] = sum[i];
                obs_hist[t % 10][i] = sum[i];
            }
        }
        std::cout << "\n\nAlgorytm2:\n";

        float error = 0;
        if (iter2 > 20)
        {
            for (size_t t = 0; t < 10; t++)
            {
                for (size_t i = 0; i < N; i++)
                {
                    error += (obs_hist[t][i] - obs[i]) * (obs_hist[t][i] - obs[i]);
                }
            }
        }
        if (error > 0.8)
        {
            std::cout << "\nWynik nie jest staly algorytm korzysta z sredniej z ostatnich 10 iteracji:";

            for (size_t i = 0; i < N; i++)
            {
                obs[i] = 0;
            }
            for (size_t t = 0; t < 10; t++)
            {
                for (size_t i = 0; i < N; i++)
                {
                    obs[i] += obs_hist[t][i] / 10;
                }
            }
        }

        for (size_t i = 0; i < N; i++)
        {
            //   std::cout << "Vertex " << names[i] << " Page rank: " << (float)PageRank1[i] / (float)iter << "\n";
            sorted_ranking2.push(Rank(names[i], (float)obs[i]));
        }
        for (size_t i = 0; i < N; i++)
        {
            std::cout << "Vertex " << sorted_ranking2.top().name << " Page rank: " << sorted_ranking2.top().v << "\n";
            sorted_ranking2.pop();
        }
    }
    //ZAD2
    //
    //
    //
    //

    {

        constexpr float kwadrat_x = 2, kwadrat_y = 2; //ofsety 0
        constexpr int il_punkt = 20, iter3 =122;
        float tab[2][il_punkt] = {};
        std::array<int, il_punkt> P;    //indeksy punktow
        std::array<int, il_punkt> Pnew; //indeksy punktow

        for (size_t i = 0; i < il_punkt; i++)
        {
            tab[0][i] = (float)rand() / (float)RAND_MAX * kwadrat_x;
            tab[1][i] = (float)rand() / (float)RAND_MAX * kwadrat_y;
            P[i] = i;
            std::cout << "v: " << i << " ";
            std::cout << "x: " << tab[0][i] << " ";
            std::cout << "y: " << tab[1][i] << "\n";
        }

        auto fd = [tab](std::array<int, il_punkt> P, bool print = 0) -> float {
            float distance = 0;
            int i = 0;

            do
            {
                int a = i;
                int b = P[i];
                distance += sqrt((tab[0][a] - tab[0][b]) * (tab[0][a] - tab[0][b]) + (tab[1][a] - tab[1][b]) * (tab[1][a] - tab[1][b]));
                if (print)
                {
                    std::cout << "Idę z " << a << " do " << b << " całkowidy przebyty dystans to " << distance << "\n";
                }

                i = P[i];
            } while (i != 0);

            if (print)
            {
                std::ofstream myfile;
                myfile.open("zad62.txt");
                do
                {
                   

                    myfile << tab[0][i] << " " << tab[1][i] << "\n";

                    i = P[i];
                } while (i != 0);

                myfile.close();
            }
            return distance;
        };
        for (size_t i = 0; i < il_punkt; i++)
        {
            P[i] = (i + 1) % il_punkt;
        }

        for (size_t i = 100; i >= 1; i--)
        {
            float T = 0.001 * i * i;
            for (size_t it = 0; it < iter3; it++)
            {
                int a = rand() % il_punkt;
                int b = P[a];
                int c = rand() % il_punkt;
                int d = P[c];

                while (a == c || a == d || b == c || b == d)
                {
                    c = rand() % il_punkt;
                    d = P[c];
                    // std::cout << "ok\n";
                }
                std::copy(std::begin(P), std::end(P), std::begin(Pnew));

                //!!
                Pnew[a] = c;
                Pnew[b] = d;
                int temp = b;
                int next = P[temp];
                int nnext = P[next];

                while (temp != c)
                {
                    nnext = Pnew[next];
                    Pnew[next] = temp;
                    temp = next;
                    next = nnext;
                    //      std::cout<< temp<<" "<<c<<"\n";
                }

                //   std::cout << a << " " << b << " " << c << " " << d << " \n";

                // for (size_t i = 0; i < il_punkt; i++)
                // {
                //     std::cout<<"\n"<<i<<" "<<P[i]<<"\n";
                // }

                if (fd(Pnew) < fd(P))
                {
                    std::copy(std::begin(Pnew), std::end(Pnew), std::begin(P));
                }
                else
                {
                    float r = (float)rand() / (float)RAND_MAX;
                    if (r < exp(-(fd(Pnew) - fd(P)) / T))
                    {
                        std::copy(std::begin(Pnew), std::end(Pnew), std::begin(P));
                    }

             //       std::cout<<exp(-(fd(Pnew)- fd(P)) / T)<<"\n";
                }
            }
        }

        fd(P, 1);
    }
}

int main()
{
    // srand(time(NULL));
    srand(122);
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
    // project_5();
    project_6();

    return 0;
}