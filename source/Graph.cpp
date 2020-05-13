#include "headers/Graph.hpp"
#include "headers/AdjacencyList.hpp"
#include "headers/AdjacencyMatrix.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h> 
#include <algorithm>

std::ostream &operator<<(std::ostream &o, Graph const *graph)
{
    return graph->print(o);
}

Graph &Graph::addVertex(unsigned int vertices)
{
    while (vertices)
    {
        addVertex();
        --vertices;
    }
    return *this;
}

Graph &Graph::convert(Graph const &source, Graph &destination)
{
    return destination.convertFromList(source.convertToList());
}

AdjacencyList Graph::randomByEdges(unsigned int n, unsigned int l)
{
    AdjacencyMatrix graph;

    graph.addVertex(n);

    srand (time(NULL));

    int first, second;
    
    while (l)
    {
        first = rand() % n;
        second = rand() % n;
        //lepsze byloby sprawdzenie czy istnieje krawedz
        auto matrix = graph.getMatrix();
        if (first != second && !matrix[first][second])
        {
            
            graph.addEdge(first, second);
            --l;
        }
    }

    return graph.convertToList();
}

AdjacencyList Graph::randomByProbability(unsigned int n, double p)
{
    AdjacencyList graph;

    graph.addVertex(n);

    srand (time(NULL));

    double draw;

    auto list = graph.getList();

    for (unsigned int i = 0; i < list.size(); ++i)
    {
        for (unsigned int j = i + 1; j < list.size(); ++j)
        {
            draw = ((double) rand() / (RAND_MAX));
            if (draw <= p)
                graph.addEdge(i, j);
        }
    }

    return graph;
}

bool Graph::degreeSequence(std::vector<int> A)
{
    while(1) 
    {
        sort(A.begin(), A.end(), std::greater<>()); 
        if(A[0] == 0)
            return true;
        unsigned int value = A[0];
        A.erase(A.begin()+0);

        if(value > A.size())
            return false;
        for(unsigned int i = 0; i < value; i++)
        {
            A[i]--;
            if(A[i] < 0)
            {
                return false;
            }
        }
    }
    
}

AdjacencyList Graph::constuctGraphFromDegreeSequence(std::vector<int>& A)
{
    if(Graph::degreeSequence(A))
    {
        std::cout << "Ciag jest graficzny\n";
        unsigned int rowsize = A.size();
        std::vector<std::vector<int>> matrix = std::vector<std::vector<int>> (rowsize, std::vector<int>(rowsize));
        
        for (unsigned int i = 0; i < rowsize; i++) { 
            for (unsigned int j = i + 1; j < rowsize; j++) { 
                if (A[i] > 0 && A[j] > 0) { 
                    A[i]--; 
                    A[j]--; 
                    matrix[i][j] = 1; 
                    matrix[j][i] = 1; 
                } 
            } 
        }

        AdjacencyMatrix adjacencyMatrix(matrix);
    
        return AdjacencyList(adjacencyMatrix.convertToList());
    }

    std::cout << "Ciag nie jest graficzny\n";
    return AdjacencyList();
}




void Graph::largestComponent(AdjacencyList adjacencyList)
{
    int nr = 0;
    std::vector<std::list<Edge>> list = adjacencyList.getList();
    int n = list.size();
    int comp[n];
    for(int i = 0; i < n; i++)
    {
        comp[i] = -1;
    }
    for(int i = 0; i < n; i++)
    {
        if(comp[i] == -1)
        {
            nr += 1;
            comp[i] = nr;
            Graph::components_r(nr, i, list, comp);
        }
    }

    int counter_printed_elements = 0;
    int list_nr = 1;
    int largest = 0;
    int count_largest = 0;
    int largest_id = 0;
    while(counter_printed_elements != n)
    {   
        std::cout << list_nr << ") ";
        for(int i = 0; i < n; i++)
        {
            if(list_nr == comp[i])
            {
                std::cout << i << " ";
                counter_printed_elements++;
                count_largest++;
            }
        }
        if(largest < count_largest)
        {
            largest = count_largest;
            count_largest = 0;
            largest_id = list_nr;
        }
        list_nr++;
        std::cout << "\n";
    }
    std::cout << "Najwieksza skladowa ma numer " << largest_id << ".\n";

}


