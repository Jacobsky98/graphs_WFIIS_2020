#ifndef ADJACENCY_MATRIX_HPP
#define ADJACENCY_MATRIX_HPP

#include "headers/Graph.hpp"
#include "headers/AdjacencyList.hpp"
#include <vector>
#include <cmath>

class AdjacencyMatrix : public Graph
{
public:
    AdjacencyMatrix() = default;

/*
* Allows doing:
*
*    AdjacencyMatrix adjacencyMatrix(
*        0, 1, 0, 0, 1, 1,
*        1, 0, 1, 1, 0, 0,
*        0, 1, 0, 0, 0, 1,
*        0, 1, 0, 0, 0, 1,
*        1, 0, 0, 0, 0, 0,
*        1, 0, 1, 1, 0, 0);
*/
    template<class... Args>
    AdjacencyMatrix(Args... args);
    static AdjacencyMatrix &loadFromFile(const std::string fileName);
    
    virtual Graph &addVertex() override;
    virtual Graph &addVertex(unsigned int vertices) override;

    virtual Graph &addEdge(int firstVertex, int secondVertex) override;

    virtual AdjacencyList convertToList() const override;

    virtual Graph &convertFromList(AdjacencyList const &adjacencyList) override;

    virtual std::ostream &print(std::ostream &o) const override;

    virtual std::ostream &printToFile(std::ostream &o) const override;

    std::vector<std::vector<int>> getMatrix() const;

private:
    std::vector<std::vector<int>> matrix;
    void vectorToMatrix(std::vector<int> vec, int rowsize);
};

template<class... Args>
AdjacencyMatrix::AdjacencyMatrix(Args... args)
{
    std::vector<int> tmpData = {args...};
    vectorToMatrix(tmpData, sqrt(sizeof...(args)));
}

#endif
