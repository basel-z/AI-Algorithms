#include "Graph.h"

Graph::Graph(const Graph & toClone)
{
	Copy(toClone);
}

Graph* Graph::Copy(const Graph& other)
{
	_nodesAmount = other._nodesAmount;
	_edgesAmount = other._edgesAmount;
	latestNodeIndex = other.latestNodeIndex;
	currentAverageK = other.currentAverageK;
	_nodes = vector<Node>(0);
	for (int i = 0, size = other._nodes.size(); i < size; i++)
	{
		_nodes.push_back(other._nodes[i]);
	}
	for (int i = 0, size = _nodes.size(); i < size; i++)
	{
		vector<const Node*> toCopy = other._nodes[i].getNeighbors();
		for (int j = 0, nSize = toCopy.size(); j < nSize; ++j)
		{
			_nodes[i].addNeighbour(&_nodes[toCopy[j]->getName() - 1]);
		}
	}
	defaultDomain = other.defaultDomain;
	return this;
}

Graph::Graph(const std::vector<Node>& nodes)
{
	defaultDomain = std::vector<int>(0);
	_nodes = std::vector<Node>(nodes);
	_nodesAmount = nodes.size();
	_edgesAmount = 0;
	for (int i = 0; i < _nodesAmount; ++i)
		_edgesAmount += nodes[i].getNeighbors().size();
	this->latestNodeIndex = -1;
	this->currentAverageK = 0;
}

Graph& Graph::operator=(const Graph & other)
{
	if (this == &other) return *this;
	return *Copy(other);
}

std::vector<Node> Graph::getNodes() const
{
	return _nodes;
}

void Graph::resetColors()
{
	setLatest(-1);
	for (int i = 0, size = _nodes.size(); i < size; ++i) {
		_nodes[i].setColor(-1);
		_nodes[i].setIndex(-1);
	}
	return;
}

Node* const Graph::getNode(int index)
{
 	if (index < 0 || index >= _nodes.size()) throw "Incorrect index in graph";
	return &_nodes[index];
}

void Graph::setDomainForAll(const std::vector<int>& newColors)
{
	for (int i = 0, size = _nodes.size(); i < size; ++i) {
		_nodes[i].setDomain(std::vector<int>(newColors));
	}
}

void Graph::resetDomains()
{
	for (int i = 0, size = _nodes.size(); i < size; ++i) {
		_nodes[i].setDomain(defaultDomain);
	}
}

vector<int> Graph::getDefaultDomain() const
{
	return defaultDomain;
}

void Graph::setDefaultDomain(const std::vector<int>& newColors)
{
	defaultDomain = newColors;
}

int Graph::getEdgesAmount() const
{
	return _edgesAmount;
}

void Graph::setEdgesAmount(int amount)
{
	_edgesAmount = amount;
}

void Graph::setNodesAmount(int amount)
{
	_nodesAmount = amount;
}

int Graph::getNodeIndex(const int nodeName) const
{
	for (int i = 0, size = _nodes.size(); i < size; ++i)
	{
		if (_nodes[i].getName() == nodeName)
			return i;
	}
	return -1;
}

void Graph::addEdges(const int firstNodeName, const int secondNodeName)
{
	int index1 = getNodeIndex(firstNodeName);
	int index2 = getNodeIndex(secondNodeName);
	if (index1 == -1) { index1 = firstNodeName - 1; _nodes[index1] = Node(firstNodeName, -1, -1); }
	if (index2 == -1) { index2 = secondNodeName - 1; _nodes[index2] = Node(secondNodeName, -1, -1); }
	_nodes[index1].addNeighbour(&_nodes[index2]);
	_nodes[index2].addNeighbour(&_nodes[index1]);
}

