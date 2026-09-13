# 1157E - Minimum Array

**Rating:** 1700
**Category:** Greedy / Priority-Based / Data Structures
**Solve Time:** —
**Confidence:** 7/10

## Problem Summary

Given two arrays a and b of length n with elements in [0, n - 1], reorder array b to form an array c where `c[i] = (a[i] + b[i]) % n` such that c is lexicographically as small as possible.

## Key Insight

Lexicographical order demands a greedy choice at each position: minimize c[0], then c[1], and so on. For each a[i], the ideal complement is `n - a[i]` (giving sum 0 % n). We query a multiset for the smallest element ≥ `n - a[i]` using `b.lower_bound(n - a[i])`. If no such element exists (iterator reaches `b.end()`), the sum cannot reach n, so we wrap around to `b.begin()` to pick the absolute smallest element in b.

## Solution Approach

### Step 1: Observation

Since we want the lexicographically smallest array c, the decision for index i takes strict precedence over any subsequent index j > i. Therefore, a greedy approach processing from i = 0 to n - 1 is optimal.

For a fixed a[i], we need to choose an unused element b[j] to minimize:
```text
c[i] = (a[i] + b[j]) % n
```

Because 0 ≤ a[i], b[j] < n, the sum `a[i] + b[j]` lies in [0, 2n - 2]:
1. If `b[j] >= n - a[i]`, then `n <= a[i] + b[j] < 2n`. Thus, `(a[i] + b[j]) % n = a[i] + b[j] - n >= 0`. To minimize this result, we want b[j] to be as close to `n - a[i]` as possible from above. The smallest `b[j] >= n - a[i]` yields the smallest remainder.
2. If no available element satisfies `b[j] >= n - a[i]`, then for all available elements, `a[i] + b[j] < n`. Thus, `(a[i] + b[j]) % n = a[i] + b[j]`. To minimize this sum, we should pick the smallest available b[j] overall.

### Step 2: Algorithm

1. Store all elements of array b in a `std::multiset<int>`.
2. For each element a[i] from i = 0 to n - 1:
   - Search for the smallest `x in b` such that `x >= n - a[i]` using `b.lower_bound(n - a[i])`.
   - If found (`it != b.end()`), choose `x = *it`.
   - If not found (`it == b.end()`), wrap around and pick the smallest element currently in the multiset: `it = b.begin()`, `x = *it`.
   - Print `(a[i] + x) % n`.
   - Remove this specific instance from the multiset: `b.erase(it)`.

### Step 3: Implementation

Crucial detail on binary searching in STL containers:
- **Never** use `std::lower_bound(b.begin(), b.end(), val)` on a `std::set` or `std::multiset`. Set iterators are bidirectional, not random-access. `std::lower_bound` degrades to linear step-by-step traversal (O(n) per query, resulting in O(n^2) overall → TLE).
- **Always** use the member function `b.lower_bound(val)`, which traverses the balanced BST in O(log n) time.

### Step 4: Edge Cases

- `a[i] = 0`: `n - a[i] = n`. Since all elements in b are < n, `b.lower_bound(n)` always returns `b.end()`. The code naturally falls back to `b.begin()`, picking the smallest available b[j], which produces `(0 + min(b)) % n = min(b)`. This is completely correct.
- Duplicate values in b: Handled cleanly by `std::multiset`. Calling `b.erase(it)` deletes only that single node by iterator, preserving other duplicate copies.

## Complexity Analysis

- **Time:** O(n log n). Inserting n elements into `std::multiset` takes O(n log n). Each of the n queries performs one member `lower_bound` (O(log n)) and one iterator-based `erase` (O(1) amortized / O(log n)), well within the 3.0s time limit for n = 2e5.
- **Space:** O(n) to store elements in array a and the `multiset` b.

## Why This Works

Lexicographical priority is strictly left-to-right. At index i, achieving the absolute minimum value for c[i] is always better than any consequence it might have on later positions. The partition of possible remainders into [0, n - 1] maps monotonically: values `b[j] >= n - a[i]` map to remainders `[0, n - 1 - a[i]]`, and values `b[j] < n - a[i]` map to `[a[i], n - 1]`. The best possible remainder in the first group is achieved at the minimum `b[j] >= n - a[i]`. If that group is empty, the best possible remainder in the second group is achieved at the minimum `b[j] < n - a[i]`, which is simply the smallest element in b.

## Common Mistakes

- **Using `std::lower_bound(s.begin(), s.end(), x)` instead of `s.lower_bound(x)`:** Global `std::lower_bound` takes O(n) on non-random-access iterators. Calling it inside an n-iteration loop yields O(n^2) TLE.
- **Erasing by value instead of iterator:** Writing `b.erase(*low)` deletes **all** occurrences of that number from a `multiset`. You must write `b.erase(low)` to remove only the single matched element.
- **Overcomplicating the modulo wrap-around:** Trying to construct complex branching when a simple `if (low == b.end()) low = b.begin();` handles both the wrap-around and the `a[i] = 0` case.

