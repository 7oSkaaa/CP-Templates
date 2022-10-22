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
    T lazy_default, tree_default;
    vector < T > tree, lazy; 
    vector < bool > Clazy;
    
    // initial lazy and tree
    void intial(int n){
        size = 1;
        tree_default = 0, lazy_default = 0;
        while(size <= n) size *= 2;
        tree = vector < T > (size * 2, tree_default);
        lazy = vector < T > (size * 2, lazy_default);
        Clazy = vector < bool > (size * 2, false);
    }

    Lazy_Propagation(int n){
        intial(n);
        build(lazy_default);
    }

    // the function that will be used to update the tree
    T lazy_operation(T a, T b){
        return a + b;
    }

    // the function that will be used to query on the tree
    T tree_operation(T a, T b){
        return a + b;
    }

    // push lazy value to children in lazy
    void propagate(int idx, int lx, int rx){
        if(!Clazy[idx]) return;
        tree[idx] = lazy_operation(tree[idx], lazy[idx] * (rx - lx + 1));
        if(lx != rx){
            lazy[2 * idx] = lazy_operation(lazy[2 * idx], lazy[idx]);
            lazy[2 * idx + 1] = lazy_operation(lazy[2 * idx + 1], lazy[idx]);
            Clazy[2 * idx] = Clazy[2 * idx + 1] = true;
        }
        lazy[idx] = lazy_default, Clazy[idx] = false;
    }

    // push value to children int lazy
    void propagate(int idx, int lx, int rx, T v){
        tree[idx] = lazy_operation(tree[idx], v * (rx - lx + 1));
        if(lx != rx){
            lazy[2 * idx] = lazy_operation(lazy[2 * idx], v);
            lazy[2 * idx + 1] = lazy_operation(lazy[2 * idx + 1], v);
            Clazy[2 * idx] = Clazy[2 * idx + 1] = true;
        }
    }

    // build the tree with given vector
    void build(vector < T >& nums, int idx, int lx, int rx){
        propagate(idx, lx, rx);
        if(Base ? lx >= sz(nums) : lx > sz(nums)) return;
        if(rx == lx) tree[idx] = nums[lx - !Base];
        else {
            int m = (rx + lx) / 2;
            build(nums, 2 * idx, lx, m);
            build(nums, 2 * idx + 1, m + 1, rx);
            tree[idx] = tree_operation(tree[2 * idx], tree[2 * idx + 1]);
        }
    }

    // build the tree with initial value
    void build(T initial_value, int idx, int lx, int rx){
        propagate(idx, lx, rx);
        if(rx == lx) tree[idx] = initial_value;
        else {
            int m = (rx + lx) / 2;
            build(initial_value, 2 * idx, lx, m);
            build(initial_value, 2 * idx + 1, m + 1, rx);
            tree[idx] = tree_operation(tree[2 * idx], tree[2 * idx + 1]);
        }
    }

    // build the tree with initial value
    void build(T initial_value){
        build(initial_value, 1, 1, size);
    }

    // the vector should be 1-based also the tree is 1-based
    void build(vector < T >& nums){
        build(nums, 1, 1, size);
    }

    // update the value of the tree in range [l, r] with value v
    void update(int l, int r, T v, int idx, int lx, int rx){
        propagate(idx, lx, rx);
        if(lx >= l && rx <= r) return propagate(idx, lx, rx, v);
        if(lx > r || rx < l) return;
        int m = (lx + rx) / 2;
        update(l, r, v, 2 * idx, lx, m), update(l, r, v, 2 * idx + 1, m + 1, rx);
        tree[idx] = tree_operation(tree[2 * idx], tree[2 * idx + 1]);
    }

    // update the value in one index
    void update(int i, T v){
        update(i, i, v, 1, 1, size);
    }

    // update the value of the tree in range [l, r] with value v
    void update(int l, int r, T v){
        update(l, r, v, 1, 1, size);
    }

    // query the value of the tree in range [l, r]
    T query(int l, int r, int idx, int lx, int rx){
        propagate(idx, lx, rx);
        if(lx >= l && rx <= r) return tree[idx];
        if(lx > r || rx < l) return tree_default;
        int m = (rx + lx) / 2;
        return tree_operation(query(l, r, 2 * idx, lx, m), query(l, r, 2 * idx + 1, m + 1, rx));
    }

    // query the value of the tree in range [l, r]
    T query(int l, int r){
        return query(l, r, 1, 1, size);
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