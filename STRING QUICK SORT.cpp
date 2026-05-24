#include <iostream>
#include <stack>
#include <deque>
#include <random>
#include <map>
#include <cmath>
#include <numeric>
#include <queue>
#include <set>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <chrono>
#include <tuple>

using namespace std;
#define all(a) a.begin(), a.end()
#define pb push_back
#define get(v) for (int & iq : v) cin >> iq
#define give(vv) for (int & iqq : vv) cout << iqq << " "
#define vi vector <int>
#define pii pair <int, int>
#define SOLVE int t; cin >> t; while (t--) {solve();}
typedef __int128 lll;
typedef long long ll;
typedef long double ld;
#define int ll
ll inf = 1e9 + 7, mod = 1e6 + 3;
int N = 1e6;

int getChar(const string & s, int d) {
    if (d >= (int)s.size()) return -1;
    return (unsigned char)s[d];
}

void stringQuickSort(vector <string> & a, int l, int r, int d) {
    if (l >= r) return;

    int lt = l;
    int gt = r;

    int v = getChar(a[l], d);
    int i = l + 1;

    while (i <= gt) {
        int cur = getChar(a[i], d);

        if (cur < v) {
            swap(a[lt], a[i]);
            lt++;
            i++;
        } else if (cur > v) {
            swap(a[i], a[gt]);
            gt--;
        } else {
            i++;
        }
    }

    stringQuickSort(a, l, lt - 1, d);

    if (v != -1) {
        stringQuickSort(a, lt, gt, d + 1);
    }

    stringQuickSort(a, gt + 1, r, d);
}

signed main() {
#ifdef _LOCAL
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string tmp;
    getline(cin, tmp);

    vector <string> a(n);

    for (int i = 0; i < n; i++) {
        getline(cin, a[i]);
    }

    if (n > 0) {
        stringQuickSort(a, 0, n - 1, 0);
    }

    for (int i = 0; i < n; i++) {
        cout << a[i] << '\n';
    }

    return 0;
}