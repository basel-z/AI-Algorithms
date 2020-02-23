#pragma once
#include "Strategy.h"
class HybridSearch :
	public Strategy
{
private:
	Graph HillClimbingHybrid(int maxColors);
	Graph HybridColoring();
public:
	HybridSearch(Graph graph);
	~HybridSearch();
	Graph solve();
};

