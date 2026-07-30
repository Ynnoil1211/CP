---
name: cp-quick-insight
description: Extracts and returns ONLY the key insight for a competitive programming problem. Given code and problem statement, returns a one-sentence core idea that makes the problem solvable. Minimal, fast, actionable. Use for quick problem analysis during solving sessions or weekly reviews.
---

# CP Quick Insight Extractor Skill

## Overview

Ultra-fast skill that extracts the **single most important insight** that makes a CP problem solvable.

**Core Purpose:** Capture the "aha moment" — that one idea that transforms the problem from unsolvable to obvious.

**Output:** One well-crafted sentence (max 2 lines).

**Auto-Storage:** Every insight is automatically saved as a card to `cp-insights/[TYPE]/[ID]_[Title].md` with the key insight, the type classification, a code spotlight showing where the insight manifests, and a worked example.

**Primary Axis:** Insights are classified by **type** (e.g., `Math / Parity Check`, `Greedy / Value Splitting`), not by rating. Rating is included _inside_ each card — rating folders are no longer used.

## What It Does

Input:

- C++ code (your solution)
- Problem statement

Output:

```
💡 Key Insight for [Problem ID] - [Title]

[One powerful sentence that captures the core idea]

📁 Saved to cp-insights/[TYPE]/[ID]_[Title].md
```

The card file includes three sections:

- **Key Insight** — the one-sentence core idea
- **Breakthrough** — the specific implementation trick or mental model you couldn't think of (personal, concrete, 1 sentence)
- **Code Spotlight** — 3-5 key lines from your solution that implement the insight
- **Example** — a minimal worked example showing the insight in action

## When to Use

### Use Case 1: Quick Check

After solving, grab the insight instantly:

```
Just solved 1903A.

Code: [...]
Statement: [...]

What's the insight?
```

### Use Case 2: Weekly Review

Rapid insights for all problems solved:

```
Problems solved this week: 1900A, 1901B, 1902C

Extract insights for each.
```

### Use Case 3: Problem Analysis

When reviewing or re-studying:

```
I'm reviewing 1903A. What's the key insight I should remember?
```

### Use Case 4: Pattern Recognition

Build a quick reference of insights by algorithm:

```
Extract insights for all 800-rated problems I've solved.
Tag by algorithm type.
```

## Output Format

### Standard Response

```
💡 Key Insight for [Problem ID] - [Title]

[One powerful sentence that captures the core idea]

---
Type: [Algorithm] / [Sub-type]      # ← primary axis
Rating: [800-2000]                   # ← inside the card
Tag: [Parity | Formula | Splitting | ...]
```

### With Context (Optional)

If needed for clarity:

```
💡 Key Insight for 1903A - United We Stand

Large numbers cannot divide small numbers.
Split the array into non-max values (b) and max values (c),
and no divisibility violation can occur.

---
Type: Greedy / Value Splitting
Rating: 800
Tag: max-value-separation
```

### Batch Response (Multiple Problems)

```
📋 Weekly Insights (5 problems)

1903A - United We Stand           [Greedy / Value Splitting · 800]
💡 Split by max value → eliminates divisibility constraints

1901A - Max Cost                  [Greedy / Boundary Testing · 800]
💡 Test all three boundary points: 0, first, last elements

1890A - Reorder String            [String / Frequency Check · 800]
💡 Frequency difference ≤1 allows "alternating" arrangement

1904A - Fork Checker              [Brute Force / Exhaustive Search · 800]
💡 Knight has exactly 8 moves; brute force all possibilities

1881A - Constrain Limit           [Math / Constraint Bounds · 800]
💡 Constraint n*m ≤ 25 allows exponential doubling (max 5 times)

---
Total: 5 problems | Types: Greedy (2), String (1), Brute Force (1), Math (1)
```

## Insight Quality Checklist

A good insight should:

