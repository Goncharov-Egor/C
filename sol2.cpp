//https://codeforces.com/problemset/problem/522/D?locale=ru
#include <iostream>
#include <fstream>
#include <cstring>
#include <set>
#include <map>
#include <list>
#include <queue>
#include <stack>
#include <bitset>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <assert.h>
using namespace std;

void smain();
int main(){
    ios_base::sync_with_stdio(0);
#ifdef TASK
    freopen(TASK".in","rt",stdin);
    //freopen("output.txt","rt",stdin);
    const clock_t start = clock();
#endif
    smain();
#ifdef TASK
    cerr << "\nTotal Execution Time: " << float( clock () - start ) /  CLOCKS_PER_SEC << endl;
#endif
    return 0;
}

#define forn(i,n) for (int i=0;i<n;i++)
#define rforn(i,n) for (int i=n-1;i>=0;i--)
#define fori(i,a) for(auto i=a.begin(); i!=a.end(); ++i)
#define rfori(i,a) for(auto i=a.rbegin(); i!=a.rend(); ++i)
#define int long long
#define LL long long
#define mp(a,b) make_pair(a,b)
#define INF 2000000000//2305843009213693951LL
#define MOD 1000000007
#define EPS 1E-9
#define N 500005
/* --------- END TEMPLATE CODE --------- */

int n, m;
int a[N], b[N];

int st[N][20];

inline int lg2(int x){
    int lg = 0;
    for(; (1LL << lg) <= x; lg += 1);
    return lg - 1;
}

int query(int ql, int qr){
    if(b[qr] < ql) return -1;
    int l = ql, r = qr;
    while(l < r){
        int mid = (l + r) / 2;
        if(b[mid] >= ql) r = mid;
        else l = mid + 1;
    }
    ql = l;
    int lg = lg2(qr - ql + 1);
    return min(st[ql][lg], st[qr+1-(1<<lg)][lg]);
}

void smain() {
    for(int t=0; cin >> n >> m; ++t){
        forn(i, n) cin >> a[i];
        map<int, int> q;
        forn(i, n) {
            b[i] = q.count(a[i]) ? q.at(a[i]) : -1;
            q[a[i]] = i;
        }
        forn(i, n) b[i] = i ? max(b[i], b[i-1]) : -1;
        int lg = 0;
        for(; (1LL << lg) < n; lg += 1);
        forn(i, lg + 1){
            if(i > 0) forn(l, n) st[l][i] = min(st[l][i-1], st[min(l+(1LL<<(i-1)), n-1)][i-1]);
            else forn(l, n) st[l][i] = b[l] < 0 ? INF : l - b[l];
        }

        forn(i, m){
            int l, r;
            cin >> l >> r;
            l -= 1, r -= 1;
            cout << query(l, r) << '\n';
        }
  
