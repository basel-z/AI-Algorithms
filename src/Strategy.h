#pragma once
#include "../src/Graph.h"
class Strategy
{
protected:
	Graph graph;
	bool haveADomainValue(vector<Node> neighbours);
	Graph greedyAlgo(Graph graph);
	int ColorCalcConflicts(Node& n, int color) const;
	vector<int> ConflictsPerColor(Graph graph, int n) const;
	int totalConflicts(Graph graph, int n);
	vector<int> BadEdges(Graph graph, int n);
	int objectiveFunc(const Graph& graph, int MaxColors) const;
	int CombinedObjectiveFunc(Graph graph, int n);


public:
	Strategy(Graph graph);
	virtual Graph solve()=0;
	~Strategy();
};

