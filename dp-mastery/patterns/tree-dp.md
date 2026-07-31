# Pattern: Tree DP

## Pattern Name: **Tree DP**

### Description

Your state is a **node**, computed from its children in post-order. Often you track **two states per node** — "best if I include this node" vs. "best if I exclude it".

The mental shift: the tree's structure gives you the DP order for free — children always come before parents. You never iterate over an order; you recurse, and the call stack handles it.

### When to recognize it

- The problem is explicitly on a tree / binary tree
- Parent-child decisions ("can't pick adjacent nodes", "max path", "diameter")
- "root", "subtree", "a node and its children"

### The General Template

**State:**
```
dp[node][0/1] = best value in node's subtree, excluding (0) or including (1) node
```

**Base case:**
```
leaf: dp[leaf][0] = 0, dp[leaf][1] = value(leaf)
```

**Transition:**
```
dp[node][1] = value(node) + sum over children of dp[child][0]
dp[node][0] = sum over children of max(dp[child][0], dp[child][1])
```

**Answer:** `max(dp[root][0], dp[root][1])`.

**Complexity:** O(n) time — each node visited once. O(n) space for the call stack.

### The core intuition to keep

The include/exclude pair is the tree version of **take/skip**: if I include the node, children must be excluded; if I exclude it, children are free. Post-order recursion means children are already solved when the parent needs them. Most tree DP problems are this pair plus problem-specific extra state (paths, diameters, budgets).

### 🟢 Solved Problems

None yet.

### ⏳ Next up

- [337 - House Robber III](https://leetcode.com/problems/house-robber-iii/) — the canonical include/exclude tree problem
- Later: 124 - Binary Tree Maximum Path Sum, 543 - Diameter of Binary Tree
