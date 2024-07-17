#include <bits/stdc++.h>

using namespace std;

#define fixed(n) fixed << setprecision(n)
#define ceil(n, m) (((n) + (m) - 1) / (m))
#define add_mod(a, b, m) (((a % m) + (b % m)) % m)
#define sub_mod(a, b, m) (((a % m) - (b % m) + m) % m)
#define mul_mod(a, b, m) (((a % m) * (b % m)) % m)
#define all(vec) vec.begin(), vec.end()
#define rall(vec) vec.rbegin(), vec.rend()
#define sz(x) int(x.size())
#define debug(x) cout << #x << ": " << (x) << "\n";
#define fi first
#define se second
#define ll long long
#define ull unsigned long long
#define EPS 1e-9
constexpr int INF = 1 << 30, Mod = 1e9 + 7;
constexpr ll LINF = 1LL << 62;
#define PI acos(-1)
template < typename T = int > using Pair = pair < T, T >;
vector < string > RET = {"NO", "YES"};

template < typename T = int > istream& operator >> (istream &in, vector < T > &v) {
    for (auto &x : v) in >> x;
    return in;
}

template < typename T = int > ostream& operator << (ostream &out, const vector < T > &v) { 
    for (const T &x : v) out << x << ' '; 
    return out;
}

template < typename T = long long , int Base = 0 > struct Hash {
    mt19937 rng;
    int n;
    vector < T > pow1, pow2, h1, h2;
    static constexpr array < T, 6 > powers = {307, 509, 1009, 2003, 3001, 4001};
    static constexpr array < T, 6 > mods = {1000000007, 1000000009, 1000000021, 1000000033, 1000000087, 1000000093};
    static T p1, p2;
    static T m1, m2;
 
    Hash() : rng(chrono::steady_clock::now().time_since_epoch().count()) {
        initialize_static();
    }
 
    Hash(const string &s) : rng(chrono::steady_clock::now().time_since_epoch().count()) {
        initialize_static();
        initialize(s.size());
        calculate_powers();
        calculate_hashes(s);
    }
 
    Hash(const vector < T > &vec) : rng(chrono::steady_clock::now().time_since_epoch().count()) {
        initialize_static();
        initialize(vec.size());
        calculate_powers();
        calculate_hashes(vec);
    }
 
    static void initialize_static() {
        static once_flag flag;
        static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        call_once(flag, []() {
            uniform_int_distribution<int> dist(0, 5);
            p1 = powers[dist(rng)];
            p2 = powers[dist(rng)];
            m1 = mods[dist(rng)];
            m2 = mods[dist(rng)];
        });
    }
 
    inline void initialize(int size) {
        n = size;
        pow1.reserve(n + 5);
        pow2.reserve(n + 5);
        h1.reserve(n + 5);
        h2.reserve(n + 5);
        pow1.assign(n + 5, 0);
        pow2.assign(n + 5, 0);
        h1.assign(n + 5, 0);
        h2.assign(n + 5, 0);
    }
 
    inline void calculate_powers() {
        pow1[0] = pow2[0] = 1;
        for (int i = 1; i <= n; ++i) {
            pow1[i] = (pow1[i - 1] * p1) % m1;
            pow2[i] = (pow2[i - 1] * p2) % m2;
        }
    }
 
    inline void calculate_hashes(const string& s) {
        h1[0] = h2[0] = 0;
        for (int i = 1; i <= n; ++i) {
            h1[i] = (h1[i - 1] * p1 + s[i - !Base]) % m1;
            h2[i] = (h2[i - 1] * p2 + s[i - !Base]) % m2;
        }
    }
 
    inline void calculate_hashes(const vector < T >& vec) {
        h1[0] = h2[0] = 0;
        for (int i = 1; i <= n; ++i) {
            h1[i] = (h1[i - 1] * p1 + vec[i - !Base]) % m1;
            h2[i] = (h2[i - 1] * p2 + vec[i - !Base]) % m2;
        }
    }
 
    inline pair < T, T > sub(int l, int r) const {
        T F = (h1[r] - (h1[l - 1] * pow1[r - l + 1] % m1) + m1) % m1;
        T S = (h2[r] - (h2[l - 1] * pow2[r - l + 1] % m2) + m2) % m2;
        return {F, S};
    }
 
    inline pair < T, T > merge_hash(int l1, int r1, int l2, int r2) const {
        auto a = sub(l1, r1), b = sub(l2, r2);
        T F = ((a.first * pow1[r2 - l2 + 1]) + b.first) % m1;
        T S = ((a.second * pow2[r2 - l2 + 1]) + b.second) % m2;
        return {F, S};
    }
 
    inline pair < T, T > at(int idx) const {
        return sub(idx, idx);
    }
 
    inline bool equal(int l1, int r1, int l2, int r2) const {
        return sub(l1, r1) == sub(l2, r2);
    }
};
 
template < typename T, int Base > constexpr array < T, 6 > Hash < T, Base >::powers;
template < typename T, int Base > constexpr array < T, 6 > Hash < T, Base >::mods;
template < typename T, int Base > T Hash < T, Base >::p1 = 0;
template < typename T, int Base > T Hash < T, Base >::p2 = 0;
template < typename T, int Base > T Hash < T, Base >::m1 = 0;
template < typename T, int Base > T Hash < T, Base >::m2 = 0;
 

void Solve(){
    
}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int test_cases = 1;
    // cin >> test_cases;
    for(int tc = 1; tc <= test_cases; tc++){
        // cout << "Case #" << tc << ": ";
        Solve();
    }
    return 0;
}