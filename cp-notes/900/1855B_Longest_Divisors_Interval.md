# 1855B - Longest Divisors Interval

**Rating:** 900
**Category:** Math / Number Theory
**Solve Time:** 9 minutes
**Confidence:** 10/10

## Problem Summary

Find the maximum length of an interval `[l, r]` of positive integers such that `n` is a multiple of every integer in the interval.

## Key Insight

If `k` is the smallest positive integer that does **not** divide `n`, then no interval longer than `k-1` can exist — because any interval of length `≥ k` must contain a multiple of `k`, and that would force `k` to divide `n`, a contradiction. The interval `[1, k-1]` achieves this bound.

## Solution Approach

### Step 1: Observation

Among any `k` consecutive integers, there must be a multiple of `k`. So if an interval `[l, r]` has length `≥ k`, it contains some `m` with `k | m`. If `m | n`, then `k | n` by transitivity.

Therefore: if `k` does **not** divide `n`, the interval length must be `< k`.

### Step 2: Algorithm

- Start `i = 1`
- While `n % i == 0`, increment `i`
- Output `i - 1` (the count of numbers `1...k-1` that all divide `n`)

### Step 3: Implementation

```cpp
ll n; cin >> n;
ll i = 1;
while (n % i == 0) i++;
cout << i - 1 << "\n";
```

### Step 4: Edge Cases

- **n = 1** → `1 % 1 == 0`, `1 % 2 ≠ 0` → answer = 1
- **Large n up to 1e18** → loop at most ~60 iterations because LCM(1..k) grows fast
- **n is even but not divisible by 3** → answer = 2 (interval [1, 2])
- **n is prime** → most primes are not divisible by 2, so answer = 1

## Complexity Analysis

- **Time:** O(log n) — at most ~60 iterations since LCM(1..60) > 1e18
- **Space:** O(1)

## Why This Works

Let `k` be the first positive integer that does not divide `n`.

- **Upper bound:** Any interval of length `≥ k` contains a multiple of `k`. Since that multiple divides `n`, `k` would divide `n` — contradiction. So `length < k`.
- **Achievability:** The interval `[1, k-1]` has length `k-1`, and by definition every integer `1..k-1` divides `n`.

Thus the maximum is exactly `k-1`.

## Common Mistakes

- **Searching for intervals randomly** — the maximal interval always starts at 1, don't waste time checking arbitrary `[l, r]`.
- **Thinking the answer is bounded by `sqrt(n)`** — it's actually bounded by the LCM growth, which is much smaller (~60 for 1e18).
- **Forgetting to use `long long`** — `n` can be up to 1e18.

## Clean Code

```cpp
void solve() {
    ll n; cin >> n;
    int i = 1;
    while (n % i == 0) i++;
    cout << i - 1 << "\n";
}
```

## Key Takeaway

**The first missing divisor tells you everything.** When a problem asks for the longest interval of divisors, the pigeonhole principle on consecutive integers implies the answer is just `smallest k with k ∤ n, minus 1`. Always check prefix starting from 1 first.

## Your Code

```cpp
void solve() {
    ll n; cin>>n;
    ll cnt = 0;
    for(ll i = 1; i<51; i++){
        if(n%i !=0) break;
        cnt++;
    }
    cout<<cnt<<endl;
}
```

> _This is your original solution. Keep it here to track how your coding style evolves over time._

## Code Review

### What's Good

- **Identical logic to the official solution** — your approach is exactly the same as the intended one. The only cosmetic difference is using a `for` loop with a hardcoded bound of 50 vs. a `while` loop.
- **Uses `long long` correctly** — necessary for `n ≤ 1e18`.
- **9 minutes, 10/10 confidence** — clean solve. No room for improvement in correctness.

### Minor Tweaks

**1. Hardcoded bound `i < 51`**

Your loop stops at 50, which works because LCM(1..50) > 1e18, so the answer is always found within 50 iterations. However, a `while` loop (`while (n % i == 0) i++`) is more idiomatic — it expresses the intent directly without needing to reason about the bound.

**2. `cnt` vs. `i-1`**

Using a separate counter is fine, but `i-1` from the official solution is slightly cleaner since it reuses the loop variable.

**3. Variable name `i` as `ll`**

`i` only needs to go up to ~60, so `int` is sufficient. Minor, but keeps the intent clear.

### Suggested Refactor

```cpp
void solve() {
    ll n; cin >> n;
    int i = 1;
    while (n % i == 0) i++;
    cout << i - 1 << "\n";
}
```

This says "keep going while it divides, stop at first failure, answer is count of successes". Simple and expressive.

---

**Generated:** 2026-07-22
**Next Review:** 2026-07-25
