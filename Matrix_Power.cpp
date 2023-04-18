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