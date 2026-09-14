---
name: dp-learning-tracker
description: Generates structured DP problem study notes organized by pattern type across 11 DP tracks (Linear, Segmentation, 2D Grid, LCS, Knapsack, Interval, Tree, State Machine, Game Theory, Digit, Bitmask) in dp-mastery/. Captures state definitions, recurrence relations, and transitions with zero raw LaTeX. Updates dp-mastery/ dashboards without bloating root README.
---

# DP Learning Tracker Skill

## Overview

Specialized skill for the **100 LeetCode Medium DP Problems Challenge** and Dynamic Programming mastery in competitive programming.

Unlike general problem notes, Dynamic Programming mastery requires deliberate focus on:
- **Exact State Definition**: What does `dp[i]` or `dp[i][j]` represent in plain, unambiguous language?
- **Transitions & Invariants**: How do previous states combine, and why does this avoid double-counting?
- **Sub-pattern Recognition**: e.g., Fixed-offset Linear DP (Fibonacci/Robber) vs. Scan-all-previous (Word Break / LIS).
- **Zero Raw LaTeX**: All formulas, complexities, and variables use readable Markdown code spans (`O(N)`, `dp[i][j]`, `1 <= i <= N`), never unrendered LaTeX math syntax (`$...$`, `\le`, `\sum`).
- **Clean Indexing**: Updates only `dp-mastery/README.md` and pattern sub-track READMEs; leaves the repo root `README.md` clean and minimal.

---

## The 11 DP Pattern Tracks (`dp-mastery/`)

```text
dp-mastery/
├── README.md                  # Master progress dashboard (table, stats, weak areas)
├── KEY_TIPS.md                # Anti-tunneling heuristics & trap catalog
├── linear-dp/                 # 1D fixed-offset lookback (House Robber, Climbing Stairs)
├── segmentation-dp/           # 1D scan-all-previous over partition cuts (Word Break)
├── 2d-grid-dp/                # 2D cell paths, arrive from up/left (Unique Paths)
├── lcs-dp/                    # Two sequences in lockstep (LCS, Edit Distance)
├── knapsack-dp/               # Selection with capacity constraint (0/1 vs Unbounded)
├── interval-dp/               # Range [i, j] via split point k (Burst Balloons)
├── tree-dp/                   # Tree nodes via children include/exclude (House Robber III)
├── state-machine-dp/          # Position + discrete modes (Stock with Cooldown)
├── game-theory-dp/            # Optimal minimax play (Stone Game, Predict Winner)
├── digit-dp/                  # Digit-by-digit with tight/started flags
└── bitmask-dp/                # Subset states via bitmasks (N <= 20)
```

---

## Standard Note Schema (`dp-mastery/[pattern]/[ID]_[Title].md`)

````markdown
# [ID] - [Problem Title]

**Pattern Type:** [One of 11 DP patterns]
**Difficulty:** Medium
**LeetCode Link:** https://leetcode.com/problems/[slug]/
**Topics:** [Tags]

## Problem Statement

[1-2 sentences: what the problem asks]
[Constraints: N <= X, values <= Y]

## State Definition

### What is dp[i]? (or dp[i][j])
`dp[i] = [CLEAR DEFINITION]`

### Why This State?
[Why this state captures all information needed for the optimal substructure]

## Recurrence Relation

```text
dp[i] = [Formula with clear logic]

Base cases:
dp[0] = ...
```

### Transition Logic
1. Decision made at state i.
2. How previous states combine.
3. Why this avoids double-counting and ensures optimal substructure.

## Complexity Analysis
- **Time:** O(...) — [# states] * [work per state]
- **Space:** O(...) — Can optimize to O(...) with rolling variables?

## Clean Implementation (C++)

```cpp
// ≤ 25 lines of idiomatic core DP logic
```

## Common Pitfalls & Traps in This Pattern
- [Specific mistake: e.g. using greedy single pointer instead of nested loop in scan-all-previous]
- [Base case misinitialization]

## 🔑 Breakthrough
[The specific state definition trick or mental model shift that made the recurrence obvious. 1-2 sentences.]

## Your Code
```cpp
// Submitted solution
```

---
**Generated:** YYYY-MM-DD
````

---

## Formatting Guardrails
- **Zero LaTeX**: Always write `O(N * W)`, `dp[i] = max(...)`, `1 <= i <= N`, `<=`, `>=`. Never use `$`, `\le`, `\sum`, `\cdot`.
- **Root README Protection**: Never append long problem lists or tables to the root `README.md`.
- **Sync with `cp-insights/`**: On request or for milestone problems, create a companion card in `cp-insights/dp-[subtype]/` and log breakthrough to `breakthroughs.md`.
