---
name: cp-plantilla-manager
description: Governs, expands, and verifies production-ready competitive programming algorithm and data structure templates in cp-plantilla/. Enforces C++17 compilable standards with executable main() tests, Spanish pedagogical commentary, when-to-use heuristics, and automatic synchronization of cp-plantilla/README.md.
---

# CP Plantilla Manager Skill

## Overview

Governs the personal Competitive Programming template notebook in `cp-plantilla/`.

Every template in this library is designed to be **battle-tested, production-ready, and deeply educational**:
- Ready to copy-paste during live contests without hidden bugs or name collisions.
- Accompanied by clear Spanish pedagogical commentary explaining **cuándo se usa**, **invariantes de implementación** y **complejidad**.
- Guaranteed to compile with `g++ -O3 -std=c++17 -Wall -Wextra -Werror` with zero warnings.
- Verified with an executable demonstration in `main()`.

---

## Directory Taxonomy (`cp-plantilla/`)

```text
cp-plantilla/
├── README.md                                   # Master index, cheat-sheet & compilation guide
├── data-structures/                            # Segment Tree, Fenwick, DSU, Treap, Sparse Table
├── graphs/                                     # BFS, DFS, Dijkstra, Bellman-Ford, Floyd-Warshall, MST, Flow
├── math/                                       # Number Theory, Sieve, Modular Arithmetic, Matrix Exponentiation
├── strings/                                    # Rolling Hash, Trie, KMP, Z-Algorithm, Aho-Corasick
├── dp/                                         # Digit DP template, SOS DP, Convex Hull Trick
└── geometry/                                   # Point2D, Cross Product, Convex Hull, Polygon Area
```

---

## Template Standards & Quality Checklist

Every template added to `cp-plantilla/` must meet all 5 criteria:

1. **Compilation Guarantee**:
   - Compiles cleanly: `g++ -O3 -std=c++17 -Wall -Wextra -Werror [file.cpp]`.
   - No undefined behavior, no uninitialized variables, no signed/unsigned comparison warnings.

2. **Self-Contained Executable `main()`**:
   - Contains a minimal, deterministic example demonstrating each function (`build`, `update`, `query`, etc.) with assertions or printed outputs.

3. **Spanish Pedagogical Documentation**:
   - Header comments explaining:
     - **Propósito y Cuándo se usa**: Situaciones típicas de contest donde brilla.
     - **Invariantes Críticos**: Detalles sutiles que causan WA (e.g., intervalos semiabiertos `[l, r)`, multiplicación por longitud en Lazy Sum, marcado de nodos al hacer `push` en BFS, paso de padre en árboles).
     - **Complejidad**: Tiempo de construcción, actualización y consulta en notación Big-O limpia.

4. **Zero Raw LaTeX Policy**:
   - Use `O(N log N)`, `O(1)`, `[l, r)`, `<=`, `>=`, never raw math syntax like `$O(N)$` or `\le`.

5. **Index Synchronization**:
   - Add the template row to the table in [`cp-plantilla/README.md`](file:///C:/Users/Canton%20Gourmet/OneDrive/Documents/CP/cp-plantilla/README.md) with its paradigm, complexities, and golden rule.

---

## Standard Template Boilerplate

```cpp
#include <bits/stdc++.h>
using namespace std;

/**
 * ====================================================================
 * NOMBRE DEL ALGORITMO / ESTRUCTURA
 * ====================================================================
 * 
 * ¿CUÁNDO SE USA?
 * - [Situaciones concretas de problemas]
 * 
 * INVARIANTES CLAVE:
 * - [Indexación 0 vs 1, intervalos [l, r) vs [l, r], etc.]
 * 
 * COMPLEJIDAD:
 * - Construcción: O(...)
 * - Operación:    O(...)
 * - Espacio:      O(...)
 * ====================================================================
 */

// [Estructura o funciones limpias]

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // [Ejemplo de prueba mínimo con verificación]
    return 0;
}
```

---

## Root README Protection
Never inject template code blocks into the root `README.md`. Keep the main index minimal, pointing exclusively to `cp-plantilla/README.md`.