## Clean Code

```cpp
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    multiset<int> b;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        b.insert(x);
    }
    for (int i = 0; i < n; i++) {
        auto it = b.lower_bound(n - a[i]);
        if (it == b.end()) it = b.begin();
        cout << (a[i] + *it) % n << (i + 1 == n ? "" : " ");
        b.erase(it);
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
```

## Key Takeaway

When matching elements under modular arithmetic to minimize `(a[i] + b[j]) % n`:
1. The target complement that gives 0 is `n - a[i]`.
2. Query `multiset::lower_bound(target)`.
3. If not found, wrap around to `multiset::begin()`.
4. Always use member `.lower_bound()` on associative containers, never `std::lower_bound()`.

## 🔑 Breakthrough

_`std::lower_bound(b.begin(), b.end(), val)` compiles on `std::multiset` but runs in O(n) time because set iterators are bidirectional, causing a silent O(n^2) TLE; always call the container's member function `b.lower_bound(val)` for true O(log n) tree traversal._

## Your Code

```cpp
// First attempt — TLE (used global std::lower_bound on multiset iterators)
#include <bits/stdc++.h>
#include <set>
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
    vll a(n), c(n);
    multiset<ll> b;
    for (int i = 0; i<n; i++){
        cin>>a[i];
    }
    for (int i = 0; i<n; i++){
        int x; cin>>x;
        b.insert(x);
    }
    for (int i = 0; i<n; i++){
        auto low = lower_bound(b.begin(),b.end(), n-a[i]);
        if(low==b.end()) low=b.begin();
        c[i]=(*low+a[i])%n;
        b.erase(low);
    }
    for(int i = 0; i<n; i++){
        cout<<c[i]<<" ";
    }
}

// --- Main ---
int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   
    int t = 1;
    // Read number of test cases
    //cin >> t;
   
    while (t--) {
        solve();
    }
   
    return 0;
}// Source: https://usaco.guide/general/io

// Second attempt — AC (switched to b.lower_bound and printed directly)
#include <bits/stdc++.h>
#include <set>
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
    vll a(n);
    multiset<ll> b;
    for (int i = 0; i<n; i++){
        cin>>a[i];
    }
    for (int i = 0; i<n; i++){
        int x; cin>>x;
        b.insert(x);
    }
    for (int i = 0; i<n; i++){
        auto low = b.lower_bound(n-a[i]);
        if(low==b.end()) low=b.begin();
        cout<<(*low+a[i])%n<<" ";
        b.erase(low);
    }
    
}

// --- Main ---
int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   
    int t = 1;
    // Read number of test cases
    //cin >> t;
   
    while (t--) {
        solve();
    }
   
    return 0;
}// Source: https://usaco.guide/general/io
```

> _This is your original solution. Keep it here to track how your coding style evolves over time._

## Code Review

### What Was Good
- **Algorithmic intuition was spot on:** You immediately recognized that the problem is greedy, that $(a_i + b_j) \equiv 0 \pmod n$ needs $b_j = n - a_i$, and that `b.begin()` handles the wrap-around when no element $\ge n - a_i$ is available.
- **Correct erase syntax:** You correctly used `b.erase(low)` (passing the iterator) rather than `b.erase(*low)`. Many candidates make the mistake of erasing by value, which wipes all identical copies from the multiset.
- **Fast I/O included:** `ios_base::sync_with_stdio(false); cin.tie(NULL);` is essential for $n = 2 \cdot 10^5$.
- **Direct streaming in the fix:** In your second version, printing `(*low + a[i]) % n` on the fly eliminated the intermediate vector `c(n)`.

### What Needed Fixing
1. **The O(n) iterator trap (`std::lower_bound` vs `member.lower_bound`):**
   `std::lower_bound` from `<algorithm>` accepts any iterator range. However, for non-random-access iterators (like those in `std::set`, `std::multiset`, `std::map`), advancing takes O(k) steps rather than O(1). Calling it n times gave O(n^2) time. Switching to `b.lower_bound(n - a[i])` fixed this immediately.
2. **Redundant includes and types:**
   - `<bits/stdc++.h>` already includes `<set>`, so `#include <set>` is redundant.
   - For values strictly in range [0, n - 1] with n ≤ 2e5, standard 32-bit `int` is sufficient; `long long` isn't required here and uses double the memory inside the red-black tree nodes.

---

**Generated:** 2026-09-13
**Next Review:** 2026-09-16 (3 days — reinforce member vs global binary search and multiset mechanics)
