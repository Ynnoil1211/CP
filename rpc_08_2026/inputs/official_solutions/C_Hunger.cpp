// Arup Guha
// 3/10/2024
// Solution to 2023 NAQ Problem C: Don't Hunger Together

using namespace std;

#include <bits/stdc++.h>
typedef long long ll;

bool canDo(vector<ll>& food, vector<int>& endday, double f);

int main() {

    int n, numP;
    cin >> n >> numP;
    vector<ll> food(n);
    vector<int> endday(n);

    // Read in daily food.
    double totalf = 0;
    for (int i=0; i<n; i++) {
        cin >> food[i] >> endday[i];
        totalf += food[i];
    }

    // Run a binary search with 100 iterations.
    double low = 0, high = totalf/numP;
    for (int i=0; i<150; i++) {

        double mid = (low+high)/2;

        if (canDo(food, endday, mid*numP))
            low = mid;
        else
            high = mid;
    }

    // This is annoying, apparently without the setprecision 1e+9
    // outputs in a way that Kattis doesn't accept.
    if (fabs(low)>1e-9)
        cout << setprecision(10) << low << endl;
    else
        cout << -1 << endl;

    return 0;
}

// Returns true if everyone can get f food total a day amongst them.
bool canDo(vector<ll>& food, vector<int>& endday, double f) {

    // Fill in
    int n = food.size();

    // My priority queue. Since C++ does max queue, I'll do -days.
    priority_queue<pair<int,double>> pq;

    for (int i=0; i<n; i++) {

        if (food[i] > 0)
            pq.push({ -(endday[i]-1), food[i]});

        double today = f;

        // Pop off as needed.
        while (pq.size() > 0 && today > 1e-10) {

            pair<int,double> tmp = pq.top();

            // This food has gone bad.
            if (-tmp.first < i) {
                pq.pop();
                continue;
            }

            // We must consume all of this food.
            if (today >= tmp.second) {
                today -= tmp.second;
                pq.pop();
            }

            // We can just eat some of this food.
            else {
                double newf = tmp.second - today;
                int day = tmp.first;
                pq.pop();
                pq.push({day, newf});
                today = 0;
            }

        } // end while eating for today.

        // Oops we went hungry today.
        if (today > 1e-9) return false;
    }

    // If we make it here, we're good...
    return true;
}
