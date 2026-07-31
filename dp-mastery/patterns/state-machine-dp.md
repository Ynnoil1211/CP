# Pattern: State Machine DP

## Pattern Name: **State Machine DP**

### Description

You're at position `i` **and** in one of a small number of discrete "modes" — holding stock / not holding, cooldown / normal, painting color X. The recurrence is a set of transitions between modes.

The mental shift: enumerate the modes first, then ask per mode **"which modes could I have been in last step, to get here?"** The position advances one step at a time (like Linear DP), but each step also moves you along the state diagram.

### When to recognize it

- Explicit states in the statement: "holding", "cooldown", "on/off", "fee"
- A decision that locks you out of something for future steps
- Multiple "phases" per position

### The General Template

**State:**
```
dp[i][s] = best value at position i while in mode s
```

**Base case:**
```
dp[0][s] = initial value per mode (e.g. 0 for not-holding, -∞ for holding)
```

**Transition:**
```
dp[i][s] = best over all s' that can transition to s of: dp[i-1][s'] + gain(s' → s, i)
```

**Answer:** `max over s of dp[n][s]`.

**Complexity:** O(n · #modes²) time — but #modes is tiny (2–4), so effectively O(n). O(1) space with rolling state variables.

### The core intuition to keep

**Draw the state diagram first** — the DP is just "follow the arrows". The hard part isn't the recurrence; it's correctly identifying the modes and which transitions are legal (e.g. a cooldown forces a "rest" state you must pass through before buying again).

### 🟢 Solved Problems

None yet.

### ⏳ Next up

- [276 - Paint Fence](https://leetcode.com/problems/paint-fence/) — 2-mode counting (same color as previous / different)
- Later: 309 - Best Time to Buy and Sell Stock with Cooldown, 714 - with Transaction Fee (holding / not-holding / rest modes)
