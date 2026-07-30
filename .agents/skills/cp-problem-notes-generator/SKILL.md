---
name: cp-problem-notes-generator
description: Generates structured, concise English study notes for competitive programming problems, organizing them by rating in a hierarchical folder structure with a master index. Each note includes the user's actual code and a personalized code review. Use whenever the user provides a solved or attempted CP problem (title, rating, ID, C++ code, and problem statement).
---

# CP Problem Notes Generator Skill

## Overview

Automatically generates structured, concise English study notes for competitive programming problems and organizes them by rating in a hierarchical folder structure.

**Core Purpose:** Turn solved problems into reusable learning documents with consistent structure, enabling efficient review and pattern recognition across problem types.

**Insight Card Integration:** Every note automatically generates a companion **insight card** (via the `cp-quick-insight` format) — a compact reference saved to `cp-insights/[TYPE]/[ID]_[Title].md`. The two files complement each other: the full note for deep study, the insight card for fast review.

## What It Does

When the user provides:

- Problem title, rating, and ID
- Their C++ solution code
- Full problem statement
- (Optional) Struggles, insights, solve time

This skill:

1. ✅ Analyzes the solution against the problem
2. ✅ Reviews the user's code with actionable feedback
3. ✅ Generates a standardized English study note
4. ✅ Organizes it in `cp-notes/[RATING]/` folder
5. ✅ **Creates a companion insight card** in `cp-insights/[TYPE]/` (compact, for fast review)
6. ✅ Updates master index (`README.md`) automatically
7. ✅ Tracks solve metrics (time, confidence, struggles)

## Generated Note Structure

Every note follows this format:

````markdown
# [Problem ID] - [Title]

**Rating:** [Rating]
**Category:** [Algorithm Type]
**Solve Time:** [Minutes]
**Confidence:** [1-10]

## Problem Summary

[1-2 sentences what the problem asks]

## Key Insight

[The core idea that makes this solvable]

## Solution Approach

### Step 1: Observation

[What to notice about the problem]

### Step 2: Algorithm

[Which algorithm/technique to apply]

### Step 3: Implementation

[How to code it efficiently]

### Step 4: Edge Cases

[What can go wrong]

## Complexity Analysis

- **Time:** O(...)
- **Space:** O(...)

## Why This Works

[Brief correctness explanation]

## Common Mistakes

[Pitfalls to avoid in similar problems]

## Clean Code

[The solution condensed to ≤20 lines core logic]

## Key Takeaway

[Remember this for next time]

## 🔑 Breakthrough

