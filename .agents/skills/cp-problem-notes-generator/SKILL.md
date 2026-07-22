---
name: cp-problem-notes-generator
description: Generates structured, concise English study notes for competitive programming problems, organizing them by rating in a hierarchical folder structure with a master index. Each note includes the user's actual code and a personalized code review. Use whenever the user provides a solved or attempted CP problem (title, rating, ID, C++ code, and problem statement).
---

# CP Problem Notes Generator Skill

## Overview

Automatically generates structured, concise English study notes for competitive programming problems and organizes them by rating in a hierarchical folder structure.

**Core Purpose:** Turn solved problems into reusable learning documents with consistent structure, enabling efficient review and pattern recognition across problem types.

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
5. ✅ Updates master index automatically
6. ✅ Tracks solve metrics (time, confidence, struggles)

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

```

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

1. **Analyze** the solution against the problem statement to identify the algorithm category and key insight.
2. **Review** the user's code — give constructive feedback on style, efficiency, correctness.
3. **Generate** a structured note using the template above, including the user's code and your review.
4. **Save** it to `cp-notes/[RATING]/[ID]_[Title_With_Underscores].md`.
5. **Update** the master index at `cp-notes/index.md`.

### Automatic Features

**1. Folder Organization**

```

cp-notes/
├── 800/
│ ├── 1903A_United_We_Stand.md
│ ├── 1901A_Max_Cost.md
│ └── ...
├── 900/
├── 1000/
├── 1100/
├── 1200/
└── index.md

````

**2. Master Index** (`cp-notes/index.md`)

```markdown
# CP Study Notes - Master Index

Total: 47 problems across 5 ratings

## By Difficulty

### 800 (15 problems)

- [1903A - United We Stand](./800/1903A_United_We_Stand.md)
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
````

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

- Generate 5 notes
- Organize into appropriate rating folders
- Update index
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
cp-notes/
├── 800/                                    # Difficulty tier
│   ├── 1903A_United_We_Stand.md           # [ID]_[Title].md
│   ├── 1901A_Max_Cost.md
│   └── ... (≤31 problems per tier)
│
├── 900/
├── 1000/
├── 1100/
├── 1200/
└── index.md                                # Master index
    ├── Summary stats
    ├── By difficulty (with links)
    ├── By algorithm (with links)
    └── Progress tracker table
```

### Index Schema

Master `index.md` contains:

1. **Header** — Total count, date range, rating coverage
2. **Quick Stats** — Problems/week, average time, confidence trend
3. **By Rating** — Grouped links to all problems at that rating
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

## Workflow Integration

### Weekly Routine

**Monday:** User sets a weekly target — generate notes as they solve problems.
**During Week:** User solves a problem and asks for a note — generate immediately.
**Friday:** User sends a batch report — generate all notes and update index with weekly stats.
**Sunday:** User reviews the index — help identify patterns and weak areas.

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
