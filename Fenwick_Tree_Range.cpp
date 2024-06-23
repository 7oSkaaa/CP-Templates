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

template < typename T = int > struct Fenwick_Tree_Range {
    
    int N;
    T DEFAULT;
    vector < T > M, C;

    Fenwick_Tree_Range(int sz = 0){
        N = sz + 1, DEFAULT = 0;
        M = C = vector < T > (N + 10);
    }

    int lowest_bit(int idx){
        return (idx & -idx);
    }

    void build(vector < T >& nums){
        for(int i = 0; i < sz(nums); i++)
            add(i, i, nums[i]);
    }

    void add_range(int idx, T addM, T addC){
        idx++;
        while(idx <= N){
            M[idx] += addM;
            C[idx] += addC;
            idx += lowest_bit(idx);
        }
    }

    void add(int l, int r, T val) {
        add_range(l, val, -val * (l - 1));
        add_range(r + 1, -val, val * r);
    }

    void add(int idx, T val){
        add(idx, idx, val);
    }

    T get(int idx){
        T ans = DEFAULT;
        int pos = idx++;
        while(idx){
            ans += pos * M[idx] + C[idx];
            idx -= lowest_bit(idx);
        }
        return ans;
    }

    T query(int L, int R){
        if(L > R) return DEFAULT;
        return get(R) - get(L - 1);
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