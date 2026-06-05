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

template < typename T >
struct MaxOp {
    constexpr T operator()(const T& a, const T& b) const { return a > b ? a : b; }
};

/*
 * Monotonic_Stack — Stack that tracks a running monotonic aggregate
 *
 * Template params:
 *   T  = element type               (default int)
 *   Op = binary combine functor     (default MaxOp<T> = max)
 *
 * Constructor:
 *   Monotonic_Stack<T, Op> s(Op op = Op{}, T default_val = T{});
 *
 * Methods:
 *   push(T x)          → push element, update aggregate
 *   pop()              → T, pop top and update aggregate
 *   top()              → T, peek top element
 *   monotonic_val()    → T, current aggregate over all elements
 *   empty()            → bool
 *   size()             → int
 *
 * -------------------------------------------------------------------
 * Monotonic_Queue — Deque with O(1) range aggregate using two stacks
 *
 * Template params:
 *   T  = element type               (default int)
 *   Op = binary combine functor     (default MaxOp<T> = max)
 *
 * Constructor:
 *   Monotonic_Queue<T, Op> q(Op op = Op{}, T default_val = T{});
 *
 * Methods:
 *   push(T x)          → enqueue element
 *   pop()              → dequeue front element
 *   front()            → T, peek front element (triggers rebalance if needed)
 *   monotonic_val()    → T, aggregate over all elements in queue
 *   empty()            → bool
 *   size()             → int
 *
 * Example (sliding window max of size k — default max):
 *   Monotonic_Queue<int> mq;
 *   for (int i = 0; i < n; i++) {
 *       mq.push(arr[i]);
 *       if (i >= k) mq.pop();
 *       if (i >= k - 1) cout << mq.monotonic_val() << "\n";
 *   }
 *
 * Example (sliding window min via plain function):
 *   int minOp(int a, int b) { return min(a, b); }
 *   Monotonic_Queue<int, decltype(&minOp)> mq(&minOp, INT_MAX);
 *
 * Example (sliding window min via lambda):
 *   auto minOp = [](int a, int b){ return min(a, b); };
 *   Monotonic_Queue<int, decltype(minOp)> mq(minOp, INT_MAX);
 */
template < typename T = int, typename Op = MaxOp < T > >
struct Monotonic_Stack {
    vector < T > st, mono;
    Op operation;
    T DEFAULT;

    Monotonic_Stack(Op op = Op{}, T default_val = T{})
        : operation(op), DEFAULT(default_val) {
        mono.push_back(DEFAULT);
    }

    void push(T x) {
        st.push_back(x);
        mono.push_back(operation(mono.back(), x));
    }

    T pop() {
        T res = st.back();
        st.pop_back();
        mono.pop_back();
        return res;
    }

    T top() const { return st.back(); }
    T monotonic_val() const { return mono.back(); }
    bool empty() const { return st.empty(); }
    int size() const { return st.size(); }
};

template < typename T = int, typename Op = MaxOp < T > >
struct Monotonic_Queue {
    Monotonic_Stack < T, Op > s1, s2;
    Op operation;
    T DEFAULT;

    Monotonic_Queue(Op op = Op{}, T default_val = T{})
        : s1(op, default_val), s2(op, default_val), operation(op), DEFAULT(default_val) {}

    void push(T x) { s2.push(x); }

    void pop() {
        if (s1.empty()) {
            while (!s2.empty()) s1.push(s2.pop());
        }
        s1.pop();
    }

    // front element of s1 = queue front (s1 stores in reversed order)
    T front() {
        if (s1.empty()) {
            while (!s2.empty()) s1.push(s2.pop());
        }
        return s1.top();
    }

    T monotonic_val() const {
        if (s1.empty()) return s2.monotonic_val();
        if (s2.empty()) return s1.monotonic_val();
        return operation(s1.monotonic_val(), s2.monotonic_val());
    }

    bool empty() const { return s1.empty() && s2.empty(); }
    int size() const { return s1.size() + s2.size(); }
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