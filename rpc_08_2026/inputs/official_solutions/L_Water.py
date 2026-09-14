# Arup Guha
# 1/27/2024
# Solution to 2023 NAQ Problem L: Water Journal

# Get basic data
toks = input().split()
n = int(toks[0])
low = int(toks[1])
high = int(toks[2])

# Track if we have theses
haveMin = False
haveMax = False

# Go through the numbers.
for i in range(n-1):

    x = int(input())

    # Mark if we see low or high.
    if x == low:
        haveMin = True
    if x == high:
        haveMax = True

# It can be anything.
if haveMin and haveMax:
    for i in range(low,high+1):
        print(i)

# Not possible...if low==high, it won't get here since
# there is always one reading.
elif  not haveMin and  not haveMax:
    print(-1)

# Need the min.
elif not haveMin:
    print(low)

# Need max
else:
    print(high)
