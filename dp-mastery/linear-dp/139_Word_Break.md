# 139 - Word Break

**Pattern Type:** Linear DP (segmentation)
**Difficulty:** Medium
**LeetCode Link:** https://leetcode.com/problems/word-break/
**Topics:** String segmentation, substring DP, existence check, scan-all-previous

## Problem Statement

Given a string `s` and a dictionary `wordDict`, determine if `s` can be segmented into a space-separated sequence of dictionary words.

**Constraints:**

- `1 ≤ s.length ≤ 300`
- `1 ≤ wordDict.length ≤ 1000`
- `1 ≤ wordDict[i].length ≤ 20`

## State Definition

### What is dp[i]?

```
dp[i] = true if s[0..i) (the first i characters) can be segmented using the dictionary
```

**Examples:**

- `dp[0] = true` — empty string is always segmentable (base case)
- `dp[4] = true` for `"leetcode"` if `"leet"` is in the dictionary
- `dp[8] = true` for `"leetcode"` if `dp[4]` is true and `"code"` is in the dictionary

### Why This State?

Segmentation is naturally about finding a **cut point**. If `s[0..i)` is segmentable, there must be some `j < i` where:

1. `s[0..j)` is segmentable (`dp[j] = true`)
2. `s[j..i)` is a dictionary word

This is an **existential** check — you only need _one_ valid cut point for `dp[i]` to be true. That's different from House Robber, where you need the _best_ value.

## Recurrence Relation

```
dp[i] = OR over all j < i of (dp[j] && s[j..i) is in wordDict)

Base case:
  dp[0] = true

Answer:
  dp[n]  (whether the entire string is segmentable)
```

### Transition Logic

**Step 1:** To segment `s[0..i)`, pick a cut point `j` somewhere between `0` and `i-1`.

**Step 2:** Check two things: the left part `s[0..j)` must be segmentable (`dp[j]`), and the right part `s[j..i)` must be a dictionary word.

**Step 3:** You only need ONE such `j` to exist. As soon as you find one, set `dp[i] = true` and `break` out of the inner loop.

> **🔑 This is a scan-all-previous problem — know the difference:**
>
> - **Fixed-offset Linear DP** (Fibonacci, House Robber): dp[i] looks back at only dp[i-1] and dp[i-2]. O(1) previous states, single pass.
> - **Scan-all-previous Linear DP** (Word Break, LIS): dp[i] must check ALL earlier states j < i to find one that works. This requires a **nested loop**, which is structurally required — not a style choice.
> - **How to tell:** If dp[i] depends on "the best up to i-1" with no further condition, use fixed-offset. If it depends on finding SOME earlier state that satisfies a condition (like "is s[j..i) in the dictionary?"), you must scan all previous states.

### Example Walkthrough

Input: `s = "leetcode"`, `wordDict = ["leet", "code"]`

```
dp[0] = true   (empty string)

i=1: j=0 → s[0..1)="l" not in dict → dp[1]=false
i=2: j=0→"le", j=1→"e" → none match → dp[2]=false
i=3: j=0→"lee", j=1→"ee", j=2→"e" → none → dp[3]=false
i=4: j=0→"leet" ✓  → dp[4]=true  ✓  (first segment found)
i=5: j=0..3 all false, j=4→"c" not in dict → dp[5]=false
i=6: j=0..4: dp[4]=true & s[4..6)="co" not in dict → dp[6]=false
i=7: j=4→"cod" not in dict → dp[7]=false
i=8: j=4→dp[4]=true & s[4..8)="code" ✓ → dp[8]=true  ✓

Answer: dp[8] = true
```

Output: `"leet code"` (cut at j=4)

## Implementation (C++)

```cpp
// Standard DP solution
bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> st(wordDict.begin(), wordDict.end());
    int n = s.length();
    vector<bool> dp(n + 1, false);
    dp[0] = true;  // empty string is segmentable

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (dp[j] && st.count(s.substr(j, i - j))) {
                dp[i] = true;
                break;  // found one valid cut → no need to check more j
            }
        }
    }
    return dp[n];
}
```

