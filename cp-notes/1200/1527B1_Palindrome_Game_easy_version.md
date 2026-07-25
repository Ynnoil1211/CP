# 1527B1 - Palindrome Game (easy version)

**Rating:** 1200
**Category:** Game Theory / Parity
**Solve Time:** —
**Confidence:** 7/10

## Problem Summary

A palindrome binary string s. Alice and Bob alternate flipping '0'→'1' ($1) or reversing the string (free, only if not palindrome and last move wasn't reverse). Player who spends less wins. Determine the winner with optimal play.

## Key Insight

The outcome is determined entirely by the **count of zeros** (c) and the **center zero** in odd-length strings. The free reverse operation lets players shift the cost of flipping the last zero to their opponent. Parity of c decides who can exploit this.

## Solution Approach

### Step 1: Understand the Free Reverse

When the string is **not** a palindrome, a player can reverse it for free. This is powerful because:
- Reversing changes which positions are '0' and '1' at the mirror points.
- It lets you "pass" without spending money, forcing the opponent to flip a zero on their turn.

### Step 2: Classify by Zero Count

**Case c = 0 (all '1's):** Game already over. Both spent $0 → **DRAW**. (Problem guarantees at least one '0', but handle defensively.)

**Case c = 1 (single center zero, n must be odd):**
- Alice must flip it → pays $1. Game over.
- Alice: $1, Bob: $0 → **BOB** wins.

**Case c is even:**
- Alice flips any zero → pays $1, breaks palindrome.
- Bob reverses for free → string still has one other zero (or more).
- Alice must flip again → pays another $1.
- Net: Alice pays for **two** zeros, Bob pays $0. Bob always wins.
- For c > 2, the same pattern repeats: Bob reverses after each Alice flip, Alice always pays for every zero.

→ **BOB** wins.

**Case c is odd and ≥ 3:**
- Alice flips the **center** zero → pays $1. Since the center is its own mirror, the string remains a palindrome. Now c-1 zeros remain, which is **even**.
- It's Bob's turn with an even-zero palindrome — which is exactly the losing position from above. Bob is now forced into the role Alice was in.
- Using the same reverse strategy, Alice mirrors Bob's moves and ends up paying less.

→ **ALICE** wins.

### Step 3: The Execution

```
c = count of '0's in s

if c == 0 → DRAW
if c == 1 or c % 2 == 0 → BOB
else → ALICE
```

### Step 4: Edge Cases

- n = 1, s = "0" → c = 1 → BOB (Alice flips the only zero and pays $1).
- All zeros symmetric → only the center matters for odd c.
- No need to track the actual game or simulate anything — pure parity.

## Complexity Analysis

- **Time:** O(n) per test case (counting zeros)
- **Space:** O(1)

## Why This Works

The free reverse is a **skip-a-turn** button. When c is even, Bob uses it once to force Alice to flip an extra zero. When c is odd (≥ 3), Alice flips the center first to make c even, then she becomes the one who can use the reverse, reversing the cost advantage.

The center zero is the only zero that can be flipped without breaking the palindrome, which is why c=1 (just the center) is special — there's nothing left to exploit with the reverse.

## Common Mistakes

- **Flipping a non-center zero first when c is odd.** If you flip a side zero instead of the center when c ≥ 3, you break the palindrome and give Bob the reverse advantage. Always flip the center on odd c ≥ 3.
- **Overcomplicating with `s[n/2]` checks.** The center-zero logic is already captured by the parity check: c odd ≥ 3 automatically means the center is zero (since the only way to have an odd count of zeros in a palindrome is for the center to be zero).
- **Simulating the game.** The decision is purely mathematical — no need for game tree search or DP.

## Clean Code

```cpp
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    int zeros = count(s.begin(), s.end(), '0');

    if (zeros == 0) cout << "DRAW\n";
    else if (zeros == 1 || zeros % 2 == 0) cout << "BOB\n";
    else cout << "ALICE\n";
}
```

## Key Takeaway

**Game theory + free operations = parity analysis.** When a free "pass" move exists, trace who pays for the last element. The player who can force the opponent to flip the final costly element wins. This pattern appears in many "spend to change, free to rearrange" games.

## Your Code

```cpp
void solve() {
    int n; cin>>n;
    string s; cin>>s;
    bool ok = false;
    int cnt1=0, cnt0=0;
    for(int i = 0; i<n; i++){
        if(s[i]!='1'){
            ok = true;
            cnt0++;
        } else{
            cnt1++;
        }
    }
    if(ok==false) cout<<"DRAW\n";
    else if(n-cnt1==1) cout<<"BOB\n";
    else if(cnt0%2==0) cout<<"BOB\n";
    else cout<<"ALICE\n";
}
```

> _This is your original solution. Keep it here to track how your coding style evolves over time._

## Code Review

### What You Did Right
- Got the parity insight. You correctly identified that the answer depends on whether the count of zeros is even or odd.
- Handled the edge case c=1 separately (`n-cnt1==1` → BOB).
- Handled c=0 defensively (`ok==false` → DRAW).

### What You Struggled With
Your earlier attempts focused on `s[n/2] != '0'` — checking whether the center character is zero for odd n. This is close to the right intuition (center matters for odd counts) but the exact condition is cleaner as pure zero-count parity:

```
c odd, c ≥ 3  → ALICE (not just "n odd and center is 0")
c = 1         → BOB   (center is 0 but only 1 zero total → Bob wins)
```

The confusion came from trying to combine two orthogonal conditions (center presence + parity) into one check. The official solution separates them cleanly.

### 9 Attempts — What You Learned
The first 8 attempts probably tried increasingly specific `if (s[n/2]...)` conditions. The breakthrough is realizing that **counting zeros is enough** — the palindrome property guarantees that the center being zero is equivalent to an odd count ≥ 3. The geometric intuition (`s[n/2]`) and the arithmetic intuition (`cnt0 % 2`) converge on the same answer, but the latter is simpler and less error-prone.

---

**Generated:** 2026-07-25
**Next Review:** 2026-07-29 (4 days — 7/10 confidence needs one good review to lock in)
