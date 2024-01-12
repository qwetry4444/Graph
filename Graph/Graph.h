#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Node.h"

using namespace std;

class Graph {
private:
	unordered_map<int, vector<int>> adjList;
	unordered_map<int, Node> nodeData;
	int countNodes;

	bool isDirected;
	bool isMulti;
	bool isMultiPart;

public:
	Graph();
	Graph(bool isDirected, bool isMulti, bool isMultiPart);
	~Graph();

	Node GetNodeById(int id);
	bool EdgeExists(int nodeSrcId, int nodeDestId);
	void ChangeGraphTypeDirected(bool v);
	void ChangeGraphTypeMulti(bool v);
	void ChangeGraphTypeMultiPart(bool v);

	struct VectorHash;
	void DFS(int startNodeId);
	void DFS_FindSubgraph(int startNodeId, unordered_set<int>& visitedNodes, unordered_set<int>& currentSubGraph);
	void BFS(int startNodeId);
	void FindIsolatedSubgraphs();
	unordered_map<int, int> FindShortestPathes(int srcId, unordered_map<int, int>& previous);
	vector<int> GetShortestPath(int srcId, int destId);
	bool DFS_FindCycle(int nodeId, unordered_set<int>& visited, vector<int>& curCycle, unordered_set<vector<int>, VectorHash> processedCycles);
	vector<vector<int>> GetAllCycles();
	bool hasEdgeBetween(int srcNodeId, int destNodeId);


	void AddNode(int nodeId, int value);
	void AddNode(Node node);
	void AddEdge(int nodeSrcId, int nodeDestId);
	void AddGraph(Graph otherGraph);
	void Print();
	void Input();
	void SaveToFile(string filename);
	void LoadFromFile(string filename);
};

