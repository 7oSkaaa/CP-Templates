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

// -------------------------- Trie -----------------------------
 
struct Trie {
    
    struct Node {

        Node* child[26];
        bool is_word;

        Node(){
            memset(child, 0, sizeof(child));
            is_word = false;
        }
    };

    Node* root;
    char DEFAULT;

    Trie(){
        root = new Node;
        DEFAULT = 'a';
    }
    
    ~Trie(){
        Delete_Trie(root);
        delete root;
    }

    void Delete_Trie(Node* curr){
        for(auto& new_node : curr -> child){
            if(new_node){
                Delete_Trie(new_node);
                delete new_node;
            }
        }
    }

    void insert(string& word){
        Node* curr = root; 
        for(auto& c : word){
            if(!curr -> child[c - DEFAULT]) curr -> child[c - DEFAULT] = new Node;
            curr = curr -> child[c - DEFAULT];
        }
        curr -> is_word = true;
    }
  
    bool search(string& word){
        Node* curr = root; 
        for(auto& c : word){
            if(!curr -> child[c - DEFAULT]) return false;
            curr = curr -> child[c - DEFAULT];
        }
        return curr -> is_word;
    }
 
    bool is_prefix(string& word){
        Node* curr = root; 
        for(auto& c : word){
            if(!curr -> child[c - DEFAULT]) return false;
            curr = curr -> child[c - DEFAULT];
        }
        return true;
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

template < typename T = int, int Mode = 0 > struct Segment_Tree {

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
    vector < Node > tree; 
    
    void intial(int n){
        size = 1, DEFAULT = 0;
        while(size < n) size *= 2;
        tree = vector < Node > (2 * size, DEFAULT);
    }

    Segment_Tree(int n){
        intial(n);
    }

    // Main operation to do

    Node operation(Node a, Node b){
        return a.val + b.val;
    }
    
    // If Mode is 1 so the array is 1-based else the array is 0-based
    
    void build(vector < T >& nums, int idx, int lx, int rx){
        if(Mode ? lx >= sz(nums) : lx > sz(nums)) return;
        if(rx == lx) tree[idx] = nums[lx - !Mode];
        else {
            int m = (rx + lx) / 2;
            build(nums, 2 * idx, lx, m);
            build(nums, 2 * idx + 1, m + 1, rx);
            tree[idx] = operation(tree[2 * idx], tree[2 * idx + 1]);
        }
    }

    void build(vector < T >& nums){
        build(nums, 1, 1, size);
    }

    void update(int i, T v, int idx, int lx, int rx){
        if(rx == lx) tree[idx] = v;
        else {  
            int m = (rx + lx) / 2;
            if(i <= m) update(i, v, 2 * idx, lx, m);
            else update(i, v, 2 * idx + 1, m + 1, rx);
            tree[idx] = operation(tree[2 * idx], tree[2 * idx + 1]);
        }
    }

    void update(int i, int v){
        update(i, v, 1, 1, size);
    }

    Node query(int l, int r, int idx, int lx, int rx){
        if(lx > r || l > rx) return DEFAULT;
        if(lx >= l && rx <= r) return tree[idx];
        int m = (lx + rx) / 2;
        return operation(query(l, r, 2 * idx, lx, m), query(l, r, 2 * idx + 1, m + 1, rx));
    }

    Node query(int l, int r){
        return query(l, r, 1, 1, size);
    }

    friend ostream& operator << (ostream &out, const Node &node) {
        out << node.val;
        return out;
    }
    
};

// -------------------------- Lazy Propagation -----------------------------

template < typename T = int > struct Lazy_Propagation {

    int size;
    T DEFUALT;
    vector < T > operations;
    
    void intial(int n){
        size = 1;
        DEFUALT = 0;
        while(size <= n) size *= 2;
        operations.assign(2 * size, DEFUALT);
    }

    Lazy_Propagation(int n){
        intial(n);
    }

    T operation(T a, T b){
        return max(a, b);
    }

    void build(vector < int >& nums, int idx, int lx, int rx){
        if(lx >= sz(nums)) return;
        if(rx == lx) operations[idx] = nums[lx];
        else {
            int m = (rx + lx) / 2;
            build(nums, 2 * idx, lx, m);
            build(nums, 2 * idx + 1, m + 1, rx);
            operations[idx] = operation(operations[2 * idx], operations[2 * idx + 1]);
        }
    }

    // the vector should be 1-based also the tree is 1-based
    
    void build(vector < int >& nums){
        build(nums, 1, 1, size);
    }

    void update(int l, int r, int v, int idx, int lx, int rx){
        if(lx > r || l > rx) return;
        if(lx >= l && rx <= r){
            operations[idx] = operation(operations[idx], v);
            return;
        }
        int m = (lx + rx) / 2;
        update(l, r, v, 2 * idx, lx, m), update(l, r, v, 2 * idx + 1, m + 1, rx);
    }

    void update(int l, int r, int v){
        update(l, r, v, 1, 1, size);
    }

    T query(int i, int idx, int lx, int rx){
        if(rx == lx) return operations[idx];
        else {  
            int m = (rx + lx) / 2;
            if(i <= m) return operation(operations[idx], query(i, 2 * idx, lx, m));
            else return operation(operations[idx], query(i, 2 * idx + 1, m + 1, rx));
        }
    }

    T query(int i){
        return query(i, 1, 1, size);
    }

};

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
            Pair < T > p1, p2;
            cin >> p1.fi >> p1.se >> p2.fi >> p2.se;
            if(p1.fi > p2.fi) swap(p1.fi, p2.fi);
            if(p1.se > p2.se) swap(p1.se, p2.se);
            partial[p2.fi][p2.se]++, partial[p2.fi][p1.se - 1]--; 
            partial[p1.fi - 1][p2.se]--, partial[p1.fi - 1][p1.se - 1]++;
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

// -------------------------- LCA -----------------------------

template < typename T = int > struct LCA {
    
    struct Edge {

        ll v, w;

        Edge(ll V = 0, ll W = 0) : v(V), w(W) {}

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
        while((1 << LOG) <= n) LOG++;
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

};

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

    Fenwick_Tree(int N){
        n = N + 1, DEFAULT = 0;
        Tree.assign(n + 10, DEFAULT);
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
        if(l > r) swap(l, r);
        return get_ans(r) - get_ans(l - 1);
    }

};

// -------------------------- Fenwick Tree 2D -----------------------------

template < typename T = int > struct Fenwick_Tree {
    
    vector < vector < T > > Tree;
    int n, m;
    T DEFAULT;

    Fenwick_Tree(int N, int M){
        n = N + 1, m = M + 1, DEFAULT = 0;
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

// -------------------------- Seive Factorization -----------------------------

struct Factorization {
    
    int n;
    vector < int > factors;
    vector < int > prime_factors;

    Factorization(int N){
        n = N;
        factors.assign(n + 10, 2);
        prime_factors.resize(n + 10);
    }

    // Get the number of factors for each number

    void factorization(int n){ 
        for (ll i = 2; i <= n; i++) {  
            for (ll j = i * 2; j <= n; j += i) factors[j]++;
        }
    }

    ll get_factors(ll n){
        return factors[n];
    }

    // Get the number of prime factors for each number

    void prime_factorization(int n){
        for (ll i = 2; i <= n; i++){ 
            if (!prime_factors[i]) { 
                for (ll j = 2 * i; j <= n; j += i) prime_factors[j]++;
                prime_factors[i] = 1; 
            }
        }
    }

    ll get_prime_factors(ll n){
        return prime_factors[n];
    }
};

// -------------------------- Next & Prev Element -----------------------------

struct Next_Prev_Element {

    Next_Prev_Element(){ }

    vector < ll > nextGreaterelement(vector < ll >& nums) {
        int n = nums.size();
        vector < ll > res(n);
        stack < int > st;
        for(int i = n - 1; i >= 1; i--){
            while(!st.empty() && nums[st.top()] <= nums[i]) st.pop();
            res[i] = (st.empty() ? n : st.top());
            st.push(i);
        }
        return res;
    }
    
    vector < ll > prevGreaterelement(vector < ll >& nums) {
        int n = nums.size();
        vector < ll > res(n);
        stack < int > st;
        for(int i = 1; i < n; i++){
            while(!st.empty() && nums[st.top()] <= nums[i]) st.pop();
            res[i] = (st.empty() ? 0 : st.top());
            st.push(i);
        }
        return res;
    }

    vector < ll > nextSmallerelement(vector < ll >& nums) {
        int n = nums.size();
        vector < ll > res(n);
        stack < int > st;
        for(int i = n - 1; i >= 1; i--){
            while(!st.empty() && nums[st.top()] >= nums[i]) st.pop();
            res[i] = (st.empty() ? n : st.top());
            st.push(i);
        }
        return res;
    }
    
    vector < ll > prevSmallerelement(vector < ll >& nums) {
        int n = nums.size();
        vector < ll > res(n);
        stack < int > st;
        for(int i = 1; i < n; i++){
            while(!st.empty() && nums[st.top()] >= nums[i]) st.pop();
            res[i] = (st.empty() ? 0 : st.top());
            st.push(i);
        }
        return res;
    }

};

// -------------------------- Sparse Table -----------------------------

template < typename T = int > struct Sparse_Table {

    struct Node {

        ll val;

        Node(ll V = 0) : val(V) {}
    
        Node operator = (const T& rhs) {
            val = rhs;
            return *this;
        }

    };

    int n, LOG;
    vector < vector < Node > > table;
    vector < int > Bin_Log;
    Node DEFAULT;

    Sparse_Table(vector < T >& vec){
        n = sz(vec), DEFAULT = 0, LOG = __lg(n) + 1;
        table = vector < vector < Node > > (n + 10, vector < Node > (LOG));
        Bin_Log = vector < int > (n + 10);
        for(int i = 2; i <= n; i++)
            Bin_Log[i] = Bin_Log[i >> 1] + 1;
        for(int i = 0; i < n; i++)
            table[i][0] = vec[i];
        Build_Table();
    }

    Node operation(Node a, Node b){
        Node res;
        res.val = a.val + b.val;
        return res;
    }

    void Build_Table(){
        for(int log = 1; log < LOG; log++)
            for(int i = 0; i + (1 << log) - 1 < n; i++)
                table[i][log] = operation(table[i][log - 1], table[i + (1 << (log - 1))][log - 1]);
    }

    Node query_1(int L, int R){
        int log = Bin_Log[R - L + 1];
        return operation(table[L][log], table[R - (1 << log) + 1][log]);
    }

    Node query_log_n(int L, int R){
        T answer = DEFAULT;
        for (int log = LOG; log >= 0; log--){
            if (L + (1 << log) - 1 <= R) {
                answer = operation(answer, table[L][log]);
                L += 1 << log;
            }
        }
        return answer;
    }

    T query(int L, int R, bool overlap = false){
        return (overlap ? query_1(L, R) : query_log_n(L, R)).val;
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

struct Prim {

    struct Edge {

        ll v, w;

        Edge(ll V = 0, ll W = 0) : v(V), w(W) {}

        bool operator < (const Edge &e) const {
            return w < e.w;
        }

    };

    vector < vector < Edge > > adj;
    vector < ll > marked;

    Prim(ll n = 0){
        adj = vector < vector < Edge > > (n + 10);
        marked = vector < ll > (n + 10, 0);
    }

    void build_adj(int edges, bool is_directed = false){
        for(int i = 0, u, v, w; i < edges && cin >> u >> v >> w; i++){
            adj[u].push_back(Edge(v, w));
            if(!is_directed)
                adj[v].push_back(Edge(u, w));
        }
    }

    ll get_cost(int root){
        ll cost = 0;
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

struct DSU {
    
    vector < int > parent, Gsize;

    DSU(int MaxNodes){
        parent.resize(MaxNodes + 5);
        Gsize.resize(MaxNodes + 5);
        for(int i = 1; i <= MaxNodes; i++)
          parent[i] = i, Gsize[i] = 1;
    }
    
    int find_leader(int node){
        return parent[node] = (parent[node] == node ? node : find_leader(parent[node]));
    }

    bool is_same_sets(int u, int v){
        return find_leader(u) == find_leader(v);
    }

    void union_sets(int u, int v){
        int leader_u = find_leader(u), leader_v = find_leader(v);
        if(leader_u == leader_v) return;
        if(Gsize[leader_u] < Gsize[leader_v]) swap(leader_u, leader_v);
        Gsize[leader_u] += Gsize[leader_v], parent[leader_v] = leader_u;
    }

    int get_size(int node){
        return Gsize[find_leader(node)];
    }
};

// -------------------------- Dijkstra -----------------------------

struct Dijkstra {
    
    struct Edge {

        ll v, w;
        
        Edge(ll V = 0, ll W = 0): v(V), w(W) {}
        
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

    ll Min_Cost(int src, int dest){
        int n = sz(adj);
        vector < ll > dist(n, LLONG_MAX);
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

    vector < ll > get_dist(int src){
        int n = sz(adj);
        vector < ll > dist(n, LLONG_MAX);
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

struct Coordinate_Compression {

    map < ll, ll > mapping;
    vector < ll > orig, comp, nums;
    int sz;

    Coordinate_Compression(vector < ll >& Nums){
        sz = 1;
        nums = Nums;
        sort(all(nums));
        nums.resize(unique(all(nums)) - nums.begin());
        for(auto& i : nums)
            mapping[i] = sz++;
        orig.resize(sz);
        for(auto& [f, s] : mapping) orig[s] = f;
        comp = nums;
        for(auto& i : comp) i = mapping[i];
    }

    vector < ll > orignal(){
        return orig;
    }

    vector < ll > compressed(){
        return comp;
    }

};

// -------------------------- MO -----------------------------

template < typename T = int > struct MO {

    struct query {

        int l, r, query_idx, block_idx;

        query(int L = 0, int R = 0, int Query_idx = 0){
            l = L - 1, r = R - 1, query_idx = Query_idx;
        }

        bool operator < (const query& q) const {
            return (block_idx < q.block_idx) || (block_idx == q.block_idx && r < q.r);
        }

    };

    int curr_l, curr_r, ans, n, m, Sqrt_N;
    vector < query > queries;
    vector < T > answers, nums;

    MO(int N = 0, int M = 0){
        curr_l = 1, curr_r = 0, ans = 0, n = N, m = M, Sqrt_N = sqrt(n);
        queries.resize(m), answers.resize(m), nums.resize(n);
    }

    void set_block_id(){
        for(int i = 0; i < m; i++)
            queries[i].block_idx = queries[i].l / Sqrt_N;
    }
    
    void Get_Data(){
        cin >> nums;
        for(int i = 0, l, r; i < m && cin >> l >> r; i++)
            queries[i] = query(l, r, i);
        set_block_id();
    }

    void add(int idx){
        // fill this function with what problem needs
    }

    void remove(int idx){
        // fill this function with what problem needs
    }

    void set_range(query q){
        while(curr_l < q.l) remove(curr_l++);
        while(curr_l > q.l) add(--curr_l);
        while(curr_r < q.r) add(++curr_r);
        while(curr_r > q.r) remove(curr_r--);
    }

    void Process(){
        sort(all(queries));

        for(int i = 0; i < m; i++){
            set_range(queries[i]);
            answers[queries[i].query_idx] = ans;
        }
    }

    void Print_queries_answers(){
        for(int i = 0; i < m; i++)
            cout << answers[i] << '\n';
    }

};

// -------------------------- Int Mod -----------------------------

template < int MOD = 1000000007 > struct ModInt {

    int val;

    ModInt(int V = 0) : val(V) { val %= MOD; }

    ModInt& operator += (const ModInt& rhs) {
        if ((val += rhs.val) >= MOD) val -= MOD;
        return *this;
    }
    ModInt& operator += (const int rhs) {
        if ((val += rhs) >= MOD) val -= MOD;
        return *this;
    }

    ModInt& operator -= (const ModInt& rhs) { 
        if ((val += MOD - rhs.val) >= MOD) val -= MOD; 
        return *this; 
    }
    ModInt& operator -= (const int rhs) { 
        if ((val += MOD - rhs) >= MOD) val -= MOD; 
        return *this; 
    }

    ModInt& operator *= (const ModInt& rhs) { val = (1ll * val * rhs.val) % MOD; return *this; }
    ModInt& operator *= (const int rhs) { val = (1ll * val * rhs) % MOD; return *this; }

    ModInt& operator /= (const ModInt& rhs) { return *this *= rhs.inverse(); }
    ModInt& operator /= (const int rhs) { return *this *= ModInt(rhs).inverse(); }

    ModInt& operator %= (const ModInt& rhs) { val %= rhs.val; return *this; }
    ModInt& operator %= (const int rhs) { val %= rhs; return *this; }

    ModInt& operator ++() { return *this += 1; }
    ModInt& operator --() { return *this -= 1; }
 
    ModInt operator ++(int unused) { ModInt res(*this); ++*this; return res; }
    ModInt operator --(int unused) { ModInt res(*this); --*this; return res; }
    
    ModInt operator + (const ModInt& rhs) const { ModInt res(*this); return res += rhs; }
    ModInt operator + (const int rhs) const { ModInt res(*this); return res += rhs; }

    ModInt operator % (const ModInt& rhs) const { ModInt res(*this); return res %= rhs; }
    ModInt operator % (const int rhs) const { ModInt res(*this); return res %= rhs; }

    ModInt operator - (const ModInt& rhs) const { ModInt res(*this); return res -= rhs; }
    ModInt operator - (const int rhs) const { ModInt res(*this); return res -= rhs; }

    ModInt operator * (const ModInt& rhs) const { ModInt res(*this); return res *= rhs; }
    ModInt operator * (const int rhs) const { ModInt res(*this); return res *= rhs; }

    ModInt operator / (const ModInt& rhs) const { ModInt res(*this); return res /= rhs; }
    ModInt operator / (const int rhs) const { ModInt res(*this); return res /= rhs; }

    ModInt& operator = (const ModInt& rhs) { val = rhs.val; return *this; }
    ModInt& operator = (const int rhs) { val = rhs; return *this; }

    bool operator == (const ModInt& rhs) const { return val == rhs.val; }
    bool operator == (const int rhs) const { return val == rhs; }

    bool operator != (const ModInt& rhs) const { return val != rhs.val; }
    bool operator != (const int rhs) const { return val != rhs; }

    bool operator < (const ModInt& rhs) const { return val < rhs.val; }
    bool operator < (const int rhs) const { return val < rhs; }

    bool operator <= (const ModInt& rhs) const { return val <= rhs.val; }
    bool operator <= (const int rhs) const { return val <= rhs; }

    bool operator > (const ModInt& rhs) const { return val > rhs.val; }
    bool operator > (const int rhs) const { return val > rhs; }

    bool operator >= (const ModInt& rhs) const { return val >= rhs.val; }
    bool operator >= (const int rhs) const { return val >= rhs; }

    int operator () () const { return val; }

    ModInt inverse() const { return power(MOD - 2); }

    ModInt power(ll n) const {
        ModInt a = *this, res = 1;
        while (n > 0) {
            if (n & 1) res *= a;
            a *= a, n >>= 1;
        }
        return res;
    }

    ModInt power(ModInt n) const {
        ModInt a = *this, res = 1;
        int e = n();
        while (e > 0) {
            if (e & 1) res *= a;
            a *= a, e >>= 1;
        }
        return res;
    }

    friend ModInt operator ^ (ModInt rhs, ll n) { return rhs.power(n); }
    friend ModInt operator ^ (ModInt rhs, ModInt n) { return rhs.power(n); }

    friend std::istream& operator>>(std::istream& is, ModInt& x) noexcept { return is >> x.val; }
    friend std::ostream& operator<<(std::ostream& os, const ModInt& x) noexcept { return os << x.val; }

};
using Mint = ModInt < 998244353 >;

// -------------------------- Big Integer -----------------------------

struct BigInt {

    const int BASE = 1000000000;
    vector < int > v;
    
    BigInt() {}

    BigInt(const long long &val) {
        *this = val;
    }
    
    BigInt(const string &val) {
        *this = val;
    
    }
    
    int size() const { return v.size(); }
    
    bool zero() const { return v.empty(); }
    
    BigInt& operator = (long long val) {
        v.clear();
        while (val) {
            v.push_back(val % BASE);
            val /= BASE;
        }
        return *this;
    }

    BigInt& operator = (const BigInt &a) {
        v = a.v;
        return *this;
    }

    BigInt& operator = (const vector < int > &a) {
        v = a;
        return *this;
    }

    BigInt& operator = (const string &s) {
        *this = 0;
        for (const char &ch : s)
            *this = *this * 10 + (ch - '0');
        return *this;
    }
    
    bool operator < (const BigInt &a) const {
        if (a.size() != size())
            return size() < a.size();
        for (int i = size() - 1; i >= 0; i--)
            if (v[i] != a.v[i])
                return v[i] < a.v[i];
        return false;
    }

    bool operator > (const BigInt &a) const {
        return a < *this;
    }

    bool operator == (const BigInt &a) const {
        return (!(*this < a) && !(a < *this));
    }

    bool operator <= (const BigInt &a) const {
        return ((*this < a) || !(a < *this));
    }
    
    ll val(){
        ll ans = 0;
        for (int i = 0; i < size(); i++)
            ans = ans * 10 + v[i];
        return ans;
    }

    BigInt operator + (const BigInt &a) const {
        BigInt res = *this;
        int idx = 0, carry = 0;
        while (idx < a.size() || carry) {
            if (idx < a.size())
                carry += a.v[idx];
            if (idx == res.size())
                res.v.push_back(0);
            res.v[idx] += carry;
            carry = res.v[idx] / BASE;
            res.v[idx] %= BASE;
            idx++;
        }
        return res;
    }
    
    BigInt& operator += (const BigInt &a) {
        *this = *this + a;
        return *this;
    }
    
    BigInt operator * (const BigInt &a) const {
        BigInt res;
        if (this -> zero() || a.zero())
            return res;
        res.v.resize(size() + a.size());
        for (int i = 0; i < size(); i++) {
            if (v[i] == 0)
                continue;
            long long carry = 0;
            for (int j = 0; carry || j < a.size(); j++) {
                carry += 1LL * v[i] * (j < a.size() ? a.v[j] : 0);
                while (i + j >= res.size())
                    res.v.push_back(0);
                carry += res.v[i + j];
                res.v[i + j] = carry % BASE;
                carry /= BASE;
            }
        }
        while (!res.v.empty() && res.v.back() == 0)
            res.v.pop_back();
        return res;
    }

    BigInt& operator *= (const BigInt &a) {
        *this = *this * a;
        return *this;
    }

    BigInt& operator -= (const BigInt &b){
        if(*this < b)
            throw("UNDERFLOW");
        int n = this -> size(), m = b.size();
        int i, t = 0, s;
        for (i = 0; i < n;i++){
            if(i < m)
                s = this -> v[i] - b.v[i]+ t;
            else
                s = this -> v[i] + t;
            if(s < 0)
                s += 10,
                t = -1;
            else
                t = 0;
            this -> v[i] = s;
        }
        while(n > 1 && this -> v[n - 1] == 0)
            this -> v.pop_back(),
            n--;
        return *this;
    }

    BigInt operator - (const BigInt&b){
        BigInt a = *this;
        a -= b;
        return a;
    }

    BigInt operator -- (const int){
        *this -= BigInt(1);
        return *this;
    }

    BigInt operator ++ (const int){
        *this += BigInt(1);
        return *this;
    }

    BigInt& operator /=(const ll a) {
        ll carry = 0;
        for (int i = (int) v.size() - 1; i >= 0; i--) {
            ll cur = v[i] + carry * BASE;
            v[i] = cur / a;
            carry = cur % a;
        }
        while (!v.empty() && v.back() == 0)
            v.pop_back();
        return *this;
    }
    
    BigInt operator / (const ll a) {
        ll carry = 0;
        vector < int > res = this -> v;
        for (int i = (int) res.size() - 1; i >= 0; i--) {
            ll cur = res[i] + carry * BASE;
            res[i] = cur / a;
            carry = cur % a;
        }
        BigInt ans;
        ans = res;
        return ans;
    }
    
    BigInt operator % (const ll a){
        ll res = 0;
        for (int i = (int) v.size() - 1; i >= 0; i--)
            res = (res * 10 + v[i]) % a;
        BigInt ans = res;
        return ans;
    }

    BigInt& operator %= (const ll a) {
        *this = *this % a;
        return *this;
    }

    friend ostream& operator<<(ostream &out, const BigInt &a) {
        out << (a.zero() ? 0 : a.v.back());
        for (int i = (int) a.v.size() - 2; i >= 0; i--)
            out << setfill('0') << setw(9) << a.v[i];
        return out;
    }

    friend istream& operator>>(istream &in, BigInt &a) {
        string s;
        in >> s;
        a = s;
        return in;
    }

};

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


// -------------------------- Optimizations -----------------------------

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization ("unroll-loops")

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