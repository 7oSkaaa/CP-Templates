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

    struct Node {
        T val, update;
        bool is_lazy;
        Node(T V = 0) : val(V), update(0), is_lazy(false) {}
        Node operator = (const T &other){
            this -> val = other;
            return *this;
        }
    };
    
    int size;
    T query_default, init_default;
    vector < Node > Tree;
    #define LEFT (idx << 1)
    #define RIGHT ((idx << 1) | 1)

    // initial Lazy and Tree
    void intial(int n){
        size = 1;
        query_default = 0, init_default = 0;
        while(size <= n) size *= 2;
        Tree = vector < Node > (2 * size, Node(init_default));
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
        return a + b;
    }

    // the function that will be used to query on the Tree
    Node Tree_operation(const Node& a, const Node& b){
        return Node(a.val + b.val);
    }

    // push Lazy value to children in Lazy
    void propagate(int idx, int lx, int rx){
        if(!Tree[idx].is_lazy) return;
        Tree[idx].val = Lazy_operation(Tree[idx].val, (rx - lx + 1) * Tree[idx].update);
        if(lx != rx){
            Tree[LEFT].update = Lazy_operation(Tree[LEFT].update, Tree[idx].update);
            Tree[RIGHT].update = Lazy_operation(Tree[RIGHT].update, Tree[idx].update);
            Tree[LEFT].is_lazy = Tree[RIGHT].is_lazy = true;
        }
        Tree[idx].update = init_default, Tree[idx].is_lazy = false;
    }

    void update_lazy(int idx, T v){
        Tree[idx].update = Lazy_operation(Tree[idx].update, v);
        Tree[idx].is_lazy = true;
    }

    // build the Tree with given vector
    void build(const vector < T >& nums, int idx, int lx, int rx){
        propagate(idx, lx, rx);
        if(Base ? lx >= sz(nums) : lx > sz(nums)) return;
        if(rx == lx) Tree[idx] = nums[lx - !Base];
        else {
            int mx = (rx + lx) / 2;
            build(nums, LEFT, lx, mx), build(nums, RIGHT, mx + 1, rx);
            propagate(LEFT, lx, mx), propagate(RIGHT, mx + 1, rx);
            Tree[idx] = Tree_operation(Tree[LEFT], Tree[RIGHT]);
        }
    }

    // build the Tree with initial value
    void build(const T initial_value, int idx, int lx, int rx){
        propagate(idx, lx, rx);
        if(rx == lx) Tree[idx] = initial_value;
        else {
            int mx = (rx + lx) / 2;
            build(initial_value, LEFT, lx, mx), build(initial_value, RIGHT, mx + 1, rx);
            propagate(LEFT, lx, mx), propagate(RIGHT, mx + 1, rx);
            Tree[idx] = Tree_operation(Tree[LEFT], Tree[RIGHT]);
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
        if(lx >= l && rx <= r) return update_lazy(idx, v);
        if(lx > r || rx < l) return;
        int mx = (lx + rx) / 2;
        update(l, r, v, LEFT, lx, mx), update(l, r, v, RIGHT, mx + 1, rx);
        propagate(LEFT, lx, mx), propagate(RIGHT, mx + 1, rx);
        Tree[idx] = Tree_operation(Tree[LEFT], Tree[RIGHT]);
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
    Node query(int l, int r, int idx, int lx, int rx){
        propagate(idx, lx, rx);
        if(lx >= l && rx <= r) return Tree[idx];
        if(lx > r || rx < l) return query_default;
        int mx = (rx + lx) / 2;
        propagate(LEFT, lx, mx), propagate(RIGHT, mx + 1, rx);
        return Tree_operation(query(l, r, LEFT, lx, mx), query(l, r, RIGHT, mx + 1, rx));
    }

    // query the value of the Tree in range [l, r]
    T query(int l, int r){
        return query(l, r, 1, 1, size).val;
    }

    // query the value of the Tree in index i
    T query(int i){
        return query(i, i, 1, 1, size).val;
    }

    // print the Tree
    void print(int idx, int lx, int rx){
        propagate(idx, lx, rx);
        if(lx == rx) cout << Tree[idx].val << ' ';
        else {
            int mx = (lx + rx) / 2;
            print(LEFT, lx, mx), print(RIGHT, mx + 1, rx);
        }
    }

    // print the Tree
    void print(){
        print(1, 1, size);
        cout << '\n';
    }

    // remove the defined macros
    #undef LEFT
    #undef RIGHT
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