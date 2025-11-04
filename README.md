\# PolyBench: A Multi-Language FFI Benchmarking Tool



> Compare the performance of the same algorithm implemented in \*\*Rust\*\*, \*\*C++\*\*, and \*\*Go\*\*—all called from a unified Rust benchmark runner via Foreign Function Interface (FFI).



This project explores cross-language interoperability, runtime overhead, and language tradeoffs by benchmarking a non-trivial algorithm (e.g., Dijkstra’s shortest path) across three systems programming languages.



---



\## 🧠 Why This Project?



\- ✅ Leverage \*\*Rust\*\* for safe, high-level orchestration  

\- ✅ Use \*\*C++\*\* for zero-overhead systems code (from competitive programming background)  

\- ✅ Integrate \*\*Go\*\* via CGO for comparison with garbage-collected runtimes  

\- ✅ Run everything in a \*\*reproducible Docker environment\*\*  

\- ✅ Learn FFI, shared libraries, and cross-language calling conventions  



---



\## 🧩 Algorithm



Currently implements \*\*Dijkstra’s shortest path algorithm\*\* on a weighted directed graph provided as JSON:



```json

{

&nbsp; "nodes": 5,

&nbsp; "edges": \[

&nbsp;   {"from": 0, "to": 1, "weight": 4},

&nbsp;   {"from": 0, "to": 2, "weight": 1},

&nbsp;   ...

&nbsp; ],

&nbsp; "source": 0

}

