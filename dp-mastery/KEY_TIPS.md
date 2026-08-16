# Key Tips — Distilled Lessons from the 100 DP Challenge

_One-liners extracted from every solve and re-solve. **Re-read before each session** — these are the habits that prevent the bugs you've actually hit._

---

## 1. State Definition

### 🥇 Write the state definition as a comment BEFORE coding

The recurrence, base cases, and answer line all fall out of the state — if they don't match, the state is wrong. Every stuck solve (746, 279, 53, 1043) was a state-definition problem, not a coding problem.

> Sources: [746](linear-dp/746_Min_Cost_Climbing_Stairs.md), [279](segmentation-dp/279_Perfect_Squares.md), [53](linear-dp/53_Maximum_Subarray.md), [1043](segmentation-dp/1043_Partition_Array_for_Maximum_Sum.md)

### Two state flavors — know which answer you need

- **"Up to i"** (House Robber, Climbing Stairs): best considering everything ≤ i → answer = **last cell**.
- **"Ending at i"** (Kadane): best whose right edge is exactly i → answer = **max over all dp[i]** (running max).

Ask which flavor you're in before writing the return line.

> Sources: [53](linear-dp/53_Maximum_Subarray.md), [198](linear-dp/198_House_Robber.md)

### Defining the piece IS the state

When pieces are _given_ (words, coins), the recurrence is easy. When you must _invent_ the pieces (squares, windows), you stall — because the piece definition is half the state. One question fixes it: **"what can the last piece be?"**

> Sources: [279](segmentation-dp/279_Perfect_Squares.md), [1043](segmentation-dp/1043_Partition_Array_for_Maximum_Sum.md)

---

## 2. Base Cases & Initialization

### 🥇 Initialization is part of the recurrence

| What you're computing | Init value                                 |
| --------------------- | ------------------------------------------ |
| Sums / counts of ways | `0`                                        |
| Min problems          | big sentinel (`INT_MAX - n`, `1e7`)        |
| Max problems          | low value (`INT_MIN`)                      |
| Counting ways         | `dp[0] = 1` — the empty way, like `0! = 1` |
| Min cost              | `dp[0] = 0` — doing nothing costs zero     |

When `i - x == 0`, `dp[0]` must make that state reachable — trace the single-element case and check.

> Sources: [279](segmentation-dp/279_Perfect_Squares.md), [53](linear-dp/53_Maximum_Subarray.md), [377](knapsack-dp/377_Combination_Sum_IV.md), [322](knapsack-dp/322_Coin_Change.md), [746](linear-dp/746_Min_Cost_Climbing_Stairs.md)

### The base case tells you the operation

Counting → `dp[0] = 1` (one empty way). Cost → `dp[0] = 0` (zero cost). If you're unsure whether the problem counts ways or costs, the base case answers it.

> Sources: [377](knapsack-dp/377_Combination_Sum_IV.md), [322](knapsack-dp/322_Coin_Change.md)

### Base cases guard tiny inputs FIRST

`n == 1`, `n == 2`, empty prefixes — guard them before touching the recurrence, or you index `nums[1]`/`nums[2]`/`cost[n]` into nothing.

> Sources: [213](linear-dp/213_House_Robber_II.md), [198](linear-dp/198_House_Robber.md), [746](linear-dp/746_Min_Cost_Climbing_Stairs.md)

### Base cases are the recurrence at the start of the array

`dp[1] = max(nums[0], nums[1])` isn't a special hack — it's the take/skip decision applied at the boundary where `dp[i-2]` doesn't exist yet.

> Source: [198](linear-dp/198_House_Robber.md)

---

## 3. Recurrence Structure

### Scan-all-previous vs fixed-offset

- **Fixed-offset** (Climbing Stairs, House Robber, Kadane): dp[i] reads only dp[i-1], dp[i-2] → single loop, O(1) space.
- **Scan-all-previous** (Word Break, LIS, Perfect Squares, 1043): dp[i] must try ALL earlier states / pieces → **nested loop is structurally required**, not a style choice. Greedy single-pointer = wrong.

