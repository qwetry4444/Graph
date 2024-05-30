#include "Graph.h"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>
#include <fstream>
#include <sstream>
using namespace std;


Graph::Graph()
	: countNodes(0)
	, isDirected(false)
	, isMulti(false)
{}

Graph::Graph(bool _isDirected, bool _isMulti, bool isMultiPart)
	: countNodes(0)
	, isMulti(_isMulti)
	, isDirected(_isDirected)
	, isMultiPart(isMultiPart)
{}

Graph::~Graph()
{}

void printVector(vector<int> v) {
	cout << "  [";
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << ", ";
	}
	cout << "]" << endl;
}

void printSet(unordered_set<int> s) {
	cout << "  (";
	for (int i : s)
		cout << i << ", ";
	cout << ")" << endl;
}

void printMap(unordered_map<int, int> m) {
	cout << "{";
	for (pair<int, int> pair : m) {
		cout << pair.first << " : " << pair.second << endl;
	}
	cout << "}" << endl;
}

void Graph::ChangeGraphTypeDirected(bool v) {
	if (isDirected != v) {
		if (!isDirected) {
			// Добавляем обратные ребра
			for (auto& pair : adjList) {
				for (const auto neighbor : pair.second) {
					AddEdge(neighbor, pair.first);
				}
			}
		}
		isDirected = v;
	}
}

void Graph::ChangeGraphTypeMulti(bool v) {
	if (isMulti != v) {
		if (isMulti == true) {
			//Убираем все кратные дуги
			for (auto& pair : adjList) {
				vector<int>& neighbors = pair.second;
				set<int> s(neighbors.begin(), neighbors.end());
				neighbors.assign(s.begin(), s.end());
			}
		}
		isMulti = v;
	}
}

void Graph::ChangeGraphTypeMultiPart(bool v) {
	if (isMultiPart != v) {
		if (isMultiPart == true) {
			//Убираем все дуги
			adjList.clear();
		}
		isMultiPart = v;
	}
}


bool Graph::EdgeExists(int nodeSrcId, int nodeDestId) {
	vector<int> nodeSrcNeighbors = adjList[nodeSrcId];
	return find(nodeSrcNeighbors.begin(), nodeSrcNeighbors.end(), nodeDestId) != nodeSrcNeighbors.end();
}

void Graph::AddNode(int nodeId, int nodeValue) {
	vector<int> v;
	nodeData[nodeId] = Node(nodeId, nodeValue);
	adjList[nodeId] = v;
	countNodes++;
}

void Graph::AddNode(Node node) {
	nodeData[node.id] = node;
	countNodes++;
}

void Graph::DeleteNode(int nodeId) {
	adjList.erase(nodeId);
	nodeData.erase(nodeId);

	for (auto& pair : adjList) {
		if (pair.first != nodeId) {
			auto& neighbors = pair.second;
			neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), nodeId), neighbors.end());
		}
	}

	countNodes--;
}

void Graph::DeleteEdge(int srcNodeId, int destNodeId) {
	auto& srcNeighbors = adjList[srcNodeId];
	srcNeighbors.erase(std::remove(srcNeighbors.begin(), srcNeighbors.end(), destNodeId), srcNeighbors.end());

	auto& destNeighbors = adjList[destNodeId];
	destNeighbors.erase(std::remove(destNeighbors.begin(), destNeighbors.end(), srcNodeId), destNeighbors.end());
}


void Graph::AddEdge(int nodeSrcId, int nodeDestId) {
	if (isMultiPart) {
		if (isMulti || !EdgeExists(nodeSrcId, nodeDestId)) {
			adjList[nodeSrcId].push_back(nodeDestId);
			if (!isDirected)
				adjList[nodeDestId].push_back(nodeSrcId);
		}
	}
	else cout << "  Не удалось добавить ребро, т.к. граф однодольный" << endl;
}

void Graph::Print() {
	cout << "  Вывод графа: " << endl;
	for (const auto pair : nodeData) {
		cout << "  Вершина " << pair.first << " (value = " << pair.second.value << "):" << endl;
		for (int neighbor : adjList[pair.first]) {
			cout << "  " << pair.first << "->" << neighbor << endl;
		}
		cout << endl;
	}
}

void Graph::AddGraph(Graph otherGraph) {
	for (const auto& pair : otherGraph.adjList) {
		int nodeId = pair.first;
		AddNode(nodeId, otherGraph.nodeData[nodeId].value);
	}

	for (const auto& pair : otherGraph.adjList) {
		int nodeId = pair.first;
		for (int neighbor : pair.second) {
			AddEdge(nodeId, neighbor);
		}
	}
}

