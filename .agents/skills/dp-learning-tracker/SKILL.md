---
name: dp-learning-tracker
description: Generates structured DP problem study notes organized by pattern type (Linear, 2D Grid, Knapsack, Interval, Tree, Game Theory, Digit, Bitmask). Use whenever the user submits a LeetCode medium DP problem with their C++ solution, providing state definition, recurrence relation, complexity analysis, and pattern-type classification. Automatically organizes notes in dp-mastery/ folder hierarchy by pattern type and updates the master progress index. Perfect for tracking the 100 DP medium problems learning journey.
---

# DP Learning Tracker Skill

## Overview

**Core Purpose:** Transform solved LeetCode DP medium problems into structured, pattern-focused study notes that build mental models of dynamic programming techniques.

This skill is designed for the **100 DP Medium Problems Challenge**. Unlike general CP problem notes, DP requires understanding _state spaces_ and _recurrence relations_—not just algorithms. This skill captures that learning intentionally.

**Key Difference from CP Skill:**

- CP skill organizes by _rating_ (800, 900, 1000)
- DP skill organizes by _pattern type_ (Linear DP, 2D Grid, Knapsack, etc.)
- DP skill focuses on _state definition_ and _transitions_, not just solution walkthrough

## What It Does

When the user provides:

- LeetCode problem ID and title
- Their C++ solution code
- Solve time, confidence, struggles (optional)

This skill:

1. ✅ Classifies the problem by **DP pattern type** (one of 8 categories)
2. ✅ Extracts and documents the **state definition** (what does `dp[i]` or `dp[i][j]` represent?)
3. ✅ Writes the **recurrence relation** with clear transitions
4. ✅ Provides complexity analysis
5. ✅ Generates a **structured study note** in `dp-mastery/[PATTERN]/`
6. ✅ Updates the master progress index (`dp-mastery/README.md`)
7. ✅ Tracks solve metrics and identifies pattern mastery

## DP Pattern Types (8 Categories)

The skill classifies every problem into one of these 8 patterns:

| Pattern            | Characteristics                                                    | Example Problems                                         | Folder            |
| ------------------ | ------------------------------------------------------------------ | -------------------------------------------------------- | ----------------- |
| **Linear DP**      | 1D state, sequential decisions on array/string                     | House Robber, Climbing Stairs, Decode Ways               | `linear-dp/`      |
| **2D Grid DP**     | 2D state for grid paths, matrix traversal                          | Unique Paths, Minimum Path Sum, Dungeon Game             | `2d-grid-dp/`     |
| **Knapsack**       | Selection problems with capacity constraints                       | Target Sum, Partition Equal Subset Sum, Coin Change      | `knapsack-dp/`    |
| **Interval DP**    | Range/subarray optimization, work from smaller intervals to larger | Burst Balloons, Palindrome Partitioning II, Remove Boxes | `interval-dp/`    |
| **Tree DP**        | Decisions on tree structure, node choice, parent-child relations   | House Robber III, Maximum Product of Splitted Tree       | `tree-dp/`        |
| **Game Theory DP** | Optimal play against opponent, win/lose states                     | Predict the Winner, Can I Win, Stone Game                | `game-theory-dp/` |
| **Digit DP**       | Digit-by-digit constraint satisfaction, number properties          | Count Numbers with Unique Digits (harder, advanced)      | `digit-dp/`       |
| **Bitmask DP**     | DP over subset states via bitmask, assignment problems             | Travelling Salesman Variant, Steiner Tree (harder)       | `bitmask-dp/`     |

## Generated Note Structure

Every problem generates a markdown file with this exact structure:

```markdown
# [ID] - [Problem Title]

**Pattern Type:** [One of 8 categories above]
**Difficulty:** Medium
**LeetCode Link:** https://leetcode.com/problems/[slug]/
**Topics:** [Related DP concepts]

## Problem Statement

[1-2 sentences: what does this problem ask?]

[Constraints: n ≤ X, values ≤ Y, etc.]

## State Definition

### What is dp[i]? (or dp[i][j], etc.)
```

