# 1859A - United We Stand

**Rating:** 800
**Category:** Ad-hoc / Math / Greedy
**Solve Time:** 23 minutes
**Confidence:** 8/10

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

- **Time:** O(n) — single pass to find max + single pass to distribute
- **Space:** O(n) — two output arrays

## Why This Works

If `mx` is the maximum value in `a`, then for any smaller value `v`: `mx` cannot divide `v` because `mx > v`, and `v` can divide `mx` but the problem only forbids `c[j]` dividing `b[i]` (not the reverse). By putting all non-max elements in `b` and all max elements in `c`, we guarantee no `c[j]` divides any `b[i]`.

## Common Mistakes

- **Overcomplicating** — trying to balance sizes or create complex partitions when the simplest possible separation works
- **Not realizing** the max element is the natural separator since it can't divide anything smaller
- **Confusing direction** — the constraint only says `c[j]` cannot divide `b[i]`. It's fine if a `b[i]` divides a `c[j]`.

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

When a problem asks for a partition with a divisibility constraint, **look for the maximum element** — it's often the natural separator. Don't reach for complex data structures before checking the simplest possible partitioning strategy. Also, always check _which direction_ the constraint applies.

## Your Code

```cpp
#include <bits/stdc++.h>
using namespace std;
// --- Type Aliases ---
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

// --- Constants ---
const int MOD = 1e9 + 7;
const ll INF = 1e18;
// --- Solution ---
void solve() {
    int n; cin>>n;
    map<int,int,greater<int>> mp;
    vi a,b;
    for(int i = 0; i<n; i++){
        int x; cin>>x;
        mp[x]++;
    }
    bool swp = true;
    auto it = mp.begin();
    for(auto p : mp){
        int x = p.first, y = p.second;
        while(y--){
            if(swp){
                b.push_back(x);
            } else{
                a.push_back(x);
            }
        }
        it++;
        if(it == prev(mp.end())) swp = !swp;
    }
    if(a.size()==0) cout<<-1<<endl;
    else{
        cout<<a.size()<<" "<<b.size()<<endl;
        for(int i = 0; i<a.size(); i++){
            cout<<a[i];
            cout<<((i==a.size()-1)? "\n" : " ");
        }
        for(int i = 0; i<b.size(); i++){
            cout<<b[i];
            cout<<((i==b.size()-1)? "\n" : " ");
        }

    }


}

// --- Main ---
int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // Read number of test cases
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
```

> _This is your original solution. Keep it here to track how your coding style evolves over time._

## Code Review

### What's Good

- **Fast I/O setup** with `ios_base::sync_with_stdio(false)` and `cin.tie(NULL)` — good habit for CP.
- **Type aliases** ready to go — shows you're thinking ahead about readability.
- **The core logic is correct** — you do split elements into two groups, and you correctly output -1 when one group is empty.
- **You handle the all-equal case** (all elements go into `b`, leaving `a` empty → -1).

### What Could Be Improved

**1. Overcomplicated the core logic**

You used a `map<int,int,greater<int>>` with a toggle-switch (`swp`) to distribute elements. This is far more complex than needed:

- A `map` with a custom comparator just to count frequencies is overkill when `n ≤ 100`
- The toggle-switch logic (`if(it == prev(mp.end())) swp = !swp`) is hard to follow and fragile — it only works because of the specific map ordering
- Your variable naming is confusing: `a` is the smaller-values array and `b` is the max-containing array, which is the opposite of the problem's naming

**2. Unnecessary frequency counting**

You don't need to count frequencies at all. Just find `max(a)` and split. The frequency approach works, but adds complexity without benefit.

**3. Type aliases and constants are unused**

`ll`, `vll`, `pii`, `pll`, `MOD`, `INF` are defined but never used in this problem. Only keep what you actually use to avoid clutter.

**4. Output formatting is fragile**

```
cout<<((i==a.size()-1)? "\n" : " ");
```

This works but is harder to read than a simple range-for loop. Prefer:

```cpp
for (int x : a) cout << x << " ";
cout << "\n";
```

(A trailing space is acceptable in CP.)

### Suggested Refactor

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

This is shorter, clearer, and O(n) instead of O(n log n). The lesson here: **for an 800-rated problem, start with the simplest possible approach before reaching for maps or custom comparators.**

---

**Generated:** 2026-07-22
**Next Review:** 2026-07-25
