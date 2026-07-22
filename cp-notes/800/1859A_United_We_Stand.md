# 1859A - United We Stand

**Rating:** 800
**Category:** Ad-hoc / Math / Greedy
**Solve Time:** —
**Confidence:** —

## Problem Summary

Split an array `a` into two non-empty arrays `b` and `c` such that no element of `c` divides any element of `b`. If impossible, output -1.

## Key Insight

The largest element in the array cannot divide any other element — because no other element is larger than it. Put **all occurrences of the maximum** in `c` and **everything else** in `b`. Then no `c` element can divide any `b` element.

If all elements are equal, every element is the maximum, so `b` would be empty → impossible.

## Solution Approach

### Step 1: Observation

Divisibility requires that `c[j] ≤ b[i]` for `c[j]` to potentially divide `b[i]`. Since `max(a)` is the largest number in the array, it can never divide any smaller number. So by isolating the maximum, we guarantee the condition.

### Step 2: Algorithm

- Find `mx = max(a)`
- Push all `a[i] ≠ mx` into `b`
- Push all `a[i] == mx` into `c`
- If `b` is empty → output -1
- Otherwise output `b` and `c`

### Step 3: Implementation

```cpp
int n; cin >> n;
vector<int> a(n), b, c;
for (int i = 0; i < n; i++) cin >> a[i];
int mx = *max_element(a.begin(), a.end());
for (int x : a) {
    if (x != mx) b.push_back(x);
    else         c.push_back(x);
}
if (b.empty()) cout << -1 << "\n";
else {
    cout << b.size() << " " << c.size() << "\n";
    for (int x : b) cout << x << " "; cout << "\n";
    for (int x : c) cout << x << " "; cout << "\n";
}
```

### Step 4: Edge Cases

- **All elements equal** (e.g., `[2, 2, 2]`) → `b` is empty → -1
- **Single unique max** with many smaller elements → works trivially
- **Array already satisfies condition** → distribution still works

## Complexity Analysis

- **Time:** O(n) — single pass to find max, single pass to distribute
- **Space:** O(n) — two output arrays

## Why This Works

If `mx` is the maximum value in `a`, then for any smaller value `v`, `mx` cannot divide `v` because `mx > v` and `mx % v` cannot be 0 either (since `mx` is larger). By putting all non-max elements in `b` and all max elements in `c`, we guarantee no `c[j]` divides any `b[i]`.

## Common Mistakes

- **Overcomplicating** — trying to balance sizes or create complex partitions (like I did with a toggle-switch approach over a map)
- **Not realizing** that the max element is the natural separator

## Clean Code

```cpp
void solve() {
    int n; cin >> n;
    vector<int> a(n), b, c;
    for (int &x : a) cin >> x;
    int mx = *max_element(a.begin(), a.end());
    for (int x : a) (x == mx ? c : b).push_back(x);
    if (b.empty()) { cout << "-1\n"; return; }
    cout << b.size() << " " << c.size() << "\n";
    for (int x : b) cout << x << " "; cout << "\n";
    for (int x : c) cout << x << " "; cout << "\n";
}
```

## Key Takeaway

When a problem asks for a partition with a divisibility constraint, **look for the maximum element** — it's often the natural separator. Don't reach for complex data structures before checking the simplest possible partitioning strategy.

---

**Generated:** 2026-07-22
**Next Review:** 2026-07-25
