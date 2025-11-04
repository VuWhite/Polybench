package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"math"
	"os"
)

type Edge struct {
	From   string `json:"from"`
	To     string `json:"to"`
	Weight int    `json:"weight"`
}

type Graph struct {
	adjacencyList map[string]map[string]int
}

func loadGraphFromJSON(filename string) (*Graph, error) {
	file, err := ioutil.ReadFile(filename)
	if err != nil {
		return nil, err
	}

	var edges []Edge
	err = json.Unmarshal(file, &edges)
	if err != nil {
		return nil, err
	}

	graph := &Graph{
		adjacencyList: make(map[string]map[string]int),
	}

	for _, edge := range edges {
		if graph.adjacencyList[edge.From] == nil {
			graph.adjacencyList[edge.From] = make(map[string]int)
		}
		graph.adjacencyList[edge.From][edge.To] = edge.Weight
		// Ensure all nodes are in the adjacency list
		if graph.adjacencyList[edge.To] == nil {
			graph.adjacencyList[edge.To] = make(map[string]int)
		}
	}

	return graph, nil
}

func dijkstra(graph *Graph, start string) map[string]int {
	distances := make(map[string]int)
	for node := range graph.adjacencyList {
		distances[node] = math.MaxInt32
	}
	distances[start] = 0

	// Simple implementation without priority queue for simplicity
	visited := make(map[string]bool)

	for len(visited) < len(graph.adjacencyList) {
		// Find the unvisited node with the smallest distance
		minNode := ""
		minDist := math.MaxInt32
		for node, dist := range distances {
			if !visited[node] && dist < minDist {
				minDist = dist
				minNode = node
			}
		}

		if minNode == "" {
			break
		}

		visited[minNode] = true

		for neighbor, weight := range graph.adjacencyList[minNode] {
			if !visited[neighbor] {
				newDist := distances[minNode] + weight
				if newDist < distances[neighbor] {
					distances[neighbor] = newDist
				}
			}
		}
	}

	return distances
}

func main() {
	graph, err := loadGraphFromJSON("../data/sample_graph.json")
	if err != nil {
		fmt.Printf("Error loading graph: %v\n", err)
		os.Exit(1)
	}

	distances := dijkstra(graph, "A")
	fmt.Println("Shortest distances from A:")
	for node, distance := range distances {
		fmt.Printf("%s: %d\n", node, distance)
	}
}
