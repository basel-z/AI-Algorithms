#pragma once
#include "Lecture.h"
#include "Strategy.h"

class KempeChains : public Strategy
{
private:
	static int pair1;
	static int pair2;
	Graph KempeChainsAlgorithm(Graph& graph);
	Graph MinConflicts(Graph& graph, int maxColors);
	int getMaxConflictsAmount(Graph& graph) const;
	int getMinConflictsAmount(Graph& graph) const;
	vector<int> getIndicesWithConflictsAmount(Graph& graph, int conflictAmount) const;
	void setNextPairs(int maxColors) const;
	Graph KempeChain(Graph& graph);


public:
	KempeChains(Graph& graph);
	~KempeChains();
	Graph solve();
};