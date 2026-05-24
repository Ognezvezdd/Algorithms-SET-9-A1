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

struct Answer {
    int time;
    int comparisons;
};

class StringGenerator {
public:
    string chars;
    mt19937 rnd;

    StringGenerator() {
        chars = "";

        for (char c = 'A'; c <= 'Z'; c++) chars += c;
        for (char c = 'a'; c <= 'z'; c++) chars += c;
        for (char c = '0'; c <= '9'; c++) chars += c;

        chars += "!@#%:^&*()-_";

        rnd.seed(chrono::steady_clock::now().time_since_epoch().count());
    }

    string getString(int len) {
        string s = "";

        for (int i = 0; i < len; i++) {
            s += chars[rnd() % chars.size()];
        }

        return s;
    }

    vector <string> getRandomArray(int n) {
        vector <string> a;

        for (int i = 0; i < n; i++) {
            int len = 10 + rnd() % 191;
            a.pb(getString(len));
        }

        return a;
    }

    vector <string> getReverseArray(int n) {
        vector <string> a = getRandomArray(n);

        sort(all(a));
        reverse(all(a));

        return a;
    }

    vector <string> getAlmostArray(int n) {
        vector <string> a = getRandomArray(n);

        sort(all(a));

        int cnt = max((int)1, n / 20);

        for (int i = 0; i < cnt; i++) {
            int x = rnd() % n;
            int y = rnd() % n;
            swap(a[x], a[y]);
        }

        return a;
    }

    vector <string> getPrefixArray(int n) {
        vector <string> a;

        string pref = getString(20);

        for (int i = 0; i < n; i++) {
            int len = 10 + rnd() % 191;
            string s = pref;

            while ((int)s.size() < len) {
                s += chars[rnd() % chars.size()];
            }

            if ((int)s.size() > len) {
                s.resize(len);
            }

            a.pb(s);
        }

        return a;
    }
};

class StringSortTester {
public:
    int comparisons = 0;

    int getChar(const string & s, int d) {
        if (d >= (int)s.size()) return -1;
        return (unsigned char)s[d];
    }

    bool lessString(const string & a, const string & b) {
        int n = min((int)a.size(), (int)b.size());

        for (int i = 0; i < n; i++) {
            comparisons++;

            if (a[i] < b[i]) return true;
            if (a[i] > b[i]) return false;
        }

        comparisons++;

        return (int)a.size() < (int)b.size();
    }

    int lcp(const string & a, const string & b) {
        int n = min((int)a.size(), (int)b.size());
        int res = 0;

        while (res < n) {
            comparisons++;

            if (a[res] != b[res]) break;

            res++;
        }

        return res;
    }

    bool lessFrom(const string & a, const string & b, int pos) {
        int n = min((int)a.size(), (int)b.size());

        for (int i = pos; i < n; i++) {
            comparisons++;

            if (a[i] < b[i]) return true;
            if (a[i] > b[i]) return false;
        }

        comparisons++;

        return (int)a.size() < (int)b.size();
    }

