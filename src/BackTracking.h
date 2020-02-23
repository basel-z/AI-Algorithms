#pragma once
#include "Strategy.h"
#include <vector>
class BackTracking :
	public Strategy
{
private:
	Graph backtracking(Graph graph);
public:
	BackTracking(Graph graph);
	~BackTracking();
	Graph solve();

};