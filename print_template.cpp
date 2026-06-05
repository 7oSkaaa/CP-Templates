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

void FAST_IO(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
}

// -------------------------- Trie Binary -----------------------------

template < typename T = int, int LOG = 30 > struct Trie {

    struct Node {
 
        Node* child[2];
        int freq;
 
        Node(){
            memset(child, 0, sizeof(child));
            freq = 0;
        }
    };

    Node* root;

    Trie(){
        root = new Node;
    }

    void insert(const T& x){
        Node* curr = root; 
        for(int bit = LOG; bit >= 0; --bit){
            int bit_val = (x >> bit) & 1;
            if(!curr -> child[bit_val]) 
                curr -> child[bit_val] = new Node;
            curr = curr -> child[bit_val];
            ++curr -> freq;
        }
    }
  
    void erase(const T& x, int bit, Node* curr){
        if(bit < 0) return;
        int bit_val = (x >> bit) & 1;
        erase(x, bit - 1, curr -> child[bit_val]);
        if(--curr -> child[bit_val] -> freq == 0){
            delete curr -> child[bit_val];
            curr -> child[bit_val] = nullptr;
        }
    }

    bool search(const T& x){
        Node* curr = root; 
        for(int bit = LOG; bit >= 0; --bit){
            int bit_val = (x >> bit) & 1;
            if(!curr -> child[bit_val]) 
                return false;
            curr = curr -> child[bit_val];
        }
        return true;
    }
 
    void erase(const T& x){
        if(search(x)) 
            erase(x, LOG, root);
    }
};

// -------------------------- Trie -----------------------------
 
template < int Mode = 0 > struct Trie {
    // Mode [lowercase, uppercase, digits]
    static constexpr int sz[4] = {26, 26, 10};

    struct Node {
 
        Node* child[sz[Mode]];
        bool is_word;
        int freq;
 
        Node(){
            memset(child, 0, sizeof(child));
            is_word = false;
            freq = 0;
        }
    };

    Node* root;
    char DEFAULT;

    Trie(){
        root = new Node;
        DEFAULT = "aA0"[Mode];
    }
    
    void insert(const string& word){
        Node* curr = root; 
        for(auto& c : word){
            if(!curr -> child[c - DEFAULT]) 
                curr -> child[c - DEFAULT] = new Node;
            curr = curr -> child[c - DEFAULT];
            curr -> freq++;
        }
        curr -> is_word = true;
    }
  
    void erase(const string& word, int idx, Node* curr){
        if(idx == sz(word)) return void(curr -> is_word = curr -> freq > 1);
        erase(word, idx + 1, curr -> child[word[idx] - DEFAULT]);
        if(--curr -> child[word[idx] - DEFAULT] -> freq == 0){
            delete curr -> child[word[idx] - DEFAULT];
            curr -> child[word[idx] - DEFAULT] = nullptr;
        }
    }

    bool search(const string& word){
        Node* curr = root; 
        for(auto& c : word){
            if(!curr -> child[c - DEFAULT]) return false;
            curr = curr -> child[c - DEFAULT];
        }
        return curr -> is_word;
    }
 
    void erase(const string& word){
        if(search(word)) 
            erase(word, 0, root);
    }

    bool is_prefix(const string& word){
        Node* curr = root; 
        for(auto& c : word){
            if(!curr -> child[c - DEFAULT]) return false;
            curr = curr -> child[c - DEFAULT];
        }
        return true;
    }
};

// -------------------------- PST -----------------------------

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

// -------------------------- Seive -----------------------------

template < typename T = int > struct Seive {

    vector < bool > is_prime;
    vector < T > primes;

    Seive(int n){
        is_prime.assign(n + 1, true);
        is_prime[0] = is_prime[1] = false;
        for(ll i = 2; i <= sqrt(n); i++)
            if(is_prime[i])
                for(ll j = i * i; j <= n; j += i) is_prime[j] = false;
    }

    // Build vector with prime numbers

    void get_primes(int n){
        for(int i = 1; i <= n; i++)
            if(is_prime[i])
                primes.push_back(i);
    }

    // Print the prime numbers

    void print_primes(){
        for(auto& p : primes)
            cout << p << " ";
        cout << "\n";
    }

};

// -------------------------- Segment Tree -----------------------------

template < typename T = int , int Base = 0 > struct Segment_Tree {

    struct Node {

        T val;

        Node(T V = 0) : val(V) {}
    
        Node operator = (const T rhs) {
            val = rhs;
            return *this;
        }

    };

    int size; 
    Node DEFAULT;
    vector < Node > tree; 
    #define LEFT (idx << 1)
    #define RIGHT ((idx << 1) | 1)
    
    Segment_Tree(int n = 0){
        size = 1, DEFAULT = 0;
        while(size < n) size *= 2;
        tree = vector < Node > (2 * size, DEFAULT);
    }

    Segment_Tree(int n, const vector < T >& nums){
        size = 1, DEFAULT = 0;
        while(size < n) size *= 2;
        tree = vector < Node > (2 * size, DEFAULT);
        build(nums);
    }

    // Main operation to do

    Node operation(const Node& a, const Node& b){
        return a.val + b.val;
    }
    
    // If Base is 1 so the array is 1-based else the array is 0-based
    
    void build(const vector < T >& nums, int idx, int lx, int rx){
        if(Base ? lx >= sz(nums) : lx > sz(nums)) return;
        if(rx == lx) tree[idx] = nums[lx - !Base];
        else {
            int mx = (rx + lx) / 2;
            build(nums, LEFT, lx, mx);
            build(nums, RIGHT, mx + 1, rx);
            tree[idx] = operation(tree[LEFT], tree[RIGHT]);
        }
    }

    void build(const vector < T >& nums){
        build(nums, 1, 1, size);
    }

    void update(int index, T v, int idx, int lx, int rx){
        if(rx == lx) tree[idx] = v;
        else {  
            int mx = (rx + lx) / 2;
            if(index <= mx) update(index, v, LEFT, lx, mx);
            else update(index, v, RIGHT, mx + 1, rx);
            tree[idx] = operation(tree[LEFT], tree[RIGHT]);
        }
    }

    void update(const int index, const T v){
        update(index, v, 1, 1, size);
    }

    Node query(int l, int r, int idx, int lx, int rx){
        if(lx > r || l > rx) return DEFAULT;
        if(lx >= l && rx <= r) return tree[idx];
        int mx = (lx + rx) / 2;
        return operation(query(l, r, LEFT, lx, mx), query(l, r, RIGHT, mx + 1, rx));
    }

    Node query_Node(const int l, const int r){
        return query(l, r, 1, 1, size);
    }

    T query(const int l, const int r){
        return query_Node(l, r).val;
    }

    T get(const int idx){
        return query_Node(idx, idx).val;
    }

    friend ostream& operator << (ostream &out, const Node &node) {
        out << node.val << ' ';
        return out;
    }
    
    // remove macro LEFT and RIGHT
    #undef LEFT
    #undef RIGHT
};

// -------------------------- Lazy Propagation -----------------------------

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

// -------------------------- Ternary Search -----------------------------

ll F(ll m){
    // to do function to compare the two halves in the range [L, R]
    return m;
}

ll Ternary_Search(ll L, ll R){
    while(R - L >= 10){
        ll m1 = L + (R - L) / 3, m2 = R - (R - L) / 3;
        (F(m1) < F(m1) ? R = m2 : L = m1);
    }
    ll ans = LINF;
    for(ll i = L; i <= R; i++) 
        ans = min(ans, F(i));
    return ans;
}

double F(double m){
    // to do function to compare the two halves in the range [L, R]
    return m;
}

double Ternary_Search(double L, double R){
    double ans = LINF;
    while(R - L >= EPS){
        double m1 = L + (R - L) / 3, m2 = R - (R - L) / 3;
        double f1 = F(m1), f2 = F(m1);
        (f1 < f2 ? R = m2 : L = m1);
        ans = min({ans, f1, f2});
    }
    return ans;
}

// -------------------------- Prefix Sum 2D -----------------------------

template < typename T = int > struct Prefix_2D {

    int n, m;
    vector < vector < T > > prefix;
    
    Prefix_2D(int N = 0, int M = 0){
        n = N, m = M;
        prefix.assign(n + 5, vector < T > (m + 5));
    }

    // Get the sum of the number in the rectangle between x1, y1, x2, y2

    T Get_Query(int x1, int y1, int x2, int y2){
        if(x1 > x2) swap(x1, x2);
        if(y1 > y2) swap(y1, y2);
        return prefix[x2][y2] - prefix[x1 - 1][y2] - prefix[x2][y1 - 1] + prefix[x1 - 1][y1 - 1];
    }

    void Build_Prefix(vector < vector < T > >& matrix){
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                prefix[i][j] = matrix[i - 1][j - 1] + prefix[i][j - 1] + prefix[i - 1][j] - prefix[i - 1][j - 1];
    }

    void Print_Prefix(){
        for(int i = 1; i <= n; i++, cout << '\n')
            for(int j = 1; j <= m && cout << prefix[i][j] << ' '; j++);
    }
    
};

// -------------------------- Partial Sum 2D -----------------------------

template < typename T = int > struct Partial_2D {

    vector < vector < T > > partial;
    int n, m;

    Partial_2D(int N, int M){
        n = N, m = M;
        partial.assign(n + 5, vector < T > (m + 5));
    }

    void build_partial(int queries){
        while(queries--){
            int x1, y1, x2, y2, k = 1;
            cin >> x1 >> y1 >> x2 >> y2;
            if(x1 > x2) swap(x1, x2);
            if(y1 > y2) swap(y1, y2);
            partial[x2][y2] += k, partial[x2][y1 - 1] -= k; 
            partial[x1 - 1][y2] -= k, partial[x1 - 1][y1 - 1] += k;
        }
        for(int i = n; i >= 0; i--)
            for(int j = m; j >= 0; j--)
                partial[i][j] += partial[i][j + 1];
        for(int i = n; i >= 0; i--)
            for(int j = m; j >= 0; j--)
                partial[i][j] += partial[i + 1][j];
    }

    T get(int x, int y){
        return partial[x][y];
    }

    void print(){
        for(int i = 1; i <= n; i++, cout << "\n")
            for(int j = 1; j <= m && cout << partial[i][j] << " "; j++);
    }
};

// -------------------------- Matrix Power -----------------------------

template < typename T = int >  struct Matrix {

    // The matrix
    int N;
    vector < vector < T > > Mat;

    // Constructor to fill the matrix with this value
    Matrix(int n = 0, T val = 0) {
        N = n;
        Mat.assign(N, vector < T > (N, val));

    }

    // Constructor to make matrix with this 2D Vector
    Matrix(const vector < vector < T > > & b){
        N = b.size();
        Mat = b;
    }

    // Overloaded the = operator
    Matrix& operator = (const Matrix& b){
        Mat = b.Mat;
        N = b.Mat.size();
        return *this;
    }

    // Overloaded the = operator
    Matrix& operator = (const vector < vector < T > > & b){
        Mat = b;
        N = b.size();
        return *this;
    }

    // Overload the [][] operator
    vector < T >& operator[](T index) {
        return Mat[index];
    }

    // Overload the [][] operator
    const vector < T >& operator[](T index) const {
        return Mat[index];
    }

};

