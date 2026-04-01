#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> v;
vector<bool> chk;
vector<int> res;
vector<int> s;
int sz(int i, int p) {
    s[i] = 1;
    for (int j : v[i]) {
        if (j == p || chk[j]) continue;
        s[i] += sz(j, i);
    }
    return s[i];
}
int centroid(int i, int p, int n) {
    for (int j : v[i]) {
        if (j != p and s[j] > n/2 and !chk[j]) {
            return centroid(j, i, n);
        }
    }
    return i;
}
void solve(int i) {
    sz(i, -1);
    if (s[i] == 1) return;
    chk[i] = true;
    for (int j : v[i]) {
        if (chk[j]) continue;
        int cur = centroid(j, i, s[j]);
        res[cur] = i + 1;
        solve(cur);
    }
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    v.resize(n);
    chk.assign(n, false);
    s.assign(n, 1);
    res.assign(n, 0);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        v[b].push_back(a);
        v[a].push_back(b);
    }
    sz(0, -1);
    solve(centroid(0, -1, n));
    for (int i : res) {
        cout << i << ' ';
    }
}