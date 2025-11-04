use std::collections::{BinaryHeap, HashMap};
use std::fs::File;
use std::io::BufReader;

#[derive(Debug, serde::Deserialize)]
struct Edge {
    from: String,
    to: String,
    weight: i32,
}

type Graph = HashMap<String, HashMap<String, i32>>;

fn load_graph_from_json(filename: &str) -> Result<Graph, Box<dyn std::error::Error>> {
    let file = File::open(filename)?;
    let reader = BufReader::new(file);
    let edges: Vec<Edge> = serde_json::from_reader(reader)?;

    let mut graph = Graph::new();
    for edge in edges {
        graph
            .entry(edge.from.clone())
            .or_insert_with(HashMap::new)
            .insert(edge.to.clone(), edge.weight);
        // Ensure all nodes are in the graph
        graph.entry(edge.to).or_insert_with(HashMap::new);
    }

    Ok(graph)
}

fn dijkstra(graph: &Graph, start: &str) -> HashMap<String, i32> {
    let mut distances = HashMap::new();
    for node in graph.keys() {
        distances.insert(node.clone(), i32::MAX);
    }
    distances.insert(start.to_string(), 0);

    let mut heap = BinaryHeap::new();
    heap.push((0, start.to_string()));

    while let Some((cost, node)) = heap.pop() {
        let cost = -cost; // Convert back to positive since we use max-heap as min-heap
        
        if cost > distances[&node] {
            continue;
        }

        if let Some(neighbors) = graph.get(&node) {
            for (neighbor, &weight) in neighbors {
                let next_cost = cost + weight;
                if next_cost < distances[neighbor] {
                    distances.insert(neighbor.clone(), next_cost);
                    heap.push((-next_cost, neighbor.clone()));
                }
            }
        }
    }

    distances
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let graph = load_graph_from_json("../data/sample_graph.json")?;
    let distances = dijkstra(&graph, "A");
    
    println!("Shortest distances from A:");
    for (node, distance) in distances {
        println!("{}: {}", node, distance);
    }
    
    Ok(())
}
