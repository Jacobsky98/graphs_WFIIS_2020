#include "headers/AdjacencyList.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

AdjacencyList::AdjacencyList(std::vector<std::list<int>> const &initializer) : list(initializer)
{}

AdjacencyList &AdjacencyList::loadFromFile(const std::string fileName)
{
    AdjacencyList *adjacencyList = new AdjacencyList();
    std::fstream file(fileName);
    adjacencyList->list.clear();
    int i = 0;
    std::string str;
    while(getline(file, str))
    {
        adjacencyList->list.push_back(std::list<int>());
        std::istringstream line(str);
        int variable;
        while(line >> variable)
        {
            adjacencyList->list[i].push_back(variable);
        }
        i++;
    }
    return *adjacencyList;
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
    list[firstVertex].sort();
    list[secondVertex].sort();
    list[firstVertex].unique();
    list[secondVertex].unique();

    return *this;
}

Graph &AdjacencyList::removeEdge(int firstVertex, int secondVertex)
{
    list[firstVertex].remove(secondVertex);
    list[secondVertex].remove(firstVertex);
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
    for(int i = 0; i < (int)list.size(); i++)
    {
        o << i << ".\t";
        for(auto const& node: list[i])
        {
            o << node << "\t";
        }
        o << "\n";
    }
    return o;   
}

std::ostream &AdjacencyList::printToFile(std::ostream &o) const
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

bool AdjacencyList::doesEdgeExists(int firstVertex, int secondVertex) const
{
    bool result = false;
    for(auto connection:list[firstVertex])
    {
        if(connection == secondVertex)
        {
            result = true;
            break;
        }
    }
    return result;
}

bool AdjacencyList::isVertexIsolated(int vertex) const
{
    if(dimOfVertex(vertex) == 0)
        return true;
    else
        return false;
}

int AdjacencyList::dimOfVertex(int vertex) const
{
    return list[vertex].size();
}

std::vector<int> AdjacencyList::getVectorOfVerticesConnectedTo(int vertex) const
{
    std::vector<int> result;
    for(auto vertex: list[vertex])
    {
        result.push_back(vertex);
    }
    return result;
}

int AdjacencyList::getVertexAmount() const
{
    return list.size();
}