void Graph::randomEuler(unsigned int n)
{
    for(int i = 0; i < 10000; i++)
    {
        // double prob = (double)rand() / RAND_MAX;
        double prob = 0.4;
        AdjacencyList adjacencyList = Graph::randomByProbability(n, prob);
        
        AdjacencyMatrix adjacencyMatrix;
        adjacencyMatrix.convertFromList(adjacencyList);

        int it = 0;
        // std::cout << "i=" << i <<" size = " << degree_sequence.size()<< "\n";
        bool found_cycle = false;;
        // bool found_cycle = findEulerCycle(adjacencyMatrix);
        while(!found_cycle && it < 100)
        {
            // std::cout << "it=" << it<< "\n";
            AdjacencyMatrix tmp(adjacencyMatrix);
            found_cycle = findEulerCycle(tmp);
            if(found_cycle)
                break;
            randomizeEdges(2, adjacencyMatrix);
            it++;
        }
        if(found_cycle)
        {
            std::cout << "\nGraf:\n";
            adjacencyMatrix.print(std::cout);
            return;
        }
    }
}



bool Graph::findEulerCycle(AdjacencyMatrix& adjacencyMatrix)
{
    std::vector<std::vector<int>> matrix = adjacencyMatrix.getMatrix();
    int n = matrix.size();
    for(int i = 0 ; i < n; i++)
    {
        if(adjacencyMatrix.dimOfVertex(i)%2 != 0)
            return false;
    }
    if(n == 0)
        return false;
    std::vector<int> degree(n);
    
    for (int i = 0; i < n; ++i) {
            degree.push_back(0);
            for (int j = 0; j < n; ++j)
                degree[i] += matrix[i][j];
    }

    int first = 0;
    while (!degree[first])
        ++first;

    int v1 = -1, v2 = -1;
    bool bad = false;
    for (int i = 0; i < n; ++i) {
        if (degree[i] & 1) {
            if (v1 == -1)
                v1 = i;
            else if (v2 == -1)
                v2 = i;
            else
                bad = true;
        }
    }

    if (v1 != -1)
        ++matrix[v1][v2], ++matrix[v2][v1];

    std::stack<int> st;
    st.push(first);
    std::vector<int> res;
    while (!st.empty()) {
        int v = st.top();
        int i;
        for (i = 0; i < n; ++i)
            if (matrix[v][i])
                break;
        if (i == n) {
            res.push_back(v);
            st.pop();
        } else {
            --matrix[v][i];
            --matrix[i][v];
            st.push(i);
        }
    }

    if (v1 != -1) {
        for (size_t i = 0; i + 1 < res.size(); ++i) {
            if ((res[i] == v1 && res[i + 1] == v2) ||
                (res[i] == v2 && res[i + 1] == v1)) {
                std::vector<int> res2;
                for (size_t j = i + 1; j < res.size(); ++j)
                    res2.push_back(res[j]);
                for (size_t j = 1; j <= i; ++j)
                    res2.push_back(res[j]);
                res = res2;
                break;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j])
                bad = true;
        }
    }

    if (!bad) {
        std::cout << "\nCykl Eulera:\t";
        for (int x : res)
            std::cout << x << " ";
        return true;
    }
    return false;
}




void Graph::components_r(int nr, int i, std::vector<std::list<Edge>> list, int* comp)
{
    int n = list[i].size();
    std::list<Edge>::iterator it = list[i].begin();
    for(int l = 0; l < n; l++)
    {
        // std::cout << *it << "\n";
        if(comp[(*it).destVertex] == -1)
        {
            comp[(*it).destVertex] = nr;
            Graph::components_r(nr, (*it).destVertex, list, comp);
        }
        std::advance(it, 1);
    }
}

bool Graph::hamiltonCycleFind(AdjacencyMatrix& adjacencyMatrix)
{
    int n = adjacencyMatrix.getMatrix().size();
    int path[n];
    for(int i = 0; i < n; i++)
        path[i] = -1;
    path[0] = 0;
    if(hamiltonCycle(adjacencyMatrix, path, 1) == false)
    {
        std::cout << "Cykl Hamiltona dla podanego grafu nie istnieje\n";
        return false;
    }
    std::cout << "Cykl Hamiltona dla podanego grafu:\n";
    for(int i = 0; i < n; i++)
        std::cout << path[i] << " ";
    std::cout << path[0] << "\n";
    return true;
}