// Get Transition matrix
template < typename T = long long > Matrix < T > GetTrans(){
    vector < vector < T > > Trans = {
        {0, 1},
        {1, 1}
    };
    return Matrix < T > (Trans);
}

// Get the identity matrix
template < typename T = long long > Matrix < T > GetIdentity(const int N){
    vector < vector < T > > Identity(N, vector < T > (N));
    for(int i = 0; i < N; i++)
        Identity[i][i] = 1;
    return Matrix < T > (Identity);
}

// Get the zero matrix
template < typename T = long long > Matrix < T > GetZero(const int N){
    vector < vector < T > > Zero(N, vector < T > (N));
    return Matrix < T > (Zero);
}

// Overload the * operator
template < typename T = long long > Matrix < T > operator * (const Matrix < T >& a, const Matrix < T >& b){
    int N = a.N;
    Matrix res = GetZero(N);
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            for(int k = 0; k < N; k++)
                res[i][j] = add_mod(res[i][j], mul_mod(a[i][k], b[k][j], Mod), Mod);
    return res;
}

// Overload the *= operator
template < typename T = long long >  Matrix < T > operator *= (Matrix < T >& a, const Matrix < T >& b){
    a = a * b;
    return a;
}

// Overload the ^ operator
template < typename T = long long >  Matrix < T > Power(Matrix < T >& b, ll e){
    Matrix < T > Trans = GetTrans();
    while(e){
        if(e & 1) b *= Trans;
        Trans *= Trans;
        e >>= 1;
    }
    return b;
}

// Get the k-th term
template < typename T = long long > T k_th(T k, int N){
    // base case to change
    if(N <= 0) return 0;
    if(N <= 1) return 1;
    Matrix < T >  matrix = GetIdentity(N);
    matrix = Power(matrix, k + 1);
    return matrix[0][0];
}

// -------------------------- Binary Search Tree -----------------------------

struct BST {

    int data;
    BST *left, *right;

    BST(int data = 0){
        this -> data = data;
        left = right = nullptr;
    }

    // Insert New node

    BST* Insert(BST* root, int val){
        if(!root) return new BST(val);
        if(val > root -> data)
            root -> right = Insert(root -> right, val);
        else
            root -> left = Insert(root -> left, val);
        return root;
    }

    // Inorder Traverse (LRR)

    void Inorder(BST* root){
        if(!root) return;
        Inorder(root -> left);
        cout << root -> data << " ";
        Inorder(root -> right);
    }

    // Preorde Traverse (RLR)

    void Preorder(BST* root){
        if(!root) return;
        cout << root -> data << " ";
        Preorder(root -> left);
        Preorder(root -> right);
    }

    // Postorder Traverse (LRR)

    void Postorder(BST* root){
        if(!root) return;
        Postorder(root -> left);
        Postorder(root -> right);
        cout << root -> data << " ";

    }

    // Traverse each level

    void Level_Order(BST* root){
        if(!root) return;
        queue < BST* > bfs;
        bfs.push(root);
        while(!bfs.empty()){
            BST* curr = bfs.front();
            bfs.pop();
            cout << curr -> data << " ";
            if(curr -> left)
                bfs.push(curr -> left);
            if(curr -> right)
                bfs.push(curr -> right);
        }
    }

    // Search on a node

    bool Search(BST* root, int val){
        if(!root) return false;
        if(root -> data == val) return true;
        if(val > root -> data) return Search(root -> right, val);
        else return Search(root -> left, val);
    }

    // Get minimum node in BST

    BST* minValueNode(BST* node){
        BST* current = node;
        while (current && current -> left != nullptr) current = current -> left;
        return current;
    }

    // Get maximum node in BST

    BST* maxValueNode(BST* node){
        BST* current = node;
        while (current && current -> right != nullptr) current = current -> right;
        return current;
    }

    // Delete Node

    BST* Delete_Node(BST* root, int key){
        if(!root) return root;
        if(key < root -> data)
            root -> left = Delete_Node(root -> left, key);
        else if(key > root -> data)
            root -> right = Delete_Node(root -> right, key);
        else {
            if(!root -> left && !root -> right) return nullptr;
            else if(!root -> left){
                BST* temp = root -> right;
                free(root);
                return temp;
            }else if(!root -> right){
                BST* temp = root -> left;
                free(root);
                return temp;
            }
            BST* temp = minValueNode(root -> right);
            root -> data = temp -> data;
            root -> right = Delete_Node(root -> right, temp -> data);
        }
        return root;
    }
};

// -------------------------- Power inverse -----------------------------

template < typename T = int > struct Power_Inverse {
    
    T n, r, mod;
    vector < T > fact, inv;

    T fast_power(T b, T e, T MOD){
        T power = 1;
        while(e){
            if(e & 1) power = mod_combine(power, b, MOD);
            e >>= 1, b = mod_combine(b, b, MOD);
        }
        return power % MOD;
    }

    T Inverse(T N, T MOD){
        return fast_power(N, MOD - 2, MOD) % MOD;
    }

    Power_Inverse(T N, T R, T MOD){
        n = N, r = R, mod = MOD;
        fact.assign(n + 10, 1), inv.resize(n + 10, 1);
        for(ll i = 1; i <= n; i++){
            fact[i] = mod_combine(fact[i - 1], i, mod);
            inv[i] = Inverse(fact[i], mod);
        }
    }

    // Combination

    T nCr(){
        if(r > n) return 0ll;
        return (((fact[n] % mod) * (inv[r] % mod) % mod) * (inv[n - r] % mod)) % mod;
    }

    // Permutation

    T nPr(){
        if(r > n) return 0ll;
        return ((fact[n] % mod) * (inv[r] % mod)) % mod;
    }

};

// -------------------------- Math Functions -----------------------------

struct Math {

    Math(){}

    // Greatest common divisors between two numbers

    ll GCD(ll a, ll b){
        return (!b ? a : GCD(b, a % b));
    }
    
    // least common multiplication between two numbers

    ll LCM(ll a, ll b){
        return a / GCD(a, b) * b;
    }

    // Get vector with the prime factors of number

    vector < int > prime_factorization(ll n){
        vector < int > factors;
        while(n % 2 == 0) factors.push_back(2), n /= 2;
        for(int i = 3; i <= sqrt(n); i += 2)
            while(n % i == 0) factors.push_back(i), n /= i;
        if(n > 2) factors.push_back(n);
        return factors;
    }

    // Combination

    ll nCr(ll n, ll r){
        if(r > n) return 0;
        ll p = 1, k = 1;
        if (n - r < r) r = n - r;
        // condition for minimum choose
        if(n < 1) return 0;
        while (r > 0){
            p *= n, k *= r;
            ll m = __gcd(p, k);
            p /= m, k /= m, n--, r--;        
        }
        return p;
    }

    // Permutation

    ll nPr(ll n, ll r){
        if(r > n) return 0;
        ll npr = 1;
        while(r-- > 0)
            npr *= n--;
        return npr;
    }

    // get a mod for big int

    ll Big_Mod(string s, ll mod){
        ll res = 0;
        for(auto& c : s)
            res = (res * 10 + (c - '0')) % mod;
        return res;
    }

    // add two number and take mod for them

    void add(ll& a, ll b, ll mod = 1e9 + 7){
        a += b;
        if(a >= mod)
            a -= mod;
    }

    // multiply two number and take mod for them

    void mul(ll& a, ll b, ll mod = 1e9 + 7){
        a = ((a % mod) * (b % mod)) % mod;
    }

    // b power e in O(log(n))

    ll Bin_Pow(ll b, ll e){
        ll power = 1;
        while(e){
            if(e & 1) power *= b;
            e >>= 1;
            b *= b;
        }
        return power;
    }

    // b power e % mod in O(log(e))

    ll Bin_Pow(ll b, ll e, ll mod){
        ll power = 1;
        while(e){
            if(e & 1) mul(power, b, mod);
            e >>= 1;
            mul(b, b, mod);
        }
        return power % mod;
    }

    // b multiply e % mod in O(log(e))

    ll Bin_Mul(ll b, ll e, ll mod){
        b %= mod;
        ll mult = 0;
        while(e){
            if(e & 1) add(mult, b, mod);
            e >>= 1;
            add(b, b, mod);
        }
        return mult % mod;
    }

    // Check if number is prime or not

    bool is_prime(ll n){
        if(n < 2 || (n % 2 == 0 && n != 2)) return false;
        for(int i = 3; i <= sqrt(n); i += 2)
            if(n % i == 0) return false;
        return true;
    }

    // get the number of divisors for n

    int number_of_divisors(ll n){
        int divisors = 0;
        for(int i = 1; i < sqrt(n); i++)
            if(n % i == 0) divisors += 2;
        return divisors + (sqrt(n) == (int)sqrt(n));
    }

    // get Summation of divisors for n

    ll sum_of_divisors(ll n){
        ll sum_divisors = 0;
        for(int i = 1; i < sqrt(n); i++)
            if(n % i == 0) sum_divisors += ((n / i) + i);
        ll sq = sqrt(n);
        return sum_divisors + (sq * sq == n ? sq : 0);
    }
    
    // sum of divisor of number in range [1 ... n]
    ll divisorSum(ll num){
        ll sum = 0;
        for (ll i = 1; i <= sqrt(num); i++) {
            ll t1 = i * (num / i - i + 1);
            ll t2 = (((num / i) * (num / i + 1)) / 2) - ((i * (i + 1)) / 2);
            sum += t1 + t2;
        }
        return sum;
    }


    // get vector with the divisors for n

    vector < ll > Get_Divisors(ll n){
        vector < ll > divisors;
        for(int i = 1; i < sqrt(n); i++)
            if(n % i == 0) divisors.push_back(i), divisors.push_back(n / i);
        if(sqrt(n) == int(sqrt(n))) divisors.push_back(sqrt(n));
        return divisors;
    }

    // print all permutation of an array

    void Print_Permutation(vector < int >& nums){
        sort(all(nums));
        do {
            for(auto& i : nums)
                cout << i << " ";
            cout << "\n";
        } while(next_permutation(nums.begin(), nums.end()));
    }

    // print all permutation of a string

    void Print_Permutation(string s){
        sort(all(s));
        do {
            cout << s << "\n";
        } while(next_permutation(s.begin(), s.end()));
    }

    // get the summation between two numbers or the summation between 1 and n

    ll Summation(ll r, ll l = 0){
        if(l > r) swap(l, r);
        return (r * (r + 1) / 2) - (l * (l - 1) / 2);
    }

    // Get how many number divisable by c between a and b

    ll how_many_divisors(ll a, ll b, ll c){
        return (b / c) - ((a - 1) / c);
    }

    // Get summation of numbers divisable by c between a and b

    ll Summation_of_Devisors(ll a, ll b, ll c){
        ll right = Summation(b / c);
        ll left = Summation((a - 1) / c);
        return (right - left) * c;
    }

    // get logb(a)

    double get_log(ll a, int b){
        return log(a) / log(b);
    }

    // Check if number power of another or not

    bool is_power(ll number, int base = 2){
        return (get_log(number, base) - (ll) get_log(number, base) <= EPS);
    }

    // Distination Between two points

