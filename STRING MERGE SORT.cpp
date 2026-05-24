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

int lcpCompare(const string & a, const string & b, int pos = 0) {
    int n = min((int)a.size(), (int)b.size());

    for (int i = pos; i < n; i++) {
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return 1;
    }

    if ((int)a.size() < (int)b.size()) return -1;
    if ((int)a.size() > (int)b.size()) return 1;
    return 0;
}

void mergeSort(vector <string> & a, int l, int r) {
    if (r - l <= 1) return;

    int m = (l + r) / 2;

    mergeSort(a, l, m);
    mergeSort(a, m, r);

    vector <string> b;
    int i = l;
    int j = m;

    while (i < m || j < r) {
        if (j == r) {
            b.pb(a[i]);
            i++;
        } else if (i == m) {
            b.pb(a[j]);
            j++;
        } else {
            if (lcpCompare(a[i], a[j]) <= 0) {
                b.pb(a[i]);
                i++;
            } else {
                b.pb(a[j]);
                j++;
            }
        }
    }

    for (int k = 0; k < (int)b.size(); k++) {
        a[l + k] = b[k];
    }
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

    mergeSort(a, 0, n);

    for (int i = 0; i < n; i++) {
        cout << a[i] << '\n';
    }

    return 0;
}