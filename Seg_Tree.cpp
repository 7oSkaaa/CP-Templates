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

template < typename T = int, const int Base = 0 > struct Segment_Tree {

    struct Node {

        ll val;

        Node(ll V = 0) : val(V) {}
    
        Node operator = (const T rhs) {
            val = rhs;
            return *this;
        }

    };

    int size; 
    Node DEFAULT;
    vector < Node > Tree; 
    
    void intial(int n){
        size = 1, DEFAULT = 0;
        while(size < n) size *= 2;
        Tree = vector < Node > (2 * size, DEFAULT);
    }

    Segment_Tree(int n){
        intial(n);
    }

    // Main operation to do

    Node operation(Node a, Node b){
        return a.val + b.val;
    }
    
    // If Base is 1 so the array is 1-based else the array is 0-based
    
    void build(vector < T >& nums, int idx, int lx, int rx){
        if(Base ? lx >= sz(nums) : lx > sz(nums)) return;
        if(rx == lx) Tree[idx] = nums[lx - !Base];
        else {
            int m = (rx + lx) / 2;
            build(nums, 2 * idx, lx, m);
            build(nums, 2 * idx + 1, m + 1, rx);
            Tree[idx] = operation(Tree[2 * idx], Tree[2 * idx + 1]);
        }
    }

    void build(vector < T >& nums){
        build(nums, 1, 1, size);
    }

    void update(int i, T v, int idx, int lx, int rx){
        if(rx == lx) Tree[idx] = v;
        else {  
            int m = (rx + lx) / 2;
            if(i <= m) update(i, v, 2 * idx, lx, m);
            else update(i, v, 2 * idx + 1, m + 1, rx);
            Tree[idx] = operation(Tree[2 * idx], Tree[2 * idx + 1]);
        }
    }

    void update(int i, T v){
        update(i, v, 1, 1, size);
    }

    Node query(int l, int r, int idx, int lx, int rx){
        if(lx > r || l > rx) return DEFAULT;
        if(lx >= l && rx <= r) return Tree[idx];
        int m = (lx + rx) / 2;
        return operation(query(l, r, 2 * idx, lx, m), query(l, r, 2 * idx + 1, m + 1, rx));
    }

    T query(int l, int r){
        return _query(l, r, 1, 1, size).val;
    }

    friend ostream& operator << (ostream &out, const Node &node) {
        out << node.val;
        return out;
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