    double dist(double x1, double y1, double x2, double y2){
        return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    }

    // Check if it valid triangle with 3 length sides

    bool is_triangle(ll a, ll b, ll c){
        return (a + b > c) && (a + c > b) && (b + c > a) && (a && b && c);
    }

    // Get Slope of two points

    double slope(double x1, double y1, double x2, double y2){
        if(x2 == x1) return 0;
        return (y2 - y1) / (x2 - x1);
    }

    // Check if three points in the same line

    bool is_same_line(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3){
        return (y2 - y1) * (x3 - x1) == (y3 - y1) * (x2 - x1);
    }

    // Check if is perfect square

    bool is_perfect_square(ll n){
        ll sq = sqrt(n);
        return sq * sq == n;
    }

    // number of coprime witn n from 1 to n
    
    ll phi(ll n) {
        ll result = n;
        for (ll i = 2; i * i <= n; i++) {
            if (n % i == 0) {   
                while (n % i == 0)
                    n /= i;
                result -= result / i;
            }
        }
        if (n > 1)
            result -= result / n;
        return result;
    }

    // get the power of prime factor in n
    ll FactN_PrimePowers(ll n, ll p){
        ll powers = 0;
        for(ll i = p; i <= n; i *= p)
            powers += n / i;
        return powers;
    }

    // extended euclidean algorithm and diofantian equation
    int extended_gcd(int a, int b, int& x, int& y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        int x1, y1;
        int d = extended_gcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);
        return d;
    }
    
    bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
        g = extended_gcd(abs(a), abs(b), x0, y0);
        if (c % g) {
            return false;
        }
        x0 *= c / g;
        y0 *= c / g;
        if (a < 0) x0 = -x0;
        if (b < 0) y0 = -y0;
        return true;
    }

    // Convert Decimal to any base

    string decimal_to_any_base(ll decimal, ll base){
        if(decimal == 0) return "0";
        string num = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string result;
        do{
            result.push_back(num[decimal % base]);
            decimal /= base;
        }while(decimal != 0);
        return string(result.rbegin(), result.rend());
    }
    
    // Convert any base to decimal

    ll  any_base_to_decimal(string str, int base) {
        auto val = [](char c){
            return (c >= '0' && c <= '9' ? (int) c - '0' : (int) c - 'A' + 10);
        };
        ll len = sz(str), power = 1, num = 0, i;
        for (i = len - 1; i >= 0; i--) {
            num += val(str[i]) * power;
            power = power * base;
        }
        return num;
    }

};

// -------------------------- LCA Weighted -----------------------------

template < typename T = int > struct LCA {
    
    struct Edge {

        T v, w;

        Edge(T V = 0, T W = 0) : v(V), w(W) {}

        bool operator < (const Edge &rhs) const {
            return w < rhs.w;
        }

    };

    int N, LOG;
    vector < vector < T > > anc, cost;
    vector < vector < Edge > > adj;
    vector < int > dep;
    
    LCA(int n){
        N = n + 10, LOG = 0;
        while((1 << LOG) <= N) LOG++;
        dep = vector < int > (N);
        adj = vector < vector < Edge > > (N);
        anc = cost = vector < vector < T > > (N, vector < T > (LOG));
    }
    
    void add_edge(int u, int v, T w){
        adj[u].push_back(Edge(v, w));
        adj[v].push_back(Edge(u, w));
    }

    void build_adj(int edges){
        for(int i = 0, u, v, w; i < edges && cin >> u >> v >> w; i++)
            add_edge(u, v, w);
    }

    T operation(T a, T b){
        return a + b;
    }
    
    void dfs(int u, int p = 0){
        for(auto& [v, w] : adj[u]){
            if(v == p) continue;
            dep[v] = dep[u] + 1, anc[v][0] = u, cost[v][0] = w;
            for(int bit = 1; bit < LOG; bit++){
                anc[v][bit] = anc[anc[v][bit - 1]][bit - 1];
                cost[v][bit] = operation(cost[v][bit - 1], cost[anc[v][bit - 1]][bit - 1]);
            }
            dfs(v, u);
        }
    }
    
    int kth_ancestor(int u, int k){
        if(dep[u] < k) 
            return -1;
        for(int bit = LOG - 1; bit >= 0; bit--)
            if(k & (1 << bit))
                u = anc[u][bit];
        return u;
    }
    
    int get_lca(int u, int v){
        if(dep[u] < dep[v])
            swap(u, v);
        u = kth_ancestor(u, dep[u] - dep[v]);
        if(u == v)
            return u;
        for(int bit = LOG - 1; bit >= 0; bit--)
            if(anc[u][bit] != anc[v][bit])
                u = anc[u][bit], v = anc[v][bit];
        return anc[u][0];
    }
    
    T get_cost(int u, int dist){
        if(dep[u] < dist) return -1;
        T ans = 0;
        for(int bit = 0; bit < LOG; bit++)
            if(dist & (1 << bit))
                ans = operation(ans, cost[u][bit]), u = anc[u][bit];
        return ans;
    }
    
    T query(int u, int v){
        int lca = get_lca(u, v);
        return operation(get_cost(u, dep[u] - dep[lca]), get_cost(v, dep[v] - dep[lca]));
    }

    void build(int root = 1){
        dfs(root);
    }

};

// -------------------------- LCA -----------------------------

template < typename T = int > struct LCA {
    
    int N, LOG;
    vector < vector < T > > anc;
    vector < vector < T > > adj;
    vector < int > dep;
    
    LCA(int n = 0){
        N = n + 10, LOG = 0;
        while((1 << LOG) <= N) LOG++;
        dep = vector < int > (N);
        adj = vector < vector < T > > (N);
        anc = vector < vector < T > > (N, vector < T > (LOG));
    }

    LCA(int n, const vector < vector < T > > &G) : adj(G){ 
        N = n + 10, LOG = 0;
        while((1 << LOG) <= N) LOG++;
        dep = vector < int > (N);
        anc = vector < vector < T > > (N, vector < T > (LOG));
    }

    void add_edge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build_adj(int edges){
        for(int i = 0, u, v; i < edges && cin >> u >> v; i++)
            add_edge(u, v);
    }

    void dfs(int u, int p = 0){
        for(auto& v : adj[u]){
            if(v == p) continue;
            dep[v] = dep[u] + 1, anc[v][0] = u;
            for(int bit = 1; bit < LOG; bit++)
                anc[v][bit] = anc[anc[v][bit - 1]][bit - 1];
            dfs(v, u);
        }
    }
    
    int kth_ancestor(int u, int k){
        if(dep[u] < k) 
            return -1;
        for(int bit = LOG - 1; bit >= 0; bit--)
            if(k & (1 << bit))
                u = anc[u][bit];
        return u;
    }
    
    int get_lca(int u, int v){
        if(dep[u] < dep[v])
            swap(u, v);
        u = kth_ancestor(u, dep[u] - dep[v]);
        if(u == v)
            return u;
        for(int bit = LOG - 1; bit >= 0; bit--)
            if(anc[u][bit] != anc[v][bit])
                u = anc[u][bit], v = anc[v][bit];
        return anc[u][0];
    }

    T query(int u, int v){
        int lca = get_lca(u, v);
        return dep[u] + dep[v] - 2 * dep[lca];
    }

    void build(int root = 1){
        dfs(root);
    }

};

// -------------------------- Graph  Representation -----------------------------

#define adj_loop(u, v, e) for(int e = head[u], v; ~e && (v = edges[e].to, 1); e = edges[e].nxt)

template < typename T = int > struct edgeData {

    T to, nxt, cost;

    edgeData(T TO = 0, T NXT = 0, T COST = 0) : to(TO), nxt(NXT), cost(COST) {}

};

int edge_count;
vector < edgeData < int > > edges;
vector < int > head;

void init(int n, int m){
    edges = vector < edgeData < int > > (2 * m + 5);
    head = vector < int > (n + 5, -1);
    edge_count = 1;
}

void addEdge(int u, int v, int c = 0){
    edges[edge_count].to = v;
    edges[edge_count].cost = c;
    edges[edge_count].nxt = head[u];
    head[u] = edge_count++;
}

void AddBiEdge(int u, int v, int c = 0){
    addEdge(u, v, c);
    addEdge(v, u, c);
}

// -------------------------- Graph -----------------------------

struct Graph {

    int n, m, connected_components;
    vector < vector < int > > adj;
    vector < bool > vis;
    vector < int > depth, parent, deg, colour;
    
    Graph(int N, int M){
        n = N, m = M;
        connected_components = 0;
        adj = vector < vector < int > > (n + 10);
        vis = vector < bool > (n + 10, false);
        depth = deg = colour = vector < int > (n + 10, 0);
        parent = vector < int > (n + 10, -1);
    }

    void add_edge(int u, int v, bool is_directed = false){
        adj[u].push_back(v), deg[u]++; 
        if(!is_directed) 
            adj[v].push_back(u), deg[v]++;
    }

    void remove_edge(int u, int v){
        adj[u].erase(find(all(adj[u]), v)), adj[v].erase(find(all(adj[v]), u));
    }

    void build_adj(bool is_directed = false){
        for(int i = 0, u, v; i < m && cin >> u >> v; i++)
            add_edge(u, v, is_directed);
    }

    void dfs(int node, int dep = 0, int par = -1){
        vis[node] = true, parent[node] = par, depth[node] = dep;
        for(auto& new_node : adj[node])
            if(!vis[new_node])
                dfs(new_node, dep + 1, node);
    }

    bool is_cycle(int node, int par){
        vis[node] = true;
        for(auto& new_node : adj[node]){
            if(!vis[new_node]){
                if(is_cycle(new_node, node))
                    return true;
            }
            else if(new_node != par)
                return true;
        }
        return false;
    }

    void get_path(int node){
        if(parent[node] == node) return;
        cout << node << " ";
        get_path(parent[node]);
    }

    void topology (){
        queue < int > topo;
        vector < int > graph;
        for(int i = 1; i <= n; i++)
            if(deg[i] == 1) topo.push(i), deg[i]--;
        while(!topo.empty()){
            int curr_node = topo.front();
            topo.pop();
            graph.push_back(curr_node);
            for(auto& new_node : adj[curr_node]){
                deg[new_node]--;
                if(deg[new_node] == 1)
                    topo.push(new_node);
            }
        }
        reverse(all(graph));
        cout << graph << "\n";
    }

    int bfs(int from, int to){
        if(from == to) return 0;
        queue < int > BFS;
        depth.assign(n + 10, OO);
        vis[from] = true, depth[from] = 0;
        BFS.push(from);
        while(!BFS.empty()){
            int sz = sz(BFS);
            while(sz--){
                int curr_node = BFS.front();
                BFS.pop();
                for(auto& new_node : adj[curr_node]){
                    if(!vis[new_node]){
                        BFS.push(new_node), parent[new_node] = curr_node; 
                        depth[new_node] = min(depth[new_node], depth[curr_node] + 1);
                        vis[new_node] = true;
                    }
                }
            }
        }
        return depth[to];
    }

    bool is_Bipartite(int u){
        for(auto v : adj[u]){
            if(colour[v] == colour[u])
                return false;
            else if(colour[v] == 0){
                colour[v] = -colour[u];
                if(!is_Bipartite(v)){
                    return false;
                }
            }
        }
        return true;
    }
    
