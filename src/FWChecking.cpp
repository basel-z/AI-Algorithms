#include "FWChecking.h"

Graph FWChecking::FWCheckingAlgorithm(Graph graph)
{
	if (graph.isCompleteAssignment()) {
		return graph;
	}
	int index = graph.selectUnassignedNode();
	Node* currentNode = graph.getNode(index);
	vector<int> domain = currentNode->getDomain();
	vector<int> newDomain = vector<int>();
	for (int color : domain) {
		if (currentNode->canHaveColor(color)) {
			newDomain.push_back(color);
		}
	}
	graph.setDomainForNode(index, newDomain);
	currentNode = graph.getNode(index);
	vector<int> updatedDomain = currentNode->getDomain();
	for (int color : updatedDomain) {
		if (currentNode->canHaveColor(color)) {
			// set color and backtrack check
			graph.setColorForANode(index, color);
			Graph result = FWCheckingAlgorithm(graph);
			if (!result.isEmptyGraph())
				return result;
			else graph.setColorForANode(index, -1);
		}
	}
	return Graph::emptyGraph();
}

FWChecking::FWChecking(Graph& g): Strategy(g)
{
}

Graph FWChecking::solve()
{
	return FWCheckingAlgorithm(graph);
}

FWChecking::~FWChecking()
{
}
