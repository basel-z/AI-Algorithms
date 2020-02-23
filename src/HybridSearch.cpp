#include "HybridSearch.h"

Graph HybridSearch::HillClimbingHybrid(int maxColors)
{
	int steps = 0;
	//int maxSteps=100*(map.getNodes().size());
	int maxSteps = 10;
	int segmaCB = CombinedObjectiveFunc(graph, maxColors);
	while (steps < maxSteps)
	{
		if (graph.isLegalColoring() && graph.isCompleteAssignment()) {
			return graph;
		}
		vector<Node> _nodes = graph.getNodes();
		int nodesSize = _nodes.size();
		for (int i = 0; i < nodesSize; i++)
		{
			//save the original color to assign it back of the nuew heuristic is bigger than the older one.
			int originalColor = _nodes[i].getColor();
			for (int j = 0; j < maxColors; j++)
			{
				if (originalColor != j)
				{
					graph.setColorForANode(i, j);
					int newConflict = CombinedObjectiveFunc(graph, maxColors);
					if (newConflict < segmaCB)
						segmaCB = newConflict;
					else
						graph.setColorForANode(i, originalColor);
				}

			}
		}
		steps++;
	}
	return Graph::emptyGraph();
}

Graph HybridSearch::HybridColoring()
{
	int k, c1, c2;
	Graph result, BestMap;

	result = greedyAlgo(graph);
	graph = result;
	k = result.getAvgK();
	BestMap = result;
	while (!result.isEmptyGraph())
	{
		c1 = rand() % k;
		c2 = rand() % k;
		while (c1 == c2) {
			c1 = rand() % k;
			c2 = rand() % k;
		}
		graph.setFeasibilityColoring(c1, c2);
		result = HillClimbingHybrid(k - 1);
		if (!result.isEmptyGraph())
		{
			BestMap = result;
			BestMap.setAvgK(k - 1);
		}
		k = k - 1;
	}
	return BestMap;
}

HybridSearch::HybridSearch(Graph graph):Strategy(graph)
{
}

HybridSearch::~HybridSearch()
{
}

Graph HybridSearch::solve()
{
	return HybridColoring();
}
