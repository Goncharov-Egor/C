// http://codeforces.com/problemset/problem/292/E?locale=ru
#include <string>
#include <vector>
#include <map>
#include <list>
#include <iterator>
#include <set>
#include <queue>
#include <iostream>
#include <sstream>
#include <stack>
#include <deque>
#include <cmath>
#include <memory.h>
#include <cstdlib>
#include <iomanip>
#include <cstdio>
#include <unordered_map>
#include <cctype>
#include <algorithm>
#include <utility>
#include <assert.h>
#include <time.h>
#define sz(s) ((int)s.size())
#define int long long
#define fs first
#define sc second
#define forn(i, k, n) for(int i = k; i < (int)n; ++i)
#define forc(i, k, n) for(int i = k - 1; i >= (int)n; --i)
#define pb push_back
#define mp make_pair
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<bool> vb;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef long long ll;
//#define FILE
//#define TIME
#define FAST
struct tree {
    int x;
    int dx;
    ll y;
    int sz;
    tree *l, *r;

    tree() {x = dx = 0, y = rand(), sz = 1, l = r = NULL;}
};

int _sz(tree *t) {
    if (t == NULL)
        return 0;
    return t->sz;
}

void upd(tree *t) {
    if (t == NULL)
        return;
    if (t->dx != 0) {
        t->x = max(t->x, t->dx);
        if (t->l != NULL)
            t->l->dx = t->dx;
        if (t->r != NULL)
            t->r->dx = t->dx;
        t->dx = 0;
    }
}

void upd2(tree *&t) {
    if (t == NULL)
        return;
    t->sz = 1 + _sz(t->l) + _sz(t->r);
}

void split(tree *t, tree *&l, tree *&r, int k) {
    if (t == NULL) {
        l = r = NULL;
        return;
    }
    upd(t);
    if (_sz(t->l) < k) {
        l = t;
        split(t->r, l->r, r, k - _sz(t->l) - 1);
    } else {
        r = t;
        split(t->l, l, r->l, k);
    }
    upd2(l);
    upd2(r);
}

void merge(tree *&t, tree *l, tree *r) {
    upd(l);
    upd(r);
    if (l == NULL) {
        t = r;
        return;
    }
    if (r == NULL) {
        t = l;
        return;
    }
    if (l->y > r->y) {
        t = l;
        merge(t->r, l->r, r);
    } else {
        t = r;
        merge(t->l, l, r->l);
    }
    upd2(t);
}

tree mem[1000010];
int mk = 0;

tree *get_new() {
    mem[mk] = tree();
    return &mem[mk++];
}

tree *root = NULL;

int n, m;
int a[200010];
int x[100010];
int y[100010];
int k[100010];

void _set(int l, int r, int x) {
    tree *L, *R, *M;
    split(root, L, R, r);
    split(L, L, M, l - 1);
    upd(M);
    M->dx = x;
    upd(M);
    merge(L, L, M);
    merge(root, L, R);
}

int find_num(int p) {
    tree *L, *R, *M;
    split(root, L, R, p);
    split(L, L, M, p - 1);
    upd(M);
    int res = M->x;
    merge(L, L, M);
    merge(root, L, R);
    return res;
}

int32_t main() {
#ifdef FAST
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
#ifdef FILE
    freopen("s.in", "r", stdin);
    freopen("s.out", "w", stdout);
#endif
	srand(time(NULL));
    cin >> n >> m;
    forn(i, 0, 2 * n)
        cin >> a[i];
    forn(i, 0, n) {
        tree *tmp = get_new();
        merge(root, root, tmp);
    }

    forn(i, 1, m + 1) {
        int t;
        cin >> t;
        if (t == 1) {
        	cin >> x[i] >> y[i] >> k[i];
            _set(y[i], y[i] + k[i] - 1, i);
        } else {
            int pos;
            cin >> pos;
            int num = find_num(pos);
            if (num == 0)
            	cout << a[n - 1 + pos] << endl;
            else
            	cout << a[x[num] + pos - y[num] - 1] << endl;
        }
    }
#ifdef TIME
    cout << endl;
    cout << fixed << setprecision(3) << (double) clock() / CLOCKS_PER_SEC << endl;
#endif
    return 0;
}
