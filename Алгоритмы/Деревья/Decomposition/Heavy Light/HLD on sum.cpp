#include <bits/stdc++.h>
using namespace std;
int n;
struct gc {
    vector<int> v;
    int s;
};
struct Node {
    int sum;
};
vector<vector<int>> gs;
vector<int> tin;
vector<int> tout;
vector<int> p;
vector<Node> st;
vector<gc> g;
void sets(int i, int l, int r, int x, int p) {
    if (l == r) {
        st[i].sum = x;
        return;
    }
    int m = (l + r) / 2;
    if (p <= m) {
        sets(i*2, l, m, x, p);
    }
    else {
        sets(i*2+1, m + 1, r, x, p);
    }
    st[i].sum = st[i*2].sum + st[i*2+1].sum;
}
long long get(int i, int l, int r, int ql, int qr) {
    if (ql > r || l > qr) {
        return 0;
    }
    if (l >= ql && r <= qr) {
        return st[i].sum;
    }
    int m = (l + r) / 2;
    long long a = get(i*2, l, m, ql, qr);
    long long b = get(i*2+1, m + 1, r, ql, qr);
    return a + b;
}
vector<bool> chk;
void dfs(int i) {
    chk[i] = true;
    for (int l : gs[i]) {
        if (chk[l]) continue;
        g[i].v.push_back(l);
        dfs(l);
    }
}
bool ancestor(int a, int b) {
    return tin[a] <= tin[b] && tin[b] < tout[a];
}
vector<int> s;
vector<int> h;
int t = 0;
void sizes(int i = 0) {
    s[i] = 1;
    for (int &l : g[i].v) {
        sizes(l);
        s[i] += s[l];
        if (s[l] > s[g[i].v[0]]) {
            swap(l, g[i].v[0]);
        }
    }
}
void hld(int i) {
    tin[i] = t++;
    for (int l : g[i].v) {
        p[l] = i;
        h[l] = (l == g[i].v[0] ? h[i] : l);
        hld(l);
    }
    tout[i] = t;
}

void upd(int v, int x) {
    sets(1, 0, n-1, x, tin[v]);
}
void up(int &a, int &b, long long &res) {
    while (!ancestor(h[a], b)) {
        res += get(1, 0, n-1, tin[h[a]], tin[a]);
        a = p[h[a]];
    }
}
long long gets(int a, int b) {
    long long res = 0;
    up(a, b, res);
    up(b, a, res);
    if (!ancestor(a, b)) {
        swap(a, b);
    }
    res += get(1, 0, n-1, tin[a], tin[b]);
    return res;
}

int main() {
    //cin.tie(0);
    //ios_base::sync_with_stdio(0);
    cin >> n;
    tin.assign(n, 0);
    tout.assign(n, 0);
    st.assign(4*n, Node());
    g.assign(n, {});
    gs.assign(n, {});
    p.assign(n, 0);
    chk.assign(n, false);
    s.assign(n, 0);
    h.assign(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> g[i].s;
    }
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        gs[a].push_back(b);
        gs[b].push_back(a);
    }
    dfs(0);
    sizes(0);
    hld(0);
    for (int i = 0; i < n; i++) {
        upd(i, g[i].s);
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        char c;
        int a, b;
        cin >> c >> a >> b;
        if (c == '!') {
            a--;
            upd(a, b);
        }
        else if (c == '?') {
            a--; b--;
            cout << gets(a, b) << '\n';
        }
    }
    return 0;
}
