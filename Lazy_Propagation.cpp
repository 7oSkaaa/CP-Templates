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

    int size;
    T Default, queryDefault, InitValue;
    vector < T > operations, values;
    
    void intial(int n){
        size = 1, Default = InitValue = 0, queryDefault = -1;
        while(size <= n) size *= 2;
        operations = vector < T > (size << 1, Default);
        values = vector < T > (size << 1, queryDefault);
    }

    Lazy_Propagation(int n){
        intial(n);
        build();
    }

    // Main operation to do

    T update_operation(T a, T b){
        return (a | b);
    }   

    T query_operation(T a, T b){
        return (a & b);
    }

    void apply_operation(int idx, T val){
        operations[idx] = update_operation(operations[idx], val);
        values[idx] = update_operation(values[idx], val);
    }

    void build(vector < T >& nums, int idx, int lx, int rx){
        if(Base ? lx >= sz(nums) : lx > sz(nums)) return;
        if(rx == lx) values[idx] = nums[lx - !Base];
        else {
            int m = (rx + lx) / 2; 
            build(nums, 2 * idx, lx, m);
            build(nums, 2 * idx + 1, m + 1, rx);
            values[idx] = query_operation(values[2 * idx], values[2 * idx + 1]);
        }
    }

    void build(int idx, int lx, int rx){
        if(rx == lx) values[idx] = InitValue;
        else {
            int m = (rx + lx) / 2; 
            build(2 * idx, lx, m);
            build(2 * idx + 1, m + 1, rx);
            values[idx] = query_operation(values[2 * idx], values[2 * idx + 1]);
        }
    }

    // If Base is 1 so the array is 1-based else the array is 0-based
    
    void build(vector < T >& nums){
        build(nums, 1, 1, size);
    }

    void build(){
        build(1, 1, size);
    }

    // for uncommutative operation

    void propagate(int idx, int lx, int rx){
        values[idx] = query_operation(values[2 * idx], values[2 * idx + 1]);
        values[idx] = update_operation(values[idx], operations[idx]);
    }

    void update(int l, int r, T v, int idx, int lx, int rx){
        if(lx > r || l > rx) return;
        // comment this line if the operation is commutative
        if(lx >= l && rx <= r) return apply_operation(idx, v);
        int m = (lx + rx) / 2;
        update(l, r, v, 2 * idx, lx, m); 
        update(l, r, v, 2 * idx + 1, m + 1, rx);
        propagate(idx, lx, rx);
    }

    // update the range [l, r] with value v

    void update(int l, int r, T v){
        update(l, r, v, 1, 1, size);
    }

    T query(int l, int r, int idx, int lx, int rx){
        if(lx > r || l > rx) return queryDefault;
        if(lx >= l && rx <= r) return values[idx];
        int m = (lx + rx) / 2;
        auto ret =  query_operation(query(l, r, 2 * idx, lx, m), query(l, r, 2 * idx + 1, m + 1, rx));
        ret = update_operation(ret, operations[idx]);
        return ret;
    }

    // query to get element at position i

    T query(int l, int r){
        return query(l, r, 1, 1, size);
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