// Arup Guha
// 3/8/2024
// Solution to 2023 NAQ Problem I: Missing Number
// https://open.kattis.com/problems/missingnumber2

using namespace std;

#include <bits/stdc++.h>

vector<int> solve(string s, int len);
int getnum(string s, int sI, int len);
int numd(int n);

int main() {

    int nC;
    cin >> nC;

    // Process cases.
    for (int loop=0; loop<nC; loop++) {

        // Read string.
        string s;
        cin >> s;

        // Store results here.
        vector<int> res;

        // Try each starting number.
        for (int len=1; len<=5; len++) {
            vector<int> tmp = solve(s, len);
            for (int x: tmp)
                res.push_back(x);
        }

        // Sort the answers.
        sort(res.begin(), res.end());

        // Ta da!
        cout << res.size() << endl;
        cout << res[0];
        for (int i=1; i<res.size(); i++)
            cout << " " << res[i];
        cout << endl;
    }

    return 0;
}

// Return all solutions for s with starting number length len.
vector<int> solve(string s, int len) {

    vector<int> res;

    // Be safe!
    if (s.size() < len) return res;

    // Get current value.
    int cur = getnum(s, 0, len);
    int start = cur;
    int skip = -1;

    // Index into s.
    int idx = len;

    // Loop through string.
    while (idx < s.size()) {

        // What we expect the next number to be.
        int next = cur+1;
        int nextlen = numd(next);

        // This is bad.
        if (idx+nextlen > s.size()) return res;

        // Get the next number in s of length nextlen.
        int newn = getnum(s, idx, nextlen);

        // Great it's a match.
        if (newn == next) {
            idx += nextlen;
            cur = next;
        }

        // Also a match with a skip unless we previously skipped.
        else if (newn == next+1) {
            if (skip != -1) return res;
            idx += nextlen;
            cur = next+1;
            skip = next;
        }

        // If we skipped but the length is wrong, let's try that.
        else if (numd(next+1) != nextlen) {
            if (skip != -1) return res;

            // Let's try this.
            if (idx+nextlen+1 > s.size()) return res;
            newn = getnum(s, idx, nextlen+1);

            // It didn't work.
            if (newn != next+1) return res;

            // Okay we're good.
            skip = next;
            cur = next+1;
            idx += (nextlen+1);
        }

        // Also not good.
        else return res;
    }

    // Exactly 1 possibility.
    if (skip != -1) {
        res.push_back(skip);
    }

    // Be careful need to check both bounds before adding ends.
    else {
        if (cur+1<100000) res.push_back(cur+1);
        if (start > 1) res.push_back(start-1);
    }

    return res;
}

// Returns the number in s starting at index sI of length len.
int getnum(string s, int sI, int len) {
    int res = 0;
    for (int i=sI; i<sI+len; i++)
        res = 10*res + s[i]-'0';
    return res;
}

// Returns the number of digits in n.
int numd(int n) {
    int res = 0;
    while (n > 0) {
        n = n/10;
        res++;
    }
    return res;
}
