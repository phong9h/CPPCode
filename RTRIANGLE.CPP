#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
#define max_n 1502
#define f(i, n) for (int i = 0; i<n; i++)
#define fi first
#define se second
#define INP "RTRIANGLE.INP"
#define OUT "RTRIANGLE.OUT"
ii a[max_n];
int n;

struct point {
    ll x, y, hist;
    point(ll p = 0, ll q = 0) {
        x = p;
        y = q;
    }
};
vector<point> vt;
typedef vector<point>::iterator vit;
typedef vector<point>::reverse_iterator vrit;

int cmp_coor(point a, point b) {
    if (a.x*b.y==a.y*b.x)
        return 2;
    if (a.x*b.y-a.y*b.x<0)
        return (a.y*b.y>0) ? 1 : 0;
    else
        return (a.y*b.y>0) ? 0 : 1;
}

void enter() {
    scanf("%d", &n);
    f(i, n) scanf("%lld%lld", &a[i].fi, &a[i].se);
}

ll bisect(point x) {
    int l = 0, h = vt.size()-1, mid = (l+h)/2;
    while (l!=mid && mid!=h) {
        if (cmp_coor(vt[mid], x)==1)
            l = mid;
        else if (cmp_coor(vt[mid], x)==0)
            h = mid;
        else
            return vt[mid].hist;
        mid = (l+h)/2;
    }
    for (int i = l; i<=h; i++)
        if (cmp_coor(vt[i], x)==2)
            return vt[i].hist;
    return 0;
}

void solve() {
    ll res = 0;
    f(i, n) {
        int p = 0, q = 0;
        vt.clear();
        f(j, n) {
            if (a[j].fi==a[i].fi)
                ++p;
            if (a[i].se==a[j].se)
                ++q;
            if (a[i].fi!=a[j].fi && a[i].se!=a[j].se)
                vt.push_back(point(a[j].fi-a[i].fi, a[j].se-a[i].se));
        }
        res += (p-1)*(q-1)*2;
        if (vt.empty())
            continue;
        sort(vt.begin(), vt.end(), cmp_coor);
        vt.begin()->hist = 1;
        for (vit it = vt.begin()+1; it!=vt.end(); it++)
            if (cmp_coor(*it, *(it-1))==2)
                it->hist = (it-1)->hist + 1;
            else
                it->hist = 1;
        for (vrit it = vt.rbegin()+1; it!=vt.rend(); it++)
            if (cmp_coor(*it, *(it-1))==2)
                it->hist = (it-1)->hist;
        for (vit it = vt.begin(); it!=vt.end(); it++) {
            point tmp(-1*it->y, it->x);
            res += bisect(tmp);
        }
    }
    printf("%lld", res/2);
}

int main() {
    freopen(INP, "r", stdin);
    freopen(OUT, "w", stdout);
    enter();
    solve();
}
