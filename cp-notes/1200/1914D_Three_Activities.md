# 1914D - Three Activities

**Rating:** 1200
**Category:** Greedy / Brute Force / Sorting
**Solve Time:** —
**Confidence:** 3/10

## Problem Summary

Given three arrays `a`, `b`, `c` of length `n`, pick exactly one index from each array such that **all three indices are distinct** and the sum `a[i] + b[j] + c[k]` is maximized.

## Key Insight

The optimal choice will always use a value that is among the **top 3** in its respective array. So instead of trying all O(n³) combinations, just take the top 3 from each array (sorted by value descending) and brute-force all 3×3×3 = 27 combinations, checking that indices are distinct.

## Solution Approach

### Step 1: Observation

Why top 3? Suppose the optimal solution picks `a[i]` where `i` is not in the top 3 of array `a`. Then the indices of the top 3 values in `a` — call them `p1, p2, p3` — are blocked by at most 2 indices (`j` from `b`, `k` from `c`). So at least one of `p1, p2, p3` is distinct from both `j` and `k`, and its value is ≥ `a[i]`. Replacing `i` with that index gives a sum ≥ the supposed optimum — contradiction. So the optimal `a` index **must** be among the top 3.

Same reasoning applies to `b` and `c`.

### Step 2: Algorithm

- Store each array as `(value, index)` pairs
- Sort each descending by value
- Keep only the top 3 of each
- Try all 27 combinations `(i, j, k)` ∈ top3_a × top3_b × top3_c
- If `a[i].idx ≠ b[j].idx ≠ c[k].idx ≠ a[i].idx`, compute the sum
- Output the max sum found

### Step 3: Implementation

```cpp
int n; cin >> n;
vector<pair<ll,int>> a(n), b(n), c(n);
for (int i = 0; i < n; i++) { cin >> x; a[i] = {x, i}; }
for (int i = 0; i < n; i++) { cin >> x; b[i] = {x, i}; }
for (int i = 0; i < n; i++) { cin >> x; c[i] = {x, i}; }

sort(a.rbegin(), a.rend());
sort(b.rbegin(), b.rend());
sort(c.rbegin(), c.rend());

ll ans = 0;
for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
        for (int k = 0; k < 3; k++)
            if (a[i].second != b[j].second
             && a[i].second != c[k].second
             && b[j].second != c[k].second)
                ans = max(ans, a[i].first + b[j].first + c[k].first);

cout << ans << "\n";
```

### Step 4: Edge Cases

- **n < 3** — still works because we only need 3 distinct indices; if n=2, no valid triple exists (not in constraints but conceptually impossible)
- **Top 3 values share the same index** — the distinctness check handles this
- **All values tied at the maximum** — any triple of distinct indices works
- **Large n (up to 1e5)** — sorting is O(n log n), the triple loop is constant 27 iterations

## Complexity Analysis

- **Time:** O(n log n) — sorting three arrays
- **Space:** O(n) — storing three arrays of pairs

## Why This Works

The "top 3" argument is the key:

- The optimal solution needs 3 indices, one from each array.
- For array `a`, the indices `j` (from `b`) and `k` (from `c`) can block at most 2 indices from being chosen.
- The top 3 values of `a` occupy 3 distinct indices. At least one of them is not `j` or `k`.
- Replacing the chosen `a` index with that top-3 index can only increase (or maintain) the sum.

Same argument applies symmetrically to `b` and `c`. So the optimal triple must be drawn from the top 3 of each array, and 27 checks suffice.

## Common Mistakes

- **Trying to greedily pick the single global max first** — this often leads to conflicts (same index used twice), and the fallback choices may be suboptimal.
- **Overcomplicating with complex data structures** (like my first attempt with per-index "best category" selection).
- **Only keeping the single best per array** — but two best entries might share the same index, leaving no valid triple.
- **Forgetting `long long`** — values can sum beyond int range.

## Clean Code

