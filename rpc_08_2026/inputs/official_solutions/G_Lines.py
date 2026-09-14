# Arup Guha
# 1/27/2024
# Solution to 2023 NAW Problem G: Lines Per Hour

# number of problems
toks = input().split()
n = int(toks[0])

# For 5 hours...
limit = int(toks[1])*5

# read problems
vals = []
for i in range(n):
    x = int(input())
    vals.append(x)

# Sort it...
vals.sort()

# Defaults
cur = 0
res = n

for i in range(n):

    # Add it.
    cur += vals[i]

    # If too big, answer is i.
    if cur > limit:
        res = i
        break

print(res)
