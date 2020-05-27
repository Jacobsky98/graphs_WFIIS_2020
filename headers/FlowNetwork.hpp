
#pragma once
#include "headers/AdjacencyList.hpp"

class FlowNetwork
{
public:
	FlowNetwork(int layersAmount);
	void addLayer();
	void addNodeToLastLayer(int amount = 1);
	int indexOf(int layerNum, int nodeNum);
	void addEdgeBetween(int layerNumber1, int nodeInLayer1, int layerNumber2, int nodeInLayer2);
	void print();
	std::ostream& printToFile(std::ostream& o) ;
	FlowNetwork fordFulkersonAlgorithm() const;

private:
	int _layersAmount;
	std::vector<int> _numberOfNodesInLayer;
	AdjacencyList _network;
	void _addBeginningEdges();
	void _addEvenMoreEdges();

};
