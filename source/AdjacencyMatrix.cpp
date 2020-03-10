#include "headers/AdjacencyMatrix.hpp"
#include <vector>

AdjacencyMatrix::AdjacencyMatrix(std::vector<std::vector<int>> const &initializer) : matrix(initializer)
{
}

Graph &AdjacencyMatrix::addVertex()
{
    for (unsigned int i = 0; i < matrix.size(); ++i)
        matrix[i].push_back(0);

    std::vector<int> lastColumn(matrix.size() + 1, 0);
    matrix.push_back(lastColumn);

    return *this;
}
Graph &AdjacencyMatrix::addVertex(unsigned int vertices)
{
    return Graph::addVertex(vertices);
}

Graph &AdjacencyMatrix::addEdge(int firstVertex, int secondVertex)
{
    matrix[firstVertex][secondVertex] = 1;
    matrix[secondVertex][firstVertex] = 1;

    return *this;
}

AdjacencyList AdjacencyMatrix::convertToList() const
{
    const int n = matrix.size();
    std::vector<std::list<int>> list(n);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (matrix[i][j] > 0)
                list[i].push_back(j);

    return AdjacencyList(list);
};

Graph &AdjacencyMatrix::convertFromList(AdjacencyList const &adjacencyList)
{
    auto list = adjacencyList.getList();
    const int n = list.size();
    matrix.clear();

    for (int i = 0; i < n; ++i)
    {
        std::vector<int> column(n);
        for (auto edge : list[i])
        {
            column[edge] = 1;
        }
        matrix.push_back(column);
    }
    return *this;
};

std::ostream &AdjacencyMatrix::print(std::ostream &o) const
{
    return convertToList().print(o);
}

std::vector<std::vector<int>> AdjacencyMatrix::getMatrix() const
{
    return matrix;
}
