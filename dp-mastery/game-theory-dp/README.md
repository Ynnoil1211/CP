# Pattern: Game Theory DP

## Pattern Name: **Game Theory DP** (a.k.a. Optimal Play DP)

### Description

Two players alternate **optimal moves**. State = remaining options + whose turn. The key formula: **my best move = my gain from this move − the opponent's best response from the resulting state**.

The mental shift: you don't simulate both players separately. One value per state already represents the *advantage for whoever moves next, under optimal play* — the same recurrence serves both players.

### When to recognize it

- "two players", "alternate turns", "optimal play"
- "both play optimally", "can the first player win?"
- Picking / removing from a pile, a range, or a set

### The General Template

**State:**
```
dp[i][j] = best score difference (current player − opponent) on range [i, j]
```

**Base case:**
```
dp[i][i] = values[i]   (single item: current player takes it)
```

**Transition:**
```
dp[i][j] = max(  values[i] - dp[i+1][j],   // take the left end
                 values[j] - dp[i][j-1] )  // take the right end
```

**Answer:** first player wins iff `dp[0][n-1] ≥ 0`.

**Complexity:** O(n²) time/space (memoized recursion over ranges).

### The core intuition to keep

The **minus sign is the whole pattern**: after I take an item, the remaining range's dp value is the *opponent's* advantage, so my net gain is `myTake − dp[remaining]`. One table, both players, no extra "whose turn" dimension needed.

### 🟢 Solved Problems

None yet.

### ⏳ Next up

- [486 - Predict the Winner](https://leetcode.com/problems/predict-the-winner/) → [877 - Stone Game](https://leetcode.com/problems/stone-game/) — the same recurrence; Stone Game is rigged so player 1 always wins
