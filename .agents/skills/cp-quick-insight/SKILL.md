---
name: cp-quick-insight
description: Extracts and returns ONLY the key insight for a competitive programming problem. Given code and problem statement, returns a one-sentence core idea that makes the problem solvable. Minimal, fast, actionable. Use for quick problem analysis during solving sessions or weekly reviews.
---

# CP Quick Insight Extractor Skill

## Overview

Ultra-fast skill that extracts the **single most important insight** that makes a CP problem solvable.

**Core Purpose:** Capture the "aha moment" — that one idea that transforms the problem from unsolvable to obvious.

**Output:** One well-crafted sentence (max 2 lines).

**Auto-Storage:** Every insight is automatically saved as a card to `cp-insights/[RATING]/[ID]_[Title].md` with the key insight, a code spotlight showing where the insight manifests, and a worked example.

## What It Does

Input:

- C++ code (your solution)
- Problem statement

Output:

```
💡 Key Insight for [Problem ID] - [Title]

[One powerful sentence that captures the core idea]

📁 Saved to cp-insights/[RATING]/[ID]_[Title].md
```

The card file includes three sections:

- **Key Insight** — the one-sentence core idea
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
Algorithm: [Category]
Difficulty: [Rating]
```

### With Context (Optional)

If needed for clarity:

```
💡 Key Insight for 1903A - United We Stand

Large numbers cannot divide small numbers.
Split the array into non-max values (b) and max values (c),
and no divisibility violation can occur.

---
Algorithm: Greedy (value-based splitting)
Difficulty: 800
Pattern: Leverage mathematical properties for problem simplification
```

### Batch Response (Multiple Problems)

```
📋 Weekly Insights (5 problems)

1903A - United We Stand
💡 Split by max value → eliminates divisibility constraints

1901A - Max Cost
💡 Test all three boundary points: 0, first, last elements

1890A - Reorder String
💡 Frequency difference ≤1 allows "alternating" arrangement

1904A - Fork Checker
💡 Knight has exactly 8 moves; brute force all possibilities

1881A - Constrain Limit
💡 Constraint n*m ≤ 25 allows exponential doubling (max 5 times)

---
Total: 5 problems | Algorithms: Greedy (3), Math (1), Brute Force (1)
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
1903A - United We Stand
💡 Large numbers can't divide small numbers → separate by max value.

1899A - Mod Game
💡 If n%3 == 0, second player always wins; otherwise first.

1890A - Reorder String
💡 For alternating arrangement, frequency difference must be ≤1.

1904A - Fork Checker
💡 Knights attack exactly 8 positions; check all for overlap.

1881A - Constraint Limit
💡 With n*m ≤ 25, doubling string at most 5 times finds answer.
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

Every insight is automatically saved to `cp-insights/[RATING]/[ID]_[Title].md`. No need to specify storage.

```
Extract insight for 1853A (rating 800, Greedy/Math):

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

## Auto-Storage (Default: Option B)

Every insight you extract is **automatically saved** to `cp-insights/[RATING]/[ID]_[Title].md`. No prompts, no options — just extract and store.

### Card Format

````markdown
# [ID] - [Title]

**Rating:** [Rating]
**Algorithm:** [Category]

## Key Insight

💡 [One-sentence core idea]

## Code Spotlight

```cpp
[3-5 key lines from your solution that directly implement the insight]
```
````

## Example

Input: [simple example that illustrates the insight]
Output: [expected result]
Why: [brief explanation connecting example back to the insight]

---

**Generated:** [date]

`````

### What Each Section Does

| Section | Purpose |
|---------|---------|
| **Key Insight** | The "aha moment" — what makes the problem solvable |
| **Code Spotlight** | The specific lines where the insight becomes code. Usually 3-5 lines showing the core logic, stripped of I/O boilerplate. |
| **Example** | A minimal input/output with a "Why" line connecting it back to the insight. Makes the abstraction concrete. |

### Example Card (1853A - Desorting)

````markdown
# 1853A - Desorting

**Rating:** 800
**Algorithm:** Greedy / Math

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

The default is `cp-insights/[RATING]/[ID]_[Title].md`. If you want a different destination, say so in your request:

| You say                       | Saves to                                                                    |
| ----------------------------- | --------------------------------------------------------------------------- |
| _(nothing — default)_         | `cp-insights/[RATING]/[ID]_[Title].md`                                      |
| `"alongside full notes"`      | `cp-notes/[RATING]/[ID]_[Title].md` (updates existing note or creates card) |
| `"append to master"`          | `cp-insights/README.md` (accumulates all insights in one file)              |
| `"no file"` or `"don't save"` | Output only                                                                 |

---

### Review & Reference

Once stored, use these patterns to browse your collection:

| Goal                 | What to say                                       |
| -------------------- | ------------------------------------------------- |
| Browse a rating      | `"List cp-insights/800/"`                         |
| Open a specific card | `"Show me 1853A_Desorting.md"`                    |
| Read all cards       | `"Show me all files in cp-insights/ recursively"` |
| Search by algorithm  | `"Search all insight cards for 'Greedy'"`         |
| Contest prep         | `"Give me 5 random insights from cp-insights/"`   |

## Algorithm Categories

When extracting insights, categorize by:

```

Greedy: Optimal choice at each step
DP: Optimal substructure + memoization
Graph: Path/connectivity problems
Math: Number properties, formulas
Brute Force: Exhaustive search (small constraints)
Binary Search: Monotonic property
Sorting: Order matters
String: Sequence manipulation
Simulation: Follow the rules
Game Theory: Win/lose states

```

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

| Skill                          | When to Use                                            | Output                                  | Persists                               |
| ------------------------------ | ------------------------------------------------------ | --------------------------------------- | -------------------------------------- |
| **cp-quick-insight**           | Fast review, weekly reports, pattern hunting           | Insight card (insight + code + example) | ✅ **Auto** to `cp-insights/[RATING]/` |
| **cp-problem-notes-generator** | Deep study, building knowledge base, spaced repetition | Full structured note + code review      | ✅ Auto to `cp-notes/[RATING]/`        |

**Workflow:**

1. **During contest/practice:** Use `cp-quick-insight` (grab the insight) → auto-saved to `cp-insights/[RATING]/`
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

You: I want to review my insights for 800-rated problems.
Give me the list.

Me: 📋 800-rated Insights (15 problems)

1. [insight]
2. [insight]
   ...

```

### Scenario 4: Pattern Hunting

```

You: Which 800-rated problems use Greedy?
Show their insights.

Me: 🎯 Greedy Problems (800-rated)
1903A: [insight]
1901A: [insight]
1890A: [insight]

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
├── README.md # Master index (full notes by cp-problem-notes-generator)
├── cp-notes/ # Full study notes (by rating)
│ ├── 800/
│ ├── 900/
│ └── ...
├── cp-insights/ # Auto-created insight cards (by rating)
│ ├── 800/
│ │ ├── 1853A_Desorting.md # [ID]_[Title].md
│ │ ├── 1859A_United_We_Stand.md
│ │ └── ...
│ ├── 900/
│ └── ...
└── .agents/
└── skills/
├── cp-problem-notes-generator/
│ └── SKILL.md
└── cp-quick-insight/
└── SKILL.md

```

> `cp-insights/` and rating subdirectories are created automatically on first save.
> The master file `cp-insights/README.md` is only created if you request `"append to master"`.

---

**Designed for:** Fast insight extraction and pattern recognition
**Best for:** Quick reviews, weekly summaries, contest prep
**Pairs with:** cp-problem-notes-generator skill for comprehensive learning

```

```
`````