dp[i] = [CLEAR DEFINITION]

```

**Example:** If dp[i] = maximum robbery value considering houses 0..i, then:
- dp[0] = house[0] (rob first house only)
- dp[1] = max(house[0], house[1]) (rob first or second, not both)

### Why This State?

[Explain why this particular state captures the problem structure]

## Recurrence Relation

```

dp[i] = ... [Formula with clear logic]

Base case(s):
dp[0] = ...
[optional] dp[1] = ...

```

### Transition Logic

**Step 1:** [Explain what decision we make at state i]

**Step 2:** [Show how we combine previous states]

**Step 3:** [Why does this avoid double-counting / ensure correctness?]

### Example Walkthrough

Input: [concrete example]

```

dp[0] = ...
dp[1] = ...
dp[2] = ...
dp[3] = result

````

Why dp[3] = [value]? Because we chose to [decision], which led to [outcome].

## Implementation (C++)

```cpp
// [Clean, commented code ≤ 30 lines core logic]
````

**Key Implementation Notes:**

- [Memory layout / array indexing]
- [Base case handling]
- [Avoiding off-by-one errors]

## Complexity Analysis

- **Time:** O(...)
  - Reason: [# states] × [work per state]
- **Space:** O(...)
  - Can optimize to O(...) if [condition]?

## Why This Approach Works

[Convince yourself with proof outline or induction argument]

Example: "By induction on i: if dp[i-1] correctly represents the maximum robbery value for houses 0..i-1, then dp[i] = max(rob[i] + dp[i-2], dp[i-1]) correctly represents the maximum for houses 0..i, because any optimal solution either includes house i (requiring dp[i-2]) or excludes it (giving dp[i-1])."

## Common Pitfalls in This Pattern

- [Mistake 1 specific to this pattern type]
- [Mistake 2]
- [Mistake 3]

Example: "In Linear DP, students often forget the base case. If you don't initialize dp[0] correctly, the entire recurrence is wrong."

## Pattern Connection

**This is a [Pattern Type] problem because:**

1. [Characteristic 1 of this pattern evident here]
2. [Characteristic 2 evident here]
3. [Characteristic 3 evident here]

**Similar problems in this pattern:**

- [Problem ID] - [Title]
- [Problem ID] - [Title]

## Key Takeaway

[One sentence you'll remember next time you see a similar problem]

_Example:_ "For house robbery variants, always define dp[i] as 'result considering houses 0..i' and choose: include or exclude current house."

## 🔑 Breakthrough

[The one thing you couldn't think of — the state definition trick or recurrence insight that was the real "aha" moment. 1-2 sentences, personal and concrete.]

_Example: "Index by value, not by uniqueness. After building points[x] = x * freq[x], the House Robber recurrence applies directly — I was trying to compress the unique values, which lost the gap info."_

## Your Code

```cpp
[Your submitted C++ solution — preserved verbatim]
```

_This is your original work. Keep it to track how your style evolves._

## Solve Metrics

- **Solve Time:** [X minutes]
- **Attempts:** [N]
- **Confidence:** [1-10]
- **Struggles:** [What was hard?]
- **Submitted:** [Date]
- **Last Reviewed:** [Date]
- **Next Review:** [Suggested spaced repetition date]

---

**Generated:** [Date]

```

## File Organization

