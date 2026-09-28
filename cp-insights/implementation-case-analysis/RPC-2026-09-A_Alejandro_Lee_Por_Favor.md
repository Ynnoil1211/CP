# RPC 2026-09 A - Alejandro, lee por favor

**Type:** Implementation / Case Analysis
**Rating / Context:** Div 3B / Div 2A (UTP Open 2026)
**Tag:** dynamic-caesar-cipher-simulation

## Key Insight

💡 Decrypt letter-by-letter with a dynamic shift `c`, immediately updating the frequency of the recovered original letter `L`, and increment `c` when its frequency becomes a multiple of `K`.

## Pattern Trigger

"Each letter shifted by dynamic counter `c`, counter increments when original letter appearance count is multiple of secret `K`, total chars up to `10^6`."

## Breakthrough

Never update frequency using the encrypted character read from input; the state update depends strictly on the original decrypted letter `L = (E - c + 26) % 26`.

## Code Spotlight

```python
for ch in word:
    l = (ord(ch) - a_ord - c) % 26
    out.append(chr(a_ord + l))
    count[l] += 1
    if count[l] % k == 0:
        c += 1
```

## Example

Input: `2 3`, Words: `aaa bbb`
Output: `aaa aaa`
Why: First word decodes to `aaa`, making `count['a'] = 3` (multiple of 3), which shifts `c` from 0 to 1, causing `bbb` to decode back to `aaa`.

---

**Generated:** 2026-09-26