    bool is_Bipartite(){
        for(int i = 1; i <= n; i++){
            if(colour[i] == 0) {
                colour[i] = -1;
                if(!is_Bipartite(i))
                    return false;
            }
        }
        return true;
    }

};

// -------------------------- KMP -----------------------------

struct KMP {

    vector < int > Compute_Prefix(string pat){
        vector < int > longest_prefix(sz(pat));
        for(int i = 0, k; i < sz(pat); i++){
            while(k > 0 && pat[k] != pat[i])
                k = longest_prefix[k - 1];
            if(pat[k] == pat[i]) k++;
            else k = longest_prefix[k - 1];
        }
        return longest_prefix;
    }

    KMP(string str, string pat){
        vector < int > longest_prefix = Compute_Prefix(pat);
        for(int i = 0, k; i < sz(str); i++){
            while(k > 0 && pat[k] != str[i])
                k = longest_prefix[k - 1];
            if(pat[k] == str[i]) k++;
            if(k == sz(pat))
                k = longest_prefix[k - 1];
        }
    }
};

// -------------------------- Fenwick Tree -----------------------------

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

// -------------------------- Fenwick Tree 2D -----------------------------

template < typename T = int > struct Fenwick_Tree {
    
    vector < vector < T > > Tree;
    int n, m;
    T DEFAULT;

    Fenwick_Tree(int rows = 0, int cols = 0){
        n = rows + 1, m = cols + 1, DEFAULT = 0;
        Tree.assign(n + 10, vector < ll > (m + 10, DEFAULT));
    }

    int lowest_bit(int idx){
        return (idx & -idx);
    }

    void build(vector < vector < T > >& nums){
        for(int i = 0; i < sz(nums); i++)
            for(int j = 0; j < sz(nums[0]); j++)
                add(i + 1, j + 1, nums[i][j]);
    }

    T operation(T a, T b){
        return a + b;
    }

    void add(int idx, int jdx, T val){
        int i = idx + 1, j = jdx + 1;
        while(i <= n){
            j = jdx + 1;
            while(j <= m){
                Tree[i][j] = operation(Tree[i][j], val);
                j += lowest_bit(j);    
            }
            i += lowest_bit(i);
        }
    }

    T get_sum(int idx, int jdx){
        T sum = DEFAULT;
        int i = idx + 1, j = jdx + 1;
        while(i){
            j = jdx + 1;
            while(j){
                sum = operation(sum, Tree[i][j]);
                j -= lowest_bit(j);    
            }
            i -= lowest_bit(i);
        }
        return sum;
    }

    // Get the sum of the number in the rectangle x1, y1, x2, y2

    T query(int x1, int y1, int x2, int y2) {
        if(x1 > x2) swap(x1, x2);
        if(y1 > y2) swap(y1, y2);
        return get_sum(x2, y2) - get_sum(x1 - 1, y2) - get_sum(x2, y1 - 1) + get_sum(x1 - 1, y1 - 1);
    }

};

// -------------------------- Fenwick Tree Range -----------------------------

template < typename T = int > struct Fenwick_Tree_Range {
    
    int N;
    T DEFAULT;
    vector < T > M, C;

    Fenwick_Tree_Range(int sz = 0){
        N = sz + 1, DEFAULT = 0;
        M = C = vector < T > (N + 10);
    }

    int lowest_bit(int idx){
        return (idx & -idx);
    }

    void build(vector < T >& nums){
        for(int i = 0; i < sz(nums); i++)
            add(i, i, nums[i]);
    }

    void add_range(int idx, T addM, T addC){
        idx++;
        while(idx <= N){
            M[idx] += addM;
            C[idx] += addC;
            idx += lowest_bit(idx);
        }
    }

    void add(int l, int r, T val) {
        add_range(l, val, -val * (l - 1));
        add_range(r + 1, -val, val * r);
    }

    T get(int idx){
        T ans = DEFAULT;
        int pos = idx++;
        while(idx){
            ans += pos * M[idx] + C[idx];
            idx -= lowest_bit(idx);
        }
        return ans;
    }

    T query(int L, int R){
        if(L > R) return DEFAULT;
        return get(R) - get(L - 1);
    }
};

// -------------------------- Seive Prime Factorization -----------------------------

// Vector to store smallest prime factor of numbers from 1 to N.
vector < int > SPF;

// Vector to store prime factors of numbers from 1 to N.
vector < vector < int > > primeFactors;

// Function to calculate prime factors of a number.
vector < int > PrimeFactors(int x){
    vector < int > ret;
    while(x > 1){
        ret.push_back(SPF[x]);
        x /= SPF[x];
    }
    return ret;
}

// Function to calculate smallest prime factors of numbers from 1 to N using Sieve of Eratosthenes.
void Seive(int N){
    // Initializing vector SPF to store smallest prime factor of numbers from 1 to N.
    SPF = vector < int > (N + 5);

    // Initializing vector primeFactors to store prime factors of numbers from 1 to N.
    primeFactors = vector < vector < int > > (N + 5);

    // Initializing SPF vector with i for all numbers.
    for(int i = 1; i <= N; i++)
        SPF[i] = i;

    // Updating SPF vector for even numbers.
    for(int i = 2; i <= N; i += 2)
        SPF[i] = 2;

    // Updating SPF vector for odd numbers.
    for(int i = 3; i * i <= N; i++){
        if(SPF[i] == i){
            for(int j = i * i; j <= N; j += i)
                if(SPF[j] == j)
                    SPF[j] = i;
        }
    }

    // Calculating prime factors of numbers from 1 to N.
    for(int i = 1; i <= N; i++)
        primeFactors[i] = PrimeFactors(i);
}

// -------------------------- Seive Factorization -----------------------------

struct Factorization {
    
    int n;
    vector < int > factors_cnt, prime_factors_cnt;
    vector < vector < int > > factors, prime_factors;

    Factorization(int N){
        n = N;
        factors_cnt = vector < int > (n + 5, 2);
        prime_factors_cnt = vector < int > (n + 5);
        factors = vector < vector < int > > (n + 5);
        prime_factors = vector < vector < int > > (n + 5);
        factorization(n);
        prime_factorization(n);
    }

    // Get the number of factors for each number
    void factorization(){ 
        factors_cnt[0] = 0, factors_cnt[1] = 1;
        for (int i = 2; i <= n; i++)  
            for (int j = i + i; j <= n; j += i){
                factors_cnt[j]++;
                factors[j].push_back(i);
            }
    }

    // get the number of factors of n
    int get_factors(int x){
        return factors_cnt[x];
    }

    // get the factors of n
    vector < int > get_factors(){
        return factors[n];
    }

    // Get the number of prime factors for each number
    void prime_factorization(){
        for (int i = 2; i <= n; i++){ 
            if (!prime_factors[i]) {
                for (int j = i; j <= n; j += i){ 
                    prime_factors[j]++;
                    prime_factors[j].push_back(i);
                }
            }
        }
    }

    // get the number of prime factors of n
    int get_prime_factors(int x){
        return prime_factors[x];
    }

    // get the prime factors of n
    vector < int > get_prime_factors(int x){
        return prime_factors[x];
    }
};

// -------------------------- Monotonic Deque -----------------------------

template < typename T = int > struct Monotonic_Stack {
    
    vector < T > st, Monotonic;
    T DEFAULT = 0;

    Monotonic_Stack() {
        Monotonic = { DEFAULT }, st = { };
    }

    static T operation(T a, T b){
        return max(a, b);
    }

    void push(T x){
        st.emplace_back(x);
        Monotonic.push_back(operation(Monotonic.back(), x));
    }

    T pop(){
        T res = st.back();
        st.pop_back();
        Monotonic.pop_back();
        return res;
    }
    
    bool empty(){
        return st.empty();
    }
    
    T top(){
        return st.back();
    }

    T Monotonic_val(){
        return Monotonic.back();
    }

    int size(){
        return st.size();
    }

};

template < typename T = int > struct Monotonic_Queue {

    Monotonic_Stack < T > s1, s2;

    Monotonic_Queue () {
        s1 = Monotonic_Stack < T > (), s2 = Monotonic_Stack < T > ();
    }

    void push(T x){
        s2.push(x);
    }

    void pop(){
        if(s1.empty()){
            while(!s2.empty())
                s1.push(s2.pop());
        }
        s1.pop();
    }

    T monotonic_val(){
        return Monotonic_Stack < T > ::operation(s1.Monotonic_val(), s2.Monotonic_val());
    }

    bool is_good(){
        return monotonic_val() == 1;
    }

    bool empty(){
        return s1.empty() && s2.empty();
    }

    int size(){
        return s1.size() + s2.size();
    }

};

// -------------------------- Monotonic Stacks -----------------------------

struct Monotonic_Stacks {

    Monotonic_Stacks(){ }

    template < typename T = int > vector < T > nextGreaterelement(vector < T >& nums) {
        int n = nums.size();
        vector < T > res(n);
        stack < int > st;
        for(int i = n - 1; i >= 0; i--){
            while(!st.empty() && nums[st.top()] <= nums[i]) st.pop();
            res[i] = (st.empty() ? n : st.top());
            st.push(i);
        }
        return res;
    }
    
    template < typename T = int > vector < T > prevGreaterelement(vector < T >& nums) {
        int n = nums.size();
        vector < T > res(n);
        stack < int > st;
        for(int i = 0; i < n; i++){
            while(!st.empty() && nums[st.top()] <= nums[i]) st.pop();
            res[i] = (st.empty() ? 0 : st.top());
            st.push(i);
        }
        return res;
    }

    template < typename T = int > vector < T > nextSmallerelement(vector < T >& nums) {
        int n = nums.size();
        vector < T > res(n);
        stack < int > st;
        for(int i = n - 1; i >= 0; i--){
            while(!st.empty() && nums[st.top()] >= nums[i]) st.pop();
            res[i] = (st.empty() ? n : st.top());
            st.push(i);
        }
        return res;
    }
    
    template < typename T = int > vector < T > prevSmallerelement(vector < T >& nums) {
        int n = nums.size();
        vector < T > res(n);
        stack < int > st;
        for(int i = 0; i < n; i++){
            while(!st.empty() && nums[st.top()] >= nums[i]) st.pop();
            res[i] = (st.empty() ? 0 : st.top());
            st.push(i);
        }
        return res;
    }

};

// -------------------------- SQRT Decomposition -----------------------------

