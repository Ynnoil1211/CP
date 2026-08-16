# 91 - Decode Ways

**Pattern Type:** Segmentation DP (bounded pieces + counting + gates) — **THE LAST BOSS OF THE FAMILY, CLEARED**
**Difficulty:** Medium
**LeetCode Link:** https://leetcode.com/problems/decode-ways/
**Topics:** Counting (`+`), bounded pieces (1-2), validity gates, zero handling, Fibonacci-shaped recurrence

## Problem Statement

A string of digits maps to letters (`'1'`→A ... `'26'`→Z). Given `s`, return the **number of ways** to decode it. `"06"` → 0 ways; `"10"` → 1 way; `"226"` → 3 ways.

**Constraints:**

- `1 ≤ s.length ≤ 100`
- `s` contains only digits, and may contain `'0'`

## State Definition

### What is dp[i]?

```
dp[i] = number of ways to decode the first i characters of s (1-indexed prefix)
```

**Examples:**

- `dp[0] = 1` — the empty way (counting base, from 377)
- `dp[1]` = 1 if `s[0] != '0'`, else 0 — one character can only be decoded if it's a real letter
- `dp[3] = 3` for `"226"` — ("BZ", "VF", "BBF")

### Why This State?

Segmentation on a prefix: every decoding ends with a **last piece** of 1 or 2 characters, and everything before it is a decoding of the shorter prefix. **Bounded piece set** (lengths 1-2) → only two lookbacks: `dp[i-1]` and `dp[i-2]`. It's Fibonacci with **validity gates** — the exact structure of 1043, with piece length capped at 2 and gates replacing `max·len`.

## Recurrence Relation

```
dp[i] = (s[i-1] != '0'          ? dp[i-1] : 0)   ← 1-char piece: '1'..'9'
      + (i >= 2 && 10 <= two <= 26 ? dp[i-2] : 0)  ← 2-char piece: "10".."26"

where two = (s[i-2]-'0')*10 + (s[i-1]-'0')

Base case:
  dp[0] = 1

Answer:
  dp[n]
```

### Transition Logic

**Step 1:** The last piece is either 1 char (`s[i-1]`) or 2 chars (`s[i-2..i-1]`).

**Step 2:** Each piece type has its own **independent validity gate** — a failed gate kills *that term only*, never the other one:
- 1-char gate: `'0'` has no letter → valid iff `s[i-1] != '0'`
- 2-char gate: can't start with `'0'` (no "01"), can't exceed 26 → valid iff `10 <= two <= 26` (note "10" and "20" ARE valid — a 2-char piece CAN end with `'0'`)

**Step 3:** Sum the two gated contributions. This is 377's block addition, applied per piece type.

> **🔑 The gates are independent — never `continue` out of one gate because another failed.** `"27"`: the 2-char gate fails (27 > 26), but the 1-char gate passes (`'7'` ≠ `'0'`) → `dp[2] = dp[1] = 1`. Bailing on the 2-char gate kills the 1-char term. This was bug #3 of the first attempt.

### Example Walkthrough

Input: `s = "226"`

```
dp[0] = 1
i=1 (s[0]='2'): 1-char: '2'≠'0' → dp[1] += dp[0] = 1
i=2 (s[1]='2'): 1-char: → dp[2] += dp[1] = 1
                2-char: two=22, valid → dp[2] += dp[0] → dp[2] = 2   ("22", "2 2")
i=3 (s[2]='6'): 1-char: → dp[3] += dp[2] = 2
                2-char: two=26, valid → dp[3] += dp[1] → dp[3] = 3   ("2 26", "22 6", "2 2 6")
```

Answer: `dp[3] = 3`. Zero traps: `"06"` → dp[1] stays 0 (gate), 2-char "06" < 10 → dp[2] = 0 ✓. `"10"` → 1-char gate fails on `'0'`, 2-char "10" valid → dp[2] = dp[0] = 1 ✓.

## Implementation (C++)

```cpp
// Your solution — correct
int numDecodings(string s) {
    int n = s.length();
    vector<int> dp(n + 1, 0);
    if (s[0] == '0') return 0;          // harmless early exit (the recurrence handles it anyway)
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        if (s[i-1] != '0') dp[i] += dp[i-1];              // 1-char piece gate
        if (i >= 2) {
            int two = (s[i-2]-'0')*10 + (s[i-1]-'0');
            if (two >= 10 && two < 27) dp[i] += dp[i-2];  // 2-char piece gate
        }
    }
    return dp[n];                        // audit: dp[n], not dp[n-1]
}
```

**Key Implementation Notes:**

- **Char arithmetic:** `'1'` is the number 49 — subtract `'0'` before any math. `(s[i-2]-'0')*10 + s[i-1]-'0'` parses as `digit*10 + (s[i-1]-'0')` by left-associativity — correct, but parenthesize the second term for clarity.
- **No `n==1` / `n==2` special cases needed** — the gates ARE the special cases. The recurrence computes `dp[1]` and `dp[2]` by itself. Hardcoding `n==2 → 2` was bug #2: `"10"` is 1 way.
- **Fibonacci-shaped → O(1) space possible:** only `dp[i-1]` and `dp[i-2]` are read, so two rolling variables replace the array (like Climbing Stairs).
- `dp[0] = 1` is the counting base — the whole chain starts from the empty way.

## Complexity Analysis

