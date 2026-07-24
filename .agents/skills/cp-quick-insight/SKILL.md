---
name: cp-quick-insight
description: Extracts and returns ONLY the key insight for a competitive programming problem. Given code and problem statement, returns a one-sentence core idea that makes the problem solvable. Minimal, fast, actionable. Use for quick problem analysis during solving sessions or weekly reviews.
---

# CP Quick Insight Extractor Skill

## Overview

Ultra-fast skill that extracts the **single most important insight** that makes a CP problem solvable.

**Core Purpose:** Capture the "aha moment" — that one idea that transforms the problem from unsolvable to obvious.

**Output:** One well-crafted sentence (max 2 lines).

**New: Storage Engine** — After extracting, you can persist the insight as a lightweight card in your repo. The skill offers 4 storage options and creates the file automatically.

## What It Does

Input:

- C++ code (your solution)
- Problem statement

Output:

```
💡 Key Insight: [One sentence that reveals the core idea]
```

**Then optionally:** persist the insight as a file in your repo (see [Storage Options](#storage-options)).

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

### With Storage (New)

After extracting, tell the agent where to save:

```
Extract insight for 1853A (rating 800, Greedy/Math):

Code: [...]
Statement: [...]

Store as Option B.
```

Or shorthand:

```
Insight for 1853A (800, Greedy/Math). Store in cp-insights/800/.

Code: [...]
Statement: [...]
```

Or append to master:

```
Extract insight for 1853A and save to the master file (Option C).

Code: [...]
Statement: [...]
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

## Storage Options

After extracting an insight, you can store it as a file. Choose one of four options. Each creates a lightweight **insight card** (not a full study note — that's the companion skill's job).

### Option A: Alongside Full Notes (if they exist) / New Lightweight Card

**Path:** `cp-notes/[RATING]/[ID]_[Title].md` (e.g. `cp-notes/800/1853A_Desorting.md`)

**Behavior:**

- If a full note already exists → update its `## Key Insight` section with the new insight
- If no note exists → create a lightweight insight card with minimal structure:
  ```markdown
  # [ID] - [Title]

  **Rating:** [Rating]
  **Algorithm:** [Category]

  ## Key Insight

  💡 [The insight]
  ```

**Best for:** You plan to eventually write a full note, or want insights and notes in one place.

---

### Option B: Dedicated Insights Directory

**Path:** `cp-insights/[RATING]/[ID]_[Title].md` (e.g. `cp-insights/800/1853A_Desorting.md`)

**Behavior:**

- Creates a separate `cp-insights/` directory tree mirroring the rating folders
- File format is the same lightweight card from Option A
- Keeps insights completely separate from full study notes

**Best for:** Clean separation of quick reference cards vs. deep study notes.

---

### Option C: Master Insight File (accumulated)

**Path:** `cp-insights/README.md`

**Behavior:**

- Creates/updates a single master file that accumulates **all** insights grouped by rating
- Appends the new insight under the correct rating section
- Maintains a running total at the top
- File format:
  ```markdown
  # 🧠 CP Insights Master

  **Total:** [N] insights across [M] ratings
  **Last Updated:** [date]

  ---

  ## 800 (12 insights)

  - **1853A - Desorting** — 💡 Minimal adjacent gap; each operation widens gap by 2 → (min_gap/2)+1.
  - **1859A - United We Stand** — 💡 Split by max value → eliminates divisibility.
    ...

  ## 900 (5 insights)

  ...
  ```

**Best for:** A single searchable cheat sheet you open before contests.

---

### Option D: Don't Store (current behavior)

Just print the insight to chat. No file created.

**Best for:** Quick checks, weekly reviews where you only want to read, not persist.

---

### Storage Decision Flow

When you ask to extract + store an insight, the agent will:

1. Extract the insight
2. Display it as usual
3. Ask **"Where should I save this?"** with the 4 options above
4. You pick one (or say "don't store") and the agent creates the file
5. For Options A-C, it also updates any index files (README.md or `cp-insights/README.md`)

> **Quick shorthand:** You can specify the option upfront, e.g.
> `"Extract insight for 1853A and store it as Option C"`

### Review & Reference

Once stored, use these patterns for review:

| Goal                     | What to say                                         |
| ------------------------ | --------------------------------------------------- |
| Read all stored insights | `"Show me all insights from cp-insights/README.md"` |
| Review 800-rated cards   | `"List cp-insights/800/"`                           |
| Find by algorithm        | `"Search all insight cards for 'Greedy'"`           |
| Open a card              | `"Show me 1853A_Desorting.md from cp-insights/800"` |
| Before a contest         | `"Give me 10 random insights from the master file"` |

## Algorithm Categories

When extracting insights, categorize by:

```
Greedy:       Optimal choice at each step
DP:           Optimal substructure + memoization
Graph:        Path/connectivity problems
Math:         Number properties, formulas
Brute Force:  Exhaustive search (small constraints)
Binary Search: Monotonic property
Sorting:      Order matters
String:       Sequence manipulation
Simulation:   Follow the rules
Game Theory:  Win/lose states
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

| Skill                          | When to Use                                            | Output                             | Persists?                                      |
| ------------------------------ | ------------------------------------------------------ | ---------------------------------- | ---------------------------------------------- |
| **cp-quick-insight**           | Fast review, weekly reports, pattern hunting           | 1 sentence insight                 | ✅ Optionally to `cp-notes/` or `cp-insights/` |
| **cp-problem-notes-generator** | Deep study, building knowledge base, spaced repetition | Full structured note + code review | ✅ Always to `cp-notes/[RATING]/`              |

**Workflow:**

1. **During contest/practice:** Use `cp-quick-insight` (grab the insight) → store as Option B or C for quick reference
2. **After solving:** Use `cp-problem-notes-generator` (build the full note) → stored in `cp-notes/[RATING]/`
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

The skill lives alongside its companion in the repo. Depending on your storage choice, the structure can grow:

```
my-cp-learning/
├── README.md                             # Master index (full notes)
├── cp-notes/                             # Full study notes (by rating)
│   ├── 800/
│   ├── 900/
│   └── ...
├── cp-insights/                          # [Option B/C] Lightweight insight cards
│   ├── README.md                         # [Option C] Master insight file
│   ├── 800/                              # [Option B] Cards by rating
│   ├── 900/
│   └── ...
└── .agents/
    └── skills/
        ├── cp-problem-notes-generator/
        │   └── SKILL.md
        └── cp-quick-insight/
            └── SKILL.md
```

> `cp-insights/` is created automatically on first Option B/C save.

---

**Designed for:** Fast insight extraction and pattern recognition
**Best for:** Quick reviews, weekly summaries, contest prep
**Pairs with:** cp-problem-notes-generator skill for comprehensive learning