template < typename T = int, int Base = 0 > struct Sqrt_Decomp {

    int n, len;
    vector < T > a; 
    vector < vector < T > > b;
    T U_Default, Q_Default;

    // calculate the length of each block
    T calc_sq(int N){
        int sq = sqrt(N);
        return sq * sq == N ? sq : sq + 1;
    }

    Sqrt_Decomp(int N = 0){
        n = N, len = calc_sq(n), U_Default = 0, Q_Default = 0;
        a = vector < T > (n + 5, U_Default);
        b = vector < vector < T > > (len + 5);
    }

    Sqrt_Decomp(int N, const vector < T >& vec){
        n = N, len = calc_sq(n), U_Default = 0, Q_Default = 0;
        a = vec;
        b = vector < vector < T > > (len + 5);
        build();
    }

    // build each block
    void build(){
        for(int i = 1; i <= n; i++)
            b[i / len].push_back(a[i - !Base]);
        for(int i = 0; i <= len; i++)
            sort(all(b[i]));
    }

    // just update this index in the block O(1)
    void update(int idx, T val){
        int idx2 = lower_bound(all(b[idx / len]), a[idx - !Base]) - b[idx / len].begin();
        b[idx / len][idx2] = a[idx - !Base] = val;
        sort(all(b[idx / len]));
    }

    // re-calculate the block again O(sqrt(n))
    void update_range(int idx, T val){
        a[idx - !Base] = val;
        b[idx / len].clear();
        for(int i = idx / len * len; i < min(n, (idx / len + 1) * len); i++)
            b[idx / len].push_back(a[i - !Base]);
        sort(all(b[idx / len]));
    }

    // query on the range from L to R
    T query(int l, int r, T x){
        T res = Q_Default;
        while(l < r && l % len != 0)
            res += a[l++ - !Base] >= x;
        while(l + len <= r){
            res += sz(b[l / len]) - (lower_bound(all(b[l / len]), x) - b[l / len].begin());
            l += len;
        }
        while(l <= r)
            res += a[l++ - !Base] >= x;
        return res;
    }
};

// -------------------------- Sparse Table -----------------------------

template < typename T = int , int Base = 0 > struct Sparse_Table {

    struct Node {

        T val;

        Node(T V = 0) : val(V) {}
    
        Node operator = (const T& rhs) {
            val = rhs;
            return *this;
        }

    };

    int n, LOG;
    vector < vector < Node > > table;
    vector < int > Bin_Log;
    Node DEFAULT;

    Sparse_Table(const vector < T >& vec){
        n = sz(vec) - Base, DEFAULT = INF, LOG = __lg(n) + 1;
        table = vector < vector < Node > > (n + 10, vector < Node > (LOG));
        Bin_Log = vector < int > (n + 10);
        for(int i = 2; i <= n; i++)
            Bin_Log[i] = Bin_Log[i >> 1] + 1;
        for(int i = 1; i <= n; i++)
            table[i][0] = vec[i - !Base];
        Build_Table();
    }

    Node operation(const Node& a, const Node& b){
        return a.val < b.val ? a : b;
    }

    void Build_Table(){
        for(int log = 1; log < LOG; log++)
            for(int i = 1; i + (1 << log) - 1 <= n; i++)
                table[i][log] = operation(table[i][log - 1], table[i + (1 << (log - 1))][log - 1]);
    }

    Node query_1(int L, int R){
        int log = Bin_Log[R - L + 1];
        return operation(table[L][log], table[R - (1 << log) + 1][log]);
    }

    Node query_log_n(int L, int R){
        Node answer = DEFAULT;
        for (int log = LOG; log >= 0; log--){
            if (L + (1 << log) - 1 <= R) {
                answer = operation(answer, table[L][log]);
                L += 1 << log;
            }
        }
        return answer;
    }

    T query(int L, int R, bool overlap = false){
        return (!overlap ? query_1(L, R) : query_log_n(L, R)).val;
    }

};

// -------------------------- Queue wit Stacks -----------------------------

struct Stack {
    
    vector < ll > s, GCD;
    
    Stack() {
        GCD = {0}, s = {};
    }

    void push(ll x){
        s.emplace_back(x);
        GCD.push_back(__gcd(GCD.back(), x));
    }

    ll pop(){
        ll res = s.back();
        s.pop_back();
        GCD.pop_back();
        return res;
    }
    
    bool empty(){
        return s.empty();
    }
    
    ll GCD_val(){
        return GCD.back();
    }

};

struct Queue_with_Stack {

    Stack s1, s2;

    Queue_with_Stack () {
        s1 = Stack(), s2 = Stack();
    }

    void push(ll x){
        s2.push(x);
    }

    void pop(){
        if(s1.empty())
            while(!s2.empty())
                s1.push(s2.pop());
        s1.pop();
    }

    bool is_good(){
        return __gcd(s1.GCD_val(), s2.GCD_val()) == 1;
    }

};

// -------------------------- Mancher's Algorithm -----------------------------

string longestPalSubstring(string& s){
    int strLen = 2 * sz(s) + 3, maxLen = 0, start = 0, maxRight = 0 ,center = 0;
    string str = "@#";
    for (char& c : s)
        str.push_back(c), str.push_back('#');
    str.push_back('$');
    vector < int > p(strLen);
    for(int i = 1; i < strLen - 1; i++){
        if (i < maxRight)
            p[i] = min(maxRight - i, p[2 * center - i]);
        while (str[i + p[i] + 1] == str[i - p[i] - 1]) p[i]++;
        if (i + p[i] > maxRight)
            center = i, maxRight = i + p[i];
        if (p[i] > maxLen)
            start = (i - p[i] - 1) / 2, maxLen = p[i];
    }
    return s.substr(start, maxLen);
}

// -------------------------- Prim MST -----------------------------

template < typename T = int > struct Prim {

    struct Edge {

        T v, w;

        Edge(T V = 0, T W = 0) : v(V), w(W) {}

        bool operator < (const Edge &e) const {
            return w < e.w;
        }

    };

    vector < vector < Edge > > adj;
    vector < T > marked;

    Prim(int n = 0){
        adj = vector < vector < Edge > > (n + 10);
        marked = vector < T > (n + 10, 0);
    }

    void build_adj(int edges, bool is_directed = false){
        for(int i = 0, u, v, w; i < edges && cin >> u >> v >> w; i++){
            adj[u].push_back(Edge(v, w));
            if(!is_directed)
                adj[v].push_back(Edge(u, w));
        }
    }

    T get_cost(int root){
        T cost = 0;
        priority_queue < Edge > pq;
        pq.push(Edge(root, 0));
        while(!pq.empty()){
            auto [u, curr_cost] = pq.top();
            pq.pop();
            // Checking for cycle
            if(marked[u]) continue;
            marked[u] = true;
            cost += curr_cost;
            for(auto& [v, w] : adj[u]){
                if(!marked[v])
                    pq.push(Edge(v, w));
            }
        }
        return cost;
    }
};

// -------------------------- Disjoint Set Union -----------------------------

template < typename T = int, int Base = 1 > struct DSU {
    
    vector < T > parent, Gsize, nxt, tail, pos, roots;

    DSU(int MaxNodes){
        parent = Gsize = roots = tail = pos = nxt = vector < T > (MaxNodes + Base);
        for(int i = Base; i < MaxNodes + Base; i++){
            parent[i] = roots[i] = pos[i] = tail[i] = i;
            nxt[i] = -1, Gsize[i] = 1;
        }
    }
    
    T find_leader(int node){
        return parent[node] = (parent[node] == node ? node : find_leader(parent[node]));
    }

    bool is_same_sets(int u, int v){
        return find_leader(u) == find_leader(v);
    }

    void union_sets(int u, int v){
        int leader_u = find_leader(u), leader_v = find_leader(v);
        if(leader_u == leader_v) return;
        // make leader_u is the leader with the larger component
        if(Gsize[leader_u] < Gsize[leader_v]) 
            swap(leader_u, leader_v);
        int p = pos[leader_v];
        Gsize[leader_u] += Gsize[leader_v];
        parent[leader_v] = leader_u;
        roots[p] = roots.back();
        pos[roots[p]] = p;
        roots.pop_back();
        nxt[tail[leader_u]] = leader_v;
        tail[leader_u] = tail[leader_v];
    }

    void print(){
        for(int root = Base; root < sz(roots); root++){
            for(int u = roots[root]; ~u ; u = nxt[u])
                cout << u << " \n"[!~nxt[u]];
        }
    }

    int get_size(int u){
        return Gsize[find_leader(u)];
    }

    int get_components_number(){
        return sz(roots) - Base;
    }
};

// -------------------------- Dijkstra -----------------------------

template < typename T = int > struct Dijkstra {
    
    struct Edge {

        T v, w;
        
        Edge(T V = 0, T W = 0): v(V), w(W) {}
        
        bool operator < (const Edge& e) const {
            return w > e.w;
        }
    };

    vector < vector < Edge > > adj;

    Dijkstra(int edges, bool indirected = true){
        adj = vector < vector < Edge > > (edges);
        for(int i = 0, u, v, w; i < edges; i++){
            cin >> u >> v >> w;
            adj[u].push_back(Edge(v, w));
            if(indirected)
                adj[v].push_back(Edge(u, w));
        }
    }

    T Min_Cost(int src, int dest){
        int n = sz(adj);
        vector < T > dist(n, LLONG_MAX);
        dist[src] = 0;
        priority_queue < Edge > Dij;
        Dij.push(Edge(src, 0));
        while(!Dij.empty()){
            auto [u, cost] = Dij.top();
            Dij.pop();
            for(auto& [v, w] : adj[u]){
                if(dist[v] > dist[u] + w){
                    dist[v] = dist[u] + w;
                    Dij.push(Edge(v, dist[v]));
                }
            }
        }
        return (dist[dest] == LLONG_MAX ? -1 : dist[dest]);
    }

    vector < T > get_dist(int src){
        int n = sz(adj);
        vector < T > dist(n, LLONG_MAX);
        dist[src] = 0;
        priority_queue < Edge > Dij;
        Dij.push(Edge(src, 0));
        while(!Dij.empty()){
            auto [u, cost] = Dij.top();
            Dij.pop();
            for(auto& [v, w] : adj[u]){
                if(dist[v] > dist[u] + w){
                    dist[v] = dist[u] + w;
                    Dij.push(Edge(v, dist[v]));
                }
            }
        }
        return dist;
    }
};

// -------------------------- Floyd -----------------------------

template < typename T = int > struct Floyd {

    struct Edge {
        
        ll u, v, w;
        
        Edge(int U = 0, int V = 0, int W = 0){
            u = U, v = V, w = W;
        }

        bool operator < (const Edge& e) const {
            return w < e.w;
        }

    };

    int n, m;
    vector < vector < T > > dist;
    vector < Edge > edges;
    T DEFAULT;

    Floyd(int N, int M){
        n = N, m = M, DEFAULT = 1e18;
        dist.assign(n + 10, vector < T > (n + 10, DEFAULT));
        edges.resize(m);
    }

    T operation(T a, T b, T c){
        return min(a, b + c);
    }

    void Get_Data(){
        for(auto& e : edges){
            cin >> e.u >> e.v >> e.w;
            dist[e.u][e.u] = dist[e.v][e.v] = 0;
            dist[e.u][e.v] = dist[e.v][e.u] = min({dist[e.u][e.v], dist[e.v][e.u], e.w});
        }
    }

    void Build_Dist(){
        for(int i = 1; i <= n; i++)
            for(int u = 1; u <= n; u++)
                for(int v = 1; v <= n; v++)
                    dist[u][v] = operation(dist[u][v], dist[u][i], dist[i][v]);
    }

};

// -------------------------- Kadane -----------------------------