```cpp
// Optimized (try dictionary words as lengths instead of all j)
bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> st(wordDict.begin(), wordDict.end());
    int n = s.length();
    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int i = 1; i <= n; i++) {
        for (const string& w : wordDict) {
            int len = w.length();
            if (i >= len && dp[i - len] && s.substr(i - len, len) == w) {
                dp[i] = true;
                break;
            }
        }
    }
    return dp[n];
}
```

**Key Implementation Notes:**

- The **nested loop is structurally required** — you must try ALL cut points `j`, not follow one running pointer. This is not a style choice; it's what makes the DP work (existence check over all possibilities).
- `dp[i]` uses **1-indexed length** as the state, not 0-indexed position. This avoids off-by-one confusion on substrings.
- `s.substr(j, i-j)` extracts the substring from position `j` of length `i-j`.
- Early `break` on first match is safe — we only need existence.

## Complexity Analysis

- **Time:** O(n² × L) where L is max word length (for substring extraction)
  - Reason: Two nested loops (i from 1..n, j from 0..i-1), each substring extraction costs O(L).
  - Can optimize to O(n × k) where k is the number of dictionary words (second implementation above).
- **Space:** O(n + dict size) for dp array and hash set.

## Why This Approach Works

By induction on `i`: If `dp[j]` correctly indicates whether `s[0..j)` is segmentable for all `j < i`, then `dp[i]` should be true iff there exists some `j < i` where `s[0..j)` is segmentable AND `s[j..i)` is a dictionary word. The nested loop enumerates all such `j`, and the `break` on first match gives the correct existence result. The base case `dp[0] = true` bootstraps the induction.

## Common Pitfalls in This Pattern

### 🔴 The Greedy Trap (Scan-All-Previous problems)

This is the #1 mistake. Using a **single running pointer** instead of a nested loop over all previous states. If you commit to the first matched word (e.g., always locking in `"cat"` instead of trying `"cats"`) and move on, you lose the ability to backtrack and try alternative earlier cuts. The nested loop over ALL `j < i` is not optimization — it's the correct DP structure.

**Your first attempt fell into this trap.** You used a `temp` string that accumulated characters and committed to the first dictionary match, with no mechanism to reconsider that choice.

- **How to avoid:** Before writing any code, ask yourself: _"Does dp[i] need to try every possible previous state, or only the last two?"_ If the answer is "every possible," you need a nested loop.

### Other Common Mistakes

- **Forgetting `dp[0] = true`**: If dp[0] is never set to true, no word can ever bootstrap dp[i] to true. The whole chain starts from the empty prefix.
- **Off-by-one on `i` bounds**: `dp[n]` represents `s[0..n)` — the whole string. The outer loop must go to `i <= n`, not `i < n`.
- **Substring indexing**: `s.substr(j, i-j)` gives characters from index `j` with length `i-j`. If you confused start/length with start/end, you'd get wrong substrings. Triple-check this against your dp convention.

## Pattern Connection

**This is a Linear DP problem because:**

1. **1D state**: dp[i] depends only on the prefix length i.
2. **Sequential decision**: At each step i, you decide the last cut point j. The problem decomposes into smaller prefixes (dp[j]).
3. **Existential recurrence**: dp[i] = OR over all previous states of (dp[j] && condition). This is a new operator (OR) compared to the sum/min/max you've seen before.

**Within Linear DP, this is a scan-all-previous problem:**

| Sub-pattern           | Characteristics                        | Code Structure              | Examples                                |
| --------------------- | -------------------------------------- | --------------------------- | --------------------------------------- |
| **Fixed-offset**      | dp[i] depends on dp[i-1], dp[i-2] only | Single loop, O(1) variables | Climbing Stairs, House Robber, Min Cost |
| **Scan-all-previous** | dp[i] checks ALL j < i                 | Nested loop, full dp array  | **Word Break**, LIS, Decode Ways        |

This distinction determines the code structure before you write a single line. If you ask _"fixed-offset or scan-all-previous?"_ first, you'll know whether you need a nested loop.

