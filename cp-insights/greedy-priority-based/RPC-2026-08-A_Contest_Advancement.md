# RPC 2026-08 A - Contest Advancement

**Type:** Greedy / Priority-Based
**Rating:** 1000
**Tag:** two-pass-greedy-filtering

## Key Insight

💡 Select candidates in merit order respecting the per-school quota C in pass 1, fill remaining vacancies from unselected teams in pass 2, and print strictly by original rank.

## Pattern Trigger

"Top K teams advance, max C per school, fill remaining slots with highest ranked remaining teams, output in original ranking order." When a selection process has multiple filtering stages, early selection must not dictate final output ordering.

## Breakthrough

Do not print greedily during pass 1; collect selected team IDs in a set or boolean marker array, then do a final pass over the original ranking to preserve the true relative merit order.

## Code Spotlight

```cpp
unordered_map<int, int> school_cnt;
unordered_set<int> selected;
for (auto& team : teams) {
    if (school_cnt[team.school] < c && selected.size() < k) {
        selected.insert(team.id);
        school_cnt[team.school]++;
    }
}
for (auto& team : teams) {
    if (selected.size() == k) break;
    selected.insert(team.id);
}
for (auto& team : teams) if (selected.count(team.id)) cout << team.id << "\n";
```

## Example

Input: N=5, K=3, C=1, teams: `[(1, S1), (2, S1), (3, S2), (4, S1), (5, S3)]`
Trace:
- Pass 1 accepts: Team 1 (S1), Team 3 (S2). (2 teams, need 3).
- Pass 2 fills remaining slot with Team 2 (S1).
Output: `1\n2\n3` (not `1\n3\n2`)
Why: Output must reflect original rank (1 < 2 < 3), not the order of pass fulfillment.

---

**Generated:** 2026-09-13