# Pattern: Segmentation DP

## Pattern Name: **Linear Partition DP** (a.k.a. Sequence Segmentation DP)

### Description

This pattern applies when you're given a **linear sequence** (a string or array) and asked whether — or how well — it can be **split into contiguous pieces**, where each piece must independently satisfy some condition.

The key mental shift: instead of asking "how do I cut this string?" directly, you ask a smaller question at every position: **"is this prefix (or subarray ending here) reachable/valid, given everything before it?"** You build the answer from the ground up, left to right, reusing work you've already done.

### When to recognize it

Ask yourself: _"Can/should I split this sequence into pieces, where each piece needs to pass some test?"_ If yes, this pattern likely applies. Common signals in the problem statement:

- "segmented into..."
- "partitioned into..."
- "split into subarrays/substrings such that each..."
- "break into words / numbers / groups"

### The General Template

**State:**

```
dp[i] = true/best-value, representing: "the first i elements of the sequence
         can be validly partitioned"
         (or: "the best score achievable partitioning the first i elements")
```

**Base case:**

```
dp[0] = true (or 0, or the neutral value) — an empty prefix is trivially valid
```

**Transition:**

```
For each i from 1 to n:
    For each j from 0 to i-1:
        if dp[j] is valid/true AND segment(j, i) satisfies the condition:
            dp[i] = combine(dp[i], dp[j], segment(j, i))
```

Where:

- `segment(j, i)` is the piece from index `j` to `i` (exclusive) — a substring, subarray, etc.
- `combine(...)` depends on what you're optimizing:
  - **Existence (true/false):** `dp[i] = dp[i] OR (dp[j] AND valid(segment))`
  - **Counting ways:** `dp[i] += dp[j]` (if segment is valid)
  - **Min/max cost:** `dp[i] = min(dp[i], dp[j] + cost(segment))`

**Answer:** `dp[n]` (the whole sequence).

**Complexity:** Typically **O(n²)** for the two nested loops, times whatever it costs to check/validate `segment(j, i)` (O(1) for a hash lookup, O(k) for a palindrome check, etc.).

### Problem Family (all share this exact skeleton)

| Problem                        | What `segment(j, i)` must satisfy | What `dp[i]` tracks            |
| ------------------------------ | --------------------------------- | ------------------------------ |
| **Word Break**                 | Is a word in the dictionary       | Reachable? (bool)              |
| **Word Break II**              | Is a word in the dictionary       | All valid segmentations (list) |
| **Palindrome Partitioning II** | Is a palindrome                   | Min cuts needed                |
| **Perfect Squares**            | Is a perfect square number        | Min pieces to sum to n         |
| **Decode Ways**                | Is a valid 1 or 2-digit code      | Number of ways to decode       |

### The core intuition to keep

You're not trying to _guess_ the right split in one shot. You're asking, at every prefix length, **"is there some earlier valid stopping point I could have chained from?"** — and because you scan left to right, `dp[j]` for any `j < i` is already known by the time you need it. That's what turns an exponential "try every possible split" search into a polynomial one: **you never re-derive whether a prefix is valid; you just look it up.**

Try spotting this shape cold on **Palindrome Partitioning II** or **Perfect Squares** next — see if you can write the recurrence yourself before coding.

### 🟢 Solved Problems

| ID  | Title                                     | Confidence | Core idea                                                                         |
| --- | ----------------------------------------- | ---------- | --------------------------------------------------------------------------------- |
| 139 | [Word Break](139_Word_Break.md)           | 1/10       | Existence: `dp[i] = OR over j of (dp[j] && s[j..i) in dict)`                      |
| 279 | [Perfect Squares](279_Perfect_Squares.md) | 4/10       | Min: `dp[i] = min over squares s ≤ i of (dp[i-s] + 1)` — last-piece decomposition |

> 🔴 **Still your weakest pattern (avg ~2.5/10).** Word Break 1/10 + Perfect Squares 4/10. The gap is consistent: you can spot the _pieces_ (dictionary words / squares) but not yet write the _state + recurrence_ alone. Re-solve both from scratch. Note: Perfect Squares is Coin Change in disguise — that connection is now yours.

### ⏳ Next up

- [91 - Decode Ways](https://leetcode.com/problems/decode-ways/) — the same skeleton, counting ways instead of existence
- [343 - Integer Break](https://leetcode.com/problems/integer-break/) — split `n` into pieces maximizing the product
- [322 - Coin Change](https://leetcode.com/problems/coin-change/) — Week 4, but you've already written this code: it's Perfect Squares with `coins = {1, 4, 9, ...}` swapped for any coin set