```cpp
void solve() {
    int n; cin >> n;
    vector<pair<ll,int>> a(n), b(n), c(n);
    for (int i = 0; i < n; i++) { ll x; cin >> x; a[i] = {x, i}; }
    for (int i = 0; i < n; i++) { ll x; cin >> x; b[i] = {x, i}; }
    for (int i = 0; i < n; i++) { ll x; cin >> x; c[i] = {x, i}; }
    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());
    sort(c.rbegin(), c.rend());
    ll ans = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                if (a[i].second != b[j].second
                 && a[i].second != c[k].second
                 && b[j].second != c[k].second)
                    ans = max(ans, a[i].first + b[j].first + c[k].first);
    cout << ans << "\n";
}
```

## Key Takeaway

**Only the top 3 matter.** When you need to pick distinct items from multiple categories, brute-force over the top few candidates from each category — the "blocking" argument guarantees optimality. Don't try to design a clever selection rule; just enumerate the small candidate set.

## Your Code

**Attempt 1:**

```cpp
void solve(){
    int n; cin>>n;
    vector<int> a(n),b(n),c(n);
    for(int i = 0 ; i<n; i++) cin>>a[i];
    for(int i = 0 ; i<n; i++) cin>>b[i];
    for(int i = 0 ; i<n; i++) cin>>c[i];
    vector<pair<int,int>> vt(n);
    for(int i = 0 ; i<n; i++) {
        if(a[i]>b[i] && a[i]>c[i]) vt[i]={a[i],1};
        else if(b[i]>a[i] && b[i]>c[i]) vt[i]={b[i],2};
        else if(c[i]>b[i] && c[i]>a[i]) vt[i]={c[i],3};
        else if(a[i]>b[i] && b[i]==c[i])vt[i]={a[i],1};
        else if(b[i]>a[i] && a[i]==c[i])vt[i]={b[i],2};
        else if(c[i]>a[i] && b[i]==a[i])vt[i]={c[i],3};
        else if(a[i]==b[i] && b[i]==c[i])vt[i]={a[i],1};
    }
    sort(vt.rbegin(),vt.rend());
    long long res=0;
    bool A=true,B=true,C=true;
    for(auto p : vt){
        if(p.second==1 && A){
            res+=p.first;
            A=!A;
        }
        if(p.second==2 && B){
            res+=p.first;
            B=!B;
        }
        if(p.second==3 && C){
            res+=p.first;
            C=!C;
        }
        if(!A && !B && !C) break;
    }
    cout<<res<<endl;
}
```

**Attempt 2:**

```cpp
void solve() {
    struct tri{
        int x,y,z;
    };
    int n; cin>>n;
    vi a(n),b(n),c(n);
    for(int i = 0; i<n; i++) cin>>a[i];
    for(int i = 0; i<n; i++) cin>>b[i];
    for(int i = 0; i<n; i++) cin>>c[i];
    vector<tri> vt;
    for(int i = 0; i<n; i++){
        vt.push_back({a[i],b[i],c[i]});
    }
    sort(vt.begin(), vt.end(),[](const tri& a, const tri &b){
        if(a.x != b.x) return a.x>b.x;
        if(a.y != b.y) return a.y>b.y;
        return a.z>b.z;
    });
    ll sum = 0;
    for(int i = 0; i<3; i++){
        sum += max({vt[i].x, vt[i].y, vt[i].z});
    }
    cout<<sum<<endl;
}
```

> _These are your original attempts. Keep them here to track how your coding style evolves over time._

## Code Review

You couldn't solve this one — and that's OK. Let's break down why both attempts failed and what the official solution teaches.

### Attempt 1: "Per-index best category" greedy

The idea: for each index `i`, pick the best of `a[i]`, `b[i]`, `c[i]`, tag it with the category (1/2/3), sort all picks descending, then take the top pick from each category.

**Why it fails:** This approach doesn't understand that you can pick **different indices** for different categories. It forces each index to contribute at most one value from a single category, but the problem allows (and requires) picking from any combination of indices across categories. For example, the optimal solution might take `a[0]` (largest a-value) and `b[5]` (largest b-value) — but index 5 might have a small a-value, so your per-index max would tag index 5 as category `a` or `c`, and you'd miss `b[5]` entirely.

