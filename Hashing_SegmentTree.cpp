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

template < typename T = int , int Base = 0 > struct Hash_SegmentTree {
 
    int n, size;
    vector < T > pow1, pow2, inv1, inv2;
    const T p1 = 313, p2 = 1013;
    const T m1 = 1e9 + 7, m2 = 1e9 + 9;
    vector < Pair < T > > tree;
 
    #define LEFT (idx << 1)
    #define RIGHT ((idx << 1) | 1)
    
    // multiply two numbers and return the result modulo m
    T mul(T a, T b, T m){
        return (1LL * a * b) % m;
    }
 
    // add two numbers and return the result modulo m
    T add(T a, T b, T m){
        a += b;
        if(a >= m) a -= m;
        return a;
    }
 
    // fast modular exponentiation
    T pow_mod(T b, T e, int m = Mod){
        T ret = 1;
        while(e){
            if(e & 1) ret = mul(ret, b, m);
            b = mul(b, b, m);
            e >>= 1;
        }
        return ret;
    }
    
    Hash_SegmentTree(int _n = 0) : n(_n) {
        size = 1;
        Pair < T > DEFAULT = {0, 0};
        while(size < n) size *= 2;
        tree = vector < Pair < T > > (2 * size, DEFAULT);
        pow1 = pow2 = inv1 = inv2 = vector < T > (2 * size);
 
 
        pow1[0] = pow2[0] = inv1[0] = inv2[0] = 1;
 
        T inv1_val = pow_mod(p1, m1 - 2, m1);
        T inv2_val = pow_mod(p2, m2 - 2, m2);
 
        for(int i = 1; i < 2 * size; i++){
            pow1[i] = mul(pow1[i - 1], p1, m1);
            pow2[i] = mul(pow2[i - 1], p2, m2);
            inv1[i] = mul(inv1[i - 1], inv1_val, m1);
            inv2[i] = mul(inv2[i - 1], inv2_val, m2);
        }
    }
 
    // merge two hashes into one
    Pair < T > merge(const Pair < T >& a, const Pair < T >& b){
        return {add(a.first, b.first, m1), add(a.second, b.second, m2)};
    }
 
    // build the segment tree
    void build(const vector < T >& nums, int idx, int lx, int rx){
        if(Base ? lx >= sz(nums) : lx > sz(nums)) return;
        if(rx == lx) tree[idx] = {mul(nums[lx - !Base], pow1[idx], m1), mul(nums[lx - !Base], pow2[idx], m2)};
        else {
            int mx = (rx + lx) / 2;
            build(nums, LEFT, lx, mx);
            build(nums, RIGHT, mx + 1, rx);
            tree[idx] = merge(tree[LEFT], tree[RIGHT]);
        }
    }
 
    // build the segment tree from scratch
    void build(const vector < T >& nums){
        build(nums, 1, 1, size);
    }
 
    // update the value at index idx to val
    void update(int index, T val, int idx, int lx, int rx){
        if(rx == lx) tree[idx] = {mul(val, pow1[idx], m1), mul(val, pow2[idx], m2)};
        else {  
            int mx = (rx + lx) / 2;
            if(index <= mx) update(index, val, LEFT, lx, mx);
            else update(index, val, RIGHT, mx + 1, rx);
            tree[idx] = merge(tree[LEFT], tree[RIGHT]);
        }
    }
 
    // update the value at index idx to val
    void update(const int index, const T val){
        update(index, val, 1, 1, size);
    }
 
    // update the value at index idx to val
    void update(const int index, char c){
        update(index, c - 'a' + 1, 1, 1, size);
    }
 
    // get the hash of the range [l, r]
    Pair < T > query(int l, int r, int idx, int lx, int rx){
        if(lx > r || l > rx) return {0, 0};
        if(lx >= l && rx <= r) return tree[idx];
        int mx = (lx + rx) / 2;
        return merge(query(l, r, LEFT, lx, mx), query(l, r, RIGHT, mx + 1, rx));
    }
 
    // get the hash of the range [l, r]
    Pair < T > query(const int l, const int r){
        auto [h1, h2] = query(l, r, 1, 1, size);
        return {mul(h1, inv1[l - 1], m1), mul(h2, inv2[l - 1], m2)};
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