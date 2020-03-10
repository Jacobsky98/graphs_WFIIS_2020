#ifndef ADJACENCY_MATRIX_HPP
#define ADJACENCY_MATRIX_HPP

#include "headers/Graph.hpp"
#include "headers/AdjacencyList.hpp"
#include <vector>

class AdjacencyMatrix : public Graph
{
public:
    AdjacencyMatrix() = default;

    AdjacencyMatrix(std::vector<std::vector<int>> const &initializer);

    virtual Graph &addVertex() override;
    virtual Graph &addVertex(unsigned int vertices) override;

    virtual Graph &addEdge(int firstVertex, int secondVertex) override;

    virtual AdjacencyList convertToList() const override;

    virtual Graph &convertFromList(AdjacencyList const &adjacencyList) override;

    virtual std::ostream &print(std::ostream &o) const override;

    std::vector<std::vector<int>> getMatrix() const;

private:
    std::vector<std::vector<int>> matrix;
};

#endif
