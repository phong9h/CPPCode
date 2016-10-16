#include <bits/stdc++.h>
using namespace std;

typedef vector<int> bignum;
const int BASE = 1e9;
#define FOR(i, n) for (int i = 0; i<n; i++)
#define max_n 202
#define max_m max_n/2 + 2
#define INP "input.in"
#define OUT "train.out"
int n, m, a[max_m];
bignum f[max_n][max_m];

void fix(bignum& a) {
    a.push_back(0);
    FOR(i, a.size()) {
        a[i+1] += a[i]/BASE;
        a[i] %= BASE;
    }
    while (a.back()==0 && a.size()>=2)
        a.pop_back();
}

istream& operator>>(istream& cin, bignum a) {
    string s;
    cin >> s;
    a.clear();
    a.resize(s.length()/10+1);
    FOR(i, s.length()) {
        int x = (s.length()-i-1)/10;
        a[x] = a[x]*10 + s[i] - '0';
    }
    fix(a);
    return cin;
}

ostream& operator<<(ostream& cout, bignum a) {
    printf("%d", a[a.size()-1]);
    for (int i = a.size()-2; i>=0; i--)
        printf("%010d", a[i]);
    return cout;
}

void operator+=(bignum& a, bignum b) {
    bignum res;
    a.resize(max(a.size(), b.size()));
    FOR(i, b.size())
        a[i] += b[i];
    fix(a);
}

int main() {
    freopen(INP, "r", stdin);
    //freopen(OUT, "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i<=m; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i<=n; i++) f[i][1].push_back(i/a[1]);
    for (int i = 1; i<=n; i++)
        for (int j = 2; j<=m; j++) {
        if (i<a[j])
            continue;
        for (int k = 1; k<i-a[j]; k++)
            f[i][j] += f[k][j-1];
    }
    cout << f[n][m];
}
