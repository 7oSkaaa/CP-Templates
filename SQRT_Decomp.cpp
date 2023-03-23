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

template < typename T = int, int Base = 0 > struct Sqrt_Decomp {

    int n;
    vector < T > a, b;
    int len;
    T U_Default, Q_Default;

    T calc_sq(int N){
        int sq = sqrt(N);
        return sq * sq == N ? sq : sq + 1;
    }

    Sqrt_Decomp(int N = 0){
        n = N, len = calc_sq(n), U_Default = 0, Q_Default = 0;
        a = vector < T > (n + 5, U_Default);
        b = vector < T > (len + 5, Q_Default);
    }

    Sqrt_Decomp(int N, const vector < T >& vec){
        n = N, len = calc_sq(n), U_Default = 0, Q_Default = INF;
        a = vec;
        b = vector < T > (len + 5, Q_Default);
    }

    T update_operation(const T& L, const T& R){
        return R;
    }

    T query_operation(const T& L, const T& R){
        return min(L, R);
    }

    void build(){
        for(int i = 1; i <= n; i++)
            b[i / len] = query_operation(b[i / len], a[i - !Base]);
    }

    void update_1(int idx, T val){
        b[idx / len] = query_operation(b[idx / len], val - a[idx - !Base]);
        a[idx - !Base] = val;
    }

    void update_sq(int idx, T val){
        int b_id = idx / len;
        int b_l = b_id * len, b_r = b_l + len - 1;
        a[idx - !Base] = update_operation(a[idx - !Base], val);
        b[b_id] = Q_Default;
        for(int i = b_l; i <= min(b_r, n); i++)
            b[b_id] = query_operation(b[b_id], a[i - !Base]);
    }

    T query(int l, int r){
        T res = Q_Default;
        while(l < r && l % len != 0)
            res = query_operation(res, a[l++ - !Base]);
        while(l + len <= r)
            res = query_operation(res, b[l / len]), l += len;
        while(l <= r)
            res = query_operation(res, a[l++ - !Base]);
        return res;
    }

};

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