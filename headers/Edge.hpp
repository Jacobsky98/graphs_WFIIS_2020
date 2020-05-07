#ifndef EDGE_HPP
#define EDGE_HPP
class Edge
{
public:
	Edge(int srcVertex, int destVertex, int weight = 0);
	~Edge() = default;
	int srcVertex;
	int destVertex;
	int weight;
	bool operator==(const Edge &rha)
	{
		return this->destVertex == rha.destVertex;
	}
};
#endif