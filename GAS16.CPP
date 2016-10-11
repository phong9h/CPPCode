#include <bits/stdc++.h>
using namespace std;

#define max_n 207
int parent[max_n], m = 0, res = 0, k, n;
struct edge {
    int u, v, w;
    edge(int x, int y, int c) {
        u = x;
        v = y;
        w = c;
    }
};
struct node {
    int x, y, c;
    node(int u = 0, int v = 0, int w = 0) {
        x = u;
        y = v;
        c = w;
    }
};
node a[max_n];
vector<edge> e;
typedef vector<edge>::iterator vit;

bool cmp(edge a, edge b) {
    return a.w<b.w;
}

void enter() {
    int x, y, c;
    scanf("%d%d", &k, &n);
    for (int i = 1; i<=k; i++) {
        scanf("%d%d%d", &x, &y, &c);
        a[i] = node(x, y, c);
    }
    for (int i = k+1; i<=n+k; i++) {
        scanf("%d%d", &x, &y);
        a[i] = node(x, y, 0);
    }
}

int dist(node a, node b) {
    return abs(a.x-b.x) + abs(a.y-b.y);
}

void init() {
    for (int i = 1; i<=k; i++)
        for (int j = k+1; j<=n+k; j++)
            e.push_back(edge(i, j, dist(a[i], a[j])));
    for (int i = k+1; i<=n+k; i++)
        for (int j = k+1; j<i; j++)
            e.push_back(edge(i, j, dist(a[i], a[j])));
    for (int i = 1; i<=k; i++)
        for (int j = 1; j<i; j++)
            e.push_back(edge(i, j, 0));
    int q = n+k;
    for (int i = 1; i<=k; i++)
        e.push_back(edge(i, ++q, a[i].c));
    for (int i = n+k+1; i<=q; i++)
        for (int j = n+k+1; j<i; j++)
            e.push_back(edge(i, j, 0));
    memset(parent, 0, sizeof(parent));
}

int findset(int u) {
    return (parent[u]<=0) ? u : findset(parent[u]);
}

void uni(int s, int t) {
    if (parent[s]<parent[t])
        parent[t] = s;
    else if (parent[s]>parent[t])
        parent[s] = t;
    else {
        parent[s] = t;
        parent[t]--;
    }
}

void process(edge e) {
    int s = findset(e.u);
    int t = findset(e.v);
    if (s!=t) {
        uni(s, t);
        ++m;
        res += e.w;
    }
}

void solve() {
    sort(e.begin(), e.end(), cmp);
    for (vit it = e.begin(); it!=e.end() && m<n+2*k-1; it++)
        process(*it);
    printf("%d", res);
}

int main() {
    enter();
    init();
    solve();
}
