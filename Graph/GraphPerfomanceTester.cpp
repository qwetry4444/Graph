#include "GraphPerformanceTester.h"

#include <random>
#include <chrono>


GraphPerformanceTester::GraphPerformanceTester(int maxNodes, int step, int edgesPerNode)
    : maxNodes(maxNodes), step(step), edgesPerNode(edgesPerNode) {}

void GraphPerformanceTester::CreateGraph(Graph& graph, int numNodes, int numEdges) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, numNodes - 1);

    for (int i = 0; i < numEdges; ++i) {
        int src = dis(gen);
        int dest = dis(gen);
        if (src != dest) {
            graph.AddEdge(src, dest);
        }
    }
}


double GraphPerformanceTester::MeasureDeleteNodeTime(Graph& graph, int nodeId) {
    auto start = std::chrono::high_resolution_clock::now();
    graph.DeleteNode(nodeId);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
    return 0;
}

void GraphPerformanceTester::RunTests() {
    for (int numNodes = step; numNodes <= maxNodes; numNodes += step) {
        Graph graph = Graph(true, false, true);
        CreateGraph(graph, numNodes, numNodes * edgesPerNode);

        double totalTime = 0;
        for (int nodeId = 0; nodeId < numNodes; nodeId += 100) {
            totalTime += MeasureDeleteNodeTime(graph, nodeId);
        }

        double averageTime = totalTime / numNodes * 100;
        std::cout << "Nodes: " << numNodes << ", Average DeleteNode Time: " << averageTime << " seconds" << std::endl;
    }
}