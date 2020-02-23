#include "BackJumping.h"

int BackJumping::move = 0;

Graph BackJumping::backJumping(Graph graph)
{
	if (graph.isCompleteAssignment()) {
		return graph;
	}
	int index = graph.selectUnassignedNode();
	const Node* currentNode = graph.getNode(index);
	vector<int> domain = currentNode->getDomain();
	for (int color : domain) {
		if (currentNode->canHaveColor(color)) {
			graph.setColorAndIndexForANode(index, color, move++);
			Graph result = backJumping(graph);
			if (!result.isEmptyGraph())
				return result;
			else if (currentNode->getName() != graph.getLatest()) {
				return result;
			}
			else graph.setColorForANode(index, -1);
		}
	}
	graph.setLatest(currentNode->latestIndx());
	return Graph::emptyGraph();
}

BackJumping::BackJumping(Graph graph):Strategy(graph)
{
}

BackJumping::~BackJumping()
{
}

Graph BackJumping::solve()
{
	return backJumping(graph);
}