bool Graph::isLegalColoring() const
{
	for (int i = 0, size = _nodes.size(); i < size; ++i) {
		std::vector<const Node*> neighbors = _nodes[i].getNeighbors();
		for (int j = 0, neighSize = neighbors.size(); j < neighSize; ++j) {
			int currentColor = _nodes[i].getColor();
			if (currentColor == neighbors[j]->getColor()) {
				return false;
			}
		}
	}
	return true;
}

bool Graph::isCompleteAssignment() const
{
	for (int i = 0, size = _nodes.size(); i < size; ++i) {
		if (_nodes[i].hasColor() == false) {
			return false;
		}
	}
	return true;
}

int Graph::getLatest() const
{
	return this->latestNodeIndex;
}

void Graph::setLatest(int i)
{
	this->latestNodeIndex = i;
}

int Graph::getAvgK() const
{
	return this->currentAverageK;
}

void Graph::setAvgK(int i)
{
	this->currentAverageK = i;
}

int Graph::selectUnassignedNode()
{
	for (int i = 0; i < _nodes.size(); i++)
	{
		if (!_nodes[i].hasColor()) {
			return i;
		}
	}
	throw new exception("all nodes are assigned !!");
}

std::vector<Node>::iterator Graph::nodesEnd()
{
	return _nodes.end();
}



bool Graph::sortCriteria(const Node& a, const Node& b)
{
	return a.getName() < b.getName();
}

void Graph::resize(int size)
{
	_nodes.resize(size);
}

void Graph::print() const
{
	for (int i = 0, size = _nodes.size(); i < size; ++i)
	{
		std::cout << _nodes[i].toString() << std::endl;
	}
}

bool Graph::isEmptyGraph() const
{
	return _nodes.empty();
}

Graph Graph::emptyGraph()
{
	return Graph(std::vector<Node>());
}

int Graph::getColorForANode(int index) const
{
	return _nodes[index].getColor();
}

void Graph::setColorForANode(int index, int color)
{
	_nodes[index].setColor(color);
}

void Graph::setColorAndIndexForANode(int index, int color, int _index)
{
	_nodes[index].setColor(color);
	_nodes[index].setIndex(_index);
}

void Graph::setDomainForNode(int index, const vector<int>& domain)
{
	_nodes[index].setDomain(domain);
}

int Graph::getMaxDegree() const
{
	int max = 0;
	for (int i = 0, size= _nodes.size(); i < size; i++)
	{
		int neighboursSize = _nodes[i].getNeighbors().size();
		max = neighboursSize > max ? neighboursSize : max;
	}
	return max + 1;
}

int Graph::getNodesSize() const
{
	return _nodes.size();
}

void Graph::setFeasibilityColoring(int color1, int color2)
{
	for (int i = 0, size = _nodes.size(); i < size; i++)
	{
		int currColor = _nodes[i].getColor();
		if (currColor == color1) {
			_nodes[i].setColor(color2);
		}
		else if (currColor > color1) {
			_nodes[i].setColor(currColor - 1);
		}
	}
}

vector<int> Graph::getNeigbhoursNameForANode(int index) const
{
	return _nodes[index].getNeigbhoursNameForANode();
}

vector<int> Graph::ConflictsPerColor(int n)
{
	vector<int> colors(n);
	fill(colors.begin(), colors.end(), 0);
	for (int i = 0, size = _nodes.size(); i < size; i++) {
		int nodeColor = _nodes[i].getColor();
		if (nodeColor != -1) {
			colors[nodeColor]++;
		}
	}
	return colors;

}

	bool Graph::isSameColorAssignment(const Graph & other) const
{
	for (int i = 0, size = _nodes.size(); i < size; ++i)
		if (_nodes[i].getColor() != other._nodes[i].getColor()) return false;
	return true;
}

vector<int> Graph::badEdges(int size)
{
	vector<int> colors(size);
	for (int i = 0, _size = _nodes.size(); i < _size; i++) {
		colors[_nodes[i].getColor()] += _nodes[i].getConflict();
	}
	return colors;
}

Graph::~Graph()
{
	_nodes.clear();
}
