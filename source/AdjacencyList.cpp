#include "headers/AdjacencyList.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

AdjacencyList::AdjacencyList(std::vector<std::list<Edge>> const &initializer) : list(initializer)
{
}

AdjacencyList &AdjacencyList::loadFromFile(const std::string fileName)
{
    AdjacencyList *adjacencyList = new AdjacencyList();
    std::fstream file(fileName);
    adjacencyList->list.clear();
    int i = 0;
    std::string str;
    while (getline(file, str))
    {
        adjacencyList->list.push_back(std::list<Edge>());
        std::istringstream line(str);
        int variable;
        while (line >> variable)
        {
            adjacencyList->list[i].push_back(Edge(i, variable, 1));
        }
        i++;
    }
    return *adjacencyList;
}

Graph &AdjacencyList::addVertex()
{
    std::list<Edge> newList;
    list.push_back(newList);

    return *this;
}
Graph &AdjacencyList::addVertex(unsigned int vertices)
{
    return Graph::addVertex(vertices);
}

Graph &AdjacencyList::addEdge(int firstVertex, int secondVertex, int weight)
{
    addDirectedEdge(firstVertex, secondVertex, weight);
    addDirectedEdge(secondVertex, firstVertex, weight);
    return *this;
}

Graph &AdjacencyList::addDirectedEdge(int firstVertex, int secondVertex, int weight)
{
    auto comperator = [](const Edge &edge1, const Edge &edge2) {
        return edge1.destVertex < edge2.destVertex;
    };

    if (doesEdgeExists(firstVertex, secondVertex))
        return *this;
    else
    {
        list[firstVertex].push_back(Edge(firstVertex, secondVertex, weight));
    }
    list[firstVertex].sort(comperator);
    return *this;
}

Graph &AdjacencyList::addEdge(const Edge &edge)
{
    return addEdge(edge.srcVertex, edge.destVertex, edge.weight);
}

Graph &AdjacencyList::removeEdge(int firstVertex, int secondVertex)
{
    list[firstVertex].remove(Edge(firstVertex, secondVertex));
    list[secondVertex].remove(Edge(secondVertex, firstVertex));
    return *this;
}

Graph &AdjacencyList::removeDirectedEdge(int firstVertex, int secondVertex)
{
    list[firstVertex].remove(Edge(firstVertex, secondVertex));
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
    for (int i = 0; i < (int)list.size(); i++)
    {
        o << i << ".\t";
        for (auto const &node : list[i])
        {
            o << node.destVertex << " (" << node.weight << ")"
              << "\t";
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

        if (!list[i].size())
        {
            o << x1 << '\t' << y1 << std::endl;
            o << x1 << '\t' << y1 << std::endl;
            o << std::endl;
        }

        for (auto edge : list[i])
        {
            x2 = radius * cos(angleIncrement * edge.destVertex);
            y2 = radius * sin(angleIncrement * edge.destVertex);
            o << x1 << '\t' << y1 << std::endl;
            o << x2 << '\t' << y2 << std::endl;
            o << std::endl;
        }
        angle += angleIncrement;
    }
    return o;
}

std::vector<std::list<Edge>> AdjacencyList::getList() const
{
    return list;
}

bool AdjacencyList::doesEdgeExists(int firstVertex, int secondVertex) const
{
    bool result = false;
    for (auto connection : list[firstVertex])
    {
        if (connection.destVertex == secondVertex)
        {
            result = true;
            break;
        }
    }
    return result;
}

bool AdjacencyList::isVertexIsolated(int vertex) const
{
    if (dimOfVertex(vertex) == 0)
        return true;
    else
        return false;
}

int AdjacencyList::dimOfVertex(int vertex) const
{
    if(isDirectedGraph())
    {
        int result = 0;
        for (int i = 0; i < (int)list.size(); i++)
        {
            for (Edge edge : list[i])
            {
                if(i == vertex || edge.destVertex == vertex)
                    result++;
            }
        }
        return result;
    }
    else
        return list[vertex].size();
}

std::vector<int> AdjacencyList::getVectorOfVerticesConnectedTo(int vertex) const
{
    std::vector<int> result;
    for (auto ver : list[vertex])
    {
        int tmp = ver.destVertex;
        result.push_back(tmp);
    }
    return result;
}

int AdjacencyList::getVertexAmount() const
{
    return list.size();
}

bool AdjacencyList::isDirectedGraph() const
{
    for (int i = 0; i < (int)list.size(); i++)
    {
        for (Edge edge : list[i])
        {
            if(doesEdgeExists(i, edge.destVertex) && !doesEdgeExists(edge.destVertex, i))
                return true;
        }
    }
    return false;
}

void AdjacencyList::translate()
{
    for(unsigned int i = 0; i < list.size(); i++)
        for(Edge& edge : list[i])
            edge.translate();
}