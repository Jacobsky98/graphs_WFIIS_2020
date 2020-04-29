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

void Graph::largestComponent(AdjacencyMatrix adjacencyMatrix)
{
    int current_max = INT32_MIN;
    int current_count[1] = {0};

    std::vector<std::vector<int>> matrix = adjacencyMatrix.getMatrix();
    int n = matrix.size();
    int m = matrix[0].size();
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            int visited[n][m] = {0};
            *current_count = 0;

            if(j+1 < m)
            {
                //Graph::breadthFirstSearch([i][j], matrix[i][j+1], i, j, matrix, visited, current_count);
            
                
            }
        }
    }

}

void breadthFirstSearch(int x, int y, int i, int j, std::vector<std::vector<int>> matrix, int** visited, int* current_count)
{
    if (x != y) 
        return; 
  
    visited[i][j] = 1; 
    *current_count++; 
  
    // x_move and y_move arrays 
    // are the possible movements 
    // in x or y direction 
    int x_move[] = { 0, 0, 1, -1 }; 
    int y_move[] = { 1, -1, 0, 0 }; 
  
    // checks all four points connected with input[i][j] 
    // for (int u = 0; u < 4; u++) 
    //     if (is_valid(i + y_move[u], j + x_move[u], x, input)) 
    //         BFS(x, y, i + y_move[u], j + x_move[u], input); 
}


AdjacencyList Graph::randomizeEdges(unsigned int howMany, const Graph& graph)
{
    srand(time(NULL));
    AdjacencyList adj = graph.convertToList();

    int firstEdge[2] = {-1, -1};
    int secondEdge[2] = {-1, -1};

    bool reRoll = true;
    for(int i = 0; i < howMany; i++)
    {
        auto list = adj.getList();
        while(reRoll)
        {
            reRoll = false;
            firstEdge[0] = rand() % list.size();
            if(list[firstEdge[0]].size() == 0)
            {
                reRoll = true;
                continue;
            }
            int index = rand() % list[firstEdge[0]].size();
            auto it = std::next(list[firstEdge[0]].begin(), index);
            firstEdge[1] = *it;
        }
        do
        {
            reRoll = false;
            secondEdge[0] = rand() % list.size();
            if(secondEdge[0] == firstEdge[0] || secondEdge[0] == firstEdge[1])
            {
                reRoll = true;
                continue;
            }
            int index = rand() % list[secondEdge[0]].size();
            auto it = std::next(list[secondEdge[0]].begin(), index);
            secondEdge[1] = *it;
            if(secondEdge[1] == firstEdge[0] || secondEdge[1] == firstEdge[1])
            {
                reRoll = true;
                continue;
            }
        }while(reRoll);

        adj.removeEdge(firstEdge[0], firstEdge[1]);
        adj.removeEdge(secondEdge[0], secondEdge[1]);
        adj.addEdge(firstEdge[0], secondEdge[1]);
        adj.addEdge(firstEdge[1], secondEdge[0]);
    }
    return adj;
}