    void quickSort(vector <string> & a, int l, int r) {
        if (l >= r) return;

        string x = a[(l + r) / 2];

        int i = l;
        int j = r;

        while (i <= j) {
            while (lessString(a[i], x)) i++;
            while (lessString(x, a[j])) j--;

            if (i <= j) {
                swap(a[i], a[j]);
                i++;
                j--;
            }
        }

        if (l < j) quickSort(a, l, j);
        if (i < r) quickSort(a, i, r);
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
                b.pb(a[i++]);
            } else if (i == m) {
                b.pb(a[j++]);
            } else if (lessString(a[i], a[j])) {
                b.pb(a[i++]);
            } else {
                b.pb(a[j++]);
            }
        }

        for (int k = 0; k < (int)b.size(); k++) {
            a[l + k] = b[k];
        }
    }

    void stringQuickSort(vector <string> & a, int l, int r, int d) {
        if (l >= r) return;

        int lt = l;
        int gt = r;

        int v = getChar(a[l], d);
        int i = l + 1;

        while (i <= gt) {
            int cur = getChar(a[i], d);

            comparisons++;

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

    void stringMergeSort(vector <string> & a, int l, int r) {
        if (r - l <= 1) return;

        int m = (l + r) / 2;

        stringMergeSort(a, l, m);
        stringMergeSort(a, m, r);

        vector <string> b;

        int i = l;
        int j = m;

        while (i < m || j < r) {
            if (j == r) {
                b.pb(a[i++]);
            } else if (i == m) {
                b.pb(a[j++]);
            } else {
                int p = lcp(a[i], a[j]);

                if (lessFrom(a[i], a[j], p)) {
                    b.pb(a[i++]);
                } else {
                    b.pb(a[j++]);
                }
            }
        }

        for (int k = 0; k < (int)b.size(); k++) {
            a[l + k] = b[k];
        }
    }

    void msdRadixSort(vector <string> & a, int l, int r, int d) {
        if (r - l <= 1) return;

        const int R = 256;

        vector <int> cnt(R + 2, 0);

        for (int i = l; i < r; i++) {
            int c = getChar(a[i], d) + 1;
            cnt[c + 1]++;
        }

        for (int i = 1; i < R + 2; i++) {
            cnt[i] += cnt[i - 1];
        }

        vector <int> start = cnt;
        vector <string> b(r - l);

        for (int i = l; i < r; i++) {
            int c = getChar(a[i], d) + 1;
            b[cnt[c]] = a[i];
            cnt[c]++;
        }

        for (int i = 0; i < r - l; i++) {
            a[l + i] = b[i];
        }

        for (int c = 1; c <= R; c++) {
            int L = l + start[c];
            int Rr = l + start[c + 1];

            if (Rr - L > 1) {
                msdRadixSort(a, L, Rr, d + 1);
            }
        }
    }

    void msdRadixQuickSort(vector <string> & a, int l, int r, int d) {
        if (r - l <= 1) return;

        const int ALPHA = 74;

        if (r - l < ALPHA) {
            stringQuickSort(a, l, r - 1, d);
            return;
        }

        const int R = 256;

        vector <int> cnt(R + 2, 0);

        for (int i = l; i < r; i++) {
            int c = getChar(a[i], d) + 1;
            cnt[c + 1]++;
        }

        for (int i = 1; i < R + 2; i++) {
            cnt[i] += cnt[i - 1];
        }

        vector <int> start = cnt;
        vector <string> b(r - l);

        for (int i = l; i < r; i++) {
            int c = getChar(a[i], d) + 1;
            b[cnt[c]] = a[i];
            cnt[c]++;
        }

        for (int i = 0; i < r - l; i++) {
            a[l + i] = b[i];
        }

        for (int c = 1; c <= R; c++) {
            int L = l + start[c];
            int Rr = l + start[c + 1];

            if (Rr - L > 1) {
                msdRadixQuickSort(a, L, Rr, d + 1);
            }
        }
    }

    Answer runQuick(vector <string> a) {
        comparisons = 0;

        auto st = chrono::high_resolution_clock::now();

        if (!a.empty()) {
            quickSort(a, 0, (int)a.size() - 1);
        }

        auto fn = chrono::high_resolution_clock::now();

        return {
            chrono::duration_cast <chrono::microseconds> (fn - st).count(),
            comparisons
        };
    }

    Answer runMerge(vector <string> a) {
        comparisons = 0;

        auto st = chrono::high_resolution_clock::now();

        mergeSort(a, 0, (int)a.size());

        auto fn = chrono::high_resolution_clock::now();

        return {
            chrono::duration_cast <chrono::microseconds> (fn - st).count(),
            comparisons
        };
    }

    Answer runStringQuick(vector <string> a) {
        comparisons = 0;

        auto st = chrono::high_resolution_clock::now();

        if (!a.empty()) {
            stringQuickSort(a, 0, (int)a.size() - 1, 0);
        }

        auto fn = chrono::high_resolution_clock::now();

        return {
            chrono::duration_cast <chrono::microseconds> (fn - st).count(),
            comparisons
        };
    }

    Answer runStringMerge(vector <string> a) {
        comparisons = 0;

        auto st = chrono::high_resolution_clock::now();

        stringMergeSort(a, 0, (int)a.size());

        auto fn = chrono::high_resolution_clock::now();

        return {
            chrono::duration_cast <chrono::microseconds> (fn - st).count(),
            comparisons
        };
    }

    Answer runMSD(vector <string> a) {
        comparisons = 0;

        auto st = chrono::high_resolution_clock::now();

        msdRadixSort(a, 0, (int)a.size(), 0);

        auto fn = chrono::high_resolution_clock::now();

        return {
            chrono::duration_cast <chrono::microseconds> (fn - st).count(),
            comparisons
        };
    }

    Answer runMSDQuick(vector <string> a) {
        comparisons = 0;

        auto st = chrono::high_resolution_clock::now();

        msdRadixQuickSort(a, 0, (int)a.size(), 0);

        auto fn = chrono::high_resolution_clock::now();

        return {
            chrono::duration_cast <chrono::microseconds> (fn - st).count(),
            comparisons
        };
    }
};

void printLine(string type, int n, string algorithm, int time, int comparisons) {
    cout << type << ";";
    cout << n << ";";
    cout << algorithm << ";";
    cout << time << ";";
    cout << comparisons << '\n';
}

Answer avg(vector <Answer> v) {
    int t = 0;
    int c = 0;

    for (auto x : v) {
        t += x.time;
        c += x.comparisons;
    }

    t /= (int)v.size();
    c /= (int)v.size();

    return {t, c};
}

signed main() {
#ifdef _LOCAL
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    StringGenerator gen;
    StringSortTester tester;

    const int REPEATS = 5;

    cout << "type;n;algorithm;time_microseconds;char_comparisons\n";

    for (int n = 100; n <= 3000; n += 100) {
        vector <pair <string, vector <string> > > tests;

        tests.pb({"random", gen.getRandomArray(n)});
        tests.pb({"reverse", gen.getReverseArray(n)});
        tests.pb({"almost", gen.getAlmostArray(n)});
        tests.pb({"prefix", gen.getPrefixArray(n)});

        for (auto test : tests) {
            string type = test.first;
            vector <string> a = test.second;

            vector <Answer> q;
            vector <Answer> m;
            vector <Answer> sq;
            vector <Answer> sm;
            vector <Answer> msd;
            vector <Answer> msdq;

            for (int rep = 0; rep < REPEATS; rep++) {
                q.pb(tester.runQuick(a));
                m.pb(tester.runMerge(a));
                sq.pb(tester.runStringQuick(a));
                sm.pb(tester.runStringMerge(a));
                msd.pb(tester.runMSD(a));
                msdq.pb(tester.runMSDQuick(a));
            }

            Answer res;

            res = avg(q);
            printLine(type, n, "QUICKSORT", res.time, res.comparisons);

            res = avg(m);
            printLine(type, n, "MERGESORT", res.time, res.comparisons);

            res = avg(sq);
            printLine(type, n, "STRING_QUICK_SORT", res.time, res.comparisons);

            res = avg(sm);
            printLine(type, n, "STRING_MERGE_SORT", res.time, res.comparisons);

            res = avg(msd);
            printLine(type, n, "MSD_RADIX_SORT", res.time, res.comparisons);

            res = avg(msdq);
            printLine(type, n, "MSD_RADIX_QUICK_SORT", res.time, res.comparisons);
        }
    }

    return 0;
}