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

template < typename Tabletype = int, typename numsType = int, int Base = 0 > 
class Sparse_Table {
private:

    int n, LOG;
    vector < vector < Tabletype > > table;
    vector < int > Bin_Log;
    function < Tabletype(const Tabletype&, const Tabletype&) > operation;
    Tabletype DEFAULT;

    void Build_Table(){
        for(int log = 1; log < LOG; log++)
            for(int i = 1; i + (1 << log) - 1 <= n; i++)
                table[i][log] = operation(table[i][log - 1], table[i + (1 << (log - 1))][log - 1]);
    }

    Tabletype query_1(int L, int R){
        int log = Bin_Log[R - L + 1];
        return operation(table[L][log], table[R - (1 << log) + 1][log]);
    }

    Tabletype query_log_n(int L, int R){
        Tabletype answer = DEFAULT;
        for (int log = LOG; log >= 0; log--){
            if (L + (1 << log) - 1 <= R) {
                answer = operation(answer, table[L][log]);
                L += 1 << log;
            }
        }
        return answer;
    }

public:

    Sparse_Table(
        int N = 0,
        const vector < numsType >& vec = vector < numsType > (),
        function < Tabletype(const Tabletype&, const Tabletype&) > op = [](const Tabletype& a, const Tabletype& b) { return min(a, b); },
        Tabletype def = numeric_limits < Tabletype > ::max()
    ): n(N), LOG(__lg(n) + 1), operation(op), DEFAULT(def) {
        table = vector < vector < Tabletype > > (n + 10, vector < Tabletype > (LOG, DEFAULT));
        Bin_Log = vector < int > (n + 10);
        for(int i = 2; i <= n; i++)
            Bin_Log[i] = Bin_Log[i >> 1] + 1;
        for(int i = 1; i <= N; i++)
            table[i][0] = Tabletype(vec[i - !Base]);
        Build_Table();
    }

    Tabletype query(int L, int R, bool is_overlap = false){
        return (!is_overlap ? query_1(L, R) : query_log_n(L, R));
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