#include "headers/AdjacencyList.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

AdjacencyList::AdjacencyList(std::vector<std::list<int>> const &initializer) : list(initializer)
{
}

Graph &AdjacencyList::addVertex()
{
    std::list<int> newList;
    list.push_back(newList);

    return *this;
}
Graph &AdjacencyList::addVertex(unsigned int vertices)
{
    return Graph::addVertex(vertices);
}

Graph &AdjacencyList::addEdge(int firstVertex, int secondVertex)
{
    list[firstVertex].push_back(secondVertex);
    list[secondVertex].push_back(firstVertex);

    return *this;
}

AdjacencyList AdjacencyList::convertToList() const
{
    return *this;
};

Graph &AdjacencyList::convertFromList(AdjacencyList const &adjacencyList)
{
    list = adjacencyList.getList();
    return *this;
};

std::ostream &AdjacencyList::print(std::ostream &o) const
{
    const double radius = 10.;
    const int n = list.size();
    const double angleIncrement = 2. * M_PI / n;
    double x1, y1, x2, y2, angle = 0.;
    for (int i = 0; i < n; ++i)
    {
        x1 = radius * cos(angle);
        y1 = radius * sin(angle);
        
        if(!list[i].size())
        {
            o << x1 << '\t' << y1 << std::endl;
            o << x1 << '\t' << y1 << std::endl;
            o << std::endl;
        }

        for (auto edge : list[i])
        {
            x2 = radius * cos(angleIncrement * edge);
            y2 = radius * sin(angleIncrement * edge);
            o << x1 << '\t' << y1 << std::endl;
            o << x2 << '\t' << y2 << std::endl;
            o << std::endl;
        }
        angle += angleIncrement;
    }
    return o;
}

std::vector<std::list<int>> AdjacencyList::getList() const
{
    return list;
}