> Sources: [139](segmentation-dp/139_Word_Break.md), [53](linear-dp/53_Maximum_Subarray.md), [1043](segmentation-dp/1043_Partition_Array_for_Maximum_Sum.md)

### The three split policies (same skeleton, different policy)

| Policy                                       | Recurrence shape                   | Problem                      |
| -------------------------------------------- | ---------------------------------- | ---------------------------- |
| Consume one valid piece                      | `dp[i-x] + 1` / `dp[i] += dp[i-x]` | Word Break, Coin Change, 377 |
| Piece may stay whole                         | `max(j·(i−j), j·dp[i−j])`          | Integer Break                |
| Both children must split + pay for the split | `dp[j] + dp[i-j] + cost`           | Split into Ones              |

Read the policy from the statement: _"split into ones"_ = must-split. _"maximize product"_ = may stay whole.

> Sources: [139](segmentation-dp/139_Word_Break.md), [322](knapsack-dp/322_Coin_Change.md), [377](knapsack-dp/377_Combination_Sum_IV.md), [343](segmentation-dp/343_Integer_Break.md), [3857](interval-dp/3857_Minimum_Cost_to_Split_into_Ones.md)

### Counting = add whole blocks, never +1 per path

Each way to reach `i-x` extends to exactly one way to reach `i` → `dp[i] += dp[i-x]`. A `+1` means you're counting _coins used_ (cost logic) leaking into a counting problem.

> Source: [377](knapsack-dp/377_Combination_Sum_IV.md)

### Bounded pieces = bounded scan

If the piece length is capped (≤ k, or 1-2 digits), only scan the cap — O(n·k), not O(n²). Decode Ways is 1043 with piece lengths 1-2.

> Source: [1043](segmentation-dp/1043_Partition_Array_for_Maximum_Sum.md)

---

## 4. Loops & Indexing

### 🥇 The loop-conditions trick: think in ELEMENTS, not indices

1. How many elements have I seen? → `i+1`
2. What's the piece-size cap? → `min(k, i+1)`
3. Which element is j steps back? → `arr[i-j+1]`

Memory aid: `j=1` → `arr[i]`; `j=k` → `arr[i-k+1]`. This kills the `arr[i-j]` vs `arr[i-j+1]` and `dp[i-j]` vs `dp[i-j+1]` bug class.

> Source: [1043](segmentation-dp/1043_Partition_Array_for_Maximum_Sum.md)

### Inner-loop guards compare against the current state `i`, never the global target

`if (x > i) break;` — not `if (x < amount)`. A wrong guard doesn't crash; it silently degrades the DP (only the smallest coin gets used).

> Source: [322](knapsack-dp/322_Coin_Change.md)

### 🥇 The final bounds audit — before submitting

Two checks that catch the whole off-by-one class: (1) does the inner loop **REACH the cap**? `j <= min(k, i+1)` — `j <` silently tries only k−1 lengths; (2) does the answer read the **full problem**? `dp[n]`, never `dp[n-1]` (outer loop goes to `i <= n`). Both 08-09 regressions (1043, 139) were exactly these.

> Sources: [1043](segmentation-dp/1043_Partition_Array_for_Maximum_Sum.md), [139](segmentation-dp/139_Word_Break.md)

### The j=1 convention check (for window indexing — 1043's third strike)

When a window of length j ends at the current position: **at j=1, the window must be exactly the LAST element.** 1-indexed `dp[i]`: `arr[i-1]`; 0-indexed `dp[i+1]`: `arr[i]`. Then the cap: `j <= min(k, i)` (1-indexed) — the window can't exceed the prefix. 1043's three failures all trace to flipping between conventions mid-attempt, never to the recurrence. Choose the convention once, verify j=1, then code.

> Source: [1043](segmentation-dp/1043_Partition_Array_for_Maximum_Sum.md)

### Gates are independent terms of a SUM (Decode Ways)

