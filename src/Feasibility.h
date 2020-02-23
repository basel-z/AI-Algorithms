#pragma once
#include "Strategy.h"
class Feasibility :
	public Strategy
{
private:
	Graph MinConflictsF(Graph graph, int maxColors);
	Graph FeasibilityColoring(Graph graph);
public:
	Feasibility(Graph graph);
	~Feasibility();
	Graph solve();
};