template < typename T = int > struct Kadane {
    
    // Minimum Contigours Subarray Sum

    Kadane(){};

    T Min_Subarray_Sum(vector < T >& nums){
        T Min_so_far = OO, Min_Curr = 0, DEFAULT = 0;
        for(auto& i : nums){
            Min_Curr += i;
            Min_so_far = min(Min_so_far, Min_Curr);
            Min_Curr = min(Min_Curr, DEFAULT);
        }
        return Min_so_far;
    }

    // Maximum Contigours Subarray Sum

    T Max_Subarray_Sum(vector < T >& nums){
        T Max_so_far = -OO, Max_Curr = 0, DEFAULT = 0;
        for(auto& i : nums){
            Max_Curr += i;
            Max_so_far = max(Max_so_far, Max_Curr);
            Max_Curr = max(Max_Curr, DEFAULT);
        }
        return Max_so_far;
    }

};

// -------------------------- Coordinate Compression -----------------------------

template < typename T = int > struct Coordinate_Compression {

    vector < T > compressed;
    bool is_build = true;

    Coordinate_Compression(){}

    Coordinate_Compression(vector < T > &vec) {
        compressed = vec;
        build();
    }

    void add(T x) {
        compressed.push_back(x);
        is_build = false;
    }

    void build() {
        sort(all(compressed));
        compressed.resize(unique(all(compressed)) - compressed.begin());
        is_build = true;
    }

    T get(T x) {
        if(!is_build) build();
        return upper_bound(all(compressed), x) - compressed.begin();
    }

    vector < T > get_compressed(vector < T > &vec) {
        if(!is_build) build();
        vector < T > ret;
        for (auto &x : vec) 
            ret.push_back(get(x));
        return ret;
    }

    vector < T > get_mapping(vector < T > &vec) {
        if(!is_build) build();
        vector < T > ret(sz(compressed) + 5);
        for (auto &x : vec)
            ret[get(x)] = x;
        return ret;
    }

    int size(){
        if(!is_build) build();
        return sz(compressed);
    }

};

// -------------------------- MO Tree -----------------------------

template < typename T = int > struct MO_Tree {

    static inline int64_t gilbertOrder(int x, int y, int pow, int rotate) {
        if (pow == 0) return 0;
        int hpow = 1 << (pow - 1);
        int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
        seg = (seg + rotate) & 3;
        const int rotateDelta[4] = {3, 0, 0, 1};
        int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
        int nrot = (rotate + rotateDelta[seg]) & 3;
        int64_t subSquareSize = int64_t(1) << (2 * pow - 2);
        int64_t ordd = seg * subSquareSize;
        int64_t add = gilbertOrder(nx, ny, pow - 1, nrot);
        ordd += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
        return ordd;
    }

    struct query {

        int l, r, lca, query_idx;
        int64_t ord;

        query(vector < T > &S, vector < T > &E, int L = 0, int R = 0, int Query_idx = 0, int LCA = 0){
            if(S[L] > S[R])
                swap(L, R);
            if(LCA == L)
                l = S[L], r = S[R], lca = -1, query_idx = Query_idx;
            else
                l = E[L], r = S[R], lca = LCA, query_idx = Query_idx;
            calcOrder();
        }

        query() {}

        inline void calcOrder() {
            constexpr int K = 19;
            // K should be minimum such that 2^K >= n
            ord = gilbertOrder(l, r, K, 0);
        }

        bool operator < (const query & rhs) const {
            return ord < rhs.ord;
        }
    };

    T curr_l, curr_r, ans, n, m, Sqrt_N, timer, LOG;
    vector < T > answers, val;
    vector < vector < T > > adj, anc;
    vector < T > dep, S, E, FT, node_freq;
    vector < query > queries;

    MO_Tree() { }
    
    MO_Tree(int N, int M, vector < vector < T > > &G, vector < T >& V, int root = 1){
        
        curr_l = 1, curr_r = 0, ans = 0, n = N, m = M, Sqrt_N = sqrt(n);
        LOG = 0, timer = 1;

        while((1 << LOG) <= n) LOG++;
        
        queries = vector < query > (m);
        answers = vector < T > (m);
        node_freq = S = E = dep = vector < T > (n + 5);
        FT = vector < T > (2 * n + 5);
        anc = vector < vector < T > > (n + 5, vector < T > (LOG));
        adj = G, val = V;

        dfs(root);
    }

    void dfs(int u, int p = -1){
        S[u] = timer;
        FT[timer++] = u;
        for(auto& v : adj[u]){
            if(v == p) continue;
            dep[v] = dep[u] + 1, anc[v][0] = u;
            for(int bit = 1; bit < LOG; bit++)
                anc[v][bit] = anc[anc[v][bit - 1]][bit - 1];
            dfs(v, u);
        }
        E[u] = timer;
        FT[timer++] = u;
    }

    int kth_ancestor(int u, int k){
        if(dep[u] < k) 
            return -1;
        for(int bit = LOG - 1; bit >= 0; bit--)
            if(k & (1 << bit))
                u = anc[u][bit];
        return u;
    }
    
    int get_lca(int u, int v){
        if(dep[u] < dep[v])
            swap(u, v);
        u = kth_ancestor(u, dep[u] - dep[v]);
        if(u == v)
            return u;
        for(int bit = LOG - 1; bit >= 0; bit--)
            if(anc[u][bit] != anc[v][bit])
                u = anc[u][bit], v = anc[v][bit];
        return anc[u][0];
    }

    void set_block_id(){
        for(int i = 0; i < m; i++)
            queries[i].block_idx = queries[i].l / Sqrt_N;
    }
    
    void Get_Data(){
        for(int i = 0, u, v; i < m && cin >> u >> v; i++)
            queries[i] = query(S, E, u, v, i, get_lca(u, v));
        set_block_id();
    }

    void add(int idx){
        // fill this function with what problem needs
        int u = FT[idx];
        node_freq[u]++;
        if(node_freq[u] == 1){
            // add u to the path (u is in the path)

        }else {
            // remove u from the path (u is not in the path anymore)

        }
    }
 
    void remove(int idx){
        // fill this function with what problem needs
        int u = FT[idx];
        node_freq[u]--;
        if(node_freq[u] == 1){
            // add u to the path (u is in the path)

        }else {
            // remove u from the path (u is not in the path anymore)

        }
    }

    void set_range(query& q){
        while (curr_l > q.l) curr_l--, add(curr_l);
        while (curr_r < q.r) curr_r++, add(curr_r);
        while (curr_l < q.l) remove(curr_l), curr_l++;
        while (curr_r > q.r) remove(curr_r), curr_r--;
    }

    void Process(){
        sort(all(queries));
        
        // start with the first query
        curr_l = queries[0].l, curr_r = queries[0].l - 1;

        for(int i = 0; i < m; i++){
            set_range(queries[i]);
            // if lca is -1 then the two nodes are in the same subtree
            if(queries[i].lca != -1)
                add(S[queries[i].lca]);
            
            answers[queries[i].query_idx] = ans;
            
            if(queries[i].lca != -1)
                remove(S[queries[i].lca]);
        }
    }

    void Print_queries_answers(){
        for(int i = 0; i < m; i++)
            cout << answers[i] << '\n';
    }

    vector < T > get_answers(){
        return answers;
    }

};

// -------------------------- MO -----------------------------

template < typename T = int, int Base = 0 > struct MO {

    static inline int64_t gilbertOrder(int x, int y, int pow, int rotate) {
        if (pow == 0) return 0;
        int hpow = 1 << (pow - 1);
        int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
        seg = (seg + rotate) & 3;
        const int rotateDelta[4] = {3, 0, 0, 1};
        int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
        int nrot = (rotate + rotateDelta[seg]) & 3;
        int64_t subSquareSize = int64_t(1) << (2 * pow - 2);
        int64_t ordd = seg * subSquareSize;
        int64_t add = gilbertOrder(nx, ny, pow - 1, nrot);
        ordd += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
        return ordd;
    }

    struct query {

        int l, r, query_idx;
        int64_t ord;

        query(int L = 0, int R = 0, int Query_idx = 0){
            l = L - !Base, r = R - !Base, query_idx = Query_idx, calcOrder();
        }

        inline void calcOrder() {
            constexpr int K = 19;
            // K should be minimum such that 2^K >= n
            ord = gilbertOrder(l, r, K, 0);
        }

        bool operator < (const query & rhs) const{
            return ord < rhs.ord;
        }
    };

    T curr_l, curr_r, ans, n, m, Sqrt_N;
    vector < T > answers, nums;
    vector < query > queries;

    MO(int N = 0, int M = 0){
        curr_l = 1, curr_r = 0, ans = 0, n = N, m = M, Sqrt_N = n / sqrt(m) + 1;
        queries = vector < query > (m);
        answers = vector < T > (m);
        nums = vector < T > (n + 5);
    }
    
    void Get_Data(const vector < T > &v){
        // get the array and set the queries
        nums = v;

        for(int i = 0, l, r; i < m && cin >> l >> r; i++)
            queries[i] = query(l, r, i);
        
    }

    // add the idx to the current range
    void add(int idx){

    }

    // remove the idx from the current range
    void remove(int idx){

    }

    void set_range(const query& q){
        // add the new range and remove the old range
        while (curr_l > q.l) curr_l--, add(curr_l);
        while (curr_r < q.r) curr_r++, add(curr_r);
        while (curr_l < q.l) remove(curr_l), curr_l++;
        while (curr_r > q.r) remove(curr_r), curr_r--;
    }

    void Process(){
        
        sort(all(queries));

        // to start with the first query
        curr_l = queries[0].l, curr_r = queries[0].l - 1;
        
        for(int i = 0; i < m; i++){
            set_range(queries[i]);
            answers[queries[i].query_idx] = ans;
        }
    }

    void Print_queries_answers(){
        for(int i = 0; i < m; i++)
            cout << answers[i] << '\n';
    }

    vector < T > Get_answers(){
        return answers;
    }

};

// -------------------------- Int Mod -----------------------------