**The fundamental misunderstanding:** You tried to reduce each index to a single "best" value, but the problem needs the **global top values** across all indices for each array independently.

### Attempt 2: "Sort triples by a-value" greedy

The idea: put all three values for each index into a struct, sort by `a` descending as primary key, then take the top 3 rows and sum their max values.

**Why it fails:** This assumes the top 3 best picks come from 3 different indices — but it doesn't even check distinctness, and more importantly, sorting by `a`-value means you might miss a huge `b` or `c` value at an index with a mediocre `a`. Also, taking `max` from each of the top 3 rows could reuse the same category (e.g., all 3 rows might contribute `a` values).

**Example where it fails:** Suppose:
- Index 0: a=100, b=1, c=1
- Index 1: a=2, b=99, c=1  
- Index 2: a=2, b=1, c=99

Sorted by a: index 0 (100,1,1), index 1 (2,99,1), index 2 (2,1,99). Your code would sum: max(100,1,1)=100 + max(2,99,1)=99 + max(2,1,99)=99 = 298. But the optimal is 100+99+99=298... actually that works by coincidence! But consider:

- Index 0: a=100, b=90, c=1
- Index 1: a=99, b=1, c=1

Here n=2, only 2 indices. Sorted by a: index 0 (100,90,1), index 1 (99,1,1). Your code takes top 3 (but there are only 2), sums: max(100,90,1)=100 + max(99,1,1)=99 = 199. But we can't pick 3 distinct indices from only 2 indices! (The problem guarantees n ≥ 3 though.)

A better counterexample with n=3:
- Index 0: a=100, b=1, c=1
- Index 1: a=99, b=99, c=1
- Index 2: a=1, b=1, c=99

Sorted by a: 0, 1, 2. Your code: 100 + 99 + 99 = 298. But optimal: a[0]=100 + b[1]=99 + c[2]=99 = 298. Same result by luck.

Let me find one where it truly fails:
- Index 0: a=100, b=50, c=50
- Index 1: a=1, b=99, c=1
- Index 2: a=1, b=1, c=99

Your code: sorted by a → 0, 1, 2. Sum = max(100,50,50)=100 + max(1,99,1)=99 + max(1,1,99)=99 = 298.
Optimal: a[0]=100 + b[1]=99 + c[2]=99 = 298. Still works...

The issue is more subtle. The real problem is your approach doesn't check index distinctness and assumes the top 3 rows by a-value contain the optimal combination, which isn't guaranteed by any reasoning.

### The Missing Insight

**You don't need a clever selection rule — you just need to keep the top 3 per array and brute-force.** The official solution is deliberately simple:

1. Sort each array independently
2. Keep indices (so you can check distinctness)
3. Try all 27 combos

The key realization: the optimal answer must draw from the top 3 of each array. This is a **pigeonhole / contradiction argument**, not a greedy construction. Once you see that, the implementation is trivial.

### What to Study

- **"Top K candidates" problems** — anytime you need to pick one from each category with distinct index constraints, think: keep top few per category, brute-force the combinations
- **Sorting with index tracking** — `pair<value, index>` is your friend
- **When NOT to use greedy** — if you can't prove your selection rule preserves optimality, try brute-force over a small candidate set instead

### Suggested Refactor (learn from the official solution)

```cpp
void solve() {
    int n; cin >> n;
    vector<pair<ll,int>> a(n), b(n), c(n);
    for (int i = 0; i < n; i++) { ll x; cin >> x; a[i] = {x, i}; }
    for (int i = 0; i < n; i++) { ll x; cin >> x; b[i] = {x, i}; }
    for (int i = 0; i < n; i++) { ll x; cin >> x; c[i] = {x, i}; }
    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());
    sort(c.rbegin(), c.rend());
    ll ans = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                if (a[i].second != b[j].second
                 && a[i].second != c[k].second
                 && b[j].second != c[k].second)
                    ans = max(ans, a[i].first + b[j].first + c[k].first);
    cout << ans << "\n";
}
```

---

**Generated:** 2026-07-22
**Next Review:** 2026-07-25
