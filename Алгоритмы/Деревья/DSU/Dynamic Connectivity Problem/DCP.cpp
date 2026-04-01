#include <bits/stdc++.h>

using namespace std;



vector<int> up;
stack<pair<int, int>> st;

int res;

int p(int a) {
    return up[a] < 0 ? a : p(up[a]);
}
void unite(int a, int b) {
    a = p(a);
    b = p(b);
    if (a == b) {
        st.push({1, a});
        return;
    }
    res--;
    if (up[a] > up[b]) swap(a, b);
    st.push({up[b], b});
    up[a] += up[b];
    up[b] = a;
}
int back() {
    auto a = st.top();
    st.pop();
    if (a.first > 0) return a.second;
    up[up[a.second]] -= a.first;
    up[a.second] = a.first;
    res++;
    return a.second;
}
struct Node {
    vector<pair<int, int>> v;
};
vector<Node> tree;

void add(int i, int l, int r, int ql, int qr, pair<int, int> p) {
    if (r < ql || l > qr) return;
    if (ql <= l && r <= qr){
        tree[i].v.push_back(p);
        return;
    }
    int m = (l + r) / 2;
    add(i*2, l, m, ql, qr, p);
    add(i*2+1, m+1, r, ql, qr, p);
}

vector<bool> q;

void dfs(int i, int l, int r) {
    int sz = st.size();
    for (auto j : tree[i].v) {
        unite(j.first, j.second);
    }
    if (l == r) {
        if (q[l]) {
            cout << res << '\n';
        }
    }
    else {
        int m = (l + r) / 2;
        dfs(i*2, l, m);
        dfs(i*2+1, m+1, r);
    }
    while (st.size() > sz) {
        back();
    }

}


int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    res = n;
    up.assign(n, -1);
    tree.resize(4 * m);
    set<pair<pair<int, int>, int>> v;
    q.assign(m, false);
    for (int i = 0; i < m; i++) {
        char a;
        cin >> a;
        if (a == '+') {
            int b, c;
            cin >> b >> c;
            if (b > c) swap(b, c);
            v.insert({{b, c}, i});
        }
        if (a == '-') {
            int b, c;
            cin >> b >> c;
            if (b > c) swap(b, c);
            auto d = v.lower_bound({{b, c}, 0});
            add(1, 0, m-1, d->second, i-1, d->first);
            v.erase(d);
        }
        if (a == '?') {
            q[i] = true;
        }
    }
    for (auto &e : v) {
        add(1, 0, m-1, e.second, m-1, e.first);
    }
    dfs(1, 0, m-1);
}