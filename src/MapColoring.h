#pragma once
#include "Graph.h"
#include "solvingType.h"
#include "Strategy.h"
#include "BackTracking.h"
#include "FWChecking.h"
#include "ArcConsistency.h"
#include "BackJumping.h"
#include "Feasibility.h"
#include "KempeChains.h"
#include "HybridSearch.h"

class MapColoring
{
private:
	Graph initialGraph;
	vector<int> colors;
	SolvingType solvingType;
public:
	MapColoring(Graph& _initialGraph, vector<int> _colors, SolvingType _solvingType);
	Graph colorGraph();
	~MapColoring();
};

