#include "KempeChains.h"

int KempeChains::pair1 = 0;
int KempeChains::pair2 = 1;

KempeChains::KempeChains(Graph& graph) : Strategy(graph) {}

Graph KempeChains::KempeChainsAlgorithm(Graph& graph)
{
	// give graph a legal coloring.
	Graph result = greedyAlgo(graph);
	graph = result;
	Graph bestGraph(result);
	int k = result.getAvgK();
	while (result.isEmptyGraph() == false) {

		// color1, color2 are two random colors.
		int color1 = rand() % k;
		int color2 = rand() % k;
		while (color1 == color2) { color1 = rand() % k; color2 = rand() % k; }

		int size = graph.getNodes().size();
		for (int i = 0; i < size; ++i) {
			if (graph.getColorForANode(i) == color1) {
				graph.setColorForANode(i, color2);
			}
		}
		for (int i = 0; i < size; ++i) {
			int currentColor = graph.getColorForANode(i);
			if (currentColor >= color1) {
				// below line might reach -1, but that's okay! It means we decided it's an uncolored node.
				int newColor = currentColor - 1;
				if (newColor <= -1) newColor = -1;
				graph.setColorForANode(i, newColor);
			}
		}

		// run the minConflicts algorithm, it should return a better graph
		result = MinConflicts(graph, k - 1);

		// update the best result
		if (result.isEmptyGraph() == false)
		{
			bestGraph = result;
			bestGraph.setAvgK(k - 1);
		}

		// try with a smaller k next time
		--k;
	}

	return bestGraph;
}

Graph KempeChains::MinConflicts(Graph& graph, int maxColors)
{
	Graph originalGraph = graph;
	// we need to try to maximize the objective function
	int sigmaC = objectiveFunc(graph, maxColors);
	int originalSigmaC = sigmaC;
	int maximumAllowedSteps = graph.getNodesSize();
	int currentSteps = 0;
	int nodesAmount = graph.getNodesSize();

	while (currentSteps <= maximumAllowedSteps)
	{
		if (graph.isCompleteAssignment() && graph.isLegalColoring()) {
			return graph;
		}
		int maxConflictsAmount =  getMaxConflictsAmount(graph);
		int minConflictsAmount = getMinConflictsAmount(graph);
		vector<int> allMaxConflictsIndices = getIndicesWithConflictsAmount(graph, maxConflictsAmount);
		vector<int> allMinConflictsIndices = getIndicesWithConflictsAmount(graph, minConflictsAmount);
		bool areConflictsResolved = (maxConflictsAmount != minConflictsAmount) && (allMinConflictsIndices.size() == nodesAmount);
		if (allMinConflictsIndices.size() == 0 || areConflictsResolved) return graph; // there are no conflicts, thus yay! (checking either vector is fine!)
		int randomMaxIndex = allMaxConflictsIndices[rand() % allMaxConflictsIndices.size()];
		int randomMinIndex = allMinConflictsIndices[rand() % allMinConflictsIndices.size()];
		graph.setColorForANode(randomMaxIndex, graph.getColorForANode(randomMinIndex));
		while (pair1 != -1)
		{
			graph = KempeChain(graph);
			int sigmaCTemp = objectiveFunc(graph, maxColors);
			// check if we improved the objective function
			if (sigmaCTemp > sigmaC)
			{
				sigmaC = sigmaCTemp;
				break;
			}
			setNextPairs(maxColors);
		}
		++currentSteps;
		pair1 = 0;
		pair2 = 1;
	}
	if (sigmaC <= originalSigmaC || originalGraph.isSameColorAssignment(graph)) return Graph::emptyGraph();
	return graph;
}

void KempeChains::setNextPairs(int maxColors) const {
	if (pair1 < maxColors)
	{
		if (pair2 + 1 < maxColors)
		{
			pair2++;
			return;
		}
		else
		{
			if (pair1 + 1 == maxColors)
			{
				pair1 = -1;
				return;
			}
			else
			{
				pair1++;
				pair2 = pair1 + 1;
				if (pair2 == maxColors)
					pair1 = -1;
			}
			return;
		}
	}
	pair1 = -1;
	return;
}

Graph KempeChains::KempeChain(Graph& graph)
{
	Graph orig = graph;
	int count = 0, max = 0;
	int color1 = 0;
	int color2 = 0;
	int chainSIndex = -1;
	if (pair1 == -1)
		return graph;
	for (int i = 0, size = graph.getNodes().size(); i < size; ++i)
	{
		if (graph.getColorForANode(i) == pair1 || graph.getColorForANode(i) == pair2)
		{
			count = 0;
			if (graph.getColorForANode(i) == pair1)
			{
				color1 = pair1;
				color2 = pair2;
			}
			else if (graph.getColorForANode(i) == pair2)
			{
				color1 = pair2;
				color2 = pair1;
			}
			for (const Node* m : graph.getNode(i)->getNeighbors())
			{
				if (m->getColor() == color2)
					count++;
			}
			if (count > max)
			{
				max = count;
				chainSIndex = i - 1;
			}
		}
	}
	vector<int> kempeIndices;
	kempeIndices.push_back(chainSIndex);


	for (int i = 0; i < graph.getNodesSize(); i++)
	{
		try {
			int etIndex = kempeIndices.at(i);
			if (etIndex == -1)
				throw std::out_of_range("");
			int c1 = graph.getColorForANode(etIndex);
			color1 = (c1 == pair1) ? pair1 : pair2;
			color2 = (color1 == pair1) ? pair2 : pair1;
			for (int u : graph.getNeigbhoursNameForANode(etIndex))
			{
				if (graph.getColorForANode(u - 1) == color2 && find(kempeIndices.begin(), kempeIndices.end(), u - 1) == kempeIndices.end())
					kempeIndices.push_back(u - 1);
			}
		}
		catch (const std::out_of_range& e) {
			break;
		}
	}

	vector<int>::iterator e1 = kempeIndices.begin();
	while (e1 != kempeIndices.end()) {
		int etIndex = *e1;
		if (etIndex != -1)
		{
			int c1 = graph.getColorForANode(etIndex);
			color2 = c1 == pair1 ? pair2 : pair1;
			graph.setColorForANode(etIndex, color2);
		}
		e1++;
	}

	kempeIndices.clear();
	return graph;
}

int KempeChains::getMaxConflictsAmount(Graph& graph) const
{
	int max = -1;
	for (int i = 0, size = graph.getNodesSize(); i < size; ++i)
	{
		int conflicts = ColorCalcConflicts(*graph.getNode(i), graph.getColorForANode(i));
		if (conflicts > max) max = conflicts;
	}
	return max;
}

int KempeChains::getMinConflictsAmount(Graph & graph) const
{
	int min = graph.getEdgesAmount();
	for (int i = 0, size = graph.getNodesSize(); i < size; ++i)
	{
		int conflicts = ColorCalcConflicts(*graph.getNode(i), graph.getColorForANode(i));
		if (conflicts < min) min = conflicts;
	}
	return min;
}

vector<int> KempeChains::getIndicesWithConflictsAmount(Graph & graph, int conflictAmount) const
{
	vector<int> indices;
	for (int i = 0, size = graph.getNodesSize(); i < size; ++i)
	{
		int conflicts = ColorCalcConflicts(*graph.getNode(i), graph.getColorForANode(i));
		if (conflicts == conflictAmount) indices.push_back(i);
	}
	return indices;
}

Graph KempeChains::solve()
{
	pair1 = 0;
	pair2 = 1;
	return KempeChainsAlgorithm(graph);
}

KempeChains::~KempeChains() {}
