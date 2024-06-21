#pragma GCC optimize("O3")
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

template < typename T = int > struct SplayTree {

    struct Node {
        
        Node *ch[2], *par;
        T val;
        int subSz, freq;

        Node() : subSz(0), freq(0) {
            par = ch[0] = ch[1] = this;
            val = numeric_limits < T > :: min();
        }
        
        Node(T V) : val(V), subSz(1), freq(1) {
            par = ch[0] = ch[1] = EMPTY;
        }
        
        void update() {
            subSz = freq + ch[0] -> subSz + ch[1] -> subSz;
        }
    };

    static Node* EMPTY;
    Node *root;
    enum dir {LEFT, RIGHT};

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

    // find node with value val or the node that should be the parent of the node with value val
    Node* find(Node *p, T val){
        if(p == EMPTY) return EMPTY;
        Node * ch = p -> ch[val > p -> val];
        if(p -> val == val || ch == EMPTY) return p;
        return find(ch, val);
    }

    // splay node with value val to the root of the tree it belongs to
    Node* splay_by_value(Node *p, T val){
        p = find(p, val);
        splay(p);
        return p;
    }

    // insert node with value val to the tree
    Node* insert(Node *p, T val){
        if(p == EMPTY) return new Node(val);
        p = splay_by_value(p, val);
        if(p -> val == val){
            p -> freq++;
            p -> subSz++;
            return p;
        }
        Node *q = new Node(val);
        if(p -> ch[val > p -> val] != EMPTY){
            auto ch = p -> ch[val > p -> val];
            link(p, EMPTY, val > p -> val);
            link(q, ch, q -> val < ch -> val);
            link(q, p, q -> val < p -> val);
            p = q;
        }else 
            link(p, q, val > p -> val);
        return p;
    }

    // insert node with value val to the tree
    void insert(T val){
        root = insert(root, val);
    }

    // split tree into two trees, one with values less than val and the other with values greater than or equal val
    void split(Node *p, T val, Node* &ls, Node * &ge){
        p = splay_by_value(p, val);
        if(p -> val < val){
            ls = p;
            ge = p -> ch[RIGHT];
            link(ls, EMPTY, RIGHT);
            link(EMPTY, ge, LEFT);
        }else {
            ls = p -> ch[LEFT];
            ge = p;
            link(ge, EMPTY, LEFT);
            link(EMPTY, ls, RIGHT);
        }
    }

    // merge two trees into one tree
    Node* merge(Node *ls, Node *ge){
        if(ls == EMPTY) return ge;
        if(ge == EMPTY) return ls;
        ge = splay_by_value(ge, numeric_limits < T > :: min());
        link(ge, ls, LEFT);
        return ge;
    }

    // erase node with value val from the tree
    Node* erase(Node *p, T val){
        p = splay_by_value(p, val);
        if(p -> val != val) return p;
        if(p -> freq > 1){
            p -> freq--;
            p -> subSz--;
            return p;
        } else {
            Node *ls = p -> ch[LEFT];
            Node *ge = p -> ch[RIGHT];
            delete p;
            link(EMPTY, ls, LEFT);
            link(EMPTY, ge, RIGHT);
            return merge(ls, ge);
        }
    }

    // erase node with value val from the tree
    void erase(T val){
        root = erase(root, val);
    }

    // find the kth smallest value in the tree
    Node* kth(Node *p, T k){
        if(p == EMPTY) return EMPTY;
        if(k > p -> subSz) return EMPTY;
        int sz = p -> ch[LEFT] -> subSz;
        if(sz > k) return kth(p -> ch[LEFT], k);
        if(sz + p -> freq <= k) return kth(p -> ch[RIGHT], k - sz - p -> freq);
        return p;
    }

    // find the kth smallest value in the tree
    T kth(T k){
        auto p = kth(root, k);
        splay(p);
        root = p;
        return p -> val;
    }

    // count the number of values less than val in the tree
    int count_less(T val){
        root = splay_by_value(root, val);
        return root -> ch[LEFT] -> subSz + (root -> val < val ? root -> freq : 0);
    }

    // get the size of the subtree rooted at node p
    int get_size(){
        return root -> subSz;
    }

    void print(Node* p, int depth){
        if(p == EMPTY) return;
        print(p -> ch[LEFT], depth + 1);
        cout << string(2 * depth, ' ') << setw(2) << p -> val << "\n";
        print(p -> ch[RIGHT], depth + 1);
    }

    void print(){
        print(root, 0);
        cout << "-----------------------------------\n";
    }

    bool search(T val){
        root = splay_by_value(root, val);
        return root -> val == val;
    }
};
template < typename T > typename SplayTree < T > :: Node* SplayTree < T > :: EMPTY = new typename SplayTree < T > :: Node();


void Solve(){
    int n;
    cin >> n;
    SplayTree < int > st;
    while(n--){
        char type;
        int x;
        cin >> type >> x;
        switch(type) {
            case 'I':
                if(!st.search(x)) st.insert(x);
                break;
            case 'D':
                st.erase(x);
                break;
            case 'K':
                if(st.get_size() < x) cout << "invalid\n";
                else cout << st.kth(--x) << "\n";
                break;
            case 'C':
                cout << st.count_less(x) << "\n";
                break;
        }
        // st.print();
    }
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