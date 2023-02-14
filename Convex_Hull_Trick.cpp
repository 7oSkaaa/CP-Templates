#include <bits/stdc++.h>

using namespace std;

#define cin_2d(vec, n, m) for(int i = 0; i < n; i++) for(int j = 0; j < m && cin >> vec[i][j]; j++);
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define fixed(n) fixed << setprecision(n)
#define ceil(n, m) (((n) / (m)) + ((n) % (m) ? 1 : 0))
#define fill(vec, value) memset(vec, value, sizeof(vec));
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
#define Mod  1'000'000'007
#define OO 2'000'000'000
#define EPS 1e-9
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

struct Line {

    mutable ll m, c, p;

    bool operator < (const Line &o) const { 
        return m < o.m; 
    }

    bool operator < (ll x) const { 
        return p < x; 
    }

    ll val(ll x) const { 
        return m * x + c; 
    }
};

template < typename T = int, T Mode = -1 > class CHT : multiset < Line, less < > > {
private:
    
    static constexpr T LLimit = numeric_limits < T > :: min(), RLimit = numeric_limits < T > :: max();

    T div(T a, T b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b);
    }

    bool is_intersect(iterator x, iterator y) {
        if (y == end()) return x -> p = RLimit, 0;
        if (x -> m == y -> m) x -> p = (x -> c > y -> c ? RLimit : LLimit);
        else x -> p = div(y -> c - x -> c, x -> m - y -> m);
        return x -> p >= y -> p;
    }

public:
    
    void add(T m, T c) {
        m *= Mode, c *= Mode;
        auto z = insert({m, c, 0}), y = z++, x = y;
        while (is_intersect(y, z)) z = erase(z);
        if (x != begin() && is_intersect(--x, y)) is_intersect(x, y = erase(y));
        while ((y = x) != begin() && (--x) -> p >= y -> p) is_intersect(x, erase(y));
    }

    T query(T x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return Mode * l.val(x);
    }

};

void Solve(){
    
}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--)
        Solve();
    return 0;
}