template < int MOD = 1000000007, typename T = int > struct ModInt {

    T val;

    ModInt(T V = 0) : val(V) { val %= MOD; }

    ModInt& operator += (const ModInt& rhs) {
        if ((val += rhs.val) >= MOD) val -= MOD;
        return *this;
    }
    ModInt& operator += (const T rhs) {
        if ((val += rhs) >= MOD) val -= MOD;
        return *this;
    }

    ModInt& operator -= (const ModInt& rhs) { 
        if ((val += MOD - rhs.val) >= MOD) val -= MOD; 
        return *this; 
    }
    ModInt& operator -= (const T rhs) { 
        if ((val += MOD - rhs) >= MOD) val -= MOD; 
        return *this; 
    }

    ModInt& operator *= (const ModInt& rhs) { val = (1ll * val * rhs.val) % MOD; return *this; }
    ModInt& operator *= (const T rhs) { val = (1ll * val * rhs) % MOD; return *this; }

    ModInt& operator /= (const ModInt& rhs) { return *this *= rhs.inverse(); }
    ModInt& operator /= (const T rhs) { return *this *= ModInt(rhs).inverse(); }

    ModInt& operator %= (const ModInt& rhs) { val %= rhs.val; return *this; }
    ModInt& operator %= (const T rhs) { val %= rhs; return *this; }

    ModInt& operator ++() { return *this += 1; }
    ModInt& operator --() { return *this -= 1; }
 
    ModInt operator ++(T unused) { ModInt res(*this); ++*this; return res; }
    ModInt operator --(T unused) { ModInt res(*this); --*this; return res; }
    
    ModInt operator + (const ModInt& rhs) const { ModInt res(*this); return res += rhs; }
    ModInt operator + (const T rhs) const { ModInt res(*this); return res += rhs; }

    ModInt operator % (const ModInt& rhs) const { ModInt res(*this); return res %= rhs; }
    ModInt operator % (const T rhs) const { ModInt res(*this); return res %= rhs; }

    ModInt operator - (const ModInt& rhs) const { ModInt res(*this); return res -= rhs; }
    ModInt operator - (const T rhs) const { ModInt res(*this); return res -= rhs; }

    ModInt operator * (const ModInt& rhs) const { ModInt res(*this); return res *= rhs; }
    ModInt operator * (const T rhs) const { ModInt res(*this); return res *= rhs; }

    ModInt operator / (const ModInt& rhs) const { ModInt res(*this); return res /= rhs; }
    ModInt operator / (const T rhs) const { ModInt res(*this); return res /= rhs; }

    ModInt& operator = (const ModInt& rhs) { val = rhs.val; return *this; }
    ModInt& operator = (const T rhs) { val = rhs; return *this; }

    T operator ~ () { return ~val; }
    bool operator ! () { return !val; }

    bool operator == (const ModInt& rhs) const { return val == rhs.val; }
    bool operator == (const T rhs) const { return val == rhs; }

    bool operator != (const ModInt& rhs) const { return val != rhs.val; }
    bool operator != (const T rhs) const { return val != rhs; }

    bool operator < (const ModInt& rhs) const { return val < rhs.val; }
    bool operator < (const T rhs) const { return val < rhs; }

    bool operator <= (const ModInt& rhs) const { return val <= rhs.val; }
    bool operator <= (const T rhs) const { return val <= rhs; }

    bool operator > (const ModInt& rhs) const { return val > rhs.val; }
    bool operator > (const T rhs) const { return val > rhs; }

    bool operator >= (const ModInt& rhs) const { return val >= rhs.val; }
    bool operator >= (const T rhs) const { return val >= rhs; }

    T operator () () const { return val; }

    ModInt inverse() const { return power(MOD - 2); }

    ModInt power(T n) const {
        ModInt a = *this, res = 1;
        while (n > 0) {
            if (n & 1) res *= a;
            a *= a, n >>= 1;
        }
        return res;
    }

    ModInt power(ModInt n) const {
        ModInt a = *this, res = 1;
        T e = n();
        while (e > 0) {
            if (e & 1) res *= a;
            a *= a, e >>= 1;
        }
        return res;
    }

    friend ModInt operator ^ (ModInt rhs, T n) { return rhs.power(n); }
    friend ModInt operator ^ (ModInt rhs, ModInt n) { return rhs.power(n); }

    friend std::istream& operator>>(std::istream& is, ModInt& x) noexcept { return is >> x.val; }
    friend std::ostream& operator<<(std::ostream& os, const ModInt& x) noexcept { return os << x.val; }

};
using Mint = ModInt < 998244353 >;

// -------------------------- Ordered Set -----------------------------

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template <typename K, typename V, typename Comp = std::less<K>>
using ordered_map = tree<K, V, Comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename Comp = std::less<K>>
using ordered_set = ordered_map<K, null_type, Comp>;

template <typename K, typename V, typename Comp = std::less_equal<K>>
using ordered_multimap = tree<K, V, Comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename Comp = std::less_equal<K>>
using ordered_multiset = ordered_multimap<K, null_type, Comp>;


// order_of_key(val)  count elements smaller than val
// *s.find_by_order(idx)  element with index idx


// -------------------------- Multi Ordered Set -----------------------------

template < typename T = int , typename CompFunction = std::less_equal < T > > struct Ordered_Multiset {
    
    ordered_multiset < T, CompFunction > mst;
    int Mode;

    // Constructor 
    Ordered_Multiset(bool isSmaller = true) {
        mst.clear();
        Mode = !isSmaller ? 1 : -1;
    }
    
    // Constructor with vector
    Ordered_Multiset(vector < T > &vec, bool isSmaller = true) {
        mst.clear();
        for (auto &x : vec) 
            mst.insert(x);
        Mode = !isSmaller ? 1 : -1;
    }

    // Insert element
    void insert(T val) {
        mst.insert(val);
    }

    // check if element exists or not
    bool is_exist(T val){ 
        if((mst.upper_bound(val)) == mst.end())
            return false;
        return ((*mst.upper_bound(val)) == val);
    }

    // erase element if exists
    void erase(T val){
        if(is_exist(val))
            mst.erase(mst.upper_bound(val));
    }
    
    // return element with given index
    T at(int idx){
        return (*mst.find_by_order(idx));
    }

    // return element with given index like mst[idx]
    T operator [] (int idx){
        return at(idx);
    }

    // return first index of element
    int first_idx(T val){ 
        if(!is_exist(val))
            return -1;
        return (mst.order_of_key(val));
    }

    // return last index of element
    int last_idx(T val){
        if(!is_exist(val))
            return -1;
        if(at(sz(mst) - 1) == val)
            return sz(mst) -1;
        return first_idx(*mst.lower_bound(val)) - 1;
    }

    // return number of occurences of element
    T count(T val){ 
        if(!is_exist(val))
            return 0;
        return last_idx(val) - first_idx(val) + 1;
    }

    // clear the ordered multiset
    void clear(){
        mst.clear();
    }

    // return size of ordered multiset
    int size(){
        return sz(mst);
    }

    // return number of elements < Comp > of val
    int order_of_key(T val){
        return mst.order_of_key(val - Mode);
    }

    // return iterator to element with given index
    typename ordered_multiset < T, CompFunction >::iterator find_by_order(int idx){
        return mst.find_by_order(idx);
    }

    // print the ordered multiset
    friend ostream& operator << (ostream &out, const Ordered_Multiset < T, CompFunction > &mst) { 
        for (const T &x : mst.mst) out << x << ' '; 
        return out;
    }

    // Ordered_Multiset < int, less_equal < int > > mst;
    // Ordered_Multiset < int, greater_equal < int > > mst;

};

// -------------------------- HLD -----------------------------