[The one thing you couldn't think of — the implementation trick or mental model that was the real "aha" moment. 1-2 sentences, personal and concrete.]

_Example: "Index by value, not by uniqueness. Compressing to unique values loses gap info and invents fake adjacency conflicts — I kept trying to compress until I realized gaps in the number line matter."_

## Your Code

```cpp
[The user's actual submitted code — preserved verbatim]
```
````

> _This is your original solution. Keep it here to track how your coding style evolves over time._

## Code Review

**If the user solved the problem:**

- What's good about their approach
- What could be improved (style, efficiency, edge case handling)
- Alternative/better approaches worth learning
- Specific refactoring suggestions with code snippets

**If the user could not solve it:**

- Where their attempted approach went wrong
- Walkthrough of the correct solution
- Key missing insight they should study

---

**Generated:** [Date]
**Next Review:** [Suggested date based on spaced repetition]

## Companion Insight Card

Every full note automatically produces a **companion insight card** in `cp-insights/[TYPE]/`. This card is the fast-review counterpart to the full study note, following the `cp-quick-insight` skill conventions.

### Insight Card Format

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
[3-5 key lines from the solution that directly implement the insight]
```

## Example

Input: [simple example]
Output: [expected result]
Why: [brief explanation connecting example back to the insight]

---

**Generated:** [date]
````

### How to Derive Type & Tag

Use the **Type Classification System** below to classify every problem:

1. Identify the **algorithm family** (Math, Greedy, Brute Force, etc.)
2. Pinpoint the **specific technique** that makes it solvable (Parity Check, Value Splitting, etc.)
3. Combine them: `"Math / Gap Analysis"`, `"Greedy / Value Splitting"`, `"Brute Force / Exhaustive Search"`
4. Derive the folder key: `math-gap-analysis`, `greedy-value-splitting`, `brute-force-exhaustive-search`
5. Assign a short `Tag:` (e.g., `min-adjacent-difference`, `top-k-candidate-reduction`)

The folder key follows the pattern: `[algorithm]-[sub-type-in-kebab-case]`

### Type Classification System

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

\

## Usage

### Input Format

When the user provides input like:

```

Use the cp-problem-notes-generator skill.

**Problem:**

- Title: [Name]
- Rating: [800/900/1000/etc]
- ID: [1234A]
- Platform: Codeforces

**Your Code:**
[C++ solution]

**Problem Statement:**
[Full description]

**Optional:**

- Struggles: [What made it hard]
- Insight: [Core idea]
- Solve Time: [Minutes]
- Confidence: [1-10]

```

Follow these steps:

1. **Analyze** the solution against the problem statement to identify the algorithm category, key insight, and **type** (see Type Classification System below).
2. **Review** the user's code — give constructive feedback on style, efficiency, correctness.
3. **Generate** a structured note using the template above, including the user's code and your review.
4. **Save** the full note to `cp-notes/[RATING]/[ID]_[Title_With_Underscores].md`.
5. **Create the insight card** — generate a compact card at `cp-insights/[TYPE_KEY]/[ID]_[Title_With_Underscores].md` using the Insight Card Format below. Include a 3-5 line Code Spotlight from the solution and a minimal worked Example.
6. **Log the breakthrough** — append the Breakthrough entry (problem ID, title, and the one-liner) to the central `breakthroughs.md` file at the repo root, grouped under today's date.
7. **Update** the repo's root `README.md` (NOT `cp-notes/README.md` or `cp-notes/index.md`) — add the new problem entry under the correct rating and algorithm sections, update total counts and stats.

### Automatic Features

**1. Folder Organization**

```

README.md # Master index (repo root)
cp-notes/
├── 800/
│ ├── 1903A_United_We_Stand.md
│ ├── 1901A_Max_Cost.md
│ └── ...
├── 900/
├── 1000/
├── 1100/
└── 1200/

```

**2. Master Index** (`README.md`) — the repo's landing page

```markdown
# My CP Journey

**Total:** 47 problems across 5 ratings

## By Difficulty

### 800 (15 problems)

- [1903A - United We Stand](./cp-notes/800/1903A_United_We_Stand.md)
- ...

### 900 (12 problems)

- ...

## By Algorithm

### Greedy (8 problems)

### DP (5 problems)

### Graph (7 problems)

## Progress

| Week | Solved | Notes | Avg Time |
| ---- | ------ | ----- | -------- |
| 1    | 5      | 5     | 38m      |
```

**3. Smart Filename Convention**

- Pattern: `[RATING]/[ID]_[Title_With_Underscores].md`
- Example: `800/1903A_United_We_Stand.md`
- Auto-handle conflicts with `_v2`, `_v3` suffix

**4. Metrics Tracking**

- Solve time per problem
- Confidence rating evolution
- Struggle patterns by algorithm
- Time to mastery (when confidence ≥ 8)

## Integration Points

### Weekly Reports

When the user sends Friday reports:

```
【第X周汇报】
完成了 5 道题
Problems: 1900A, 1901B, 1902C, 1903D, 1904E

Create study notes for all and organize by rating.
```

Automatically:

- Generate 5 full notes → `cp-notes/[RATING]/`
- Generate 5 insight cards → `cp-insights/[TYPE]/`
- Log all breakthroughs → `breakthroughs.md`
- Organize into appropriate rating & type folders
- Update README index
- Calculate weekly stats

### Prompt Pattern

Quick request → generate a single note with minimal input.
Detailed request → use all provided metadata including struggles, insight, solve time, and confidence.

## Key Features

### ✓ Structured Analysis

- Automatic category detection (Greedy/DP/Graph/Math/etc)
- Algorithm explanation requirement
- Complexity analysis enforcement
- Edge case documentation

### ✓ Learning Optimization

- Connect to similar problems
- Flag prerequisite concepts
- Track solve progression
- Suggest review schedule

### ✓ Repository Ready

- Clean markdown format
- No external dependencies
- Git-friendly naming
- Export-ready structure

### ✓ Filtering Capabilities

- By rating (800, 900, 1000, ...)
- By algorithm (DP, Graph, Greedy, ...)
- By solve time (quick wins vs. hard problems)
- By confidence level

## File Organization Schema

```
README.md                                    # Master index (repo root)
                                             #   - Summary stats
                                             #   - By difficulty (with links)
                                             #   - By algorithm (with links)
                                             #   - Progress tracker table
cp-notes/                                    # Full study notes (by rating)
├── 800/                                     # Difficulty tier
│   ├── 1903A_United_We_Stand.md            # [ID]_[Title].md
│   ├── 1901A_Max_Cost.md
│   └── ...
├── 900/
├── 1000/
├── 1100/
└── 1200/
cp-insights/                                 # Insight cards (by type, auto-created)
├── math-gap-analysis/
│   └── 1853A_Desorting.md
├── brute-force-exhaustive-search/
│   └── 1914D_Three_Activities.md
├── implementation-case-analysis/
│   └── 1845A_Forbidden_Integer.md
├── math-modular-arithmetic/
│   └── 1837A_Grasshopper_on_a_Line.md
├── binary-search-answer-on-range/
│   └── 1742E_Scuza.md
└── ...
```

> `cp-insights/` and type subdirectories are created automatically on first insight card save.

### README Index Schema

The repo's `README.md` serves as the master index and contains:

1. **Header** — Total count, date range, rating coverage
2. **Quick Stats** — Problems/week, average time, confidence trend
3. **By Rating** — Grouped links to all problems at that rating (e.g. `./cp-notes/800/...`)
4. **By Algorithm** — Grouped links to all problems using that algorithm
5. **Progress Table** — Week-by-week metrics

## Data Captured Per Problem

```yaml
metadata:
  id: 1903A
  title: United We Stand
  rating: 800
  platform: Codeforces
  status: AC (Accepted)

metrics:
  solve_time: 15 minutes
  attempts: 1
  confidence_after: 7/10
  confidence_now: 8/10

learning:
  category: Greedy
  key_insight: |
    Large numbers cannot divide small numbers.
    Split by max value to guarantee no divisibility.

  struggles:
    - Didn't immediately see the max-value separation trick
    - First tried frequency-based distribution

  prerequisites:
    - Array sorting
    - Min/Max operations

  similar_problems:
    - 1904A_Fork_Checker
    - 1890A_Reorder_String

timestamps:
  created: 2026-07-22
  last_reviewed: 2026-07-25
  next_review: 2026-08-01
```

## Customization

### Note Density

**Concise Mode** (default): ~250-300 words, focus on Insight + Algorithm + Code.
**Detailed Mode**: ~600-800 words, includes full proof, multiple examples, related problems.
**Reference Mode**: ~100 words, flashcard style (front: Problem + Insight, back: Solution approach).

### Folder Schemes

Default is **By Rating** (`cp-notes/800/`, `cp-notes/900/`, etc.). The user may request alternatives:

- **By Algorithm**: `cp-notes/greedy/`, `cp-notes/dp/`, etc.
- **By Date**: `cp-notes/2026-07/`, `cp-notes/2026-08/`, etc.
- **Hybrid**: `cp-notes/800/greedy/`, `cp-notes/800/dp/`, etc.

## Tips

### Do

✅ Include full problem statement (easy to search later)
✅ Paste working code the user actually submitted
✅ Note what they struggled with (identifies weak areas)
✅ Specify confidence level (track growth)
✅ Tag algorithm category (for grouping)

### Don't

❌ Paste incomplete code snippets
❌ Omit constraints (impact complexity analysis)
❌ Skip edge cases (they will miss them again)
❌ Guess at difficulty rating (use actual source)
❌ Reuse old notes (each problem deserves fresh analysis)

## Repo Structure

The final repo looks like this:

```
my-cp-learning/
├── README.md                    # Master index — auto-updated
├── cp-notes/                    # Full study notes (by rating)
│   ├── 800/
│   │   ├── 1903A_United_We_Stand.md
│   │   └── ...
│   ├── 900/
│   ├── 1000/
│   └── ...
├── cp-insights/                 # Insight cards (by type, auto-created)
│   ├── math-gap-analysis/
│   ├── brute-force-exhaustive-search/
│   ├── implementation-case-analysis/
│   ├── math-modular-arithmetic/
│   ├── binary-search-answer-on-range/
│   └── ...
└── .agents/
    └── skills/
        ├── cp-problem-notes-generator/
        │   └── SKILL.md
        └── cp-quick-insight/
            └── SKILL.md
```

## Workflow Integration

### Weekly Routine

**Monday:** User sets a weekly target — generate notes as they solve problems.
**During Week:** User solves a problem and asks for a note — generate both the full note and the insight card immediately.
**Friday:** User sends a batch report — generate all notes and cards, update indexes, calculate weekly stats.
**Sunday:** User reviews the index and insight cards — help identify patterns and weak areas by type.

### Review Schedule

Suggest spaced repetition dates automatically:

- **Day 1:** Just solved
- **Day 3:** First review (confidence ≥ 8 = move on)
- **Day 7:** Check algorithm pattern
- **Day 14:** Compare with similar problems
- **Day 30:** Monthly mastery check

---

**Designed for:** Systematic competitive programming learning  
**Best for:** 800-1500 rating progression  
**Maintenance:** Auto-update index on each note generation
