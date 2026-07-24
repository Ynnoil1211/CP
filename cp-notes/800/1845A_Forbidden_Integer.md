# 1845A - Forbidden Integer

**Rating:** 800
**Category:** Constructive / Greedy / Math
**Solve Time:** —
**Confidence:** 0/10

## Problem Summary

Given n, k, x, you have unlimited supply of every integer from 1 to k **except** x. Determine if you can sum some selection to exactly n, and output any valid multiset.

## Key Insight

The forbidden number x determines the strategy. If 1 is available (x≠1), the answer is trivially n copies of 1. If 1 is forbidden (x=1), use 2s and at most one 3 to construct n — but this only works when k≥2 (for using 2) and, for odd n, when k≥3 (for using 3).

## Solution Approach

### Step 1: Classification by x

The problem splits into two main cases based on whether the number 1 is available:

- **x ≠ 1:** Use n copies of 1. Always YES.
- **x = 1:** Need to build n without using 1. Use 2 as the base unit.

### Step 2: Handle x = 1

With x=1, the smallest available number is 2. So:

- **k = 1:** Nothing available at all → NO.
- **k = 2, x = 1:** Only 2 is available. If n is odd, impossible (sum of 2s is always even) → NO. If n even, use n/2 copies of 2.
- **k ≥ 3, x = 1:** Can use 2s and optionally one 3. If n even → n/2 copies of 2. If n odd → one 3 and (n-3)/2 copies of 2.

### Step 3: Output Format

Don't forget to print the count m on its own line before the array elements.

### Step 4: Edge Cases

- k=1, any x — only 1 is available. If x=1 → NO. If x≠1 impossible since x≤k=1, so this case never occurs.
- x=1, k=2, n odd → NO (can't sum to odd with only 2s).
- x=1, k≥3, n=1 or n=3 → use [1]?? No, can't use 1. For k≥3, n=1 is impossible (smallest available is 2). But constraints say x≤k≤n, so n≥x. If x=1, then n≥1. For n=1, k≥3, x=1: smallest available is 2, can't reach 1 → NO. But wait, the code: k≥3, x=1 case falls into else branch. For n=1 (odd): tot = n/2 = 0, tot-1 = -1 → the for loop doesn't run, then prints 3. But that would exceed n. So there's a subtle edge case!

Actually, let me re-examine. The constraints say 1 ≤ x ≤ k ≤ n ≤ 100. So n ≥ k ≥ x. If x = 1 and k ≥ 3, then n ≥ k ≥ 3. So n ≥ 3. The smallest n in this branch is 3, which works (just [3]).

## Complexity Analysis

- **Time:** O(n) per test case (constructing the output array)
- **Space:** O(1) auxiliary, O(n) for output

## Why This Works

This is a constructive case analysis. By examining which small numbers are available (1, 2, 3), we cover all possibilities because:
- 1 can represent any n when available.
- 2 can represent any even n when available.
- 2 and 3 together can represent any n ≥ 3 (since 2 and 3 are coprime, and by the Chicken McNugget theorem, the largest unrepresentable number is 2·3 - 2 - 3 = 1, so all n ≥ 2 work — but here n≥3).

The constraints (n ≤ 100) also mean we could brute-force, but the constructive approach is cleaner.

## Common Mistakes

- **Forgetting to print `m`** (the count line before the array). The user's original code omitted this in the x≠1 branch.
- **Confusing the odd-n construction.** For x=1, k≥3, n odd: use one 3, not two 3s or a different pattern. The formula is (n/2) copies where n/2 is integer division: output (n/2 - 1) copies of 2 and one 3.
- **Thinking this is a DP / subset-sum problem.** The constraints (n ≤ 100) are small enough that DP works, but the constructive greedy approach is simpler and expected at this rating.

## Clean Code

```cpp
void solve() {
    int n, k, x;
    cin >> n >> k >> x;

    if (x != 1) {
        cout << "YES\n" << n << "\n";
        for (int i = 0; i < n; i++) cout << "1 ";
        cout << "\n";
        return;
    }

    // x == 1 from here
    if (k == 1 || (k == 2 && n % 2 == 1)) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    if (n % 2 == 0) {
        cout << n / 2 << "\n";
        for (int i = 0; i < n / 2; i++) cout << "2 ";
    } else {
        cout << n / 2 << "\n";
        for (int i = 0; i < n / 2 - 1; i++) cout << "2 ";
        cout << "3";
    }
    cout << "\n";
}
```

## Key Takeaway

**Case analysis problems reward a calm, systematic breakdown.** When a number is "forbidden", ask: what's the simplest fallback? Here, 1 is the universal building block; when 1 is gone, 2 and 3 take over. Always check the edge of each branch (smallest n, parity, etc.).

## Your Code

```cpp
void solve() {
    int n,k,x; cin>>n>>k>>x;
    if(k==1)cout<<"NO"<<endl;
    else if(x == 1 && k == 2 && n%2!=0) cout<<"NO"<<endl;
    else{
        cout<<"YES"<<endl;
        if(x!=1){
            cout<<n<<endl;
            for(int i = 0; i<n; i++){
                cout<<1<<" ";
            }
            cout<<'\n';
        }
        else{
            if(n%2==0){
                int tot = n/2;
                cout<<tot<<endl;
                for(int i = 0; i<tot; i++){
                    cout<<2<<" ";
                }
                cout<<endl;
            }
            else {
                int tot = n/2;
                cout<<tot<<endl;
                for(int i = 0; i<tot-1; i++){
                    cout<<2<<" ";
                }
                cout<<3<<endl;
            }
            return;
        }
    }
}
```

> _This is your original solution. Keep it here to track how your coding style evolves over time._

## Code Review

### What's Good
- The case logic structure is correct: you correctly identified the three branches (x≠1, x=1 & even, x=1 & odd).
- You found the key edge case (x=1, k=2, n odd → NO) on your own.

### What to Improve
1. **Missing the count `m` line** — In the x≠1 branch, you printed n elements but never printed `n` on its own line first. The problem requires an extra line showing the number of integers. This was probably why it didn't pass.
2. **The odd-n construction used `tot = n/2 + 1` before hints** — That gives one extra 2. The correct formula keeps `tot = n/2` (integer division) and replaces the last 2 with a 3.
3. **Readability** — The deeply nested if-else is hard to follow. Using early returns flattens the logic (see Clean Code above).

### What to Work On
This was a **constructive case analysis** problem — a very common pattern at 800-900. The skill is: enumerate the branches systematically and verify each with a small example before coding. Don't jump straight to implementation; sketch the decision tree on paper first.

### Don't Be Discouraged
Confidence 0/10 means you saw the answer, not that you couldn't have gotten there. The tutorial showed you the clean branch structure — next time a "forbidden number" problem appears, you'll recognize the pattern immediately. That's real learning.

---

**Generated:** 2026-07-24
**Next Review:** 2026-07-27 (3 days — low confidence needs early review)