- **Time:** O(n) — single pass, two lookbacks per state.
- **Space:** O(n) (array) or **O(1)** with rolling variables — bounded pieces, fixed-offset lookback, no nested loop.

## Why This Approach Works

By induction on `i`: every decoding of the first `i` characters ends with a 1-char piece (valid iff `s[i-1] ≠ '0'`) or a 2-char piece (valid iff `"10" ≤ s[i-2..i-1] ≤ "26"`). These two classes are disjoint (different last-piece length), so the count is exactly the sum of the two gated terms. Base `dp[0] = 1` bootstraps.

## Common Pitfalls in This Pattern

### 🔴 The three bugs from the first attempt (all mechanical, all fixed)

1. **ASCII math:** `s[i-2]*10` multiplies the char code (49, not 1). Always `-'0'`.
2. **Hardcoded base cases:** `if (n==2) return 2;` — `"10"` and `"20"` are 1 way. Special cases can't know the digits; gates can.
3. **The `continue` that dropped a gate:** bailing when the 2-char piece fails also killed the 1-char term (`"27"` → 0 instead of 1). Gates are independent and summed.

### Other Common Mistakes

- **Zero handling:** `'0'` alone is never decodable; `"10"`/`"20"` are valid 2-char pieces. Test `"06"`, `"10"`, `"210"` (1 way: `"2"+"10"`) after coding.
- **`dp[0] = 0` instead of 1:** counting problem — the empty way must be reachable (377's lesson).
- **Answer line:** `dp[n]`, never `dp[n-1]` — the whole string must be decoded.
- **Scanning all j (O(n²)):** unnecessary — the piece set is bounded to lengths 1-2. Two lookbacks, like Fibonacci (1043's bounded-scan lesson).

## Pattern Connection

**This is a Segmentation DP problem because:**

1. **1D prefix state**, split into contiguous pieces (1-2 chars), each piece must pass a validity test.
2. **Counting operator** (`+`) — the fourth operator in the family, now complete: OR (139) · min (279) · max (343) · **count (91/377)**.
3. **Bounded pieces** → O(n), like 1043 but with the cap fixed at 2 and gates replacing `max·len`.

**The family is now COMPLETE — this was the last boss:**

| Problem | Pieces | Piece test | Operator | Status |
| --- | --- | --- | --- | --- |
| 139 Word Break | unbounded | is a word? | OR | ✅ 10/10 |
| 279 Perfect Squares | unbounded | is a square? | min | ✅ 9/10 |
| 343 Integer Break | unbounded | may stay whole | max | ✅ 10/10 |
| 1043 Partition Max | ≤ k | length cap | max | 🟡 6/10 (one more) |
| 377 Combination Sum IV | nums | none | count | ✅ 10/10 |
| **91 Decode Ways** | **1-2** | **digit gates** | **count** | ✅ cleared 08-15 |

**Similar problems in this pattern:**

- 639 - Decode Ways II — same gates plus `'*'` wildcards (the sequel, harder)
- 139 - Word Break — unbounded pieces, existence
- 1043 - Partition Array for Max Sum — bounded pieces, max (the engine-builder)

## Key Takeaway

_"Counting + bounded pieces + gates: dp[i] = gated(dp[i-1]) + gated(dp[i-2]). Each gate contributes independently — sum them, never continue out of one because another failed. Chars need -'0'; gates ARE the special cases."_

## 🔑 Breakthrough

_"The boss fell after three mechanical bugs — and each one mapped to a lesson I already had in KEY_TIPS. The real insight: the two gates are INDEPENDENT terms of a SUM, not branches of an if-else. '27' only works because the 1-char gate fires while the 2-char gate fails. And the zero traps ('06' → 0, '10' → 1, '210' → 1) all fall out of the gates by themselves — no special-casing needed. The structure (bounded pieces, dp[0]=1, 1-indexed, dp[n]) was mine from the start; the polish was ASCII math, deleting the n==2 hardcode, and not skipping a gate."_

## Your Code

```cpp
class Solution {
public:
    int numDecodings(string s) {
        int n = s.length();
        vector<int> dp(n+1,0);
        if(s[0]=='0')return 0;
        dp[0] = 1;
        for(int i = 1; i<=n; i++){  
            if(s[i-1]!='0') dp[i] += dp[i-1];
            if(i>=2){
                int curr = (s[i-2]-'0')*10 + s[i-1]-'0';
                if(curr>=10 && curr<27){
                    dp[i]+=dp[i-2];
                }
            }
        }

        return dp[n];
    }
};
```

_Your original work — accepted. The first attempt (with the three bugs) is preserved in the conversation; this is the clean version._

## Solve Metrics

- **Solve Time:** — (not reported)
- **Attempts:** 2 (first: 3 bugs — ASCII math, `n==2` hardcode, dropped 1-char gate; second: AC)
- **Confidence:** 7/10 _(estimate — tell me the real number and I'll update)_
- **Struggles:** The gates' independence (never `continue` across them); char-to-digit conversion; resisting special cases and letting the gates do the work.
- **Key Lesson:** _\"Gates are independent terms of a sum. Chars need -'0'. No hardcoded base cases — the gates ARE the base cases.\"_
- **Submitted:** 2026-08-15
- **Last Reviewed:** 2026-08-15
- **Next Review:** 2026-08-18 (Day 3) — re-solve, target < 10 min, zero-hint.

---

**Generated:** 2026-08-15