bool Graph::hamiltonCycle(AdjacencyMatrix& adjacencyMatrix, int path[], int pos)
{
    int n = adjacencyMatrix.getMatrix().size();
    auto matrix = adjacencyMatrix.getMatrix();
    if(pos == n)
    {
        if(matrix[path[pos-1]][path[0]] == 1)
            return true;
        else
            return false;
    }

    for(int v = 1; v < n; v++)
    {
        bool vertex_can_be_add = true;
        if(matrix[path[pos-1]][v] == 0)
            vertex_can_be_add = false;
        for(int k = 0; k < pos; k++)
        {
            if(path[k] == v)
            {
                vertex_can_be_add = false;
                break;
            }
        }
        if(vertex_can_be_add)
        {
            path[pos] = v;
            if(hamiltonCycle(adjacencyMatrix, path, pos+1))
                return true;

            path[pos] = -1;
        }
    }

    return false;
}

AdjacencyList Graph::randomizeEdges(unsigned int howMany, const Graph& graph)
{
    srand(time(NULL));
    AdjacencyList adj = graph.convertToList();
    int firstEdge[2] = {-1, -1};
    int secondEdge[2] = {-1, -1};
    int safe = 0;
    bool reRoll = true;
    for(unsigned int i = 0; i < howMany; i++)
    {
        do
        {
            safe ++;
            reRoll = false;
            firstEdge[0] = rand() % adj.getVertexAmount();
            if(adj.isVertexIsolated(firstEdge[0]))
            {
                reRoll = true;
                continue;
            }
            int index = rand() % adj.dimOfVertex(firstEdge[0]);
            firstEdge[1] = adj.getVectorOfVerticesConnectedTo(firstEdge[0])[index];

            secondEdge[0] = rand() % adj.getVertexAmount();
            if(secondEdge[0] == firstEdge[0] || secondEdge[0] == firstEdge[1])
            {
                reRoll = true;
                continue;
            }
            if(adj.isVertexIsolated(secondEdge[0]))
            {
                reRoll = true;
                continue;
            }
            index = rand() % adj.dimOfVertex(secondEdge[0]);
            secondEdge[1] = adj.getVectorOfVerticesConnectedTo(secondEdge[0])[index];;
            if(secondEdge[1] == firstEdge[0] || secondEdge[1] == firstEdge[1])
            {
                reRoll = true;
                continue;
            }
            if(adj.doesEdgeExists(firstEdge[0], secondEdge[1]) ||
               adj.doesEdgeExists(secondEdge[0], firstEdge[1]) )
            {
                reRoll = true;
                continue;
            }
        }while(reRoll && safe < 10000);

        adj.removeEdge(firstEdge[0], firstEdge[1]);
        adj.removeEdge(secondEdge[0], secondEdge[1]);
        adj.addEdge(firstEdge[0], secondEdge[1], rand()%10 + 1);
        adj.addEdge(firstEdge[1], secondEdge[0], rand()%10 + 1);
    }
    return adj;
}

AdjacencyList Graph::generateKRegularGraph(const unsigned int n, const unsigned int k)
{
    if(((n*k)%2 == 1) || (k >= n) || (k < 0))
    {
        std::cout << "Nie da sie skonstruowac grafu " << k << "-regularnego o " << n << " wierzcholkach\n";
        return AdjacencyList();
    }
    std::vector<std::list<Edge>> list;
    list.resize(n);
    if(k == 0)
        return AdjacencyList(list);
    unsigned int i = 0;
    int generated_edges = 0;
    AdjacencyList adjacencyList(list);
    while((unsigned int)generated_edges != n*k)
    {
        generated_edges = 0;
        adjacencyList = AdjacencyList(list);
        for(i = 0; i < n; i++)
        {
            int it = 0;
            bool current_edges[n];
            for(unsigned int k = 0; k < n; k++)
            {
                current_edges[k] = false;
            }
            current_edges[i] = true;
            auto tmp = adjacencyList.getList();
            for(auto k : tmp[i])
            {
                current_edges[k.destVertex] = true;
            }
            while(tmp[i].size() != k && it < 10)
            {
                int random_vertex = i+rand()%(n-i)+1;
                if(current_edges[random_vertex] ==  false && tmp[random_vertex].size() < k)
                {
                    adjacencyList.addEdge(i, random_vertex);
                    generated_edges += 2;
                }    
                tmp = adjacencyList.getList();
                it++;
            }
            if(it == 10)
                i = n + it;

            if((unsigned int)generated_edges == n*k)
                break;
        }
    }
    AdjacencyList test(list);
    adjacencyList.print(std::cout);
    return AdjacencyList(adjacencyList.getList());
}