```

dp-mastery/
├── README.md # Master progress dashboard
│
├── linear-dp/ # Pattern: 1D sequential
│ ├── 198_House_Robber.md
│ ├── 213_House_Robber_II.md
│ ├── 70_Climbing_Stairs.md
│ └── [more linear DP problems]
│
├── 2d-grid-dp/ # Pattern: 2D grid paths
│ ├── 62_Unique_Paths.md
│ ├── 64_Minimum_Path_Sum.md
│ └── [more grid DP problems]
│
├── knapsack-dp/ # Pattern: Selection + capacity
│ ├── 416_Partition_Equal_Subset_Sum.md
│ ├── 494_Target_Sum.md
│ └── [more knapsack problems]
│
├── interval-dp/ # Pattern: Range optimization
│ ├── 1039_Minimum_Score_Triangulation.md
│ ├── 312_Burst_Balloons.md
│ └── [more interval DP problems]
│
├── tree-dp/ # Pattern: Tree decisions
│ ├── 337_House_Robber_III.md
│ └── [more tree DP problems]
│
├── game-theory-dp/ # Pattern: Optimal play
│ ├── 486_Predict_the_Winner.md
│ └── [more game theory problems]
│
├── digit-dp/ # Pattern: Digit constraints
│ ├── [digit DP problems - advanced]
│
└── bitmask-dp/ # Pattern: Subset enumeration
└── [bitmask DP problems - advanced]

````

## Master Progress Dashboard (README.md)

The skill automatically updates `dp-mastery/README.md` with:

```markdown
# 100 DP Medium Problems Challenge

**Progress:** X/100 problems solved
**Current Week:** [Week N]
**Target Completion:** [Estimated date]
**Overall Confidence:** [Average 1-10]

## Progress by Pattern Type

| Pattern | Solved | Target | % Complete | Avg Time | Mastery |
|---------|--------|--------|------------|----------|---------|
| Linear DP | 5/12 | 12 | 42% | 14m | 🟡 In Progress |
| 2D Grid DP | 0/12 | 12 | 0% | - | ⏳ Upcoming |
| Knapsack | 0/10 | 10 | 0% | - | ⏳ Upcoming |
| Interval DP | 0/10 | 10 | 0% | - | ⏳ Upcoming |
| Tree DP | 0/8 | 8 | 0% | - | ⏳ Upcoming |
| Game Theory | 0/8 | 8 | 0% | - | ⏳ Upcoming |
| Digit DP | 0/15 | 15 | 0% | - | ⏳ Advanced |
| Bitmask DP | 0/15 | 15 | 0% | - | ⏳ Advanced |

## By Week

### Week 1-2: Foundation (0/10 problems)
Pre-medium warmup: Climbing Stairs, House Robber basics
- [ ] 70 - Climbing Stairs
- [ ] 198 - House Robber
- ...

### Week 3: Linear DP (0/12 problems)
- [ ] 213 - House Robber II
- [ ] 139 - Word Break
- ...

### Week 4: 2D Grid DP + Knapsack (0/22 problems)
- [ ] 62 - Unique Paths
- [ ] 416 - Partition Equal Subset Sum
- ...

[Continue through Week 10]

## Problems Mastered (Confidence ≥ 8/10)

_List grows as you gain confidence_

## Weakest Patterns (Confidence ≤ 5/10)

_Identify patterns to review_

## Weekly Summary

| Week | Problems | Avg Time | Avg Confidence | Top Topic |
|------|----------|----------|---------------|-----------|
| 1 | 3 | 20m | 6/10 | Linear DP |
| 2 | 4 | 18m | 6.5/10 | 2D Grid |

---

**Last Updated:** [Date]
````

## Usage Workflow

### Input Format

When the user submits a problem:

````
Use the dp-learning-tracker skill.

**Problem:**
- ID: 198
- Title: House Robber
- Pattern Type: [Optional; Claude detects if not provided]

**Your Code:**
```cpp
[C++ solution]
````

**Optional Metadata:**

- Solve Time: 15 minutes
- Attempts: 2
- Confidence: 7/10
- Struggles: Forgot about dp[i-2] at first

**Problem Statement:**
[Full problem description or link]

```

### Steps

