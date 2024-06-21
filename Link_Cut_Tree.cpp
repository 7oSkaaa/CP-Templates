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

template < typename T = int , int Base = 0 > struct LCT {
    
    struct Node {
        
        T val, siz;
        int par, ch[2];

        Node() : val(0), siz(0), par(0), ch{0, 0} {}
    };
    
    vector < Node > nodes;

    #define par(x) nodes[x].par
    #define left(x) nodes[x].ch[0]
    #define right(x) nodes[x].ch[1]
    #define siz(x) nodes[x].siz
    #define val(x) nodes[x].val
    
    LCT(int _n = 0) : nodes(_n + 5) { 
        for(int i = 1; i <= _n; i++){
            par(i) = left(i) = right(i) = 0;
            siz(i) = val(i) = 1;
        }
    }

    LCT(int _n, vector < T > &v) : nodes(_n + 5) {
        for(int i = 1; i <= _n; i++){
            par(i) = left(i) = right(i) = 0;
            val(i) = v[i - !Base];
            siz(i) = 1;
        }
    }

    // check if x is a root
    bool is_root(int x){
        return par(x) == 0 || (left(par(x)) != x && right(par(x)) != x);
    }

    // update the sum of the node
    void update(int x){
        siz(x) = siz(left(x)) + siz(right(x)) + val(x);
    }

    // is x a right child
    bool is_right(int x){
        return right(par(x)) == x;
    }

    // rotate the edge between x and its parent
    void rotate(int x){
        int p = par(x), g = par(p), t = is_right(x);
        if(!is_root(p)) nodes[g].ch[is_right(p)] = x;
        nodes[p].ch[t] = nodes[x].ch[!t];
        par(nodes[p].ch[t]) = p;
        nodes[x].ch[!t] = p; 
        par(p) = x, par(x) = g;
        update(p), update(x);
    }

    // splay the node x
    void splay(int x){
        while(!is_root(x)){
            int p = par(x);
            if(!is_root(p)) rotate(is_right(p) == is_right(x) ? p : x);
            rotate(x);
        }
    }

    // expose the path between x and the root
    void expose(int x){
        for(int p = 0; x; p = x, x = par(x)){
            splay(x);
            if(right(x)) val(x) += siz(right(x));
            if(p) val(x) -= siz(p);
            right(x) = p;
            update(x);
        }
    }

    // make x the root of the tree
    void make_root(int x){
        expose(x);
        splay(x);
        val(x) = -val(x);
        swap(left(x), right(x));
    }

    // check if x and y are connected
    bool connected(int x, int y){
        expose(x), expose(y);
        return x == y || par(x);
    }

    // get the root of the tree
    int get_root(int x){
        expose(x), splay(x);
        while(left(x)) x = left(x);
        splay(x);
        return x;
    }

    // link the edge between x and y
    void link(int x, int y){
        expose(x), splay(x);
        expose(y), splay(y);
        par(y) = x;
        val(x) += siz(y);
        update(x);
    }

    // link the edge between x and its parent
    void link(int x){
        link(x, par(x));
    }

    // cut the edge between x and y
    void cut(int x, int y){
        expose(y), splay(x);
        right(x) = par(y) = 0;
        update(x);
    }

    // cut the edge between x and its parent
    void cut(int x){
        cut(x, par(x));
    }

    // query the sum of the path between x and y
    T query(int x, int y){
        make_root(x);
        expose(y);
        return siz(y);
    }

    // query the value of subtree of x
    T query_subtree(int x){
        expose(x);
        return val(x);
    }

    // update the value of the node x
    void set(int x, T v){
        val(x) = v;
        splay(x);
    }

    #undef par
    #undef left
    #undef right
    #undef val
    #undef siz
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