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
    static IncidenceMatrix &loadFromFile(const std::string fileName);

    virtual Graph &addVertex() override;

    virtual Graph &addDirectedEdge(int firstVertex, int secondVertex, int weight) override;

    virtual Graph &addEdge(int firstVertex, int secondVertex, int weight) override;

    virtual Graph &removeEdge(int firstVertex, int secondVertex) override;
    virtual Graph &removeDirectedEdge(int firstVertex, int secondVertex) override;
    virtual AdjacencyList convertToList() const override;

    virtual Graph &convertFromList(AdjacencyList const &adjacencyList) override;

    virtual std::ostream &print(std::ostream &o) const override;

    virtual std::ostream &printToFile(std::ostream &o) const override;

    virtual bool doesEdgeExists(int firstVertex, int secondVertex) const override;
    
    virtual bool isVertexIsolated(int vertex) const override;
    
    virtual int dimOfVertex(int vertex)const override;
    
    virtual std::vector<int> getVectorOfVerticesConnectedTo(int vertex) const override;
    
    virtual int getVertexAmount() const override;
private:
    std::vector<std::vector<int>> matrix;

    /**
     * Ilosc wierzcholkow
    */
    int _n = 0;
};

#endif