void Graph::DFS(int startNodeId) {
	unordered_set<int> visited;
	stack<int> dfsStack;
	int curNodeId;

	dfsStack.push(startNodeId);

	while (!dfsStack.empty()) {
		curNodeId = dfsStack.top();
		dfsStack.pop();
		cout << "  ";
		if (visited.find(curNodeId) == visited.end()) {
			cout << "  " << curNodeId << " ";
			visited.insert(curNodeId);
			for (int neighborId : adjList[curNodeId]) {
				if (visited.find(neighborId) == visited.end()) {
					dfsStack.push(neighborId);
				}
			}
		}
	}
	printSet(visited);
}

void Graph::BFS(int startNodeId) {
	unordered_set<int> visited;
	queue<int> dfsQueue;
	int curNodeId;

	dfsQueue.push(startNodeId);

	while (!dfsQueue.empty()) {
		curNodeId = dfsQueue.front();
		dfsQueue.pop();
		cout << "  ";
		if (visited.find(curNodeId) == visited.end()) {
			cout << curNodeId << " ";
			visited.insert(curNodeId);
			for (int neighborId : adjList[curNodeId]) {
				if (visited.find(neighborId) == visited.end()) {
					dfsQueue.push(neighborId);
				}
			}
		}
	}
	printSet(visited);
}


void Graph::FindIsolatedSubgraphs() {
	unordered_set<int> visited;
	vector<unordered_set<int>> isolatedSubgraphs;

	for (const auto& pair : nodeData) {
		int curNodeId = pair.first;
		if (visited.find(curNodeId) == visited.end()) {
			unordered_set<int> curSubgraph;
			DFS_FindSubgraph(curNodeId, visited, curSubgraph);
			isolatedSubgraphs.push_back(curSubgraph);
		}
	}

	cout << "  Количество подграфов: " << isolatedSubgraphs.size() << endl;
	for (auto s : isolatedSubgraphs) {
		printSet(s);
	}
}

void Graph::DFS_FindSubgraph(int startNodeId, unordered_set<int>& visitedNodes, unordered_set<int>& currentSubgraph) {
	stack<int> dfsStack;
	int curNodeId;

	dfsStack.push(startNodeId);

	while (!dfsStack.empty()) {
		curNodeId = dfsStack.top();
		dfsStack.pop();
		if (visitedNodes.find(curNodeId) == visitedNodes.end()) {
			visitedNodes.insert(curNodeId);
			currentSubgraph.insert(curNodeId);
			for (int neighborId : adjList[curNodeId]) {
				if (visitedNodes.find(neighborId) == visitedNodes.end()) {
					dfsStack.push(neighborId);
				}
			}
		}
	}
}


vector<int> Graph::GetShortestPath(int srcId, int destId) {
	unordered_map<int, int> previous;
	unordered_map<int, int> distances = FindShortestPathes(srcId, previous);

	vector<int> path;
	int curNodeId = destId;
	while (curNodeId != -1) {
		path.insert(path.begin(), curNodeId);
		curNodeId = previous[curNodeId];
	}
	if (path.size() == 1) {
		cout << "  Нет пути между " << srcId << " и " << destId << endl;
	}
	else {
		cout << "  Кратчайший путь между " << srcId << " и " << destId << ": ";
		printVector(path);
	}
	return path;
}

unordered_map<int, int> Graph::FindShortestPathes(int srcId, unordered_map<int, int>& previous) {
	unordered_map<int, int> distance;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	for (const auto& pair : nodeData) {
		int nodeId = pair.first;
		distance[nodeId] = (nodeId == srcId) ? 0 : countNodes + 1;
		pq.push({ nodeId, distance[nodeId] });
		previous[nodeId] = -1;
	}

	while (!pq.empty()) {
		int currentNodeId = pq.top().first;
		pq.pop();

		for (const auto& neighbor : adjList[currentNodeId]) {
			int neighborNodeId = neighbor;
			int edgeWeight = 1;

			int newDistance = distance[currentNodeId] + edgeWeight;
			if (newDistance < distance[neighborNodeId]) {
				distance[neighborNodeId] = newDistance;
				pq.push({ neighborNodeId, newDistance });
				previous[neighborNodeId] = currentNodeId;
			}
		}
	}
	return distance;
}

