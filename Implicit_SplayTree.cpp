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

struct Data {
    ll val, sum, pref, suff, max_seg;
    Data() : val(0), sum(0), pref(-LINF), suff(-LINF), max_seg(-LINF) {}
    Data(ll v) : val(v), sum(val), pref(val), suff(val), max_seg(val) {}
};
 
Data combine(const Data& a, const Data& b){
    Data res;
    res.sum = a.sum + b.sum;
    res.pref = max(a.pref, a.sum + b.pref);
    res.suff = max(b.suff, b.sum + a.suff);
    res.max_seg = max({a.max_seg, b.max_seg, a.suff + b.pref});
    return res;
}
 
template < typename T = int > struct SplayTree { // 0-indexed

    struct Node {
        
        Node *ch[2], *par;
        T val, update;
        int subSz;
        bool is_lazy;
 
        Node() : subSz(0), update(0), is_lazy(false) {
            par = ch[0] = ch[1] = this;
        }
        
        Node(T V) : val(V), subSz(1), update(0), is_lazy(false) {
            par = ch[0] = ch[1] = EMPTY;
        }

        // update node values
        void update() {
            subSz = ch[0] -> subSz + ch[1] -> subSz + 1;
            auto v = val.val;
            val = combine(ch[0] -> val, combine(Data(v), ch[1] -> val));
            val.val = v;
        }

        // push down lazy propagation
        void push_down(){
            if(this == EMPTY || !is_lazy) return;
            val = Data(update * subSz);
            ch[0] -> lazy_update(update);
            ch[1] -> lazy_update(update);
            is_lazy = false;
        }

        // lazy change
        void lazy_update(ll c){
            if(this == EMPTY) return;
            update = c;
            is_lazy = true;
        }

    };
 
    static Node* EMPTY;
    Node *root;
    enum dir {LEFT, RIGHT};
    #define returnType ll 
 
    SplayTree(){
        root = EMPTY;
    }
 
    // Link two nodes with direction d
    void link(Node *p, Node *c, int d){
        if(p != EMPTY) p -> ch[d] = c, p -> update();
        if(c != EMPTY) c -> par = p;
    }
 
    // 0 for LEFT, 1 for RIGHT
    int get_dir(Node *p, Node *c){
        return p -> ch[RIGHT] == c;
    }
 
    /*
            gp                       gp
            | gd                     | gd
            p                        q
          / \d                   !d/  \
         a   q    ->         <-   p    c
          !d/ \                 / \d
           b   c                a   b
    */
 
    // rotate node p with direction d
    void rotate(Node *p, int d){
        Node *q = p -> ch[d];
        Node *gp = p -> par;
        int gd = get_dir(gp, p);
        link(p, q -> ch[!d], d);
        link(q, p, !d);
        link(gp, q, gd);
    }
 
    // splay node p to the root of the tree it belongs to
    void splay(Node *q){
        // splay p until it becomes the root of the tree
        while(q -> par != EMPTY){
            Node *p = q -> par;
            Node *gp = p -> par;
            int d1 = get_dir(p, q);
            int d2 = get_dir(gp, p);
            if(gp == EMPTY){ // direct parent
                rotate(p, d1);
            }else if(d1 == d2){ // zig-zig
                rotate(gp, d2);
                rotate(p, d1);
            }else { // zig-zag 
                rotate(p, d1);
                rotate(gp, d2);
            }
        }
        root = q;
    }
 
    // split tree into two trees, one with values less than val and the other with values greater than or equal val
    void split(Node *p, int idx, Node* &ls, Node * &ge){
        if(idx >= p -> subSz) {
            ls = p, ge = EMPTY;
            return;
        }
        p = splay_by_idx(p, idx);
        ls = p -> ch[LEFT];
        ge = p;
        link(ge, EMPTY, LEFT);
        link(EMPTY, ls, RIGHT);
    }

    // make the node with index idx the root of the tree
    Node* splay_by_idx(Node* p, int idx){
        p = at(p, idx);
        splay(p);
        return p;
    }
 
    // merge two trees into one tree
    Node* merge(Node *ls, Node *ge){
        if(ls == EMPTY) return ge;
        if(ge == EMPTY) return ls;
        ge = splay_by_idx(ge, 0);
        link(ge, ls, LEFT);
        return ge;
    }
 
    // merge two trees into one tree
    void merge(Node* p){
        root = merge(root, p);
    }
 
    // find node with index idx or the node that should be the parent of the node with index idx
    Node* at(Node *p, int k){
        if(p == EMPTY) return EMPTY;
        p -> push_down();
        if(k > p -> subSz) return EMPTY;
        int sz = p -> ch[LEFT] -> subSz;
        if(sz > k) return at(p -> ch[LEFT], k);
        if(sz + 1 <= k) return at(p -> ch[RIGHT], k - sz - 1);
        return p;
    }
    
    // find node with index idx or the node that should be the parent of the node with index idx
    returnType at(int k){
        auto p = splay_by_idx(root, k);
        return p -> val;
    }
 
    // insert node with index idx to the tree
    void insert(int idx, int val){
        Node *before, *after;
        split(root, idx, before, after);
        Node* between = new Node(val);
        root = merge(merge(before, between), after);
    }
    
    // erase node with index idx from the tree
    void erase(int idx){
        Node *before, *after, *between;
        split(root, idx + 1, before, after);
        split(before, idx, before, between);
        delete between;
        root = merge(before, after);
    }
    
    // replace node with index idx with node with value val
    void replace(int idx, int val){
        Node *before, *after, *between;
        split(root, idx + 1, before, after);
        split(before, idx, before, between);
        
        // change the value of the node
        between -> val = val;

        root = merge(merge(before, between), after);
    }

    //  get query result for the range [s, e]
    returnType query(int s, int e){
        Node *before, *after, *between;
        split(root, e + 1, before, after);
        split(before, s, before, between);
        returnType ans = between -> val.max_seg;
        root = merge(merge(before, between), after);
        return ans;
    }
    
    // propagate lazy updates from node q to the root of the tree
    void push_down_to_root(Node* p){
        if(p == EMPTY) return;
        push_down_to_root(p -> par);
        p -> push_down();
    }
 
    // get the index of node q
    int get_idx(Node* p){
        push_down_to_root(p);
        splay(p);
        return p -> ch[LEFT] -> subSz;
    }
 
    // get the size of the subtree rooted at node p
    int get_size(){
        return root -> subSz;
    }
 
    // print the tree for debugging purposes
    void print(Node* p, int depth){
        if(p == EMPTY) return;
        print(p -> ch[LEFT], depth + 1);
        cout << string(2 * depth, ' ') << setw(2) << p -> val.val << "\n";
        print(p -> ch[RIGHT], depth + 1);
    }
    
    // print the tree for debugging purposes
    void print(){
        print(root, 0);
        cout << "-----------------------------------\n";
    }
};
template < typename T > typename SplayTree < T > :: Node* SplayTree < T > :: EMPTY = new typename SplayTree < T > :: Node();

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