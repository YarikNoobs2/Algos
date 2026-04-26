#include <bits/stdc++.h>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC optimize("Ofast")

using namespace std;
//Вперёд обганять игоря
//Ура Центроиды. Надеюсь он прекратит решать задачи, чтобы можно было обойтись без геомы

struct Node {
    map<int, pair<int, int>> c;
};

vector<bool> chk;
vector<int> sz;
vector<Node> centroids;
vector<vector<pair<int, int>>> g;
vector<vector<pair<int, int>>> dist;

void sizes(int i, int p) {
    sz[i] = 1;
    for (auto j : g[i]) {
        if (j.first != p && !chk[j.first]) {
            sizes(j.first, i);
            sz[i] += sz[j.first];
        }
    }
}
int centroid(int i, int p, int n) {
    for (auto j : g[i]) {
        if (j.first != p && !chk[j.first] && sz[j.first] > n/2) {
            return centroid(j.first, i, n);
        }
    }
    return i;
}
void dfs(int i, int p, int d, int c) {
    dist[i].push_back({c, d});
    for (auto j : g[i]) {
        if (j.first == p || chk[j.first]) continue;
        dfs(j.first, i, d+j.second, c);
    }
}
void solve(int i) {
    sizes(i, -1);
    int c = centroid(i, -1, sz[i]);
    dfs(c, -1, 0, c);
    chk[c] = true;
    for (auto j : g[c]) {
        if (!chk[j.first]) {
            solve(j.first);
        }
    }
}
int get(int i) {
    int res = 0;
    int id = -1;
    for (auto j : dist[i]) {
        auto cur = centroids[j.first].c.lower_bound(j.second);
        if (cur != centroids[j.first].c.end()) {
            if (cur->second.second > id) {
                id = cur->second.second;
                res = cur->second.first;
            }
        }
    }
    return res;
}
int t = 0;
void doit(int i, int d, int c) {
    auto pos = centroids[i].c.upper_bound(d);
    centroids[i].c.erase(centroids[i].c.begin(), centroids[i].c.upper_bound(d));
    centroids[i].c.insert({d, {c, t++}});
}
void st(int i, int d, int c) {
    for (auto j : dist[i]) {
        int cur = d - j.second;
        if (cur >= 0) {
            doit(j.first, cur, c);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    g.resize(n);
    for (int i = 0; i < n-1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;b--;
        g[b].push_back({a, c});
        g[a].push_back({b, c});
    }
    chk.resize(n);
    sz.resize(n);
    centroids.resize(n);
    dist.resize(n);
    solve(0);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int a;
        cin >> a;
        if (a == 1) {
            int b, c, d;
            cin >> b >> c >> d;
            b--;
            st(b, c, d);
        }
        else {
            int b;
            cin >> b;
            b--;
            cout << get(b) << '\n';
        }
    }
    return 0;
}