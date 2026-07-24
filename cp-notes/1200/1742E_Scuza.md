# 1742E - Scuza

**Rating:** 1200
**Category:** Binary Search / Prefix Sum / Greedy
**Solve Time:** —
**Confidence:** 5/10

## Problem Summary

A staircase of n steps — step i is a_i meters high. For each query k (leg length), find the maximum height reachable: you can climb step j only if k ≥ a_j for **every** step up to j. Answer q queries independently.

## Key Insight

The limiting factor is the **maximum step height encountered so far** (prefix maximum), not the individual step heights. If your legs clear the tallest step in the first t steps, you can climb all of them. Use binary search on the prefix maximum array to find how many steps you can take.

## Solution Approach

### Step 1: Observation

The requirement "k ≥ a_j for each step j climbed" means you're blocked the first time you encounter a step taller than your legs. This is **not** about the sequence order of a_j — it's about the peak so far.

Example: steps = [1, 5, 2, 3]. With k=3:
- Step 1: a=1 ≤ 3 ✅ → climb
- Step 2: a=5 > 3 ❌ → stuck
- Even though steps 3 and 4 (2, 3) are within reach, you can't get past step 2.

So the constraint is the **running maximum**: `max_a_so_far ≤ k`.

### Step 2: Transform to Prefix Data

Precompute two arrays:
- **prefix sum** `pref[i] = a₁ + a₂ + ... + aᵢ`
- **prefix max** `check[i] = max(a₁, a₂, ..., aᵢ)` — the highest step up to i

Now for a query k, find the **last index** where `check[i] ≤ k`. The answer is `pref[last]`.

### Step 3: Binary Search

Since `check[]` is non-decreasing (prefix maximums only grow), we can binary search:

```
last = upper_bound(check, k) - 1
answer = pref[last]
```

`upper_bound` returns the first index where `check[i] > k`, so `last` is the last index where `check[i] ≤ k`.

### Step 4: Edge Cases

- **k = 0**: Can't climb any step (a₁ ≥ 1). `upper_bound(check, 0)` returns index 1 (first element), so last = 0, pref[0] = 0. Correct.
- **k is huge**: `upper_bound` goes past the end, last = n, answer = full prefix sum. Correct.
- **Large values**: Use `long long` for prefix sums (aᵢ ≤ 1e9, n ≤ 2e5 → sum up to 2e14 fits in 64-bit).

## Complexity Analysis

- **Time:** O(n + q log n) per test case — linear preprocessing, log n per query via binary search.
- **Space:** O(n) for prefix arrays.

## Why This Works

The prefix maximum is monotonically non-decreasing (it never shrinks), so binary search applies. The condition "max step so far ≤ k" is necessary and sufficient: if you've survived the tallest step so far, all earlier steps are ≤ that max, so you've survived them too.

## Common Mistakes

