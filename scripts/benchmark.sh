#!/bin/bash

set -e

echo "Building and benchmarking Dijkstra implementations..."

# Build C++ implementation
echo -e "\n=== Building C++ implementation ==="
cd cpp
mkdir -p build
cd build
cmake ..
make
cd ../..

# Build Go implementation
echo -e "\n=== Building Go implementation ==="
cd go
go build -o dijkstra_go dijkstra.go
cd ..

# Build Rust implementation
echo -e "\n=== Building Rust implementation ==="
cd rust
cargo build --release
cd ..

echo -e "\n=== Running benchmarks ==="

# Run C++ implementation
echo -e "\n--- C++ ---"
time ./cpp/build/dijkstra_cpp

# Run Go implementation
echo -e "\n--- Go ---"
time ./go/dijkstra_go

# Run Rust implementation
echo -e "\n--- Rust ---"
time ./rust/target/release/dijkstra_rust

echo -e "\nBenchmarking complete!"
