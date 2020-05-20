
#include "headers/FlowNetwork.hpp"
#include <numeric>
#include <time.h>
#include <algorithm>
#include <queue>
#define INF 214748364

FlowNetwork::FlowNetwork(int layersAmount)
	: _layersAmount(0)
{
	addLayer();
	addNodeToLastLayer(); //source
	for (int layer = 1; layer <= layersAmount; layer++)
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
	_numberOfNodesInLayer[_layersAmount - 1] += amount;
	for (int node = 0; node < amount; node++)
		_network.addVertex();
}

void FlowNetwork::addEdgeBetween(int layerNumber1, int nodeInLayer1, int layerNumber2, int nodeInLayer2)
{
	if (indexOf(layerNumber1, nodeInLayer1) == indexOf(_layersAmount - 1, 0) || indexOf(layerNumber2, nodeInLayer2) == indexOf(0, 0))
		throw "Tried to add wrong edge";
	_network.addDirectedEdge(indexOf(layerNumber1, nodeInLayer1), indexOf(layerNumber2, nodeInLayer2), rand() % 10 + 1);
}

int FlowNetwork::indexOf(int layerNum, int nodeNum)
{
	int sum = 0;
	for (int layer = 0; layer < layerNum; layer++)
		sum += _numberOfNodesInLayer[layer];
	return sum + nodeNum;
}

void FlowNetwork::_addBeginningEdges()
{
	for (int layer = 0; layer < _layersAmount - 1; layer++)
	{
		std::vector<int> nodesInNextLayer;
		std::vector<int> nodesInCurrentLayer;
		for (int nodeIndex = 0; nodeIndex < _numberOfNodesInLayer[layer]; nodeIndex++)
			nodesInCurrentLayer.push_back(nodeIndex);
		for (int nodeIndex = 0; nodeIndex < _numberOfNodesInLayer[layer + 1]; nodeIndex++)
			nodesInNextLayer.push_back(nodeIndex);
		while (nodesInNextLayer.size() || nodesInCurrentLayer.size())
		{
			int targetNode;
			int sourceNode;

			if (nodesInCurrentLayer.size())
			{
				int sourceNodeIndex = rand() % nodesInCurrentLayer.size();
				sourceNode = nodesInCurrentLayer[sourceNodeIndex];
				nodesInCurrentLayer.erase(nodesInCurrentLayer.begin() + sourceNodeIndex);
			}
			else
				sourceNode = rand() % _numberOfNodesInLayer[layer];

			if (nodesInNextLayer.size())
			{
				int targetNodeIndex = rand() % nodesInNextLayer.size();
				targetNode = nodesInNextLayer[targetNodeIndex];
				nodesInNextLayer.erase(nodesInNextLayer.begin() + targetNodeIndex);
			}
			else
				targetNode = rand() % _numberOfNodesInLayer[layer + 1];

			addEdgeBetween(layer, sourceNode, layer + 1, targetNode);
		}
	}
}

void FlowNetwork::print()
{
	for (int layer = 0; layer < _layersAmount; layer++)
	{
		std::cout << "In layer " << layer << " there is " << _numberOfNodesInLayer[layer] << " nodes" << std::endl;
	}
	_network.print(std::cout);
}

void FlowNetwork::_addEvenMoreEdges()
{
	int toAdd = (_layersAmount - 2) * 2;
	while (toAdd)
	{
		int sourceNode = rand() % (_network.getVertexAmount() - 1);
		int destNode = rand() % (_network.getVertexAmount() - 1) + 1;
		if (!(_network.doesEdgeExists(sourceNode, destNode) || _network.doesEdgeExists(destNode, sourceNode)))
		{
			_network.addDirectedEdge(sourceNode, destNode, rand() % 10 + 1);
			toAdd--;
		}
	}
}
std::list<Edge> augmentingPath(AdjacencyList residualNetwork, int s = 0)
{
	std::list<Edge> path;
	std::vector<int> d;
	std::vector<int> p;

	int t = residualNetwork.getVertexAmount() - 1;
	for (int i = 0; i < residualNetwork.getVertexAmount(); i++)
	{
		d.push_back(INF);
		p.push_back(-1);
	}
	d[s] = 0;
	std::queue<int> Q;
	Q.push(s);

	while (!Q.empty())
	{
		auto v = Q.front();
		Q.pop();

		auto neighbours = residualNetwork.getList()[v];
		for (auto edge : neighbours)
		{
			auto u = edge.destVertex;
			if (d[u] == INF && edge.weight > 0)
			{
				d[u] = d[v] + 1;
				p[u] = v;
				Q.push(u);
				if (u == t)
				{
					Q = std::queue<int>();
				}
			}
		}
	}

	int trace = t;

	while (p[trace] != -1)
	{
		path.push_back(Edge(p[trace], trace, residualNetwork.getEdge(p[trace], trace).weight));
		trace = p[trace];
	}

	return path;
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

FlowNetwork FlowNetwork::fordFulkersonAlgorithm() const
{
	FlowNetwork maxFlow = *this;

	auto list = this->_network.getList();
	auto residualNetwork = this->_network;
	for (auto vertex : residualNetwork.getList())
	{
		for (auto edge : vertex)
		{
			residualNetwork.addDirectedEdge(edge.destVertex, edge.srcVertex, 0);
		}
	}

	std::list<Edge> edgesList;
	for (auto vertex : list)
	{
		edgesList.insert(edgesList.end(), vertex.begin(), vertex.end());
	}

	for (auto vertex : maxFlow._network.getList())
	{
		for (auto edge : vertex)
		{
			maxFlow._network.setDirectedEdgeWeight(edge.srcVertex, edge.destVertex, 0);
		}
	}

	bool isAugmentingPath = true;
	while (isAugmentingPath)
	{
		auto p = augmentingPath(residualNetwork);
		isAugmentingPath = p.size() > 0;

		auto minFlow = (*std::min_element(p.begin(), p.end(),
										  [](const Edge &e1, const Edge &e2) {
											  return e1.weight < e2.weight;
										  }))
						   .weight;

		for (auto edge : p)
		{
			if (this->_network.doesEdgeExists(edge.srcVertex, edge.destVertex))
			{
				maxFlow._network.setDirectedEdgeWeight(edge.srcVertex, edge.destVertex, maxFlow._network.getEdge(edge.srcVertex, edge.destVertex).weight + minFlow);
			}
			else
			{
				maxFlow._network.setDirectedEdgeWeight(edge.destVertex, edge.srcVertex, maxFlow._network.getEdge(edge.destVertex, edge.srcVertex).weight - minFlow);
			}
			residualNetwork.setDirectedEdgeWeight(edge.srcVertex, edge.destVertex, residualNetwork.getEdge(edge.srcVertex, edge.destVertex).weight - minFlow);
			residualNetwork.setDirectedEdgeWeight(edge.destVertex, edge.srcVertex, residualNetwork.getEdge(edge.destVertex, edge.srcVertex).weight + minFlow);
		}
	}

	return maxFlow;

}