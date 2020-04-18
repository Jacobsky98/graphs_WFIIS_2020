#ifndef ADJACENCY_LIST_HPP
#define ADJACENCY_LIST_HPP

#include "headers/Graph.hpp"
#include <vector>
#include <list>


class AdjacencyList : public Graph
{
public:
    AdjacencyList() = default;

    AdjacencyList(std::vector<std::list<int>> const &initializer);
    static AdjacencyList &loadFromFile(const std::string fileName);

    virtual Graph &addVertex() override;
    virtual Graph &addVertex(unsigned int vertices) override;

    virtual Graph &addEdge(int firstVertex, int secondVertex) override;

    virtual AdjacencyList convertToList() const override;

    virtual Graph &convertFromList(AdjacencyList const &adjacencyList) override;

    virtual std::ostream &print(std::ostream &o) const override;

    virtual std::ostream &printToFile(std::ostream &o) const override;

    std::vector<std::list<int>> getList() const;

private:
    std::vector<std::list<int>> list;
};

#endif