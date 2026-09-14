// Arup Guha
// 1/28/2024
// Solution to 2023 NAQ Problem E: Team Generation

using namespace std;

#include <bits/stdc++.h>

bool canDo(int idx, vector<int> minR, vector<int> maxR);

int main() {

    int n;
    cin >> n;
    vector<int> minR(n);
    vector<int> maxR(n);

    // Read in ranges.
    for (int i=0; i<n; i++) {
        cin >> minR[i] >> maxR[i];
    }

    // idx is best person we're forming a team with.
    int idx = 0, res = 0;

    // Go through contestants.
    while (idx+2 < n) {

        // Try to put these 3 consecutive people together.
        // Replacement argument due to input bounds says this
        // produces an optimal answer.
        if (canDo(idx, minR, maxR)) {
            res++;
            idx += 3;
        }

        // Can't use contestant idx, move on.
        else
            idx++;
    }

    // Ta da!
    cout << res << endl;

    return 0;
}

// Returns true if contestants idx, idx+1 and idx+2 can form a team.
bool canDo(int idx, vector<int> minR, vector<int> maxR) {

    // Best person's rank.
    int r = idx+1;

    // See if anyone doesn't want people in this range.
    for (int i=idx; i<idx+3; i++) {
        if (minR[i]>r || maxR[i]<r+2)
            return false;
    }

    // If we make it here, we're good...
    return true;
}
