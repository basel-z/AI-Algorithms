#pragma once
#include "Node.h"
#include <algorithm>
#include <string>


class Graph
{
private:
	std::vector<Node> _nodes;
	int _nodesAmount;
	int _edgesAmount;
	int latestNodeIndex;
	int currentAverageK;
	std::vector<int> defaultDomain;

	int getNodeIndex(const int node) const;
	static bool sortCriteria(const Node& a, const Node& b);
	Graph* Copy(const Graph& copy);
public:
	// constructs a graph with the nodes 'nodes'
	Graph(const Graph& toClone);
	Graph(const std::vector<Node>& nodes = std::vector<Node>());
	Graph& operator=(const Graph& other);
	~Graph();

	// returns the nodes of this graph
	std::vector<Node> getNodes() const;

	// removes all colors on all nodes (clears all nodes colors).
	void resetColors();

	// returns node at the given index
	Node* const getNode(int index);

	// updates everyone's domain to be newColors.
	void setDomainForAll(const std::vector<int>& newColors);
	void resetDomains();
	vector<int> getDefaultDomain() const;
	void setDefaultDomain(const std::vector<int>& newColors);

	int getEdgesAmount() const;
	void setEdgesAmount(int amount);
	void setNodesAmount(int amount);

	// add edges 
	void addEdges(const int firstNodeName, const int secondNodeName);

	// checks if the current coloring of the graph is legal (i.e no two adjacent nodes have the same color)
	bool isLegalColoring() const;
	// checks if all nodes have been given an assignment (color).
	bool isCompleteAssignment() const;

	int getLatest() const;
	void setLatest(int i);

	int getAvgK() const;
	void setAvgK(int i);

	int selectUnassignedNode();
	std::vector<Node>::iterator nodesEnd();

	// resizes the vector
	void resize(int size);

	void print() const;

	bool isEmptyGraph() const;
	static Graph emptyGraph();

	int getColorForANode(int index) const;
	void setColorForANode(int index, int color);
	void setColorAndIndexForANode(int index, int color, int _index);
	void setDomainForNode(int index,const vector<int>& domain);
	int getMaxDegree() const;
	int getNodesSize() const;
	void setFeasibilityColoring(int color1, int color2);
	vector<int> getNeigbhoursNameForANode(int index)const;
	vector<int> ConflictsPerColor(int n);

	bool isSameColorAssignment(const Graph& other) const;
	vector<int> badEdges(int size);
};