### The Family of Linear DP Recurrence Operators

| Operator | Meaning       | Example Problem          |
| -------- | ------------- | ------------------------ |
| +        | Count ways    | Climbing Stairs          |
| min      | Cheapest path | Min Cost Climbing Stairs |
| max      | Best value    | House Robber             |
| ∃ (OR)   | Exists a path | Word Break               |

**Similar problems in this pattern:**

- 91 - Decode Ways — similar segmentation structure, but counting ways instead of existence
- 140 - Word Break II — return all possible segmentations
- 300 - Longest Increasing Subsequence — similar "try all previous" pattern

## Key Takeaway

_"In segmentation DP, dp[i] = true if there EXISTS some cut point j where the left is segmentable and the right is a word. The nested loop over all j is the core — you can't follow one pointer because you need to try every possible cut."_

## 🔑 Breakthrough

_"dp[i] = true doesn't mean 'the best single path' — it means 'there EXISTS some valid cut point j < i.' I was stuck on a greedy single-pointer approach (`temp` string accumulating characters), committing to the first match found and never reconsidering. The nested loop over ALL possible j is structurally required — you must scan **every** previous state, not follow one pointer._

_`s.substr(j, i-j)` extracts the candidate word: start at position j, take i-j characters. The reason it's `i-j` (not `i-j+1` or something else) is that `dp[i]` represents the prefix of length i (positions 0..i-1). So `s[j..i-1]` has length `(i-1) - j + 1 = i-j`. Getting this indexing right is critical — if you use the wrong length, you check the wrong substring and the whole DP fails silently._

_Without trying every j, you can never backtrack from a wrong early choice (like locking in `'cat'` when you needed `'cats'`). The scan-all-previous pattern isn't a style choice — it's the definition of the recurrence itself."_

## Your Code

```cpp
// Final solution
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> st(wordDict.begin(), wordDict.end());
        int n = s.length();
        vector<bool> dp(n + 1, false);
        dp[0] = true;
        for(int i = 1; i<=n; i++){
            for (int j = 0; j < i; j++) {
                if(dp[j]==true && st.count(s.substr(j, i-j))){
                    dp[i]=true;
                    cout<<s.substr(j,i-j)<<" ";
                    break;
                }
            }
        }
        return dp[n];
    }
};
```

```cpp
// First attempt (greedy — wrong approach)
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> st(wordDict.begin(), wordDict.end());
        int n = s.length();
        vector<bool> dp(n+1, false);
        string temp;
        temp+=s[0];
        if(n==1){ return st.count(temp);}
        temp+=s[1];
        if(n==2) return st.count(temp);
        string curr;
        for(int i = 2; i<s.length()+1; i++){
            if(i<s.length()) temp+=s[i];
            if(st.find(temp)!=st.end()){
                if(st.count((temp+s[i+1]))) continue;
                else {
                    curr+=temp;
                    temp="";
                }
            }
        }
        return s==curr;
    }
};
```

_Your original work — both attempts. Keep your wrong attempt here too; it shows exactly where the greedy-to-DP mental shift happened._

## Solve Metrics

- **Solve Time:** ~2 hours (with extensive hints)
- **Attempts:** 3+ major rewrites
- **Confidence:** 1/10
- **Struggles:**
  1. Kept trying a **greedy single-pointer** approach — commit to the first match, never backtrack
  2. Didn't realize the nested loop was **structurally required**, not a style choice
  3. Base case bug: forgot `dp[0] = true` bootstraps everything
  4. Off-by-one: `i <= n` vs `i < n`, `j < i` vs `j <= i`
  5. Indexing mismatch on substring construction
- **Key Lesson:** _"dp[i] = true means there EXISTS some cut point. Try ALL possible j. The nested loop is the DP, not the pointer."_
- **Submitted:** 2026-07-27
- **Last Reviewed:** 2026-07-27
- **Next Review:** 2026-07-30 (Day 3) — re-solve from scratch without hints

---

**Generated:** 2026-07-27
