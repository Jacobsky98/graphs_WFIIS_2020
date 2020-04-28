#ifndef INCIDENCE_MATRIX_HPP
#define INCIDENCE_MATRIX_HPP

#include "headers/Graph.hpp"
#include "headers/AdjacencyList.hpp"
#include <vector>


class IncidenceMatrix : public Graph
{
public:
    IncidenceMatrix() = default;

    IncidenceMatrix(std::vector<std::vector<int>> const &initializer);
    IncidenceMatrix &loadFromFile(const std::string fileName);

    virtual Graph &addVertex() override;

    virtual Graph &addEdge(int firstVertex, int secondVertex) override;

    virtual AdjacencyList convertToList() const override;

    virtual Graph &convertFromList(AdjacencyList const &adjacencyList) override;

    virtual std::ostream &print(std::ostream &o) const override;

    virtual std::ostream &printToFile(std::ostream &o) const override;

private:
    std::vector<std::vector<int>> matrix;

    /**
     * Ilosc wierzcholkow
    */
    int _n = 0;
};

#endif
