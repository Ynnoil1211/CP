---
name: cp-quick-insight
description: Extracts and stores ultra-concise, high-density pattern flashcards for competitive programming problems in cp-insights/. Classifies by algorithm/sub-type, generates 1-2 sentence core insight, pattern triggers, personal breakthrough, 3-8 line code spotlight, and minimal example. Zero raw LaTeX syntax.
---

# CP Quick Insight Extractor Skill

## Overview

Ultra-fast skill that extracts the **single most important insight** that makes a CP problem solvable and persists it as an actionable flashcard in `cp-insights/`.

**Core Purpose:** Capture the "aha moment" and the structural pattern trigger. High density, zero fluff, instant pre-contest review.

**Primary Axis:** Categorized strictly by **algorithm pattern and sub-type** (e.g. `greedy-priority-based`, `math-number-theory`, `binary-search-answer-on-range`), NOT by rating or date.

**Format Standard:** 100% clean Markdown. **STRICTLY ZERO RAW LATEX** (no `$O(N)$`, no `$\sqrt{N}$`, no `\le`, no `\ge`). Always use backtick code spans like `O(N)`, `sqrt(N) <= 10^6`, `1 <= L <= 5`.

---

## What It Does

When the user provides:
- Problem title, platform/contest, and ID
- C++ / Python solution code
- Problem statement or brief summary
- (Optional) Rating, struggles, solve time

This skill:
1. Identifies the core algorithmic paradigm and sub-type using the **Type Classification System**.
2. Formulates the **Key Insight** (1-2 sentences with 💡).
3. Identifies the **Pattern Trigger** (what in the constraints or statement gives away the technique).
4. Captures the **Breakthrough** (the mental shift or implementation trick).
5. Extracts a clean **Code Spotlight** (3-8 lines of pure logic, stripped of I/O boilerplate).
6. Provides a minimal concrete **Example**.
7. Automatically saves the card to `cp-insights/[TYPE_KEY]/[ID]_[Title].md`.
8. Appends the breakthrough to `breakthroughs.md` under today's date.
9. **Never bloats the root `README.md`** with massive multi-row tables.

---

## Card Structure & Schema

Every insight card saved in `cp-insights/[TYPE_KEY]/` adheres to this exact template:

````markdown
# [Contest/ID] [Letter/ID] - [Title]

**Type:** [Algorithm] / [Sub-type]
**Rating / Context:** [Rating or Contest tier]
**Tag:** [hyphenated-tag]

## Key Insight

💡 [One to two sentence core transformation, invariant, or reduction]

## Pattern Trigger

[What specific constraints (e.g., N <= 10^5, K <= 20) or problem phrasing trigger this pattern]

## Breakthrough

[The single mental epiphany, implementation trick, or false-assumption break. 1-2 sentences, personal and concrete.]

## Code Spotlight

```cpp
// 3 to 8 lines containing the crux of the algorithm
```

## Example

Input: `...`
Output: `...`
Why: [Brief sentence connecting example directly back to the insight]

---

**Generated:** YYYY-MM-DD
````

---

## Type Classification System (Folder Keys)

Cards are stored under `cp-insights/[folder-key]/` using kebab-case `[algorithm]-[sub-type]`:

```text
Math
├── math-parity-check          — odd/even properties determine outcome
├── math-gap-analysis          — min/max adjacent differences
├── math-formula-development   — derive closed-form expression
├── math-modular-arithmetic    — mod cycles, periodicity
├── math-number-theory         — GCD, LCM, primes, factoring, O(sqrt(N)) divisors
├── math-combinatorics         — counting arrangements, combinations
├── math-pigeonhole-principle  — pigeonhole forces a boundary / duplicate
└── math-constraint-bounds     — leverage tiny bounds

Greedy
├── greedy-value-splitting     — separate by value threshold (e.g., max element)
├── greedy-boundary-testing    — only edge points matter (0, first, last)
├── greedy-sorting-based       — sort then decide in one pass (knapsack ordering)
├── greedy-priority-based      — heap / multiset for best candidate
└── greedy-interval-selection  — non-overlapping interval scheduling

Binary Search
├── binary-search-answer-on-range — search the continuous/discrete answer space (BSTA)
├── binary-search-monotonic-check — predicate monotonicity (TTTFFF)
└── binary-search-bounds          — lower_bound / upper_bound queries

Brute Force
├── brute-force-exhaustive-search — try all possibilities (small N)
├── brute-force-constraint-exploit — bounded prefix length (e.g., L <= 5)
└── brute-force-bitmask           — enumerate 2^N subsets

DP
├── dp-linear-progression      — 1D DP, one state dimension (min cost + count)
├── dp-state-exploration       — 2D+ DP, multiple dimensions
└── dp-knapsack-style          — take / skip decisions

Graph
├── graph-connectivity-check   — BFS/DFS reachability
├── graph-shortest-path        — BFS, Dijkstra, MST chord replacement
├── graph-topological-sort     — DAG post-order traversal
└── graph-tree-algorithms      — DFS with parent passing (no visited)

String
├── string-pattern-build       — polynomial rolling hash, Trie, prefix/suffix PIE
├── string-frequency-check     — char counts, histogram matching
└── string-stack-processing    — bracket / token matching with stacks

Game Theory
└── game-theory-parity-turn    — symmetric mirror moves, turn parity

Implementation
└── implementation-case-analysis — boundary cases, simulation without complex state
```

---

## Formatting Guidelines (Zero LaTeX Rule)

- ❌ NEVER USE: `$O(N)$`, `$O(N \log N)$`, `$\sqrt{N}$`, `$10^{11}$`, `$1 \le L \le 5$`, `\le`, `\ge`, `\sum`.
- ✅ ALWAYS USE: `O(N)`, `O(N log N)`, `sqrt(N)`, `10^11`, `1 <= L <= 5`, `<=`, `>=`, `sum(X_i)`.
- Use clean backticks for variable names, states, and formulas: `dp[i]`, `low <= mid`, `freq[x]`.

---

## Integration Points

1. **`breakthroughs.md`**: Whenever an insight card is saved, append the 1-line breakthrough to the central `breakthroughs.md` file grouped under the current date.
2. **`README.md` Raíz**: Never dump 20+ rows of cards into root `README.md`. Keep root `README.md` minimal, pointing directly to `cp-insights/`.
