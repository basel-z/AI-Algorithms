#pragma once
#include <iostream>
#include <vector>
#include <unordered_map> 
#include <string>

using namespace std;
class Node
{
private:
	std::vector<const Node*> neighbors;
	std::vector<int> domain;
	int name = -1;
	int color = -1;
	int index = -1;
public:
	
	Node(int name = -1, int color = -1, int index = -1);
	Node(const Node& toClone);
	vector<const Node*> getUnassignedNeighbours() const;
	vector<const Node*> getNeighbors() const;
	void setNeighbours(const vector<Node*>& neighbours);
	void addNeighbour(const Node* neighbour);
	int getName() const;
	int getColor() const;
	int getIndx() const;
	void setIndex(int i);
	void setColor(int color);
	vector<int> getDomain() const;
	void setDomain(const vector<int>& domain);
	void addColorToDomain(int color);
	void removeColorFromDomain(int color);
	bool hasColor() const;
	int latestIndx() const;
	bool canHaveColor(int color) const;
	string toString() const;
	const Node* getSpecificNeighbour(int name);
	vector<int> getNeigbhoursNameForANode()const;
	int getConflict();
	~Node();
};

