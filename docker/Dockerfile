FROM ubuntu:22.04

# Install system dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    golang \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Install Rust
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"

WORKDIR /app
COPY . .

# Build all implementations
RUN cd cpp && mkdir build && cd build && cmake .. && make
RUN cd go && go build -o dijkstra_go dijkstra.go
RUN cd rust && cargo build --release

CMD ["./scripts/benchmark.sh"]
