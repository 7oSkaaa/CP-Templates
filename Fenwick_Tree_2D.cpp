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