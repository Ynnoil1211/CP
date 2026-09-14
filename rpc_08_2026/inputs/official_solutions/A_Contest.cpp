// Arup Guha
// 1/27/2024
// Solution to 2023 NAQ Problem A: Contest Advancement

using namespace std;

#include <bits/stdc++.h>

int main() {

	int n, k, c;
	cin >> n >> k >> c;

	vector<int> team(n);
	vector<int> school(n);

	vector<bool> used(n);
	for (int i=0; i<n; i++) used[i] = false;
	vector<int> freq(n);
	for (int i=0; i<n; i++) freq[i] = 0;

	// Read in teams 0 based.
	for (int i=0; i<n; i++) {
		cin >> team[i] >> school[i];
        team[i]--;
        school[i]--;
	}

	int cnt = 0;

	// First pass.
	for (int i=0; i<n; i++) {

        // Got all teams.
		if (cnt == k) break;

		// Add 1 to this school's count.
		freq[school[i]]++;

		// They qualify...
		if (freq[school[i]] <= c) {
			used[i] = true;
			cnt++;
		}
	}

	// We have to pick up more teams.
	if (cnt < k) {
		for (int i=0; i<n; i++) {
			if (used[i]) continue;
			cnt++;
			used[i] = true;
			if (cnt == k) break;
		}
	}

	// Now, output in order of finish.
	for (int i=0; i<n; i++)
        if (used[i])
            cout << team[i]+1 << endl;

	return 0;
}
