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

template < typename T = int, const int Base = 0 > struct Lazy_Propagation {

    int size;
    T Lazy_default, Tree_default;
    vector < T > Tree, Lazy; 
    vector < bool > is_Lazy;
    
    // initial Lazy and Tree
    void intial(int n){
        size = 1;
        Tree_default = 0, Lazy_default = 0;
        while(size <= n) size *= 2;
        Tree = vector < T > (size * 2, Tree_default);
        Lazy = vector < T > (size * 2, Lazy_default);
        is_Lazy = vector < bool > (size * 2, false);
    }

    Lazy_Propagation(int n){
        intial(n);
    }

    Lazy_Propagation(int n, const vector < T > &v){
        intial(n);
        build(v);
    }

    // the function that will be used to update the Tree
    T Lazy_operation(T a, T b){
        return b;
    }

    // the function that will be used to query on the Tree
    T Tree_operation(T a, T b){
        return min(a, b);
    }

    // push Lazy value to children in Lazy
    void propagate(int idx, int lx, int rx){
        if(!is_Lazy[idx]) return;
        Tree[idx] = Lazy_operation(Tree[idx], Lazy[idx]);
        if(lx != rx){
            Lazy[2 * idx] = Lazy_operation(Lazy[2 * idx], Lazy[idx]);
            Lazy[2 * idx + 1] = Lazy_operation(Lazy[2 * idx + 1], Lazy[idx]);
            is_Lazy[2 * idx] = is_Lazy[2 * idx + 1] = true;
        }
        Lazy[idx] = Lazy_default, is_Lazy[idx] = false;
    }

    // push value to children int Lazy
    void propagate(int idx, int lx, int rx, T v){
        Tree[idx] = Lazy_operation(Tree[idx], v);
        if(lx != rx){
            Lazy[2 * idx] = Lazy_operation(Lazy[2 * idx], v);
            Lazy[2 * idx + 1] = Lazy_operation(Lazy[2 * idx + 1], v);
            is_Lazy[2 * idx] = is_Lazy[2 * idx + 1] = true;
        }
    }

    // build the Tree with given vector
    void build(const vector < T >& nums, int idx, int lx, int rx){
        propagate(idx, lx, rx);
        if(Base ? lx >= sz(nums) : lx > sz(nums)) return;
        if(rx == lx) Tree[idx] = nums[lx - !Base];
        else {
            int m = (rx + lx) / 2;
            build(nums, 2 * idx, lx, m);
            build(nums, 2 * idx + 1, m + 1, rx);
            Tree[idx] = Tree_operation(Tree[2 * idx], Tree[2 * idx + 1]);
        }
    }

    // build the Tree with initial value
    void build(const T initial_value, int idx, int lx, int rx){
        propagate(idx, lx, rx);
        if(rx == lx) Tree[idx] = initial_value;
        else {
            int m = (rx + lx) / 2;
            build(initial_value, 2 * idx, lx, m);
            build(initial_value, 2 * idx + 1, m + 1, rx);
            Tree[idx] = Tree_operation(Tree[2 * idx], Tree[2 * idx + 1]);
        }
    }

    // build the Tree with initial value
    void build(const T initial_value){
        build(initial_value, 1, 1, size);
    }

    // the vector should be 1-based also the Tree is 1-based
    void build(const vector < T >& nums){
        build(nums, 1, 1, size);
    }

    // update the value of the Tree in range [l, r] with value v
    void update(int l, int r, T v, int idx, int lx, int rx){
        propagate(idx, lx, rx);
        if(lx >= l && rx <= r) return propagate(idx, lx, rx, v);
        if(lx > r || rx < l) return;
        int m = (lx + rx) / 2;
        update(l, r, v, 2 * idx, lx, m), update(l, r, v, 2 * idx + 1, m + 1, rx);
        Tree[idx] = Tree_operation(Tree[2 * idx], Tree[2 * idx + 1]);
    }

    // update the value in one index
    void update(int i, T v){
        update(i, i, v, 1, 1, size);
    }

    // update the value of the Tree in range [l, r] with value v
    void update(int l, int r, T v){
        update(l, r, v, 1, 1, size);
    }

    // query the value of the Tree in range [l, r]
    T query(int l, int r, int idx, int lx, int rx){
        propagate(idx, lx, rx);
        if(lx >= l && rx <= r) return Tree[idx];
        if(lx > r || rx < l) return Tree_default;
        int m = (rx + lx) / 2;
        return Tree_operation(query(l, r, 2 * idx, lx, m), query(l, r, 2 * idx + 1, m + 1, rx));
    }

    // query the value of the Tree in range [l, r]
    T query(int l, int r){
        return query(l, r, 1, 1, size);
    }

    // query the value of the Tree in index i
    T query(int i){
        return query(i, i, 1, 1, size);
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