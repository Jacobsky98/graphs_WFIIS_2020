#include "headers/FlowNetwork.hpp"
#include <numeric>
#include <time.h>
#include <math.h>

FlowNetwork::FlowNetwork(int layersAmount)
:_layersAmount(0)
{
	srand(time(NULL));
	addLayer();
	addNodeToLastLayer();//source
	for(int layer = 1; layer <= layersAmount; layer++)
	{
		addLayer();
		int howManyToAdd = layersAmount <= 2 ? layersAmount : rand() % (layersAmount - 1) + 2;
		addNodeToLastLayer(howManyToAdd);
	}
	addLayer();
	addNodeToLastLayer();
	_addBeginningEdges();
	_addEvenMoreEdges();
}

void FlowNetwork::addLayer()
{
	_numberOfNodesInLayer.push_back(0);
	_layersAmount++;
}

void FlowNetwork::addNodeToLastLayer(int amount)
{
	_numberOfNodesInLayer[_layersAmount-1] += amount;
	for(int node = 0; node < amount; node++)
		_network.addVertex();
}

void FlowNetwork::addEdgeBetween(int layerNumber1, int nodeInLayer1, int layerNumber2, int nodeInLayer2)
{
	if(indexOf(layerNumber1, nodeInLayer1) == indexOf(_layersAmount - 1, 0) || indexOf(layerNumber2, nodeInLayer2) == indexOf(0,0))
		throw "Tried to add wrong edge";
	_network.addDirectedEdge(indexOf(layerNumber1, nodeInLayer1), indexOf(layerNumber2, nodeInLayer2), rand()%10 + 1);
}

int FlowNetwork::indexOf(int layerNum, int nodeNum) const
{
	int sum = 0;
	for(int layer = 0; layer < layerNum; layer++)
		sum += _numberOfNodesInLayer[layer];
	return sum + nodeNum;
}

void FlowNetwork::_addBeginningEdges()
{
	for(int layer = 0; layer < _layersAmount-1; layer++)
	{
		std::vector<int> nodesInNextLayer;
		std::vector<int> nodesInCurrentLayer;
		for(int nodeIndex = 0; nodeIndex < _numberOfNodesInLayer[layer]; nodeIndex++)
			nodesInCurrentLayer.push_back(nodeIndex);
		for(int nodeIndex = 0; nodeIndex < _numberOfNodesInLayer[layer+1]; nodeIndex++)
			nodesInNextLayer.push_back(nodeIndex);
		while(nodesInNextLayer.size() || nodesInCurrentLayer.size())
		{
			int targetNode;
			int sourceNode;

			if(nodesInCurrentLayer.size())
			{
				int sourceNodeIndex = rand() % nodesInCurrentLayer.size();
				sourceNode = nodesInCurrentLayer[sourceNodeIndex];
				nodesInCurrentLayer.erase(nodesInCurrentLayer.begin() + sourceNodeIndex);
			}
			else
				sourceNode = rand() % _numberOfNodesInLayer[layer];

			if(nodesInNextLayer.size())
			{
				int targetNodeIndex = rand() % nodesInNextLayer.size();
				targetNode = nodesInNextLayer[targetNodeIndex];
				nodesInNextLayer.erase(nodesInNextLayer.begin() + targetNodeIndex);
			}
			else
				targetNode = rand() % _numberOfNodesInLayer[layer+1];
			 
			addEdgeBetween(layer, sourceNode, layer + 1, targetNode);
		}
		
	}
}

void FlowNetwork::print()
{
	for(int layer = 0; layer < _layersAmount; layer++)
	{
		std::cout << "In layer " << layer << " there is " << _numberOfNodesInLayer[layer] << " nodes" << std::endl;
	}
	_network.print(std::cout);
}

std::ostream& FlowNetwork::printToFile(std::ostream& o) const
{
	int maxNodesInLayer = 0;
	for(int i : _numberOfNodesInLayer)
		if(i > maxNodesInLayer)
			maxNodesInLayer = i;
	o << "maxNodesLayer:" << maxNodesInLayer << "\n";
	o << "layers:" << _numberOfNodesInLayer.size() << "\n";
	
	auto list = _network.getList();
	bool nodeWrited[list.size()];
	for(unsigned int layer = 0; layer < _numberOfNodesInLayer.size(); layer++)
	{
		o << "layer:" << layer << "_" << _numberOfNodesInLayer[layer] <<"\n";//, nodes: " << _numberOfNodesInLayer[layer] << std::endl;
		for(int nodeNum = 0; nodeNum < _numberOfNodesInLayer[layer]; nodeNum++)
		{
			auto edge = list[indexOf(layer, nodeNum)];
			for(Edge e : edge)
			{
				nodeWrited[e.srcVertex] = true;
				o << e.srcVertex << ":" << e.destVertex << "\n";
			}
		}
	}

	for(unsigned int i = 0; i < list.size(); i++)
	{
		if(nodeWrited[i] == false)
			o << i << ":\n";
	}


	return o;
}

void FlowNetwork::_addEvenMoreEdges()
{
	int toAdd = (_layersAmount-2) * 2;
	while(toAdd)
	{
		int sourceNode = rand() % (_network.getVertexAmount() - 1);
		int destNode = rand() % (_network.getVertexAmount() - 1) + 1;
		if(!(_network.doesEdgeExists(sourceNode, destNode) || _network.doesEdgeExists(destNode, sourceNode)))
		{
			_network.addDirectedEdge(sourceNode, destNode, rand()%10 + 1);
			toAdd--;
		}
	}
}