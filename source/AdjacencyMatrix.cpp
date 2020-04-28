#include "headers/AdjacencyMatrix.hpp"
#include <vector>
#include <cmath>


AdjacencyMatrix::AdjacencyMatrix(std::vector<std::vector<int>> matrix)
{
    this->matrix = matrix;
}

AdjacencyMatrix &AdjacencyMatrix::loadFromFile(const std::string fileName)
{
    AdjacencyMatrix *adjacencyMatrix = new AdjacencyMatrix();
    std::fstream file(fileName);
    std::vector<int> data;
    int variable;
    while(file >> variable)
    {
        data.push_back(variable);
    }
    adjacencyMatrix->vectorToMatrix(data, sqrt(data.size()));
    return *adjacencyMatrix;
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
    for(int i = 0; i < (int)matrix.size(); i++)
    {
        for(int j = 0; j < (int)matrix[i].size(); j++)
            o << matrix[i][j] << "\t";
        o << "\n";
    }
    return o;
}

std::ostream &AdjacencyMatrix::printToFile(std::ostream &o) const
{
    return convertToList().printToFile(o);
}

std::vector<std::vector<int>> AdjacencyMatrix::getMatrix() const
{
    return matrix;
}

void AdjacencyMatrix::vectorToMatrix(std::vector<int> vec, int rowsize)
{
    matrix = std::vector<std::vector<int>> (rowsize, std::vector<int>(rowsize));
    for(int i = 0; i < rowsize; i++)
    {
        for(int j = 0; j < rowsize; j++)
        {
            matrix[i][j] = vec[j + i * rowsize];
        }
    }
}