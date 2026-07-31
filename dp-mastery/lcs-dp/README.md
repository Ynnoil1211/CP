# Pattern: Two-Sequence DP (LCS family)

## Pattern Name: **Two-Sequence DP** (a.k.a. LCS-family DP)

### Description

Two strings/arrays advance **in lockstep**: `dp[i][j]` is the answer for the prefixes `s1[0..i)` and `s2[0..j)`. At each pair of characters you have the same three choices: **skip from s1, skip from s2, or (if they match) take both**.

The mental shift: the state is a *position pair*, and the recurrence is about deciding what to do with the current characters — match them, or drop one of them. The two sequences move together, never independently.

### When to recognize it

- "given s1 and s2"
- "longest common ...", "edit distance", "transform one into another", "interleaving"
- Two sequences compared / aligned / merged

### The General Template

**State:**
```
dp[i][j] = answer for prefixes s1[0..i) and s2[0..j)
```

**Base case:**
```
dp[0][j] = dp[i][0] = 0   (empty prefix vs anything: nothing in common / base cost)
```

**Transition:**
```
if s1[i-1] == s2[j-1]:  dp[i][j] = dp[i-1][j-1] + 1          // match: consume both
else:                   dp[i][j] = max(dp[i-1][j], dp[i][j-1])  // skip one of them
```

**Answer:** `dp[n][m]`.

**Complexity:** O(n·m) time, O(n·m) space — optimizable to O(m) (two rows at a time).

### The core intuition to keep

The 3-direction table is the signature: **diagonal = match, horizontal/vertical = skip**. When characters match, take them; when they don't, throw away the worse option from one side. Edit Distance is the same table with different costs (insert/delete/replace), and Interleaving String is the same table with a boolean.

### 🟢 Solved Problems

None yet.

### ⏳ Next up

- [1143 - Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/) — the canonical entry point to this family
- Later: 72 - Edit Distance, 97 - Interleaving String (same table, different semantics)