1. **Parse** the problem ID, title, solution code
2. **Classify** the problem into one of 8 DP pattern types (if not provided, infer from solution structure)
3. **Extract State Definition**: Analyze the code and problem to identify what `dp[i]` or `dp[i][j]` represents
4. **Derive Recurrence**: Write the recurrence relation and explain transitions
5. **Analyze Complexity**: Time and space complexity with reasoning
6. **Generate Full Note**: Write the markdown file with all sections above
7. **Save to Folder**: `dp-mastery/[PATTERN_TYPE]/[ID]_[Title].md`
8. **Update Dashboard**: Increment the counter in `dp-mastery/README.md`, update progress table
9. **Log the breakthrough** — append the Breakthrough entry (problem ID, title, and the one-liner) to the central `breakthroughs.md` file at the repo root, grouped under today's date.
10. **Calculate Next Review**: Suggest a spaced repetition date (Day 3, Day 7, Day 14, etc.)

## Pattern Detection Logic

Automatically infer the pattern type by analyzing:

- **State dimensions**: 1D array → Linear DP, 2D array → 2D Grid DP or Knapsack
- **Recurrence structure**: Single transition → Linear, multiple dimensions → 2D, etc.
- **Problem domain**: House/street → Linear, Grid traversal → 2D Grid, Selection + target → Knapsack, Range processing → Interval, Tree node → Tree DP, Game moves → Game Theory
- **Code patterns**: Bitmask usage → Bitmask DP, digit iteration → Digit DP

## Learning Milestones

The skill tracks **pattern mastery**:

- **Confidence ≥ 8/10 on 3 problems in a pattern** → Mark as "Comfortable with [Pattern]"
- **Confidence ≤ 5/10 across pattern** → Flag for review
- **Solve time < average for pattern** → Indicates internalization

## Integration with Your Weekly Routine

### Monday (Start of Week)

```

Weekly plan for Week 3: targeting 3 Linear DP problems.
Problems: 213, 139, 740

```

Remind the user of the pattern focus and suggest related problems.

### During Week (Problem Submission)

Each time the user solves and submits:

```

I just solved LeetCode 213. Code: [paste]. Took 18 minutes, confidence 6/10.
Struggled with understanding why we need TWO previous states.

```

Generate the full note, save it, update the dashboard.

### Friday (Weekly Review)

```

Weekly report for Week 3.
Solved: 213, 139, 740

```

Generate all notes, update progress tables, identify weak areas, suggest next week's focus.

## Tips for Best Results

### Do ✅

- Include full problem statement or link (helps identify state definition)
- Paste working C++ code you actually submitted
- Note what you struggled with (identifies weak mental models)
- Specify confidence level (tracks progress objectively)
- Include solve time (spot when you internalize a pattern)

### Don't ❌

- Paste incomplete or pseudo-code snippets
- Omit constraints (they affect complexity analysis)
- Skip explaining your solution (state definition must be extracted)
- Guess at solve time (this is a learning metric)

## Spaced Repetition Schedule

Suggested review dates based on initial confidence:

| Confidence | Day 1 | Day 3 | Day 7 | Day 14 | Day 30 |
|------------|-------|-------|-------|--------|--------|
| ≤5 | ✓ Solved | ⚠️ Review | ⚠️ Review | ⚠️ Review | ✓ Master |
| 6-7 | ✓ Solved | ✓ Review | ⚠️ Review | ✓ Master | - |
| 8-10 | ✓ Solved | ✓ Master | - | - | - |

## Customization Options

### Pattern Distribution

Default targets per week:

- **Week 1-2:** Foundation (10 problems, mixed easy)
- **Weeks 3-6:** Core patterns (50 problems across Linear, 2D, Knapsack, Interval, Tree, Game Theory)
- **Weeks 7-10:** Advanced patterns (40 problems: Digit DP, Bitmask DP, mixed hard)

User can adjust based on schedule.

### Note Density

- **Concise:** State + Recurrence + Code (~300 words)
- **Detailed:** Full with walkthrough example (~600 words, default)
- **Reference:** Flashcard style (~150 words)

---

**Designed for:** 100 LeetCode Medium DP Problems Challenge
**Best for:** CF 1200+ rating, ready for DP deep dive
**Output:** Structured markdown repository at `dp-mastery/`
**Maintenance:** Auto-updates dashboard on each problem submission
```
