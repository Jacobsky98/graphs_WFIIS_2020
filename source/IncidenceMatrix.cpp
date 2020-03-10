#include "headers/IncidenceMatrix.hpp"

IncidenceMatrix::IncidenceMatrix(std::vector<std::vector<int>> const &initializer) : matrix(initializer)
{
}

Graph &IncidenceMatrix::addVertex()
{
    _n++;
    for (unsigned int i = 0; i < matrix.size(); ++i)
        matrix[i].push_back(0);

    return *this;
}

Graph &IncidenceMatrix::addEdge(int firstVertex, int secondVertex)
{
    std::vector<int> newColumn(_n);

    newColumn[firstVertex] = 1;
    newColumn[secondVertex] = 1;

    matrix.push_back(newColumn);

    return *this;
}

AdjacencyList IncidenceMatrix::convertToList() const
{
    const int numberOfEdges = matrix.size();
    std::vector<std::list<int>> list(_n);

    int first, second;
    for (int i = 0; i < numberOfEdges; ++i)
    {
        first = -1;
        second = -1;
        for (int j = 0; j < _n; ++j)
            if (matrix[i][j] > 0 && first < 0)
                first = j;
            else if (matrix[i][j] > 0 && second < 0) {
                second = j;
        
                //zaklada ze graf jest prosty
                list[first].push_back(second);
                list[second].push_back(first);
                break;
            }
    }

    return AdjacencyList(list);
};

Graph &IncidenceMatrix::convertFromList(AdjacencyList const &adjacencyList)
{
    auto list = adjacencyList.getList();
    _n = list.size();
    matrix.clear();

    for (int i = 0; i < _n; ++i)
    {

        for (auto edge : list[i])
        {
            std::vector<int> column(_n);
            column[i] = 1;
            column[edge] = 1;
            matrix.push_back(column);
            for (auto it = list[edge].begin(); it != list[edge].end(); ++it)
            {
                if (*it == i)
                {
                    list[edge].erase(it);
                    break;
                }
            }
        }
    }
    return *this;
};

std::ostream &IncidenceMatrix::print(std::ostream &o) const
{
    return convertToList().print(o);
}