When pieces have validity tests (digit gates, dictionary lookups), each piece type contributes its OWN gated term — a failed gate kills that term only. Never `continue`/`else` across gates: `"27"` needs the 1-char term even though the 2-char gate fails. Also: **chars need `-'0'` before arithmetic** (`'1'` is 49, not 1), and hardcoded base cases (`if (n==2) return 2`) can't know the digits — the gates ARE the special cases.

> Source: [91](segmentation-dp/91_Decode_Ways.md)

---

## 5. Meta-Lessons

### 🥇 An accidental AC is not understanding

A solution can pass because of a hidden invariant (3857's max-variant passes only because total cost is always n(n−1)/2). If you can't explain _why_ it works structurally, flag the problem for re-solve anyway.

> Source: [3857](interval-dp/3857_Minimum_Cost_to_Split_into_Ones.md)

### The greedy trap

"Commit to the first/best-looking piece and move on" loses the ability to backtrack. If the answer depends on finding SOME earlier state that satisfies a condition, you must try all of them.

> Source: [139](segmentation-dp/139_Word_Break.md)

### Overflow is real in counting problems

Intermediates can exceed 32-bit even when the final answer fits (dp[630] ≈ 4.6×10¹⁸ while dp[999] = 1). Use `unsigned int` (wraps mod 2³², preserves the answer) or clamp at `INT_MAX`.

> Source: [377](knapsack-dp/377_Combination_Sum_IV.md)

---

**Maintained by:** the re-solve sessions. Every new lesson gets a row here AND a breakthrough entry.
**Last Updated:** 2026-08-15

---

## 📋 Your Personal Error Log (as of 2026-08-09)

**The verdict: one class recurs — bookkeeping (bounds + base cases). Conceptual errors are gone.**

### The literal repeats (same mistake, different day)

| Repeat          | When                       | The mistake                                                                                                                                                   |
| --------------- | -------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 746 base case   | 08-01 AND 08-04            | `dp[1] = min(cost[0], cost[1])` from memory — twice                                                                                                           |
| 377 base case   | 08-01 AND 08-04            | `dp[0] = 1` for counting — debugged twice                                                                                                                     |
| 1043 off-by-one | original, 08-09, AND 08-15 | window index/cap (`arr[i-j+1]` vs `arr[i-j]`; `j <` vs `j <=`) — the most repeated error. Root cause found 08-15: 0/1-indexed convention flipping mid-attempt |

### The full resume (13 problems, ~20 errors)

| Class                                          | Occurrences                          | Problems                                                                                                                    |
| ---------------------------------------------- | ------------------------------------ | --------------------------------------------------------------------------------------------------------------------------- |
| **Bounds / off-by-one / answer line / guards** | ~11                                  | 1043 (×3 — THE repeat), 139 (×2), 53 (dp[n-1]), 322 (`x < amount`), 746 (`cost[n]`, `dp[n-1]`), 198/213 (n==1/2 guards, ×2) |
| **Base cases / initialization**                | ~9                                   | 746 (×2), 377 (×2), 279, 740, 3857, 213, 198                                                                                |
| **State definition**                           | 5 — **all before 08-01, none since** | 746, 198, 279, 53, 1043                                                                                                     |
| **Concept (greedy / operator / policy)**       | 3 — each once, all internalized      | 139 (greedy), 377 (+1 leak), 3857 (+dp[j])                                                                                  |

### The trend that matters

Errors are getting **shallower and faster to catch**: 139 took 2h (concept) → 3 min (clean) → 08-09 slipped on a bound. 3857: 15:45 (forgot the recurrence shape) → 2:10 (only base case). The remaining class is the **last 5% polish** — the logic is right, the boundaries leak.

### The antidote — the 3-step pre-submit audit (each step kills one class)

1. **State comment written?** → kills state-definition errors
2. **Base cases match the state?** trace the SMALLEST input by hand → kills base-case errors
3. **Bounds audit:** inner loop REACHES the cap (`<=`, not `<`) · answer reads `dp[n]`, never `dp[n-1]` · tiny-input guards (`n==1/2`) present → kills bounds errors

_All three recurring classes map 1:1 to the three audit steps. The audit isn't about knowing — it's about doing it, in order, before hitting submit._
