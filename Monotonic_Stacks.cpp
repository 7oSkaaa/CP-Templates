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

/*
 * Monotonic_Stacks — Next/prev greater/smaller index queries (O(n) each)
 *
 * All functions return 0-indexed results (indices into the input array).
 * Sentinels: next* → n (past-end), prev* → -1 (before-start) when no match found.
 *
 * strict = true  (default) → strict comparison  (>, <)
 * strict = false            → non-strict         (>=, <=)
 *
 * Functions:
 *   next_greater(nums, strict=true)  → vector<int>, next j > i where nums[j] > nums[i]
 *   prev_greater(nums, strict=true)  → vector<int>, prev j < i where nums[j] > nums[i]
 *   next_smaller(nums, strict=true)  → vector<int>, next j > i where nums[j] < nums[i]
 *   prev_smaller(nums, strict=true)  → vector<int>, prev j < i where nums[j] < nums[i]
 *
 * Example:
 *   vector<int> a = {2, 1, 5, 3, 4};
 *   auto nge = next_greater(a);  // {2, 2, 5, 4, 5}   — 5 = n means none
 *   auto pse = prev_smaller(a);  // {-1, -1, 1, 1, 3} — -1 means none
 *
 * Example (non-strict — next greater or equal):
 *   auto ngoe = next_greater(a, false);  // next j where nums[j] >= nums[i]
 */
template < typename T >
vector < int > next_greater(const vector < T >& nums, bool strict = true) {
    int n = nums.size();
    vector < int > res(n, n);
    stack < int > st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && (strict ? nums[st.top()] <= nums[i] : nums[st.top()] < nums[i]))
            st.pop();
        res[i] = st.empty() ? n : st.top();
        st.push(i);
    }
    return res;
}

template < typename T >
vector < int > prev_greater(const vector < T >& nums, bool strict = true) {
    int n = nums.size();
    vector < int > res(n, -1);
    stack < int > st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && (strict ? nums[st.top()] <= nums[i] : nums[st.top()] < nums[i]))
            st.pop();
        res[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    return res;
}

template < typename T >
vector < int > next_smaller(const vector < T >& nums, bool strict = true) {
    int n = nums.size();
    vector < int > res(n, n);
    stack < int > st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && (strict ? nums[st.top()] >= nums[i] : nums[st.top()] > nums[i]))
            st.pop();
        res[i] = st.empty() ? n : st.top();
        st.push(i);
    }
    return res;
}

template < typename T >
vector < int > prev_smaller(const vector < T >& nums, bool strict = true) {
    int n = nums.size();
    vector < int > res(n, -1);
    stack < int > st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && (strict ? nums[st.top()] >= nums[i] : nums[st.top()] > nums[i]))
            st.pop();
        res[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    return res;
}

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