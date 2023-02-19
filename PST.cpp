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

template < typename T = int > struct PST {

    struct Node {
       
        T val;
        Node *left, *right;

        Node() {
            val = 0;
            left = right = this;
        }

        Node(T v, Node *l = new Node, Node *r = new Node) : val(v), left(l), right(r) {}

    };

    vector < Node* > roots;
    int N, Lx, Rx;

    PST(int n = 0, T lx = -1e9, T rx = 1e9) : N(n), Lx(lx), Rx(rx) {
        roots = vector < Node* > (n + 5, new Node);
    }

    T operation(T a, T b) {
        return a + b;
    }

    Node* insert(Node* root, T val, T lx, T rx){
        if(val < lx || val > rx) return root;
        if(lx == rx) return new Node(root -> val + 1);
        T mx = lx + (rx - lx) / 2;
        Node* L = insert(root -> left, val, lx, mx);
        Node* R = insert(root -> right, val, mx + 1, rx);
        return new Node(operation(L -> val, R -> val), L, R);
    }
  
    void insert(int idx, int prev, T val){
        roots[idx] = insert(roots[prev], val, Lx, Rx);
    }

    T query(Node* l, Node* r, T k, T lx, T rx){
        if(lx == rx) return lx;
        T mx = lx + (rx - lx) / 2;
        T cnt = r -> left -> val - l -> left -> val;
        if(cnt >= k) 
            return query(l -> left, r -> left, k, lx, mx);
        return query(l -> right, r -> right, k - cnt, mx + 1, rx);
    }
    
    T query(int l, int r, T k){
        return query(roots[l - 1], roots[r], k, Lx, Rx);
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