#include "Feasibility.h"



Graph Feasibility::MinConflictsF(Graph graph, int maxColors)
{
	int steps = 0;
	int min, conflictPerColor;
	int assignColor = 0;
	while (steps <= 10000) {
		if (graph.isLegalColoring() && graph.isCompleteAssignment()) {
			return graph;
		}
		/* for each node we check how many neightbour' nodes are the same color as me*/
		vector<int> NodeConflicts(graph.getNodesSize());
		fill(NodeConflicts.begin(),NodeConflicts.end(),0);
		/* for each node NodeConflicts returns how many conflicts for each node*/
		std::vector<Node> nodes = graph.getNodes();
		for (int  i = 0, size = nodes.size(); i < size; i++)
		{
			vector<const Node*> _neighbors = nodes[i].getNeighbors();
			for (int j = 0, _size = _neighbors.size(); j < _size; j++)
			{
				if (_neighbors[j]->getColor() == nodes[i].getColor()) {
					NodeConflicts[nodes[i].getName()]++;
				}
			}
		}
		int maxIndex = 0;
		for (int i = 1, size = nodes.size(); i < size; i++) {
			if (NodeConflicts[i] > NodeConflicts[maxIndex]) {
				maxIndex = i;
			}
		}
		min = maxColors;
		for (int i = 1; i <= maxColors; i++)
		{
			conflictPerColor = ColorCalcConflicts(nodes[maxIndex], i);
			if (conflictPerColor < min)
			{
				min = conflictPerColor;
				assignColor = i;
			}
		}
		graph.setColorForANode(maxIndex, assignColor);
		steps++;
	}
	return Graph::emptyGraph();
}

Graph Feasibility::FeasibilityColoring(Graph graph)
{
	int k, c1, c2;
	Graph result, BestMap;

	result = greedyAlgo(graph);
	k = result.getAvgK();
	BestMap = result;
	while (!result.isEmptyGraph())
	{
		c1 = rand() % k + 1;
		c2 = rand() % k + 1;
		while (c1 == c2) {
			c1 = rand() % k + 1;
			c2 = rand() % k + 1;
		}
		graph.setFeasibilityColoring(c1, c2);
		result = MinConflictsF(graph, k - 1);
		if (!result.isEmptyGraph())
		{
			BestMap = result;
			BestMap.setAvgK(k - 1);
		}
		/*map.setAvgK(k-1);*/
		k = k - 1;
	}
	return BestMap;
}


Feasibility::Feasibility(Graph graph):Strategy(graph)
{
}


Feasibility::~Feasibility()
{
}

Graph Feasibility::solve()
{
	return FeasibilityColoring(graph);
}
