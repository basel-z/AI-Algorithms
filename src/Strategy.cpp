#include "Strategy.h"



Strategy::Strategy(Graph _graph):graph(_graph) {
}

Strategy::~Strategy()
{
}

bool Strategy::haveADomainValue(vector<Node> neighbours)
{
	for (Node neighbour : neighbours) {
		if (neighbour.getDomain().empty()) {
			return false;
		}
	}

	return true;
}

Graph Strategy::greedyAlgo(Graph graph)
{
	int V = graph.getNodesSize();

	vector<int> result(V);
	vector<bool> available(V);
	fill(result.begin(), result.end(), -1);
	fill(available.begin(), available.end(), true);
	result[0] = 0;
	int max = 0, cr = 0;
	vector<Node> nodes = graph.getNodes();
	for(int i = 0, size = nodes.size();i<size;i++){
		vector<int> neighbour = graph.getNeigbhoursNameForANode(i);
		for (int j = 0, _size = neighbour.size(); j < _size; j++) {
			if (result[neighbour[j]-1] != -1)
				available[result[neighbour[j]-1]] = false;
		}
		for (cr = 0; cr < V; cr++)
		{
			if (available[cr])
				break;
		}
		result[nodes[i].getName()-1] = cr;
		graph.setColorForANode(i, cr);
		fill(available.begin(), available.end(), true);
	}
	for (int i = 0, size = nodes.size(); i < size; i++){
		if (result[nodes[i].getName()-1] > max)
			max = result[nodes[i].getName() - 1];
	}
	graph.setAvgK(max + 1);
	return graph;
}

int Strategy::ColorCalcConflicts(Node& n, int color) const
{
	int count = 0;
	for (const Node* m : n.getNeighbors())
		if (m->getColor() == color)
			count++;
	return count;
}

vector<int> Strategy::ConflictsPerColor(Graph graph, int n) const
{
	return graph.ConflictsPerColor(n);
}

int Strategy::totalConflicts(Graph graph, int n)
{
	int sum = 0;
	vector<int> colors(n);
	colors = ConflictsPerColor(graph, n);
	for (int i = 0; i < n; i++)
		sum += colors[i];
	return sum;
}

vector<int> Strategy::BadEdges(Graph graph, int n)
{
	return graph.badEdges(n);
}

// sigma(ci^2)
int Strategy::objectiveFunc(const Graph& graph, int MaxColors) const
{
	int sum = 0;
	vector<int> colors(MaxColors);
	colors = ConflictsPerColor(graph, MaxColors);
	for (int i = 0; i < MaxColors; i++)
	{
		sum += colors[i] * colors[i];
	}
	return sum;
}

int Strategy::CombinedObjectiveFunc(Graph graph, int n)
{
	int sum = 0;
	vector<int> colors(n);
	colors = ConflictsPerColor(graph, n);
	vector<int> bad(n);
	bad = BadEdges(graph, n);
	for (int i = 0; i < n; i++)
	{
		sum += colors[i] * bad[i];
	}
	return (2 * sum - objectiveFunc(graph, n));
}
