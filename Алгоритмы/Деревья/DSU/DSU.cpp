#include <bits/stdc++.h>

using namespace std;



vector<int> up;

int p(int a) {
    return up[a] < 0 ? a : up[a] = p(up[a]);
}
void unite(int a, int b) {
    a = p(a);
    b = p(b);
    if (up[a] > up[b]) swap(a, b);
    up[a] += up[b];
    up[b] = a;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    long long n, m;
    cin >> n >> m;
    up.assign(n, -1);
    for (int i = 0; i < m; i++) {
        char a;
        cin >> a;
        if (a == '+') {
            int b, c;
            cin >> b >> c;
            unite(b, c);
            cout << -up[p(b)] << endl;
        }
        if (a == '?') {
            int b;
            cin >> b;
            cout << -up[p(b)] << endl;
        }
    }
}