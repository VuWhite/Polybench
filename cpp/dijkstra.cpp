#include "dijkstra.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <limits>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::unordered_map<std::string, int> dijkstra(const Graph& graph, const std::string& start) {
    std::unordered_map<std::string, int> distances;
    for (const auto& node : graph.adjacency_list) {
        distances[node.first] = std::numeric_limits<int>::max();
    }
    distances[start] = 0;

    auto compare = [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second;
    };
    std::priority_queue<std::pair<std::string, int>, 
                       std::vector<std::pair<std::string, int>>, 
                       decltype(compare)> pq(compare);
    pq.push({start, 0});

    while (!pq.empty()) {
        auto [current, current_distance] = pq.top();
        pq.pop();

        if (current_distance > distances[current]) {
            continue;
        }

        if (graph.adjacency_list.find(current) != graph.adjacency_list.end()) {
            for (const auto& [neighbor, weight] : graph.adjacency_list.at(current)) {
                int distance = current_distance + weight;
                if (distance < distances[neighbor]) {
                    distances[neighbor] = distance;
                    pq.push({neighbor, distance});
                }
            }
        }
    }

    return distances;
}

Graph load_graph_from_json(const std::string& filename) {
    Graph graph;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return graph;
    }

    json j;
    file >> j;

    for (const auto& edge : j) {
        std::string from = edge["from"];
        std::string to = edge["to"];
        int weight = edge["weight"];
        graph.adjacency_list[from][to] = weight;
        // Ensure all nodes are in the adjacency list, even if they have no outgoing edges
        graph.adjacency_list[to];
    }

    return graph;
}

int main() {
    Graph graph = load_graph_from_json("../data/sample_graph.json");
    auto distances = dijkstra(graph, "A");
    
    std::cout << "Shortest distances from A:\n";
    for (const auto& [node, distance] : distances) {
        std::cout << node << ": " << distance << std::endl;
    }
    
    return 0;
}
