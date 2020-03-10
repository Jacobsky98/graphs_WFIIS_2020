#include "headers/Graph.hpp"
#include "headers/AdjacencyList.hpp"
#include "headers/AdjacencyMatrix.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h> 

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
