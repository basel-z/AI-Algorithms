#include "GraphGeneration.h"

GraphGenerator::GraphGenerator(const std::string path) : _file (path) { }

bool isNumber(char c)
{
	return ((c - '0') >= 0) && ((c - '0') <= 9);
}

void inferGraphMetaData(Graph* const graph, const std::string& info)
{
	unsigned int nodesNumberIndex = 7;
	unsigned int nodesAmount = 0;
	while (nodesNumberIndex < info.length() && isNumber(info[nodesNumberIndex]))
	{
		nodesAmount = nodesAmount * 10 + (info[nodesNumberIndex] - '0');
		++nodesNumberIndex;
	}

	unsigned int edgesNumberIndex = nodesNumberIndex + 1;
	unsigned int edgesAmount = 0;
	while (edgesNumberIndex < info.length() && isNumber(info[edgesNumberIndex]))
	{
		edgesAmount = edgesAmount * 10 + (info[edgesNumberIndex] - '0');
		++edgesNumberIndex;
	}

	graph->setNodesAmount(nodesAmount);
	graph->setEdgesAmount(edgesAmount);
	graph->resize(nodesAmount);
}

void inferGraphEdge(Graph* const graph, const std::string& info)
{
	unsigned int firstNodeIndex = 2;
	unsigned int firstNodeName = 0;
	while (firstNodeIndex < info.length() && isNumber(info[firstNodeIndex]))
	{
		firstNodeName = firstNodeName * 10 + (info[firstNodeIndex] - '0');
		++firstNodeIndex;
	}

	unsigned int secondNodeIndex = firstNodeIndex + 1;
	unsigned int secondNodeName = 0;
	while (secondNodeIndex < info.length() && isNumber(info[secondNodeIndex]))
	{
		secondNodeName = secondNodeName * 10 + (info[secondNodeIndex] - '0');
		++secondNodeIndex;
	}

	graph->addEdges(firstNodeName, secondNodeName);
}

void updateGraphInfo(Graph* const graph, const std::string& info)
{
	// if the graph is null, we cant 'update' anything
	if (graph == nullptr) return;
	// if the line is empty, need not do anything (this serves as a safety check for substr)
	if (info.length() == 0) return;
	if (info.substr(0, 1) == "p") { inferGraphMetaData(graph, info); }
	if (info.substr(0, 1) == "e") { inferGraphEdge(graph, info); }
}

Graph GraphGenerator::buildGraph()
{
	Graph g;
	string line = "";
	if (_file.is_open())
	{
		while (getline(_file, line))
		{
			updateGraphInfo(&g, line);
		}
		_file.close();
	}
	return g;
}

GraphGenerator::~GraphGenerator() {}
