#include "BackTracking.h"



Graph BackTracking::backtracking(Graph graph)
{
	if (graph.isCompleteAssignment()) {
		return graph;
	}
	int index = graph.selectUnassignedNode();
	const Node* currentNode = graph.getNode(index);
	vector<int> domain = currentNode->getDomain();
	for (int color : domain) {
		if (currentNode->canHaveColor(color)) {
			// set color and backtrack check
			//graph.setColorForANode(it, color);
			graph.setColorForANode(index, color);
			//node.setIndex(Main.move++);
			Graph result = backtracking(graph);
			if (!result.isEmptyGraph())
				return result;
			else graph.setColorForANode(index, -1);
		}
	}
	return Graph::emptyGraph();
}

BackTracking::BackTracking(Graph _graph):Strategy(_graph)
{
}


BackTracking::~BackTracking()
{
}

Graph BackTracking::solve()
{
	return backtracking(graph);
}
