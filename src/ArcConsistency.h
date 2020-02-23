#pragma once
#include "Lecture.h"
#include "Strategy.h"

class ArcConsistency : public Strategy
{
private:
	Graph ArcConsistencyAlgorithm(Graph graph);
	void updateDomainByUnaryCheck(Graph& graph, int index);
	void updateDomainByArcConsistency(Graph& graph, int index);
	bool isArcConsistentWithNeighbor(const vector<const Node*>& neighbors, int color) const;
	void _updateDomainsProperly(Graph& graph);
	static int moves;
	static int maximumAllowed;
public:
	ArcConsistency(Graph& g);
	Graph solve();
	~ArcConsistency();
};
