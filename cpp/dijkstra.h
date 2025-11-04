#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <unordered_map>
#include <string>

struct Graph {
    std::unordered_map<std::string, std::unordered_map<std::string, int>> adjacency_list;
};

std::unordered_map<std::string, int> dijkstra(const Graph& graph, const std::string& start);
Graph load_graph_from_json(const std::string& filename);

#endif
