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

template < typename T = int , const T MOD = 1000000007, T N = 2 >  struct Matrix {

    vector < vector < T > > Mat;

    // add two elements
    static T add(const T& a, const T& b){
        return (a + b) % MOD;
    }

    // multiplicatate two element
    static T mul(const T& a, const T& b){
        return ((a % MOD) * (b % MOD)) % MOD;
    }

    // Constructor to fill the matrix with this value
    Matrix(T val = 0) {
        Mat.assign(N, vector < T > (N, val));
    }

    // Constructor to make matrix with this 2D Vector
    Matrix(const vector < vector < T > > & b){
        Mat = b;
    }

    // Overloaded the = operator
    Matrix& operator = (const Matrix& b){
        Mat = b.Mat;
        return *this;
    }

    // Overloaded the = operator
    Matrix& operator = (const vector < vector < T > > & b){
        Mat = b;
        return *this;
    }

    // Get Transition matrix
    static vector < vector < T > > GetTrans(){
        vector < vector < T > > Trans {
            {0, 1},
            {3, 2}
        };
        return Trans;
    }

    // Get the identity matrix
    static vector < vector < T > > GetIdentity(){
        vector < vector < T > > Identity(N, vector < T > (N));
        for(int i = 0; i < N; i++)
            Identity[i][i] = 1;
        return Identity;
    }

    // Get the zero matrix
    static vector < vector < T > > GetZero(){
        vector < vector < T > > Zero(N, vector < T > (N));
        return Zero;
    }

    // Overload the [][] operator
    vector < T >& operator[](T index) {
        return Mat[index];
    }

    // Overload the [][] operator
    const vector < T >& operator[](T index) const {
        return Mat[index];
    }

    // Overload the * operator
    Matrix friend operator * (const Matrix& a, const Matrix& b){
        Matrix res = GetZero();
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                for(int k = 0; k < N; k++)
                    res[i][j] = add(res[i][j], mul(a[i][k], b[k][j]));
        return res;
    }

    // Overload the ^ operator
    Matrix friend operator ^ (Matrix b, ll e){
        Matrix Trans = GetTrans();
        while(e){
            if(e & 1) b *= Trans;
            Trans *= Trans;
            e >>= 1;
        }
        return b;
    }

    // Overload the + operator
    Matrix friend operator + (const Matrix& a, const Matrix& b){
        Matrix res = GetZero();
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                res[i][j] = add(a[i][j], b[i][j]);
        return res;
    }

    // Overload the += operator
    Matrix friend operator += (Matrix& a, const Matrix& b){
        a = a + b;
        return a;
    }

    // Overload the *= operator
    Matrix friend operator *= (Matrix& a, const Matrix& b){
        a = a * b;
        return a;
    }

    // Overload the ^= operator
    Matrix friend operator ^= (Matrix& a, ll b){
        a = a ^ b;
        return a;
    }

    // Get the n-th term
    T n_th(T n){
        if(n <= 1) return 0;
        Matrix < T >  Ans = GetTrans();
        Ans ^= (n - 1);
        return Ans[0][0];
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