#pragma once
#include "Strategy.h"
class BackJumping :
	public Strategy
{
private: 
	Graph backJumping(Graph graph);
public:
	static int move;
	BackJumping(Graph graph);
	~BackJumping();
	Graph solve();
};