✅ **Be one sentence** (or naturally splits into 1-2 sentences)
✅ **Reveal the core transformation** (what makes it solvable)
✅ **Be memorable** (something you'd write in your notes)
✅ **Avoid implementation details** (no specific code)
✅ **Connect to the algorithm** (name the technique if obvious)
✅ **Be actionable** (hint at what to do next)

## Examples

### ✅ Good Insights

```
1903A - United We Stand           [Greedy / Value Splitting · 800]
💡 Large numbers can't divide small numbers → separate by max value.

1899A - Mod Game                  [Game Theory / State Analysis · 800]
💡 If n%3 == 0, second player always wins; otherwise first.

1890A - Reorder String            [String / Frequency Check · 800]
💡 For alternating arrangement, frequency difference must be ≤1.

1904A - Fork Checker              [Brute Force / Exhaustive Search · 800]
💡 Knights attack exactly 8 positions; check all for overlap.

1881A - Constraint Limit          [Math / Constraint Bounds · 800]
💡 With n*m ≤ 25, doubling string at most 5 times finds answer.

1853A - Desorting                 [Math / Gap Analysis · 800]
💡 Min adjacent gap determines operations needed: gap/2 + 1.
```

### ❌ Bad Insights

```
❌ "Use a map to count frequencies"
   (Too implementation-focused)

❌ "Sort the array and iterate"
   (Describes code, not the idea)

❌ "Apply dynamic programming"
   (Too vague, doesn't explain what DP does here)

❌ "Check if all elements are the same"
   (Edge case, not the core insight)
```

## How to Use

### Direct Request

```
Extract key insight:

Code: [your solution]
Statement: [problem description]
```

### With Metadata

```
Extract insight for 1903A (rating 800):

Code: [...]
Statement: [...]
```

### Batch Extract

```
Extract insights for these problems:
- 1900A: [code] [statement]
- 1901B: [code] [statement]
- 1902C: [code] [statement]

Format as list, one per line.
```

### Default Behavior (Auto-Storage)

Every insight is automatically saved to `cp-insights/[TYPE]/[ID]_[Title].md`. No need to specify storage.

```
Extract insight for 1853A (rating 800, type: Math / Gap Analysis):

Code: [...]
Statement: [...]
```

### Alternative Locations (on request)

If you want a different destination, just say so:

```
Extract insight for 1853A and save it alongside the full notes.
# → saves to cp-notes/800/1853A_Desorting.md
```

```
Extract insight for 1853A and append to the master file.
# → appends to cp-insights/README.md
```

```
Extract insight for 1853A, no file.
# → output only
```

---

### Integration with Weekly Report

When the user sends Friday reports:

```
【第X周汇报】
完成了 5 道题
Problems: 1900A, 1901B, 1902C, 1903D, 1904E

Extract key insight for each problem.
```

Response:

```
✅ Weekly Insights Extracted

1900A: [Insight 1]
1901B: [Insight 2]
1902C: [Insight 3]
1903D: [Insight 4]
1904E: [Insight 5]
```

## Auto-Storage

Every insight you extract is **automatically saved** to `cp-insights/[TYPE]/[ID]_[Title].md`. No prompts, no options — just extract and store.

The **Breakthrough** entry is also logged to the central `breakthroughs.md` file at the repo root, grouped under today's date alongside entries from all other skills.

### Card Format

````markdown
# [ID] - [Title]

**Type:** [Algorithm] / [Sub-type]
**Rating:** [800-2000]
**Tag:** [short-hyphenated-tag]

## Key Insight

💡 [One-sentence core idea]

## Breakthrough

[The specific implementation trick or mental model that was the real "aha" moment — 1 sentence, personal.]

_Example: "Index by value, not by uniqueness — gaps in the number line matter."_

## Code Spotlight

```cpp
[3-5 key lines from your solution that directly implement the insight]
```

## Example

Input: [simple example that illustrates the insight]
Output: [expected result]
Why: [brief explanation connecting example back to the insight]

---

**Generated:** [date]
````

### What Each Section Does

| Section            | Purpose                                                                                                                   |
| ------------------ | ------------------------------------------------------------------------------------------------------------------------- |
| **Key Insight**    | The "aha moment" — what makes the problem solvable                                                                        |
| **Breakthrough**   | The specific trick you couldn't think of — personal, concrete, for your future self to remember                           |
| **Code Spotlight** | The specific lines where the insight becomes code. Usually 3-5 lines showing the core logic, stripped of I/O boilerplate. |
| **Example**        | A minimal input/output with a "Why" line connecting it back to the insight. Makes the abstraction concrete.               |

### Example Card (1853A - Desorting)

````markdown
# 1853A - Desorting

**Type:** Math / Gap Analysis
**Rating:** 800
**Tag:** min-adjacent-difference

## Key Insight

💡 Find the minimum adjacent difference; each operation widens one specific
gap by 2, so breaking sortedness needs (min_gap/2)+1 operations, or 0 if
already unsorted.

## Code Spotlight

```cpp
int mn = INT_MAX;
for (int i = 1; i < n; i++) {
    mn = min(mn, a[i] - a[i-1]);
}
cout << (mn < 0 ? 0 : mn / 2 + 1) << "\n";
```

## Example

Input: `[1, 3, 3, 5]` → gaps: `[2, 0, 2]`, min gap = 0
Output: `1`
Why: The zero gap means adjacent equal elements; one operation flips
the prefix/suffix and creates `[2, 3, 2, 4]` which is not sorted.

---

**Generated:** 2026-07-23
````

---

### Alternative Locations (on request)

The default is `cp-insights/[TYPE]/[ID]_[Title].md`. If you want a different destination, say so in your request:

| You say                       | Saves to                                                                    |
| ----------------------------- | --------------------------------------------------------------------------- |
| _(nothing — default)_         | `cp-insights/[TYPE]/[ID]_[Title].md`                                        |
| `"alongside full notes"`      | `cp-notes/[RATING]/[ID]_[Title].md` (updates existing note or creates card) |
| `"append to master"`          | `cp-insights/README.md` (accumulates all insights in one file)              |
| `"no file"` or `"don't save"` | Output only                                                                 |

---

### Review & Reference

Once stored, use these patterns to browse your collection:

| Goal                        | What to say                                       |
| --------------------------- | ------------------------------------------------- |
| Browse by type              | `"List cp-insights/math-gap-analysis/"`           |
| Browse all of one algorithm | `"List all cards under cp-insights/*greedy*/"`    |
| Open a specific card        | `"Show me 1853A_Desorting.md"`                    |
| Read all cards              | `"Show me all files in cp-insights/ recursively"` |
| Search by type              | `"Search all insight cards for 'Parity Check'"`   |
| Search by rating            | `"Search all insight cards for 'Rating: 800'"`    |
| Contest prep                | `"Give me 5 random insights from cp-insights/"`   |

## Type Classification System

Every insight is classified by **`[Algorithm] / [Sub-type]`**. The sub-type captures the specific technique or pattern that makes the problem solvable — this is the primary axis for organization and retrieval.

### Full Taxonomy

```
Math
├── Parity Check          — odd/even properties determine outcome
├── Gap Analysis          — min/max adjacent differences
├── Formula Development   — derive closed-form expression
├── Modular Arithmetic    — mod cycles, periodicity
├── Number Theory         — GCD, LCM, primes, factoring
├── Combinatorics         — counting arrangements, combinations
├── Prefix / Suffix       — cumulative sums, products, min/max
├── Arithmetic Progression — AP/GP patterns, averages
├── Constraint Bounds     — leverage small n, small value ranges
├── Contribution Sum      — count how many times each element contributes
├── Pigeonhole Principle  — pigeonhole forces a property
├── Invariant             — quantity that never changes

Greedy
├── Value Splitting       — separate by value threshold (e.g., max)
├── Boundary Testing      — only edge points matter (0, first, last)
├── Sorting-Based         — sort then decide in one pass
├── Interval Selection    — pick optimal non-overlapping intervals
├── Priority-Based        — use heap / multiset for best candidate
├── Frequency Exploit     — use counts to guide decisions

Brute Force
├── Exhaustive Search     — try all possibilities (small n)
├── Constraint Exploit    — small bounds make brute force viable
├── Generate & Check      — generate candidates, verify each
├── Bitmask Enumeration   — enumerate subsets via bitmasks
├── Permutation Try       — try all orderings

Binary Search
├── Answer on Range       — binary search the answer, check feasibility
├── Monotonic Check       — predicate is monotonic (TTTFFF)
├── Lower / Upper Bound   — find first/last position satisfying condition

DP
├── Linear Progression    — 1D DP, one state dimension
├── State Exploration     — 2D+ DP, multiple dimensions
├── KnapSack Style        — take / skip decisions
├── Interval DP           — range-based (dp[l][r])
├── Bitmask DP            — DP over subsets
├── Digit DP              — digit-by-digit construction

Graph
├── Connectivity Check    — BFS/DFS reachability
├── Component Analysis    — connected components count
├── Cycle Detection       — detect cycles in directed/undirected
├── Shortest Path         — BFS, Dijkstra, Floyd-Warshall
├── Union Find            — DSU for connectivity queries
├── Topological Order     — DAG ordering

String
├── Frequency Check       — char counts, can/can't arrange
├── Palindrome Check      — symmetry properties
├── Pattern Build         — construct string from pieces
├── Two Pointers          — sliding window, compare
├── Z / Prefix Function   — string matching

Game Theory
├── State Analysis        — determine win/lose per position
├── Nim-Style             — XOR-based (grundy numbers)
├── Symmetry Strategy     — mirror opponent's move
├── Parity Turn           — turn-based parity determines winner

Simulation
├── Direct Simulation     — follow rules exactly as written
├── Optimized Simulation  — skip redundant steps, jump ahead
├── Event Processing      — process events in order

Implementation
├── Case Analysis         — handle all scenarios (if-else tree)
├── Boundary Testing      — edge cases (empty, single, max)
├── Two Pointers          — efficient linear scanning
├── Coordinate Compression — map large values to small indices
```

> **Rating is always included _inside_ the card** — it's metadata, not the folder key.
> The type tag (e.g., `math-gap-analysis`) becomes the directory name.

### How to Determine the Type

1. Identify the **algorithm family** (Math, Greedy, Brute Force, etc.)
2. Pinpoint the **specific technique** that makes it solvable (Parity Check, Value Splitting, etc.)
3. Combine them: `"Math / Gap Analysis"`, `"Greedy / Value Splitting"`, `"Brute Force / Exhaustive Search"`
4. Derive the folder key: `math-gap-analysis`, `greedy-value-splitting`, `brute-force-exhaustive-search`

The folder key follows the pattern: `[algorithm]-[sub-type-in-kebab-case]`

## Tips

### Do This

✅ One insight per problem (not multiple ways to solve)
✅ Focus on the mathematical or logical core
✅ Make it memorable (you'll re-read this 6 months later)
✅ Include the "why" this insight works
✅ Connect to constraint sizes (why brute force works here)

### Don't Do This

❌ Multiple sentences per insight (defeats the purpose)
❌ Implementation details (that's for full notes)
❌ Multiple approaches (pick the intended one)
❌ Vague algorithm names ("use DP" is not an insight)

## Integration with Full Skill

| Skill                          | When to Use                                            | Output                                  | Persists                             |
| ------------------------------ | ------------------------------------------------------ | --------------------------------------- | ------------------------------------ |
| **cp-quick-insight**           | Fast review, weekly reports, pattern hunting           | Insight card (insight + code + example) | ✅ **Auto** to `cp-insights/[TYPE]/` |
| **cp-problem-notes-generator** | Deep study, building knowledge base, spaced repetition | Full structured note + code review      | ✅ Auto to `cp-notes/[RATING]/`      |

**Workflow:**

1. **During contest/practice:** Use `cp-quick-insight` (grab the insight) → auto-saved to `cp-insights/[TYPE]/`
2. **After solving:** Use `cp-problem-notes-generator` (build the full note) → auto-saved to `cp-notes/[RATING]/`
3. **Weekly review:** Use `cp-quick-insight` (rapid pattern recognition from stored cards)

## Example Scenarios

### Scenario 1: Just Solved, Need Quick Win

```

You: I just solved 1903A! What's the insight?

Code: [...]
Statement: [...]

Me: 💡 Key Insight: Large numbers can't divide small numbers →
split array by max value.

```

### Scenario 2: Weekly Review

```

You: Extract insights for 5 problems I solved this week.

[5 code + statement pairs]

Me: 📋 Weekly Insights
1900A: [insight]
1901B: [insight]
1902C: [insight]
1903D: [insight]
1904E: [insight]

```

### Scenario 3: Studying Before Contest

```

You: I want to review all Math / Gap Analysis insights.
Give me the list.

Me: 📋 Math / Gap Analysis (3 cards)

1853A - Desorting          [800]
💡 Min adjacent gap determines operations needed.

1690B - Array Decrements   [900]
💡 Track non-zero differences between adjacent elements.

1720A - Minimum LCM        [1000]
💡 Minimize adjacent gap to reduce LCM.

```

### Scenario 4: Pattern Hunting

```

You: Show me all insights tagged as "Value Splitting".

Me: 🎯 Greedy / Value Splitting (2 problems)

1903A - United We Stand    [800]
💡 Split by max value → eliminates divisibility.

1805A - Unfair Game        [900]
💡 Split values into balanced groups.

```

## Customization

### Insight Length

**Ultra-short** (default):

```

💡 Max value separation.

```

**Short:**

```

💡 Split by max → eliminates divisibility.

```

**Normal:**

```

💡 Large numbers can't divide small numbers →
split array into max values (c) and non-max values (b).

```

### Format

**Emoji style** (default):

```

💡 Key Insight: ...

```

**Minimal:**

```

Insight: ...

```

**With category:**

```

💡 [Category] - ...

```

## File Organization

The skill auto-creates and maintains the `cp-insights/` directory. You'll never have to create it manually.

```
my-cp-learning/
├── README.md                     # Master index (full notes by cp-problem-notes-generator)
├── cp-notes/                     # Full study notes (by rating — unchanged)
│   ├── 800/
│   ├── 900/
│   └── ...
├── cp-insights/                  # Auto-created insight cards (by type)
│   ├── math-parity-check/
│   │   ├── 1899A_Mod_Game.md
│   │   └── ...
│   ├── math-gap-analysis/
│   │   ├── 1853A_Desorting.md
│   │   └── ...
│   ├── greedy-value-splitting/
│   │   ├── 1903A_United_We_Stand.md
│   │   └── ...
│   ├── greedy-boundary-testing/
│   │   ├── 1901A_Max_Cost.md
│   │   └── ...
│   ├── brute-force-exhaustive-search/
│   │   ├── 1904A_Fork_Checker.md
│   │   └── ...
│   ├── string-frequency-check/
│   │   ├── 1890A_Reorder_String.md
│   │   └── ...
│   └── ...
└── .agents/
    └── skills/
        ├── cp-problem-notes-generator/
        │   └── SKILL.md
        └── cp-quick-insight/
            └── SKILL.md
```

> `cp-insights/` and type subdirectories are created automatically on first save.
> The master file `cp-insights/README.md` is only created if you request `"append to master"`.

### Folder Key Convention

Each type folder uses kebab-case: `[algorithm]-[sub-type]`

| Display Name                    | Folder Key                      |
| ------------------------------- | ------------------------------- |
| Math / Parity Check             | `math-parity-check`             |
| Math / Gap Analysis             | `math-gap-analysis`             |
| Greedy / Value Splitting        | `greedy-value-splitting`        |
| Greedy / Boundary Testing       | `greedy-boundary-testing`       |
| Brute Force / Exhaustive Search | `brute-force-exhaustive-search` |
| String / Frequency Check        | `string-frequency-check`        |
| Game Theory / State Analysis    | `game-theory-state-analysis`    |

---

**Designed for:** Fast insight extraction and pattern recognition
**Best for:** Quick reviews, weekly summaries, contest prep
**Pairs with:** cp-problem-notes-generator skill for comprehensive learning
