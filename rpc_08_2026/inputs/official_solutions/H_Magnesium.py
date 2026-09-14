# Arup Guha
# 1/27/2024
# Solution to 2023 NAQ Problem H: Magnesium Supplementation

def divs(n):

    # Store divisors here.
    res = []

    # Go upto sqrt
    i = 1
    while i*i <= n:

        # See if i is a divisor.
        if n%i == 0:
            res.append(i)

            # Add this as long as it's unique
            if i < n//i:
                res.append(n//i)

        i+=1

    return res
            
# Get basic data
toks = input().split()
n = int(toks[0])
maxPill = int(toks[1])
maxDays = int(toks[2])

# Get divisors and sort.
vals = divs(n)
vals.sort()

# Now go through and find all the valid ones.
res = []
for x in vals:

    # Skip over.
    if n//x > maxDays:
        continue

    # Nothing else will work.
    if x > maxPill:
        break

    # Add
    res.append(x)

# Ta Da!
print(len(res))
for x in res:
    print(x)