struct Graph::VectorHash {
	size_t operator()(const std::vector<int>& v) const {
		std::hash<int> hasher;
		size_t seed = 0;
		for (int i : v) {
			seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};

bool Graph::DFS_FindCycle(int nodeId, unordered_set<int>& visited, vector<int>& curCycle, unordered_set<vector<int>, VectorHash> processedCycles) {
	stack<int> dfsStack;
	unordered_set<int> nodesInStack;

	dfsStack.push(nodeId);
	nodesInStack.insert(nodeId);

	while (!dfsStack.empty()) {
		int curNodeId = dfsStack.top();
		dfsStack.pop();

		visited.insert(curNodeId);
		curCycle.push_back(curNodeId);

		for (const auto& neighbor : adjList[curNodeId]) {
			if (!visited.count(neighbor)) {
				dfsStack.push(neighbor);
				nodesInStack.insert(neighbor);
			}
			else if (nodesInStack.count(neighbor) && processedCycles.find(curCycle) == processedCycles.end()) {
				while (!dfsStack.empty() && dfsStack.top() != neighbor) {
					curCycle.push_back(dfsStack.top());
					dfsStack.pop();
				}
				curCycle.push_back(neighbor);
				processedCycles.insert(curCycle);
				return true;
			}
			else {
				nodesInStack.erase(neighbor);
			}
		}
	}
	curCycle.clear();
	return false;
}



vector<vector<int>> Graph::GetAllCycles() {
	vector<vector<int>> cycles;
	unordered_set<int> visited;
	unordered_set<vector<int>, VectorHash> processedCycles;

	for (const auto& node : nodeData) {
		int nodeId = node.first;
		vector<int> curCycle;
		if (DFS_FindCycle(nodeId, visited, curCycle, processedCycles)) {
			cycles.push_back(curCycle);
		}
	}
	if (cycles.empty()) {
		cout << "  В графе нет циклов." << endl;
	}
	else {
		cout << "  Циклы: " << endl;
		for (const auto& vec : cycles) {
			printVector(vec);
		}
	}
	return cycles;
}

bool Graph::hasEdgeBetween(int srcNodeId, int destNodeId) {
	vector<int> v = adjList[srcNodeId];
	return find(v.begin(), v.end(), destNodeId) != v.end();
}

void Graph::SaveToFile(string filename) {
	ofstream file(filename);
	if (file.is_open()) {
		file << countNodes << "\n";
		file << (isDirected ? 1 : 0) << " " << (isMulti ? 1 : 0) << " " << (isMultiPart ? 1 : 0) << '\n';
		for (const auto& pair : adjList) {
			file << pair.first << " " << nodeData[pair.first].value;
			for (int neighbor : pair.second) {
				file << " " << neighbor;
			}
			file << '\n';
		}
		file.close();
	}
}


void Graph::LoadFromFile(string filename) {
	ifstream file(filename);
	if (file.is_open()) {
		adjList.clear();
		nodeData.clear();

		string line;
		int lineNumber = 0;
		while (getline(file, line)) {
			lineNumber++;
			if (!line.empty()) {
				istringstream iss(line);

				if (lineNumber == 1) {
					iss >> countNodes;
				}
				else if (lineNumber == 2) {
					int directed, multi, multiPart;
					iss >> directed;
					iss >> multi;
					iss >> multiPart;
					isDirected = (directed == 1);
					isMulti = (multi == 1);
					isMultiPart = (multiPart == 1);
				}
				else {
					int nodeId;
					int nodeValue;
					vector<int> neighbors;

					iss >> nodeId;
					iss >> nodeValue;
					nodeData[nodeId].value = nodeValue;

					int neighbor;
					while (iss >> neighbor) {
						neighbors.push_back(neighbor);
					}

					for (int neighbor : neighbors) {
						AddEdge(nodeId, neighbor);
					}

					iss.clear();
					iss.seekg(0);
				}
			}
		}
		file.close();
	}
}


void Graph::Input()
{
	int multi, directed, multiPart = 1;
	cout << "  Ориентированный граф?" << endl;
	cout << "  1 - Да  2 - Нет" << endl;
	cout << "  Выбор: ";
	cin >> directed;
	cout << endl << "  Мульти граф?" << endl;
	cout << "  1 - Да  2 - Нет" << endl;
	cout << "  Выбор: ";
	cin >> multi;
	//cout << endl << "  Многодольный граф?" << endl;
	//cout << "  1 - Да  2 - Нет" << endl;
	//cout << "  Выбор: ";
	//cin >> multiPart;
	isDirected = (directed == 1);
	isMulti = (multi == 1);
	isMultiPart = (multiPart == 1);
}