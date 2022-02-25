#include <bits/stdc++.h>

using namespace std;

#define cin_2d(vec, n, m) for(int i = 0; i < n; i++) for(int j = 0; j < m && cin >> vec[i][j]; j++);
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define cout_map(mp) for(auto& [f, s] : mp) cout << f << "  " << s << "\n";
#define Time cerr << "Time Taken: " << (float)clock() / CLOCKS_PER_SEC << " Secs" << "\n";
#define fixed(n) fixed << setprecision(n)
#define ceil(n, m) (((n) / (m)) + ((n) % (m) ? 1 : 0))
#define fill(vec, value) memset(vec, value, sizeof(vec));
#define Num_of_Digits(n) ((int)log10(n) + 1)
#define mod_combine(a, b, m) (((a % m) * (b % m)) % m)
#define all(vec) vec.begin(), vec.end()
#define rall(vec) vec.rbegin(), vec.rend()
#define sz(x) int(x.size())
#define debug(x) cout << #x << ": " << (x) << "\n";
#define fi first
#define se second
#define Pair pair < int, int >
#define ll long long
#define ull unsigned long long
#define Mod  1'000'000'007
#define OO 2'000'000'000
#define EPS 1e-9
#define PI acos(-1)

template < typename T = int > istream& operator >> (istream &in, vector < T > &v) {
    for (auto &x: v) in >> x;
    return in;
}

template < typename T = int > ostream& operator << (ostream &out, const vector < T > &v) { 
    for (const T &x: v) out << x << ' '; 
    return out;
}

void AhMeD_HoSSaM(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout); 
    #endif
}

struct Lazy_Propagation {

    int size;
    vector < ll > operations; 
    
    void intial(int n){
        size = 1;
        while(size <= n) size *= 2;
        operations.assign(2 * size, 0ll);
    }

    Lazy_Propagation(int n){
        intial(n);
    }

    ll operation(ll a, ll b){
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

    ll query(int i, int idx, int lx, int rx){
        if(rx == lx) return operations[idx];
        else {  
            int m = (rx + lx) / 2;
            if(i <= m) return operation(operations[idx], query(i, 2 * idx, lx, m));
            else return operation(operations[idx], query(i, 2 * idx + 1, m + 1, rx));
        }
    }

    ll query(int i){
        return query(i, 1, 1, size);
    }

};

void Solve(){
    
}

int main(){
    AhMeD_HoSSaM();
    int t = 1;
    //cin >> t;
    while(t--)
        Solve();
    return 0;
}