AdjacencyList Graph::createRandomWeightedConnectedGraph(int vertexNum, float edgeProbability)
{
    srand(time(NULL));
    AdjacencyList result;
    result.addVertex();
    for(int currSize = 1; currSize < vertexNum; currSize++)
    {
        result.addVertex();
        int solidEdgeDest = rand() % currSize;
        int weight = rand() % 10 + 1;
        result.addEdge(currSize, solidEdgeDest, weight);
        for(int vertex = 0; vertex < currSize; vertex++)
        {
            double test = rand() / (double)RAND_MAX;
            if(test < edgeProbability && vertex != solidEdgeDest && vertex != currSize)
            {
                weight = rand() % 10 + 1;
                result.addEdge(currSize, vertex, weight);
            }
        }
    }
    Graph * gr = &result;
    result = randomizeEdges((int)vertexNum/3, *gr);
    return AdjacencyList(result.getList());
}

void Graph::dijkstraInit(const Graph& graph, const int& beginningVertex, std::vector<int>& ds, std::vector<int>& ps)
{
    ds.clear();
    ps.clear();
    AdjacencyList tmp = graph.convertToList();
    for(int i = 0; i < tmp.getVertexAmount(); i++)
    {
        ds.push_back(std::numeric_limits<int>::max());
        ps.push_back(-1);
    }
    ds[beginningVertex] = 0;
}

void Graph::dijkstraRelax(std::vector<int>& ds, std::vector<int>& ps, const int& firstVertex, const int& secondVertex, const int& weight)
{
    if(ds[secondVertex] > ds[firstVertex] + weight)
    {
        ds[secondVertex] = ds[firstVertex] + weight;
        ps[secondVertex] = firstVertex;
    }
}

std::vector<int> Graph::dijkstraAlgorithm(const Graph& graph, const int& beginningVertex, const bool& wantToDisplay)
{
    std::vector<int> ds;
    std::vector<int> ps;
    std::vector<int> s;
    std::vector<int> result;
    result.resize(graph.getVertexAmount());
    Graph::dijkstraInit(graph, beginningVertex, ds, ps);
    std::vector<std::list<Edge>> list = graph.convertToList().getList();
    while((int)s.size() != graph.getVertexAmount())
    {
        int min = -1;
        while (std::find(s.begin(), s.end(), ++min) != s.end());
        for(int i = 0; i < (int)ds.size(); i++)
        {
            bool isVertexInS = std::find(s.begin(), s.end(), i) != s.end();
            if(!isVertexInS && ds[i] < ds[min])
                min = i;
        }
        s.push_back(min);
        for(auto edge : list[min])
        {
            Graph::dijkstraRelax(ds, ps, min, edge.destVertex, edge.weight);
        } 
        result[min] = ds[min];
    }
    if(wantToDisplay)
        for(int vert = 0; vert < graph.getVertexAmount(); vert++)
        {
            std::cout << "d(" << vert << ") = " << ds[vert] << " ==> [";   
            int trace = vert;
            while(ps[trace] != -1)
            {
                std::cout << trace << " <- ";
                trace = ps[trace];
            }
            std::cout << trace << "]\n";
        }
    return result;
}

