#include "Node.h"


Node::~Node()
{
}

Node::Node(int name, int color, int index)
{
	this->name = name;
	this->color = color;
	this->index = index;
	this->domain = std::vector<int>();
	this->neighbors = std::vector<const Node*>();
}

Node::Node(const Node& toClone)
{
	this->name = toClone.name;
	this->color = toClone.color;
	this->index = toClone.index;
	
	vector<int> domain;
	vector<int> domain_copy = toClone.getDomain();
	for (int i = 0; i < domain_copy.size(); i++)
	{
		domain.push_back(domain_copy.at(i));
	}
	this->setDomain(domain);
	
	neighbors.resize(0);
	//clone the neighbours
	//for (int i = 0, size = toClone.neighbors.size(); i < size; ++i)
	//{
	//	neighbors.push_back(toClone.neighbors[i]);
	//}
}

vector<const Node*> Node::getUnassignedNeighbours() const
{
	vector<const Node*> unassignedNeighbours = std::vector<const Node*>();
	for (int i = 0, size = neighbors.size(); i < size; ++i) 
	{
		if (!(*neighbors[i]).hasColor()) {
			unassignedNeighbours.push_back(neighbors[i]);
		}
	}

	return unassignedNeighbours;
}

vector<const Node*> Node::getNeighbors() const
{
	return neighbors;
}

void Node::setNeighbours(const vector<Node*>& neighbours)
{
	for each (Node* var in neighbours)
	{
		this->neighbors.push_back(var);
	}
}
vector<int> Node::getNeigbhoursNameForANode() const
{
	int size = neighbors.size();
	vector<int> returnVal;
	for (int i = 0; i < size; i++) {
		returnVal.push_back(neighbors[i]->getName());
	}
	return returnVal;
}
int Node::getConflict()
{
	int counter = 0;
	for (int i = 0, size = neighbors.size(); i < size; i++) {
		if (neighbors[i]->getColor() == color)
			counter++;
	}
	return counter;
}
void Node::addNeighbour(const Node* neighbour)
{
	this->neighbors.push_back(neighbour);
}

int Node::getName() const
{
	return name;
}

int Node::getColor() const
{
	return color;
}

int Node::getIndx() const
{
	return index;
}

void Node::setIndex(int i)
{
	this->index = i;
}

void Node::setColor(int color)
{
	this->color = color;
}

vector<int> Node::getDomain() const
{
	return domain;
}

void Node::setDomain(const vector<int>& domain)
{
	this->domain = domain;
}

void Node::addColorToDomain(int color)
{
	domain.push_back(color);
}

void Node::removeColorFromDomain(int color)
{
	vector<int>::iterator it =  domain.begin();
	while (it != domain.end()) {
		if (*it == color) {
			domain.erase(it);
			break;
		}
		it++;
	}
}

bool Node::hasColor() const
{
	return this->color != -1;
}

int Node::latestIndx() const
{
	int m = -1;
	for (int i = 0, size = neighbors.size(); i < size; ++i)
	{
		if (neighbors[i]->hasColor() && neighbors[i]->index > m) {
			m = neighbors[i]->index;
		}
	}
	return m;
}

bool Node::canHaveColor(int color) const
{
	for (int i = 0, size = neighbors.size(); i < size; ++i)
	{
		if (color == (*neighbors[i]).getColor()) {
			return false;
		}
	}
	return true;
}

string Node::toString() const
{
	string a = "node " + std::to_string(getName()) + ": ";
	//for (int i = 0, size = neighbors.size(); i < size; ++i)
	//{
	//	a += std::to_string(neighbors[i].getName()) + ", ";
	//}
	a += std::to_string(color);
	return a;
}

const Node* Node::getSpecificNeighbour(int name)
{
	for each (const Node* var in neighbors)
	{
		if (var->getName() == name) {
			return var;
		}
	}

	throw new exception("invalid neighbour name");
}
