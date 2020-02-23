#include "ArcConsistency.h"
int ArcConsistency::moves = 0;
int ArcConsistency::maximumAllowed = 0;

Graph ArcConsistency::ArcConsistencyAlgorithm(Graph graph) 
{
	if (graph.isCompleteAssignment() && graph.isLegalColoring()) {
		return graph;
	}
	if (moves++ > maximumAllowed) return Graph::emptyGraph();
	int index = graph.selectUnassignedNode();
	_updateDomainsProperly(graph);
	const Node* currentNode = graph.getNode(index);
	vector<int> updatedDomain = currentNode->getDomain();
	for (int color : updatedDomain) {
		if (currentNode->canHaveColor(color)) {
			// set color and backtrack check
			Graph oldGraph = graph;
			graph.setColorForANode(index, color);
			Graph result = ArcConsistencyAlgorithm(graph);
			if (!result.isEmptyGraph())
				return result;
			else {
				graph = oldGraph;
			}
		}
	}
	return Graph::emptyGraph();
}

void ArcConsistency::_updateDomainsProperly(Graph& graph)
{
	vector<Node> nodes = graph.getNodes();
	for (int i = 0, size = nodes.size(); i < size; ++i)
	{
		if (nodes[i].hasColor()) continue;
		updateDomainByUnaryCheck(graph, i);
		updateDomainByArcConsistency(graph, i);
	}
}

void ArcConsistency::updateDomainByArcConsistency(Graph& graph, int index)
{
	Node* node = graph.getNode(index);
	vector<int> domain = node->getDomain();
	vector<int> newDomain = domain;
	vector<const Node*> neighbors = node->getNeighbors();
	for (int color : domain)
	{
		if (isArcConsistentWithNeighbor(neighbors, color) == false)
		{
			vector<int>::iterator position = find(newDomain.begin(), newDomain.end(), color);
			if (position != newDomain.end())
				newDomain.erase(position);
		}
	}
	graph.setDomainForNode(index, newDomain);
}

bool ArcConsistency::isArcConsistentWithNeighbor(const vector<const Node*>& neighbors, int color) const
{
	int counter = 0;
	for (const Node* neighbor : neighbors)
	{
		int neighborColor = neighbor->getColor();
		// if the neighbor has a color already, then their domain should only be [color]
		if (false)
		{
			if (neighborColor == color)
				return false;
		}
		// if the neighbor has no color assigned, then we should have a look at their domain [color1, color2, ...]
		else
		{
			vector<int> neighborDomain = neighbor->getDomain();
			if (neighborDomain.size() == 0)
				return false;
			if (neighborDomain.size() == 1 && neighborDomain[0] == color)
				return false;
		}
	}
	return true;
}



void ArcConsistency::updateDomainByUnaryCheck(Graph& graph, int index)
{
	Node* node = graph.getNode(index);
	vector<int> domain = node->getDomain();
	vector<int> newDomain = vector<int>();
	for (int color : domain) {
		if (node->canHaveColor(color)) {
			newDomain.push_back(color);
		}
	}
	vector<int> defaultDomain = graph.getDefaultDomain();
	for (int color : defaultDomain) {
		if (find(newDomain.begin(), newDomain.end(), color) == newDomain.end() 
			&& node->canHaveColor(color)) {
			newDomain.push_back(color);
		}
	}
	graph.setDomainForNode(index, newDomain);
}

ArcConsistency::ArcConsistency(Graph & g) : Strategy(g)
{
}

Graph ArcConsistency::solve()
{
	moves = 0;
	int nodesAmnt = graph.getNodesSize();
	int edgesAmnt = graph.getEdgesAmount();
	maximumAllowed = 100 * (edgesAmnt > nodesAmnt ? edgesAmnt : nodesAmnt);
	return ArcConsistencyAlgorithm(graph);
}

ArcConsistency::~ArcConsistency()
{
}