- **Using `upper_bound` on raw step heights (as in user's second version).** The raw a array is NOT sorted — a step might be short but come after a tall one. Binary search only works on monotonic data.
- **Tracking differences instead of absolute heights (as in user's first version).** The leg length constraint is on the step height a_j, not the rise from the previous step. Tracking `a_i - a_{i-1}` is irrelevant.
- **Forgetting 64-bit integers.** Prefix sums can exceed 2³¹ — use `long long`.

## Clean Code

```cpp
void solve() {
    int n, q;
    cin >> n >> q;
    vector<long long> pref(n + 1);
    vector<int> mx(n + 1);  // prefix max of step heights
    for (int i = 1; i <= n; i++) {
        int a; cin >> a;
        pref[i] = pref[i - 1] + a;
        mx[i] = max(mx[i - 1], a);
    }
    while (q--) {
        int k; cin >> k;
        int last = upper_bound(mx.begin() + 1, mx.end(), k) - mx.begin() - 1;
        cout << pref[last] << " ";
    }
    cout << "\n";
}
```

## Key Takeaway

**"Can you pass all items up to position i?" problems often reduce to a prefix maximum.** The trick is recognizing that the bottleneck is the worst item seen so far, not the current item. Build the prefix max array, then binary search on it for each query.

This pattern appears frequently at 1200-1400:
- "Maximum prefix that satisfies constraint C" → precompute constraint as prefix array
- Queries on that prefix → binary search on the monotonic array

## Your Code

```cpp
// First attempt — wrong: tracked step differences instead of heights
void solve() {
    int n,k; cin>>n>>k;
    vll steps(n+1), que(k+1);
    vll pref(n+1), diff(n+1);
    for(int i = 1; i<=n; i++){
        cin>>steps[i];
        pref[i]= pref[i-1]+steps[i];
        ll dif = steps[i]-steps[i-1];
        diff[i]=(max(diff[i-1],dif));
    }
    for(int i = 1; i<=k; i++){
        cin>>que[i];
        auto it = upper_bound(diff.begin(), diff.end(), que[i]);
        auto dis = distance(diff.begin(),it-1);
        ll resIt = pref[dis];
        cout<<resIt<<" ";
    }
    cout<<endl;
}

// Second attempt — wrong: binary searched on raw (unsorted) steps
void solve() {
    int n,k; cin>>n>>k;
    vll steps(n+1), que(k+1);
    vll pref(n+1);
    for(int i = 1; i<=n; i++){
        cin>>steps[i];
        pref[i]= pref[i-1]+steps[i];
    }
    for(int i = 1; i<=k; i++){
        int x; cin>>x;
        ll res=0;
        auto it = upper_bound(steps.begin(), steps.end(), x);
        auto dis = distance(steps.begin(), it-1);
        res = pref[dis];
        cout<<res<<" ";
    }
    cout<<endl;
}

// Final version — correct: binary search on prefix max
void solve() {
    int n,k; cin>>n>>k;
    vll steps(n+1), que(k+1);
    vll pref(n+1), check(n+1);
    for(int i = 1; i<=n; i++){
        cin>>steps[i];
        pref[i]= pref[i-1]+steps[i];
        check[i] = max(check[i-1], steps[i]);
    }
    for(int i = 1; i<=k; i++){
        int x; cin>>x;
        ll res=0;
        auto it = upper_bound(check.begin(), check.end(), x);
        auto dis = distance(check.begin(), it-1);
        res = pref[dis];
        cout<<res<<" ";
    }
    cout<<endl;
}
```

> _This is your original solution. Keep it here to track how your coding style evolves over time._

## Code Review

### What Went Wrong

**First version — tracking differences:**
You computed `diff[i] = max(diff[i-1], steps[i] - steps[i-1])`, which is the maximum rise between consecutive steps. But the problem constraints say your leg length must be ≥ the step height a_j itself, not the rise from the previous step. The difference is irrelevant here.

**Second version — binary search on raw steps:**
You correctly used prefix sums and `upper_bound`, but on the wrong array. `steps[]` is not sorted (it's just the sequence of step heights in order), so binary search on it gives garbage results.

**The core misconception:**
You thought the constraint was about the current step's value, but it's actually about the **maximum** step value seen so far. Once you understand that the prefix max is what matters, the rest falls into place.

### What Was Good
- You already knew you needed prefix sums (`pref`).
- You reached for `upper_bound` — the right tool.
- You kept iterating through 3 versions instead of giving up. That persistence matters more than getting it right immediately.

### Suggested Next Practice
Problems that use the same "prefix max + binary search" pattern:
- **1791C - Prepend and Append** (prefix/suffix concept)
- **1692E - Binary Deque** (binary search on prefix sums)
- **1744D - Divisibility by 2^n** (similar "worst so far" thinking)

---

**Generated:** 2026-07-24
**Next Review:** 2026-07-28 (4 days — moderate confidence, needs reinforcement)