template < typename T = int, const int VAL_ON_EDGE = 0 > struct HLD {

    const vector < vector < T > > &adj;
    vector < T > dep, par, root, pos, SubtreeSz, child;
    int nxtPos;

    HLD(int n, const vector < vector < T > >& G, int treeRoot = 1) : adj(G) {
        nxtPos = 1;
        // child is heavy child
        dep = par = root = pos = SubtreeSz = child = vector < T > (n + 5);
        init(treeRoot);
        build(treeRoot);
    }

    void init(int u, int p = -1, int d = 0){
        dep[u] = d, par[u] = p, SubtreeSz[u] = 1;
        for (int v : adj[u]){ 
            if (v == p) continue;
            init(v, u, d + 1);
            SubtreeSz[u] += SubtreeSz[v];
            if (SubtreeSz[v] > SubtreeSz[child[u]]) 
                child[u] = v;
        }
    }

    int get_lca(int u, int v){
        while (root[u] != root[v]){
            if (dep[root[u]] < dep[root[v]]) 
                swap(u, v);
            u = par[root[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }

    void build(int u, bool newChain = true){
        root[u] = newChain ? u : root[par[u]];
        pos[u] = nxtPos++;
        if (child[u]) 
            build(child[u], false);
        for (int v : adj[u]){
            if(v == par[u] || v == child[u]) continue;
            build(v, true);
        }
    }

    // make u lower
    void makeULower(int& u, int& v){
        if(dep[root[u]] < dep[root[v]] || (root[u] == root[v] && dep[u] < dep[v]))
            swap(u, v);
    }

    // move up the chain and also change the next position
    Pair < T > moveUp(int& u){
        Pair < T > ret = {pos[root[u]], pos[u]};
        u = par[root[u]];
        return ret;
    }

    vector < Pair < T > > queryPath(int u, int v){
        // return all ranges in segment tree
        vector < Pair < T > > ret;
        while(root[u] != root[v]){
            makeULower(u, v);
            ret.push_back(moveUp(u));
        }
        // add range between u and v
        makeULower(u, v);
        if(!VAL_ON_EDGE) // value on nodes
            ret.push_back({pos[v], pos[u]});
        else if(u != v) // don't include the root node
            ret.push_back({pos[v] + 1, pos[u]});
        return ret;
    }

    // get child of a node for problem that value on edges
    int getChild(int u, int v){
        if(par[u] == v) 
            return u;
        return v;
    }

};

// -------------------------- Hashed Deque -----------------------------

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Hashed_Deque {

    int len;
    vector < int > val; 
    deque < int > curr;
    // N is the larget size of the container
    // base is the minimum prime number larger than the maximum value of the container
    const int N = 5e5 + 5, base = 1e9 + 7;

    Hashed_Deque(){
        val = vector < int > (2);
        curr.clear();
        len = 0;
        initial();
    }

    ll rand(ll l, ll r){
        return uniform_int_distribution < ll >(l, r)(rng);
    }

    vector < ll > mod;
    vector < vector < ll > > p, inv;

    bool is_prime(ll x){
        if(x < 2 || (x % 2 == 0 && x != 2)) return false;
        for(int i = 3; i <= sqrt(x); i += 2)
            if(x % i == 0) 
                return false;
        return true;
    }

    ll nxt_prime(ll x){
        while(!is_prime(x)) x++;
        return x;
    }

    void get_mods(){
        mod[0] = nxt_prime(rand(9e8, 1e9 + 9));
        mod[1] = nxt_prime(rand(9e8, 1e9 + 9));
        while(mod[1] == mod[0])
            mod[1] = nxt_prime(rand(9e8, 1e9 + 9));
    }

    ll fast_power(ll b, ll md){
        ll e = md - 2, res = 1;
        while(e) {
            if(e & 1)
                res = ((res % md) * (b % md)) % md;
            b = ((b % md) * (b % md)) % md;
            e >>= 1;
        }
        return res;
    }

    void initial(){
        mod = vector < ll > (2);
        p = inv = vector < vector < ll > > (N, vector < ll > (2, 1));
        get_mods();
        for(int i = 1; i < N;++i) 
            for(int j = 0;j < 2; ++j){
                p[i][j] = 1ll * p[i - 1][j] * base % mod[j];
                inv[i][j] = fast_power(p[i][j], mod[j]);
            }
    }

    void push_back(int x){
        for(int i = 0; i < 2; ++i)
            val[i] = (1ll * val[i] * base % mod[i] + x) % mod[i];
        curr.push_back(x);
        ++len;
    }

    void push_front(int x){
        for(int i = 0; i < 2;++i)
        val[i] = (1ll * x * p[len][i] % mod[i] + val[i]) % mod[i];
        curr.push_front(x);
        ++len;
    }

    void pop_back(){
        for(int i = 0; i < 2; ++i){
            val[i] = ((val[i] - curr.back()) % mod[i] +mod[i]) %mod[i];
            val[i] = 1ll * val[i] * inv[1][i] % mod[i];
        }
        curr.pop_back();
        --len;
    }

    void pop_front(){
        --len ;
        for(int i = 0; i < 2; ++i){
            int v = 1ll * curr.front() * p[len][i] % mod[i];
            val[i] = ((val[i] - v) % mod[i] + mod[i]) % mod[i];
        }
        curr.pop_front();
    }

    int size(){
        return len;
    }

    bool operator ==(const Hashed_Deque &rhs){
        return (rhs.len == len) && (rhs.val[0] == val[0]) && (rhs.val[1] == val[1]);
    }

};

// -------------------------- Miller Robin -----------------------------

template < typename T = long long , int Rounds = 10 > struct Miller_Rabin {

    T BinMul(T b, T e, T mod) {
        T res = 0;
        while (e > 0) {
            if (e & 1)
                res = ((res % mod) + (b % mod)) % mod;
            e >>= 1;
            b = ((b % mod) + (b % mod)) % mod;
        }
        return res;
    }

    T BinPow(T b, T e, T mod) {
        T res = 1;
        while (e > 0) {
            if (e & 1)
                res = BinMul(res, b, mod);
            e >>= 1;
            b = BinMul(b, b, mod);
        }
        return res;
    }

    bool is_prime(T num){
        // Handling base cases:
        if(num < 2) return false;
        if(num != 2 && num % 2 == 0) return false;

        // Now our num is odd number greater than 1
        T d = num - 1;

        while (d % 2 == 0)
            d >>= 1;
        
        for (int loop = 1; loop <= Rounds; loop++) {
            T a = rand() % (num - 1) + 1, temp = d;
            T x = BinPow(a, temp, num);
            while (temp != num - 1 && x != 1 && x != num - 1) {
                x = BinMul(x, x, num);
                temp <<= 1;
            }
            if (x != num - 1 && temp % 2 == 0)
                return false;
        }
        // If we reach here, then the number is prime
        return true; 
    }

};

// -------------------------- Convex Hull -----------------------------

typedef complex < double > point;
#define X real()
#define Y imag()
#define angle(a)                (atan2((a).imag(), (a).real()))
#define vec(a, b)                ((b)-(a))
#define same(p1, p2)             (dp(vec(p1, p2), vec(p1,p2)) < EPS)
#define dp(a, b)                 ( (conj(a) * (b)).real() )	// a * b cos(T), if zero -> prep
#define cp(a, b)                 ( (conj(a) * (b)).imag() )	// a * b sin(T), if zero -> parllel
#define length(a)               (hypot((a).imag(), (a).real()))
#define normalize(a)            (a) / length(a)
#define polar(r, ang)            ((r) * exp(point(0, ang))) 
#define rotateO(p, ang)          ((p) * exp(point(0, ang)))
#define rotateA(p, ang, about)  (rotateO(vec(about, p), ang) + about)
int dcmp(double a, double b) { return fabs(a - b) <= EPS ? 0 : a < b ? -1 : 1; }

istream& operator >> (istream &in, point& p) {
    double x, y;
    in >> x >> y;
    p = point(x, y);
    return in;
}

ostream& operator << (ostream &out, const point& p) { 
    out << p.X << ' ' << p.Y;
    return out;
}

struct Converx_Hull {

    struct angleCMP {
        
        point center;

        angleCMP(point C) : center(C) {}

        bool operator()(const point &lhs, const point rhs) const {
            if(dcmp(cp(lhs - center, rhs - center), 0) == 0) {
                if(fabs(lhs.Y - rhs.Y) < EPS)
                    return lhs.X < rhs.X;
                return lhs.Y < rhs.Y;
            }
            return cp((lhs - center), (rhs - center)) < 0;
        }

    };

    vector < point > Convex_Points;

    Converx_Hull(vector < point > &points) {
        if(sz(points) <= 1) Convex_Points = points;
        else {
            for(int i = 0; i < sz(points); i++){
                if(make_pair(points[i].Y, points[i].X) < make_pair(points[0].Y, points[0].X))
                    swap(points[i], points[0]);
            }
            sort(points.begin() + 1, points.end(), angleCMP(points[0]));

            // To remove co-linear points, un-comment this part

            // vector < point > tmp;
            // for(int i = 0; i < sz(points); i++){
            //     if(sz(tmp) > 1 && !cp(tmp.back() - tmp[0], points[i] - tmp[0])){
            //         if(length(points[0] - tmp.back()) < length(points[0] - points[i]))
            //             tmp.back() = points[i];
            //     }else {
            //         tmp.push_back(points[i]);
            //     }
            // }
            // points = tmp;
            
            for(int i = 0; i < sz(points); i++){
                int sz = sz(Convex_Points);
                while(sz > 1 && cp(Convex_Points[sz - 2] - Convex_Points[sz - 1], points[i] - Convex_Points[sz - 1]) < 0)
                    Convex_Points.pop_back(), sz--;
                Convex_Points.push_back(points[i]);
            }
            if(sz(Convex_Points) >= 3) // not a line
                Convex_Points.push_back(Convex_Points[0]);
        }
    }

};

// -------------------------- Convex Hull Trick -----------------------------

struct Line {

    mutable ll m, c, p;

    bool operator < (const Line &o) const { 
        return m < o.m; 
    }

    bool operator < (ll x) const { 
        return p < x; 
    }

    ll val(ll x) const { 
        return m * x + c; 
    }
};

template < typename T = int, T Mode = -1 > class CHT : multiset < Line, less < > > {
private:
    
    static constexpr T LLimit = numeric_limits < T > :: min(), RLimit = numeric_limits < T > :: max();

    T div(T a, T b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b);
    }

    bool is_intersect(iterator x, iterator y) {
        if (y == end()) return x -> p = RLimit, 0;
        if (x -> m == y -> m) x -> p = (x -> c > y -> c ? RLimit : LLimit);
        else x -> p = div(y -> c - x -> c, x -> m - y -> m);
        return x -> p >= y -> p;
    }

public:
    
    void add(T m, T c) {
        m *= Mode, c *= Mode;
        auto z = insert({m, c, 0}), y = z++, x = y;
        while (is_intersect(y, z)) z = erase(z);
        if (x != begin() && is_intersect(--x, y)) is_intersect(x, y = erase(y));
        while ((y = x) != begin() && (--x) -> p >= y -> p) is_intersect(x, erase(y));
    }

    T query(T x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return Mode * l.val(x);
    }

};

// -------------------------- Hashing -----------------------------

template < typename T = long long , int Base = 0 > struct Hash {
    
    int n;
    vector < T > pow1, pow2, h1, h2;
    const T p1 = 313, p2 = 1013;
    const T m1 = 1e9 + 7, m2 = 1e9 + 9;
 
    Hash(const string& s){
        n = s.size();
        h1 = h2 = pow1 = pow2 = vector < T > (n + 5);

        // calulcate the powers
        pow1[0] = pow2[0] = 1;
        for(int i = 1; i <= n; i++) {
            pow1[i] = (pow1[i - 1] * p1) % m1;
            pow2[i] = (pow2[i - 1] * p2) % m2;
        }

        // calculate the hashes
        h1[0] = h2[0] = 1;
        for(int i = 1; i <= n; i++) {
            h1[i] = (h1[i - 1] * p1 + s[i - !Base]) % m1;
            h2[i] = (h2[i - 1] * p2 + s[i - !Base]) % m2;
        }
    }

    Hash(const vector < T >& vec){
        n = vec.size();
        h1 = h2 = pow1 = pow2 = vector < T > (n + 5);
        
        // calulcate the powers
        pow1[0] = pow2[0] = 1;
        for(int i = 1; i <= n; i++) {
            pow1[i] = (pow1[i - 1] * p1) % m1;
            pow2[i] = (pow2[i - 1] * p2) % m2;
        }

        // calculate the hashes
        h1[0] = h2[0] = 1;
        for(int i = 1; i <= n; i++) {
            h1[i] = (h1[i - 1] * p1 + vec[i - !Base]) % m1;
            h2[i] = (h2[i - 1] * p2 + vec[i - !Base]) % m2;
        }
    }

    // get the hash of substring [i, j]
    pair < T, T > sub(int l, int r) {
        // first hash
        T F = h1[r];
        F -= h1[l - 1] * pow1[r - l + 1];
        F = ((F % m1) + m1) % m1;
        
        // second hash
        T S = h2[r];
        S -= h2[l - 1] * pow2[r - l + 1];
        S = ((S % m2) + m2) % m2;
        
        return {F, S};
    }
 
    // merge two substrings
    pair < T, T > merge_hash(int l1, int r1, int l2, int r2) {
        auto a = sub(l1, r1), b = sub(l2, r2);
        ll F = ((a.first * pow1[r2 - l2 + 1]) + b.first) % m1;
        ll S = ((a.second * pow2[r2 - l2 + 1]) + b.second) % m2;
        return {F, S};
    }
 
    // get the hash of the idx'th character
    pair < T, T > at(int idx){
        return sub(idx, idx);
    }

    // check if two parts are equals
    bool equal(int l1, int r1, int l2, int r2) {
        return sub(l1, r1) == sub(l2, r2);
    }

};

// -------------------------- Centroid Decomposition -----------------------------

template < typename T = int > struct Centroid_Decomposition {

    int n, treeRoot;
    const vector < vector < T > > adj;
    vector < T > SubtreeSz, isCentroid;

    // Initialize the Centroid Decomposition
    Centroid_Decomposition(int N, const vector <vector < T > > &G, int Root = 1) : adj(G){
        n = N, treeRoot = Root;
        SubtreeSz = isCentroid = vector < T > (n + 5, 0);
    }

    // update subtree size of each node
    int updateSize(int u, int p = -1){
        SubtreeSz[u] = 1;
        for (int v : adj[u]) 
            if (v != p && !isCentroid[v]) 
                SubtreeSz[u] += updateSize(v, u);
        return SubtreeSz[u];
    }

    // get centroid of subtree rooted at u
    int getCentroid(int u, int target, int p = -1){
        for(auto& v : adj[u]){
            if(v == p || isCentroid[v]) continue;
            if(SubtreeSz[v] * 2 > target) 
                return getCentroid(v, target, u);
        }
        return u;
    }

    // decompose tree into centroid tree
    void Centroid(int u, int p = 0){
        int centroidPoint = getCentroid(u, updateSize(u));
        
        // do something with centroid

        isCentroid[centroidPoint] = true;
        for(auto& v : adj[centroidPoint]){
            if(isCentroid[v]) continue;
            Centroid(v, centroidPoint);
        }
    }
    
    // call this function to decompose the tree
    void Decompose(){
        Centroid(treeRoot);
    }

};

// -------------------------- Optimizations -----------------------------

#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3") // GCC
#undef _GLIBCXX_DEBUG       // disable run-time bound checking, etc
#pragma GCC optimize("Ofast,inline")        // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC target("bmi,bmi2,lzcnt,popcnt")     // bit manipulation
#pragma GCC target("movbe")     // byte swap
#pragma GCC target("aes,pclmul,rdrnd")      // encryption
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2")        // SIMD

// -------------------------- Directions -----------------------------
 
vector < Pair < int > > dir_4 = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
vector < Pair < int > > dir_8 = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

// -------------------------- Knight moves -----------------------------

vector < Pair < int > > k_mov = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

// -----------------------------------------------------------------------

void Solve(){
    
}

int main(){
    int t = 1;
    //cin >> t;
    while(t--)
        Solve();
    return 0;
}