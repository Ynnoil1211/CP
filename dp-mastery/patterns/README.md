# DP Pattern Library

The 11 DP families of the 100-problem challenge. Each page contains a full description, the "when to recognize it" signals, the general template (state → base → transition → answer → complexity), the canonical problem family, and **your solved problems in that pattern**.

| # | Pattern | Doc | Folder | Solved | Status |
|---|---------|-----|--------|--------|--------|
| 1 | **Linear / Sequence DP** | [linear-dp.md](linear-dp.md) | `linear-dp/` | 5 (3 medium) | 🟡 In Progress |
| 2 | **Segmentation DP** | [segmentation-dp.md](segmentation-dp.md) | `segmentation-dp/` | 1 | 🟡 In Progress |
| 3 | **2D Grid / Path DP** | [2d-grid-dp.md](2d-grid-dp.md) | `2d-grid-dp/` | 0 | ⏳ Upcoming |
| 4 | **Two-Sequence DP (LCS)** | [lcs-dp.md](lcs-dp.md) | `lcs-dp/` | 0 | ⏳ Upcoming |
| 5 | **Knapsack DP** | [knapsack-dp.md](knapsack-dp.md) | `knapsack-dp/` | 0 | ⏳ Upcoming |
| 6 | **Interval DP** | [interval-dp.md](interval-dp.md) | `interval-dp/` | 0 | ⏳ Upcoming |
| 7 | **Tree DP** | [tree-dp.md](tree-dp.md) | `tree-dp/` | 0 | ⏳ Upcoming |
| 8 | **State Machine DP** | [state-machine-dp.md](state-machine-dp.md) | `state-machine-dp/` | 0 | ⏳ Upcoming |
| 9 | **Game Theory DP** | [game-theory-dp.md](game-theory-dp.md) | `game-theory-dp/` | 0 | ⏳ Upcoming |
| 10 | **Digit DP** | [digit-dp.md](digit-dp.md) | `digit-dp/` | 0 | 🔴 Advanced |
| 11 | **Bitmask DP** | [bitmask-dp.md](bitmask-dp.md) | `bitmask-dp/` | 0 | 🔴 Advanced |

## Quick Recognition Cheatsheet

| Keyword in problem | Likely pattern |
|---|---|
| Adjacent / consecutive / can't pick neighbors | Linear DP |
| Split / partition / segment into pieces | Segmentation DP |
| Grid / matrix / paths | 2D Grid DP |
| Two strings compared / transform one into another | Two-Sequence (LCS) DP |
| Subset sums to target / capacity / budget | Knapsack |
| Merge / burst / remove a range | Interval DP |
| Tree / binary tree / parent-child | Tree DP |
| Holding / not holding / cooldown / modes | State Machine DP |
| Small n (≤ 20), visit all, subsets | Bitmask DP |
| Count numbers in range satisfying X | Digit DP |
| Two players, optimal play, alternate turns | Game Theory DP |

## How this library is maintained

Every time a problem note is generated in `dp-mastery/[pattern]/`, the skill also updates the matching doc here: the problem is added to (or refreshed in) the **🟢 Solved Problems** table. If a pattern has no solved problems yet, its **⏳ Next up** list shows the planned entries.

**Last updated:** 2026-07-30
