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

template < typename T = int >
struct Monotonic_Stack {
    vector < T > st, Monotonic;
    function < T(const T&, const T&) > operation;
    T DEFAULT;

    Monotonic_Stack(
        function < T(const T&, const T&) > op = [](const T& a, const T& b) { return max(a, b); },
        T default_val = T()
    ) : operation(op), DEFAULT(default_val) {
        Monotonic.push_back(DEFAULT);
    }

    void push(T x) {
        st.push_back(x);
        Monotonic.push_back(operation(Monotonic.back(), x));
    }

    T pop() {
        T res = st.back();
        st.pop_back();
        Monotonic.pop_back();
        return res;
    }

    bool empty() const {
        return st.empty();
    }

    T top() const {
        return st.back();
    }

    T Monotonic_val() const {
        return Monotonic.back();
    }

    int size() const {
        return st.size();
    }
};

template < typename T = int >
struct Monotonic_Queue {
    Monotonic_Stack < T > s1, s2;
    function < T(const T&, const T&) > operation;
    T DEFAULT;

    Monotonic_Queue(
        function < T(const T&, const T&) > op = [](const T& a, const T& b) { return max(a, b); },
        T default_val = T()
    ) : s1(op, default_val), s2(op, default_val), operation(op), DEFAULT(default_val) {}

    void push(T x) {
        s2.push(x);
    }

    void pop() {
        if (s1.empty()) {
            while (!s2.empty()) {
                s1.push(s2.pop());
            }
        }
        s1.pop();
    }

    T monotonic_val() const {
        if (s1.empty()) return s2.Monotonic_val();
        if (s2.empty()) return s1.Monotonic_val();
        return operation(s1.Monotonic_val(), s2.Monotonic_val());
    }

    bool empty() const {
        return s1.empty() && s2.empty();
    }

    int size() const {
        return s1.size() + s2.size();
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