# CP Plantilla: Competitive Programming Template & Algorithm Library

A production-grade, battle-tested competitive programming template library engineered for collegiate contests (ICPC / RPC) and Codeforces rounds. Designed for zero overhead, strict cache locality, clean interfaces, and rapid copy-paste deployment.

---

## 🧭 Master Template Catalog

### 1. Data Structures (`data-structures/`)

| Template | Paradigm | Build / Init | Query | Update | Space | Primary Invariant / Key Rule of Thumb |
| :--- | :--- | :---: | :---: | :---: | :---: | :--- |
| [**Segment Tree Iterativo**](data-structures/segment_tree_iterativo.cpp) | Range Query (Iterative) | O(N) | O(log N) | O(log N) | 2N | **Semi-open interval `[l, r)`**: Bitwise `l & 1` and `r & 1`. Query closed interval `[L, R]` with `query(L, R + 1)`. 2x-4x faster than recursive due to cache locality. |
| [**Segment Tree Recursivo**](data-structures/segment_tree_recursivo.cpp) | Divide & Conquer / RMQ | O(N) | O(log N) | O(log N) | 4N | **Segment bounds `[low, high]`**: Compare against query `[l, r]`. Total overlap (`l <= low && high <= r`) vs. disjoint (`high < l \|\| low > r`). Safe 4N tree size. |
| [**Segment Tree Lazy Assignment**](data-structures/segment_tree_lazy_assignment.cpp) | Lazy Propagation | O(N) | O(log N) | O(log N) | 4N | **Range Assignment / Point Query**: Push parent's assigned value down to children before descending. Use boolean `has_lazy` flag to safely support `0` and negative values. |
| [**Segment Tree Lazy Sum**](data-structures/segment_tree_lazy_sum.cpp) | Lazy Propagation | O(N) | O(log N) | O(log N) | 4N | **Range Add / Range Sum**: Must multiply lazy by segment length `(high - low + 1)`. Accumulate additively (`lazy[c] += lazy[node]`). Always use 64-bit `long long`. |

---

### 2. Graph Algorithms (`graphs/`)

| Template | Paradigm | Time Complexity | Auxiliary Space | Key Pattern & Gotchas |
| :--- | :--- | :---: | :---: | :--- |
| [**DFS Camino a Destino**](graphs/dfs_camino_destino.cpp) | Depth-First Search | O(V + E) | O(V) | **Early Exit ("Pass the Ball Backwards")**: Returns `bool`. As soon as target is found, unwinds call-stack with `return true`. Avoids exhaustive exploration when checking reachability. |
| [**DFS Componente & Costo Mínimo**](graphs/dfs_componente_min_costo.cpp) | DFS / Connected Components | O(V + E) | O(V) | **Accumulator by Reference**: `void` signature passing `long long& min_costo`, `long long& sum`, `int& size`. Classic CF "Rumor" pattern to collect global statistics per island. |
| [**DFS Ordenamiento y Rutas**](graphs/dfs_ordenamiento_rutas.cpp) | DFS / Topological Sort | O(V + E) | O(V) | **Pre-Order vs. Post-Order**: Pre-order (`push` before neighbors) = discovery tree / Euler tour. Post-order (`push` after neighbors) reversed = Topological Sort in DAGs with 3-color cycle detection. |
| [**DFS Árbol sin Visited**](graphs/dfs_arbol_sin_visited.cpp) | Tree DFS / Tree DP | O(N) | O(H) | **Parent-Passing Optimization**: Takes `(int u, int p)`. Evaluates `if (v != p)` to prune back-edges in acyclic trees. Eliminates `visited` array allocation and reset overhead. |
| [**BFS Camino Más Corto**](graphs/bfs_distancia.cpp) | Breadth-First Search | O(V + E) | O(V) | **Push-Time Marking Invariant**: Always update distance and mark visited *at the time of push* into queue (never at pop!) to prevent exponential queue explosion. `-1` acts as unvisited sentinel. |

---

## ⚡ Compilation & Testing Guide

All templates are written in standard C++17, are warning-free under `-Wall -Wextra -Werror`, and contain a runnable `main()` function demonstrating key use cases and asserting expected outputs.

### Compiling a Template:
```bash
# General compilation command
g++ -O3 -std=c++17 -Wall -Wextra <template_name>.cpp -o solution.exe

# Example: Iterative Segment Tree
g++ -O3 -std=c++17 -Wall -Wextra data-structures/segment_tree_iterativo.cpp -o st_it.exe
./st_it.exe

# Example: BFS Shortest Path
g++ -O3 -std=c++17 -Wall -Wextra graphs/bfs_distancia.cpp -o bfs_dist.exe
./bfs_dist.exe
```

---

## 🛠️ Implementation Cheat-Sheet & Common Pitfalls

### Segment Trees
1. **Iterative vs Recursive**:
   - Prefer **Iterative Segment Tree** for point-update + range-query problems. It has minimal code footprint, 2N memory, and superior cache locality.
   - Prefer **Recursive Segment Tree with Lazy Propagation** when handling range updates (range addition, range assignment, affine updates).
2. **Semi-open Interval `[l, r)`**:
   - When using iterative segment tree, remember that `r` is exclusive. Querying range `[0, n - 1]` requires calling `query(0, n)`. Querying `[L, R]` requires `query(L, R + 1)`.
3. **Lazy Multiplication Bug**:
   - In range sum segment trees, never do `tree[node] += lazy[node];`. It MUST be `tree[node] += lazy[node] * (high - low + 1);`.
4. **Integer Overflow**:
   - Range sum queries can easily exceed 2 * 10^9 when N <= 2 * 10^5 and A_i <= 10^9. Always type `tree`, `lazy`, and query return values as `long long`.

### Graphs & Trees
1. **BFS Queue Mark Invariant**:
   - Never mark nodes when popped from the queue. If node v has multiple incoming edges from the current BFS frontier, it will be pushed into the queue multiple times, leading to O(V^2) or O(E * V) blowup and TLE/MLE.
2. **Tree Traversal Memory**:
   - In tree problems, never allocate a `vector<bool> visited(N)`. Passing `parent` directly cuts memory by O(N) and eliminates `memset`/`vector` reallocation overhead between multiple test cases.
3. **Topological Sort Cycles**:
   - Always track 3 node states (`0 = unvisited`, `1 = in-stack`, `2 = completed`). Encountering a neighbor with state `1` indicates a back-edge (directed cycle), making topological ordering impossible.