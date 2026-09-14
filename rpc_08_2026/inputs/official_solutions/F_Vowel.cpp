// Arup Guha
// 1/27/2024
// Solution to 2023 NAQ Problem F: Is Y a Vowel?

using namespace std;

#include <bits/stdc++.h>

int main() {

    // Read in the string.
    string s;
	cin >> s;
    int f[26];
    for (int i=0; i<26; i++) f[i] = 0;

    // Update charscter frewuencies.
    for (int i=0; i<s.length(); i++)
        f[s[i]-'a']++;

    // vowels.
    int regv = f[0] + f[4] + f[8] + f[14] + f[20];

    // Add y to the vowels.
    int y = regv + f[24];

    // Ta da!
    cout << regv << " " << y << endl;

	return 0;
}