AdjacencyList Graph::primsAlgorithm() const
{
    AdjacencyList graph = this->convertToList();

    AdjacencyList minimumSpanningTree;

    auto graphList = graph.getList();
    for (auto vertex : graphList)
        minimumSpanningTree.addVertex();

    auto edgesList = *graphList.begin();
    std::vector<int> T = {0};

    while (T.size() < graphList.size())
    {
        auto minWeight = std::min_element(edgesList.begin(), edgesList.end(),
                                          [](const Edge &e1, const Edge &e2) {
                                              return e1.weight < e2.weight;
                                          });

        minimumSpanningTree.addEdge(*minWeight);

        auto addedVertex = (*minWeight).destVertex;
        T.push_back(addedVertex);
        edgesList.insert(edgesList.end(), graphList[addedVertex].begin(), graphList[addedVertex].end());

        for (auto edge : graphList[addedVertex])
        {
            if (std::find(T.begin(), T.end(), edge.destVertex) != T.end())
            {
                edgesList.remove(edge);
                edgesList.remove(Edge(edge.destVertex, edge.srcVertex, edge.weight));
            }
        }
    }

    return minimumSpanningTree;
}

AdjacencyList Graph::createRandomDigraph(int vertexNum, float edgeProbability)
{
    srand(time(NULL));
    AdjacencyList result;
    for(int i = 0; i < vertexNum; i++)
        result.addVertex();
    for(int firstIndex = 0; firstIndex < vertexNum; firstIndex++)
    {
        for (int secondIndex = 0; secondIndex < vertexNum; secondIndex++)
        {
            double test = (double)rand() / RAND_MAX;
            if(test < edgeProbability && firstIndex != secondIndex)
            {
                result.addDirectedEdge(firstIndex, secondIndex, 1);
            }
        }
    }
    return result;

}


std::vector<int> Graph::kosarajuAlgorithm(const Graph& graph)
{
    AdjacencyList adjacencyList = graph.convertToList();
    int n = adjacencyList.getList().size();
    std::vector<int>  d(n);
    std::vector<int> f(n);
    for(int i = 0; i < n; i++)
    {
        d[i] = f[i] = -1;
    }
    int t = 0;

    for(int v = 0; v < n; v++)
    {
        if(d[v] == -1)
        {
            kosarajuDFS_visit(v, adjacencyList, d, f, t);
        }
    }

    AdjacencyList adjacencyListT = graph.convertToList();
    adjacencyListT.translate();
    
    
    int nr = 0;
    std::vector<int> comp(n);
    for(int i = 0; i < n; i++)
    {
        comp[i] = -1;
    }
    std::vector<int> f_sorted(n);
    for(int i = 0; i < n; i++)
    {
        f_sorted[i] = f[i];
    }
    std::sort(f_sorted.begin(), f_sorted.end(), std::greater<int>());
    for(int i = 0; i < n; i++)
    {
        int v = i;
        for(; v < n; v++)
        {
            if(f[v] == f_sorted[i])
                break;
        }
        f_sorted[i] = v;
    }


    for(int i = 0; i < n; i++)
    {
        int v = f_sorted[i];
        if(comp[v] == -1)
        {
            nr += 1;
            comp[v] = nr;
            kosarajuComponents_r(nr, v, adjacencyListT, comp);
        }
    }

    std::cout << "Graf:\n";
    adjacencyList.print(std::cout);
    std::cout << "\nSilnie spojne skladowe:\n";
    while(nr > 0)
    {
        std::cout << nr << ": ";
        for(int i = 0; i < n; i++)
        {
            if(comp[i] == nr)
                std::cout << i << " ";
        }
        std::cout << "\n";
        nr--;
    }
    return comp;
}



void Graph::kosarajuDFS_visit(int v, AdjacencyList& adjacencyList, std::vector<int>& d, std::vector<int>& f, int& t)
{
    t += 1;
    d[v] = t;
    std::list<Edge> edge = adjacencyList.getList()[v];
    for(Edge ed : edge)
    {
        int u = ed.destVertex;
        if(d[u] == -1)
        {
            kosarajuDFS_visit(u, adjacencyList, d, f, t);
        }
    }

    t += 1;
    f[v] = t;
}

void Graph::kosarajuComponents_r(int& nr, int& v, AdjacencyList& adjacencyListT, std::vector<int>& comp)
{
    std::list<Edge> edge = adjacencyListT.getList()[v];
    for(Edge ed : edge)
    {
        int u = ed.srcVertex;
        if(comp[u] == -1)
        {
            comp[u] = nr;
            kosarajuComponents_r(nr, u, adjacencyListT, comp);
        }
    }
}

