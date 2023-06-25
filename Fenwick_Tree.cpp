#include <bits/stdc++.h>

using namespace std;

#define cin_2d(vec, n, m) for(int i = 0; i < n; i++) for(int j = 0; j < m && cin >> vec[i][j]; j++);
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define fixed(n) fixed << setprecision(n)
#define ceil(n, m) (((n) / (m)) + ((n) % (m) ? 1 : 0))
#define fill(vec, value) memset(vec, value, sizeof(vec));
#define mul_mod(a, b, m) (((a % m) * (b % m)) % m)
#define add_mod(a, b, m) (((a % m) + (b % m)) % m)
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

template < typename T = int > struct Fenwick_Tree {
    
    vector < T > Tree;
    int n;
    T DEFAULT;

    Fenwick_Tree(int sz = 0){
        n = sz + 1, DEFAULT = 0;
        Tree = vector < T > (n + 10, DEFAULT);
    }

    T operation(T a, T b){
        return a + b;
    }

    int lowest_bit(int idx){
        return (idx & -idx);
    }

    void build(vector < T >& nums){
        for(int i = 0; i < sz(nums); i++)
            add(i, nums[i]);
    }

    void add(int idx, T val){
        idx++;
        while(idx <= n){
            Tree[idx] = operation(Tree[idx], val);
            idx += lowest_bit(idx);
        }
    }

    T get_ans(int idx){
        T ans = DEFAULT;
        idx++;
        while(idx){
            ans = operation(ans, Tree[idx]);
            idx -= lowest_bit(idx);
        }
        return ans;
    }

    T query(int l, int r){
        if(l > r) return DEFAULT;
        return get_ans(r) - get_ans(l - 1);
    }

    T get(int idx){
        return query(idx, idx);
    }

};

void Solve(){
    
}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--)
        Solve();
    return 0;
}