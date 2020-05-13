#include "headers/IncidenceMatrix.hpp"

IncidenceMatrix::IncidenceMatrix(std::vector<std::vector<int>> const &initializer) : matrix(initializer)
{
    if (initializer.size() > 0)
        _n = initializer[0].size();
    else
        _n = 0;
}

IncidenceMatrix &IncidenceMatrix::loadFromFile(const std::string fileName)
{

    IncidenceMatrix *incidenceMatrix = new IncidenceMatrix();
    std::fstream file(fileName);
    incidenceMatrix->matrix.clear();
    std::string str;
    int i = 0;
    while (getline(file, str))
    {
        incidenceMatrix->matrix.push_back(std::vector<int>());
        std::istringstream line(str);
        int variable;
        while (line >> variable)
        {
            incidenceMatrix->matrix[i].push_back(variable);
        }
        i++;
    }
    incidenceMatrix->_n = incidenceMatrix->matrix.size();
    return *incidenceMatrix;
}

Graph &IncidenceMatrix::addVertex()
{
    _n++;
    std::vector<int> newRow;
    newRow.resize(matrix[0].size());
    matrix.push_back(newRow);

    return *this;
}

Graph &IncidenceMatrix::addEdge(int firstVertex, int secondVertex, int weight)
{
    if (!doesEdgeExists(firstVertex, secondVertex))
    {
        for (int row = 0; row < _n; ++row)
        {
            if (row == firstVertex || row == secondVertex)
                matrix[row].push_back(weight);
            else
                matrix[row].push_back(0);
        }
    }
    return *this;
}

Graph &IncidenceMatrix::addDirectedEdge(int firstVertex, int secondVertex, int weight)
{
    if (!doesEdgeExists(firstVertex, secondVertex))
    {
        for (int row = 0; row < _n; ++row)
        {
            if (row == firstVertex)
                matrix[row].push_back(-1*weight);
            else if(row == secondVertex)
                matrix[row].push_back(weight);
            else
                matrix[row].push_back(0);
        }
    }
    return *this;
}

Graph &IncidenceMatrix::removeEdge(int firstVertex, int secondVertex)
{
    for (long unsigned int column = 0; column < matrix[0].size(); column++)
    {
        if (matrix[firstVertex][column] != 0 && matrix[secondVertex][column] > 0)
        {
            for (int row = 0; row < _n; row++)
                matrix[row].erase(matrix[row].begin() + column);
            break;
        }
    }
    return *this;
}

Graph &IncidenceMatrix::removeDirectedEdge(int firstVertex, int secondVertex)
{
    removeEdge(firstVertex, secondVertex);
    return *this;
}

AdjacencyList IncidenceMatrix::convertToList() const
{
    auto comperator = [](const Edge &edge1, const Edge &edge2) {
        return edge1.destVertex < edge2.destVertex;
    };
    const int numberOfEdges = matrix[0].size();
    std::vector<std::list<Edge>> list(_n);
    int first, second;
    for (int column = 0; column < numberOfEdges; ++column)
    {
        first = 0;
        second = 0;
        for (int row = 0; row < _n; ++row)
        {
            if (matrix[row][column] > 0 && first != 0)
                first = row;
            else if (matrix[row][column] > 0 && second != 0)
            {
                second = row;

                //zaklada ze graf jest prosty
                if(first > 0 && second > 0)
                {
                    list[first].push_back(Edge(first, second, matrix[row][column]));
                    list[second].push_back(Edge(second, first, matrix[row][column]));
                    list[first].sort(comperator);
                    list[second].sort(comperator);
                }
                else if(first < 0)
                {
                    list[first].push_back(Edge(first, second, matrix[row][column]));
                    list[first].sort(comperator);
                }
                else
                {
                    list[second].push_back(Edge(second, first, matrix[row][column]));
                    list[second].sort(comperator);
                }
                break;
            }
        }
    }

    return AdjacencyList(list);
};

Graph &IncidenceMatrix::convertFromList(AdjacencyList const &adjacencyList)
{
    auto list = adjacencyList.getList();
    _n = list.size();
    matrix.clear();
    matrix.resize(_n);
    for (int first = 0; first < _n; first++)
    {
        for (Edge second : list[first])
        {
            if(adjacencyList.isDirectedGraph())
                addDirectedEdge(first, second.destVertex, second.weight);
            else
                addEdge(first, second.destVertex, second.weight);
        }
    }
    return *this;
};

std::ostream &IncidenceMatrix::print(std::ostream &o) const
{
    for (int i = 0; i < (int)matrix.size(); i++)
    {
        for (int j = 0; j < (int)matrix[i].size(); j++)
            o << matrix[i][j] << "\t";
        o << "\n";
    }
    return o;
}

std::ostream &IncidenceMatrix::printToFile(std::ostream &o) const
{
    return convertToList().printToFile(o);
}

bool IncidenceMatrix::doesEdgeExists(int firstVertex, int secondVertex) const
{
    for (long unsigned int column = 0; column < matrix[0].size(); column++)
    {
        if (matrix[firstVertex][column] != 0 && matrix[secondVertex][column] > 0)
            return true;
    }
    return false;
}

bool IncidenceMatrix::isVertexIsolated(int vertex) const
{
    if (dimOfVertex(vertex) == 0)
        return true;
    else
        return false;
}

int IncidenceMatrix::dimOfVertex(int vertex) const
{
    int result = 0;
    for (long unsigned int column = 0; column < matrix[0].size(); column++)
    {
        if (matrix[vertex][column] != 0)
            result += 1;
    }
    return result;
}

std::vector<int> IncidenceMatrix::getVectorOfVerticesConnectedTo(int vertex) const
{
    std::vector<int> result;
    for (int vertexToCheck = 0; vertexToCheck < _n; vertexToCheck++)
    {
        if (vertex != vertexToCheck && doesEdgeExists(vertex, vertexToCheck))
            result.push_back(vertexToCheck);
    }
    return result;
}

int IncidenceMatrix::getVertexAmount() const
{
    return _n;
}

bool IncidenceMatrix::isDirectedGraph() const
{
    for(int column = 0; column < (int)matrix[0].size(); column++)
    {
        for(int row = 0; row < _n; row ++)
        {
            if(matrix[row][column] < 0)
                return true;
        }
    }
    return false;
}