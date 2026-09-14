# Competitive Programming Portfolio & Knowledge Base

[![ICPC / RPC Contests](https://img.shields.io/badge/RPC%20Contests-07%20%7C%2008%20(NAQ)-orange?style=flat-square)](rpc_08_2026/)
[![DP Mastery](https://img.shields.io/badge/DP%20Mastery-12%2F100%20Medium-purple?style=flat-square)](dp-mastery/)
[![Problem Insights](https://img.shields.io/badge/CP%20Insights-23%20Flashcards-success?style=flat-square)](cp-insights/)
[![Algorithm Notebook](https://img.shields.io/badge/CP%20Plantilla-9%20Templates-blueviolet?style=flat-square)](cp-plantilla/)

A structured, production-grade repository cataloging algorithmic problem solving, collegiate contest post-mortems (RPC / ICPC), dynamic programming specialization tracks, and core paradigm heuristics.

---

## 🧭 Repository Navigation

| Section | Focus Area | Description |
| :--- | :--- | :--- |
| 🏆 [**RPC 08 (NAQ 2023-2024)**](#-rpc-08-septiembre-2026--naq-2023-2024-editorial) | Contest Editorial | Full 12-problem autopsy, verified AC solutions, and upsolving guide |
| 🧠 [**DP Mastery Roadmap**](#-dynamic-programming-mastery-100-medium-challenge) | LeetCode DP 100 | 11 pattern tracks, recognition cheatsheet, and state-transition models |
| ⚡ [**CP Insights Flashcard Catalog**](#-flagship-cp-insights-catalog-cp-insights) | Pattern Engineering | Flagship library of 23 high-density insight flashcards organized by paradigm |
| 📦 [**CP Plantilla Notebook**](#-cp-plantilla-reusable-algorithm--data-structure-notebook-cp-plantilla) | Reusable Codebook | Battle-tested CP algorithm templates and data structure implementations (Segment Trees, DFS, BFS) |
| 📚 [**Theory & Cheatsheets**](#-theory--algorithmic-cheatsheets-cp-theory) | Fundamental Theory | Ready-to-use reference material on Binary Search and STL Containers |

---

## 🏆 RPC 08 (Septiembre 2026) / NAQ 2023-2024 Editorial

> 📖 **Full Master Report & Autopsy:** [`rpc_08_2026/README.md`](rpc_08_2026/README.md)  
> 🎯 **Official Problemset:** [`rpc_08_2026/inputs/problemset/ProblemsetRPC08.pdf`](rpc_08_2026/inputs/problemset/ProblemsetRPC08.pdf)  
> 💻 **Team AC Solutions:** [`rpc_08_2026/inputs/solutions/`](rpc_08_2026/inputs/solutions/)  
> 🏛️ **Official Solutions (Arup Guha):** [`rpc_08_2026/inputs/official_solutions/`](rpc_08_2026/inputs/official_solutions/)

### Problem Matrix & Study Notes

| ID | Problem | Contest Status | Solution Source | Difficulty | Primary Paradigm | Complexity | Study Note |
| :---: | :--- | :---: | :---: | :---: | :--- | :---: | :---: |
| **A** | Contest Advancement | **AC** | Team (v3) | Div 2A | Two-Pass Greedy Filtering + Hash Set | $O(N \log N)$ | [Editorial Note](rpc_08_2026/outputs/notes/A_Contest_Advancement.md) |
| **B** | Digit Translation | *Upsolved* | Official | Div 2C / 1A | 1D Linear Dynamic Programming (Min + Count) | $O(N)$ | [Editorial Note](rpc_08_2026/outputs/notes/B_Digit_Translation.md) |
| **C** | Don't Hunger Together | *Upsolved* | Official | Div 1B / 2E | Binary Search on Answer + Min-Heap (EDF) | $O(I \cdot N \log N)$ | [Editorial Note](rpc_08_2026/outputs/notes/C_Dont_Hunger_Together.md) |
| **D** | Garden of Thorns | *Upsolved* | Official | Div 1C / 2F | Linearity of Expectation + Circle-Box Geometry | $O(N)$ | [Editorial Note](rpc_08_2026/outputs/notes/D_Garden_of_Thorns.md) |
| **E** | ICPC Team Generation | **AC** | Team (v1) | Div 2B | Monotonic Sliding Greedy | $O(N)$ | [Editorial Note](rpc_08_2026/outputs/notes/E_ICPC_Team_Generation.md) |
| **F** | Is Y a Vowel? | **AC** | Team (v1) | Div 3A | Linear String Simulation | $O(\|S\|)$ | [Editorial Note](rpc_08_2026/outputs/notes/F_Is_Y_a_Vowel.md) |
| **G** | Lines Per Hour | **AC** | Team (v2) | Div 3A | Greedy Fractional Knapsack Ordering | $O(N \log N)$ | [Editorial Note](rpc_08_2026/outputs/notes/G_Lines_Per_Hour.md) |
| **H** | Magnesium Supplementation | **AC** | Team (v3) | Div 2B | Number Theory ($O(\sqrt{N})$ Divisor Factorization) | $O(\sqrt{N} + D \log D)$ | [Editorial Note](rpc_08_2026/outputs/notes/H_Magnesium_Supplementation.md) |
| **I** | Missing Number | *Upsolved* | Official | Div 2C | Prefix Length Bounded Brute Force ($L \le 5$) | $O(\sum \|S\|)$ | [Editorial Note](rpc_08_2026/outputs/notes/I_Missing_Number.md) |
| **J** | Tip of Your Tongue | *Upsolved* | Official | Div 1B / 2E | Double Polynomial Hash + Hash Tables + PIE | $O(\sum \|W\| + \sum \|p\|)$ | [Editorial Note](rpc_08_2026/outputs/notes/J_Tip_of_Your_Tongue.md) |
| **K** | Very Important Edge | *Upsolved* | Official | Div 1C | Kruskal MST + Path Min Range Update with DSU | $O(M \log M)$ | [Editorial Note](rpc_08_2026/outputs/notes/K_Very_Important_Edge.md) |
| **L** | Water Journal | **AC** | Team (v2) | Div 3A | Boundary Analysis + Pigeonhole Principle | $O(N)$ | [Editorial Note](rpc_08_2026/outputs/notes/L_Water_Journal.md) |

### Key Takeaways & Contest Antipatterns
- **Hardcoded Sample Values ("Burned Example Syndrome"):** Never burn sample constants into cutoffs (e.g. `sum > 500` instead of `5 * b` in Problem G).
- **Silent Overflow via Inconsistent Typedefs:** Avoid blindly using `vi` (`vector<int>`) when inputs reach $10^{12}$; enforce 64-bit (`vll`) uniformly across accumulators and containers (Problem H).
- **Search Space vs. Input Magnitude:** Look for mathematical duality ($O(\sqrt{N})$ factorization) rather than iterating raw limits ($K \le 10^{12}$) (Problem H).
- **Complementary Condition Fallacy:** In boundary tracking with multiple invariants, avoid assuming `not A => B`; cover the joint failure case `not A and not B` (Problem L).

---

## 🧠 Dynamic Programming Mastery (100 Medium Challenge)

> 📊 **Master Tracker & Progress:** [`dp-mastery/README.md`](dp-mastery/README.md)  
> 🥇 **Distilled Rules & Traps:** [`dp-mastery/KEY_TIPS.md`](dp-mastery/KEY_TIPS.md)

A systematic program mastering 11 foundational dynamic programming patterns through 100 curated medium-level problems.

### 11 Pattern Tracks

| Pattern | Focus & Keywords | Progress | Status | Guide |
| :--- | :--- | :---: | :---: | :---: |
| **1. Linear DP** | Adjacent / consecutive / non-adjacent choices | 7 / 10 | 🟡 In Progress | [`linear-dp`](dp-mastery/linear-dp/README.md) |
| **2. Segmentation DP** | Split / partition / segment into valid chunks | 5 / 10 | 🟢 Family Complete | [`segmentation-dp`](dp-mastery/segmentation-dp/README.md) |
| **3. 2D Grid DP** | Grid traversal / bounded movement / matrix costs | 0 / 10 | ⏳ Upcoming | [`2d-grid-dp`](dp-mastery/2d-grid-dp/README.md) |
| **4. Two-Sequence (LCS)** | String transformation / editing / alignment | 0 / 10 | ⏳ Upcoming | [`lcs-dp`](dp-mastery/lcs-dp/README.md) |
| **5. Knapsack DP** | Capacity constraints / subset sum / bounded choice | 2 / 10 | 🟡 In Progress | [`knapsack-dp`](dp-mastery/knapsack-dp/README.md) |
| **6. Interval DP** | Merge ranges / burst / optimal subsegment collapse | 1 / 10 | 🟢 Started | [`interval-dp`](dp-mastery/interval-dp/README.md) |
| **7. Tree DP** | Subtree aggregation / tree re-rooting / tree independent set | 0 / 8 | ⏳ Upcoming | [`tree-dp`](dp-mastery/tree-dp/README.md) |
| **8. State Machine DP** | Transaction states / cooldown periods / finite modes | 0 / 8 | ⏳ Upcoming | [`state-machine-dp`](dp-mastery/state-machine-dp/README.md) |
| **9. Game Theory DP** | Minimax / impartial games / Sprague-Grundy | 0 / 8 | ⏳ Upcoming | [`game-theory-dp`](dp-mastery/game-theory-dp/README.md) |
| **10. Digit DP** | Counting numbers in range $[A, B]$ satisfying digit predicates | 0 / 8 | 🔴 Advanced | [`digit-dp`](dp-mastery/digit-dp/README.md) |
| **11. Bitmask DP** | Small $N \le 20$, subset tracking, TSP formulations | 0 / 8 | 🔴 Advanced | [`bitmask-dp`](dp-mastery/bitmask-dp/README.md) |

---

## ⚡ Flagship CP Insights Catalog (`cp-insights/`)

A curated, high-density pattern flashcard library capturing the core invariant, trigger pattern, breakthrough epiphany, code spotlight, and worked trace for competitive programming problems.

| Paradigm | Problem ID & Name | Rating / Context | Key Invariant & Strategy | Insight Card |
| :--- | :--- | :---: | :--- | :---: |
| **Binary Search** | CF 1742E — Scuza | 1200 | Binary search on prefix-max step array | [`1742E_Scuza.md`](cp-insights/binary-search-answer-on-range/1742E_Scuza.md) |
| **Binary Search** | RPC 2026-08 C — Don't Hunger Together | 1800 | BSTA on continuous daily rate + EDF min-heap | [`RPC-2026-08-C_Dont_Hunger_Together.md`](cp-insights/binary-search-answer-on-range/RPC-2026-08-C_Dont_Hunger_Together.md) |
| **Brute Force** | CF 1914D — Three Activities | 1200 | Top-3 candidates per activity eliminate $O(N^3)$ | [`1914D_Three_Activities.md`](cp-insights/brute-force-exhaustive-search/1914D_Three_Activities.md) |
| **Brute Force** | RPC 2026-08 I — Missing Number | 1400 | Bounded prefix length $L \in [1, 5]$ removes branching | [`RPC-2026-08-I_Missing_Number.md`](cp-insights/brute-force-exhaustive-search/RPC-2026-08-I_Missing_Number.md) |
| **Dynamic Programming** | RPC 2026-08 B — Digit Translation | 1500 | Simultaneous min-length and way-count 1D DP | [`RPC-2026-08-B_Digit_Translation.md`](cp-insights/dp-linear-progression/RPC-2026-08-B_Digit_Translation.md) |
| **Game Theory** | CF 1527B1 — Palindrome Game (easy) | 1200 | Zero-count parity and turn order guarantee win | [`1527B1_Palindrome_Game_easy_version.md`](cp-insights/game-theory-parity-turn/1527B1_Palindrome_Game_easy_version.md) |
| **Graph Algorithms** | RPC 2026-08 K — Very Important Edge | 2000 | Kruskal MST + non-tree chord replacement via DSU | [`RPC-2026-08-K_Very_Important_Edge.md`](cp-insights/graph-shortest-path/RPC-2026-08-K_Very_Important_Edge.md) |
| **Greedy** | RPC 2026-08 E — ICPC Team Generation | 1100 | Monotonic preference bounds enable leftmost trio greedy | [`RPC-2026-08-E_ICPC_Team_Generation.md`](cp-insights/greedy-boundary-testing/RPC-2026-08-E_ICPC_Team_Generation.md) |
| **Greedy** | CF 1157E — Minimum Array | 1700 | Multiset member `lower_bound` for complement modulo $n$ | [`1157E_Minimum_Array.md`](cp-insights/greedy-priority-based/1157E_Minimum_Array.md) |
| **Greedy** | RPC 2026-08 A — Contest Advancement | 1000 | Two-pass school-quota filtering with rank order preservation | [`RPC-2026-08-A_Contest_Advancement.md`](cp-insights/greedy-priority-based/RPC-2026-08-A_Contest_Advancement.md) |
| **Greedy** | RPC 2026-08 G — Lines Per Hour | 800 | Fractional knapsack ordering: ascending sort by line count | [`RPC-2026-08-G_Lines_Per_Hour.md`](cp-insights/greedy-sorting-based/RPC-2026-08-G_Lines_Per_Hour.md) |
| **Greedy** | CF 1859A — United We Stand | 800 | Isolate $\max(a)$ into array $c$ to break divisibility | [`1859A_United_We_Stand.md`](cp-insights/greedy-value-splitting/1859A_United_We_Stand.md) |
| **Implementation** | CF 1845A — Forbidden Integer | 800 | Construct sum using $1$, or combinations of $2$ and $3$ | [`1845A_Forbidden_Integer.md`](cp-insights/implementation-case-analysis/1845A_Forbidden_Integer.md) |
| **Implementation** | RPC 2026-08 F — Is Y a Vowel? | 800 | Single-pass dual-counter classification | [`RPC-2026-08-F_Is_Y_a_Vowel.md`](cp-insights/implementation-case-analysis/RPC-2026-08-F_Is_Y_a_Vowel.md) |
| **Mathematics** | RPC 2026-08 D — Garden of Thorns | 2100 | Linearity of expectation decoupled via circle-box clipping | [`RPC-2026-08-D_Garden_of_Thorns.md`](cp-insights/math-formula-development/RPC-2026-08-D_Garden_of_Thorns.md) |
| **Mathematics** | CF 1853A — Desorting | 800 | Minimum adjacent difference determines operations needed | [`1853A_Desorting.md`](cp-insights/math-gap-analysis/1853A_Desorting.md) |
| **Mathematics** | CF 1837A — Grasshopper on a Line | 800 | Modular step decomposition: single leap or $x-1$ and $1$ | [`1837A_Grasshopper_on_a_Line.md`](cp-insights/math-modular-arithmetic/1837A_Grasshopper_on_a_Line.md) |
| **Mathematics** | CF 1855B — Longest Divisors Interval | 900 | Interval bound by smallest non-divisor $k - 1$ | [`1855B_Longest_Divisors_Interval.md`](cp-insights/math-number-theory/1855B_Longest_Divisors_Interval.md) |
| **Mathematics** | RPC 2026-08 H — Magnesium Supplementation | 1100 | $O(\sqrt{N})$ symmetric divisor search with 64-bit storage | [`RPC-2026-08-H_Magnesium_Supplementation.md`](cp-insights/math-number-theory/RPC-2026-08-H_Magnesium_Supplementation.md) |
| **Mathematics** | CF 1857A — Array Coloring | 800 | Parity invariant: sum equal parity iff count of odds is even | [`1857A_Array_Coloring.md`](cp-insights/math-parity-check/1857A_Array_Coloring.md) |
| **Mathematics** | RPC 2026-08 L — Water Journal | 800 | 4-state boolean matrix + pigeonhole extreme coverage | [`RPC-2026-08-L_Water_Journal.md`](cp-insights/math-pigeonhole-principle/RPC-2026-08-L_Water_Journal.md) |
| **String Processing** | RPC 2026-08 J — Tip of Your Tongue | 1900 | Rolling double-hash grouped by length + PIE for AND/OR/XOR | [`RPC-2026-08-J_Tip_of_Your_Tongue.md`](cp-insights/string-pattern-build/RPC-2026-08-J_Tip_of_Your_Tongue.md) |
| **String Processing** | RPC 2026-07 H — You You See What? | Div 2B | Stack-based bang-path loop and duplicate collapse | [`RPC-2026-07-H_You_You_See_What.md`](cp-insights/string-stack-processing/RPC-2026-07-H_You_You_See_What.md) |

---

## 📦 CP Plantilla: Reusable Algorithm & Data Structure Notebook (`cp-plantilla/`)

> 📖 **Full Template Documentation & Cheatsheet:** [`cp-plantilla/README.md`](cp-plantilla/README.md)

A modular, zero-overhead C++ competitive programming template library engineered for collegiate contests (ICPC / RPC) and Codeforces rounds. Designed for fast copy-paste integration, strong type safety, zero compiler warnings under `-Wall -Wextra -Werror`, and optimal cache efficiency.

### 1. Data Structures (`cp-plantilla/data-structures/`)
- 🌲 [`segment_tree_iterativo.cpp`](cp-plantilla/data-structures/segment_tree_iterativo.cpp) — Iterative Segment Tree on 0-indexed array with $2N$ space and semi-open intervals $[l, r)$. Ultra-fast due to cache locality.
- 🌿 [`segment_tree_recursivo.cpp`](cp-plantilla/data-structures/segment_tree_recursivo.cpp) — Recursive Segment Tree on $[l, r]$ closed ranges with complete vs. partial overlap logic and $4N$ node safety.
- 🎯 [`segment_tree_lazy_assignment.cpp`](cp-plantilla/data-structures/segment_tree_lazy_assignment.cpp) — Lazy Propagation Segment Tree for Range Assignment updates and Point Queries, featuring robust `has_lazy` boolean state.
- ➕ [`segment_tree_lazy_sum.cpp`](cp-plantilla/data-structures/segment_tree_lazy_sum.cpp) — Lazy Propagation Segment Tree for Range Addition and Range Sum Queries with explicit segment-length multiplication $(high - low + 1)$.

### 2. Graph Algorithms (`cp-plantilla/graphs/`)
- 🚪 [`dfs_camino_destino.cpp`](cp-plantilla/graphs/dfs_camino_destino.cpp) — Boolean DFS with early exit ("pass the ball backwards") recursion and path reconstruction for target-reachability queries.
- 💰 [`dfs_componente_min_costo.cpp`](cp-plantilla/graphs/dfs_componente_min_costo.cpp) — Void DFS passing accumulator metrics by reference (`min_costo`, `suma_total`, `tamano`), solving connected component grouping problems like CF "Rumor".
- 🔄 [`dfs_ordenamiento_rutas.cpp`](cp-plantilla/graphs/dfs_ordenamiento_rutas.cpp) — Pre-Order (discovery) vs. Post-Order (finishing) traversals, featuring DAG Topological Sort with 3-color cycle detection.
- 🌳 [`dfs_arbol_sin_visited.cpp`](cp-plantilla/graphs/dfs_arbol_sin_visited.cpp) — Lightweight Tree DFS passing `(actual, padre)` avoiding all `visited` array allocations and resets, computing subtree sizes and depths.
- 🌊 [`bfs_distancia.cpp`](cp-plantilla/graphs/bfs_distancia.cpp) — Queue-based Breadth-First Search with the sacred push-time distance marking invariant and shortest path reconstruction.

---

## 📚 Theory & Algorithmic Cheatsheets (`cp-theory/`)

- 🎯 [**Búsqueda Binaria (Binary Search)**](cp-theory/binary-search/README.md) — Monotonicity predicates, discrete vs. continuous search space, lower/upper bound patterns.
- 📦 [**Estructuras de Datos STL**](cp-theory/data-structures/README.md) — Practical guide to `std::set`, `std::multiset`, `std::map`, and `std::unordered_map` operations and pitfalls.

---

## 📁 Repository Directory Structure

```text
CP/
├── .gitignore                             # C++, Java, Python, OS & CP scratch rules
├── README.md                              # Main portfolio and index (this file)
├── breakthroughs.md                       # Distilled cognitive breakthrough journal
│
├── rpc_08_2026/                           # RPC 08 (NAQ 2023-2024) Contest Package
│   ├── README.md                          # Master contest report & pedagogical autopsy
│   ├── inputs/
│   │   ├── problemset/ProblemsetRPC08.pdf # Official problemset PDF
│   │   ├── solutions/                     # Team AC solutions (A, E, F, G, H, L)
│   │   └── official_solutions/            # Official reference solutions (Arup Guha)
│   └── outputs/
│       └── notes/                         # 12 detailed problem study notes (A - L)
│
├── dp-mastery/                            # 100 LeetCode DP Medium Challenge
│   ├── README.md                          # Master tracker & pattern roadmap
│   ├── KEY_TIPS.md                        # Anti-tunneling heuristics & trap catalog
│   ├── linear-dp/                         # Linear / Sequence DP
│   ├── segmentation-dp/                   # Segmentation / Partition DP
│   ├── 2d-grid-dp/                        # 2D Grid / Matrix Path DP
│   ├── lcs-dp/                            # Two-Sequence / LCS DP
│   ├── knapsack-dp/                       # 0/1 & Unbounded Knapsack DP
│   ├── interval-dp/                       # Interval DP
│   ├── tree-dp/                           # Tree DP
│   ├── state-machine-dp/                  # State Machine DP
│   ├── game-theory-dp/                    # Game Theory DP
│   ├── digit-dp/                          # Digit DP
│   └── bitmask-dp/                        # Bitmask DP
│
├── cp-insights/                           # High-density pattern flashcard library (23 cards)
│   ├── binary-search-answer-on-range/     # CF 1742E, RPC 08-C
│   ├── brute-force-exhaustive-search/     # CF 1914D, RPC 08-I
│   ├── dp-linear-progression/             # RPC 08-B
│   ├── game-theory-parity-turn/           # CF 1527B1
│   ├── graph-shortest-path/               # RPC 08-K
│   ├── greedy-boundary-testing/           # RPC 08-E
│   ├── greedy-priority-based/             # CF 1157E, RPC 08-A
│   ├── greedy-sorting-based/              # RPC 08-G
│   ├── greedy-value-splitting/            # CF 1859A
│   ├── implementation-case-analysis/      # CF 1845A, RPC 08-F
│   ├── math-formula-development/          # RPC 08-D
│   ├── math-gap-analysis/                 # CF 1853A
│   ├── math-modular-arithmetic/           # CF 1837A
│   ├── math-number-theory/                # CF 1855B, RPC 08-H
│   ├── math-parity-check/                 # CF 1857A
│   ├── math-pigeonhole-principle/         # RPC 08-L
│   ├── string-pattern-build/              # RPC 08-J
│   └── string-stack-processing/           # RPC 07-H
├── cp-plantilla/                          # Production CP Template & Algorithm Library
│   ├── README.md                          # Master index, cheatsheet & compilation manual
│   ├── data-structures/                   # Iterative & recursive Segment Trees, Lazy Assignment & Sum
│   └── graphs/                            # DFS (exit, components, topo, tree) & BFS shortest path
│
└── cp-theory/                             # Algorithm & Data Structure Cheatsheets
    ├── binary-search/
    └── data-structures/
```
