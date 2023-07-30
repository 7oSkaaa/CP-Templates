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

template < typename T = int , int Base = 0 > struct PST {
 
    struct Node {
       
        T val, prefix;
        Node *left, *right;
 
        Node(T _val = 0) {
            this -> val = _val;
            this -> prefix = max(0ll, _val);
            left = right = this;
        }
 
        Node(Node* node, Node* l = new Node, Node* r = new Node) {
            val = node -> val;
            prefix = node -> prefix;
            left = l;
            right = r;
        }
    };
 
    vector < Node* > roots;
    T N, Lx, Rx;
 
    PST(int n = 0, T lx = -1e9, T rx = 1e9) : N(n), Lx(lx), Rx(rx) {
        roots = vector < Node* > (n + 5, new Node);
    }

    Node* build(const vector < T >& nums, T l, T r){
        if(l == r) return new Node(nums[l - !Base]);
        T mx = l + (r - l) / 2;
        Node* L = build(nums, l, mx);
        Node* R = build(nums, mx + 1, r);
        return new Node(operation(L, R), L, R);
    }

    void build(const vector < T >& nums){
        roots[0] = build(nums, Lx, Rx);
    }
 
    Node* operation(Node* a, Node* b){
        Node* Merged = new Node();
        Merged -> val = a -> val + b -> val;
        Merged -> prefix = max(a -> prefix, a -> val + b -> prefix);
        return Merged;
    }
 
    Node* update(Node* root, int idx, T val, T lx, T rx){
        if(idx < lx || idx > rx) return root;
        if(lx == rx) return new Node(val);
        T mx = lx + (rx - lx) / 2;
        Node* L = update(root -> left, idx, val, lx, mx);
        Node* R = update(root -> right, idx, val, mx + 1, rx);
        return new Node(operation(L, R), L, R);
    }
  
    void insert(int idx, T val, int curr_time, int prev_time){
        roots[curr_time] = update(roots[prev_time], idx, val, Lx, Rx);
    }

    void update(int idx, T val, int curr_time){
        roots[curr_time] = update(roots[curr_time], idx, val, Lx, Rx);
    }
 
    Node* query(Node* root, int l, int r, T lx, T rx){
        if (root == nullptr) return new Node(); // Base case for null pointer
        if (lx > r || l > rx) return new Node(); // Base case for out-of-range interval
        if(lx >= l && rx <= r) return root;
        int mx = (lx + rx) / 2;
        Node* L = query(root -> left, l, r, lx, mx);
        Node* R = query(root -> right, l, r, mx + 1, rx);
        return operation(L, R);
    }
    
    T query(int l, int r, int time){
        return query(roots[time], l, r, Lx, Rx) -> prefix;
    }

    T get(int time, int idx){
        return query(idx, idx, time) -> prefix;
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