#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
#define max_n 1502
#define x first
#define y second
#define INP "cake.inp"
#define OUT "cake.out"
ii v[max_n];
int n;

void enter() {
    memset(v, 0, sizeof(v));
    scanf("%d", &n);
    for (int i = 1; i<=n; i++)
        scanf("%lld%lld", &v[i].x, &v[i].y);
}

double distnce(int a, int b, int c, ii p) {
    return abs((a*p.x+b*p.y+c)/sqrt(a*a+b*b));
}

ll QuadArea(ii a, ii b, ii c, ii d) {
    ll res = (a.x-b.x)*(a.y+b.y)+(b.x-c.x)*(b.y+c.y)
            +(c.x-d.x)*(c.y+d.y)+(d.x-a.x)*(d.y+a.y);
    return abs(res);
}

int bisect(int l, int h, ll a, ll b, ll c) {
    int mid = (l+h)/2;
    do {
        double d = distnce(a, b, c, v[mid]);
        double d1 = distnce(a, b, c, v[mid-1]);
        double d2 = distnce(a, b, c, v[mid+1]);
        if (d>d1 && d>d2)
            return mid;
        else if (d1<=d && d<=d2)
            l = mid;
        else if (d2<=d && d<=d1)
            h = mid;
        mid = (l+h)/2;
    } while (l!=mid && mid!=h);
    ll res;
    double dist = 0;
    for (int i =l; i<=h; i++)
        if (distnce(a, b, c, v[i])>dist) {
            res = i;
            dist = distnce(a, b, c, v[i]);
        }
    return res;
}

void solve() {
    ll res = 0;
    for (int i = 1; i<=n; i++)
        for (int j = i+2; j<=n; j++) {
            ll a = v[i].y - v[j].y;
            ll b = v[j].x - v[i].x;
            ll c = v[i].x*v[j].y - v[i].y*v[j].x;
            int k = bisect(i+1, j-1, a, b, c);
            int h = bisect(j,n,a,b,c);
            h = max(h, bisect(1,i,a,b,c));
            if (QuadArea(v[i], v[k], v[j], v[h])>res)
                res = QuadArea(v[i], v[k], v[j], v[h]);
        }
    cout << setiosflags(ios::fixed) << setprecision(1) << double(res)/2;
}

int main() {
    freopen(INP, "r", stdin);
    enter();
    solve();
}
