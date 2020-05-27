#ifndef ADJACENCY_LIST_HPP
#define ADJACENCY_LIST_HPP

#include "headers/Graph.hpp"
#include <vector>
#include <list>

class AdjacencyList : public Graph
{
public:
    AdjacencyList() = default;

    AdjacencyList(std::vector<std::list<Edge>> const &initializer);
    static AdjacencyList &loadFromFile(const std::string fileName);

    virtual Graph &addVertex() override;
    virtual Graph &addVertex(unsigned int vertices) override;

    virtual Graph &addEdge(int firstVertex, int secondVertex, int weight = 1) override;
    virtual Graph &addDirectedEdge(int firstVertex, int secondVertex, int weight = 1) override;
    Graph &setDirectedEdgeWeight(int firstVertex, int secondVertex, int weight);
    Graph &addEdge(const Edge &edge);
    virtual Graph &removeEdge(int firstVertex, int secondVertex) override;
    virtual Graph &removeDirectedEdge(int firstVertex, int secondVertex) override;
    virtual AdjacencyList convertToList() const override;

    virtual Graph &convertFromList(AdjacencyList const &adjacencyList) override;

    virtual std::ostream &print(std::ostream &o) const override;

    virtual std::ostream &printToFile(std::ostream &o) const override;
    virtual bool doesEdgeExists(int firstVertex, int secondVertex) const override;
    virtual bool isVertexIsolated(int vertex) const override;
    virtual int dimOfVertex(int vertex) const override;
    virtual std::vector<int> getVectorOfVerticesConnectedTo(int vertex) const override;
    virtual int getVertexAmount() const override;
    std::vector<std::list<Edge>> getList() const;
    Edge getEdge(int firstVertex, int secondVertex) const;
    virtual bool isDirectedGraph() const override;
    void removeVertex(int vertex);


	  void translate();


private:
    std::vector<std::list<Edge>> list;
};

#endif
