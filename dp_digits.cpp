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

// ═══ CUSTOMIZE ════════════════════════════════════════════════════════════════

const int K        = 7;   // example: digit-sum divisible by K
const int INIT_ST  = 0;   // initial state
const int MAX_ST   = 100; // state space size (exclusive upper bound)

int  transit(int state, int digit) { return (state + digit) % K; }
bool accept (int state)            { return state == 0; }

// ══════════════════════════════════════════════════════════════════════════════

const int MAXD = 19;
ll   dp [MAXD][2][2][2][MAX_ST];
bool vis[MAXD][2][2][2][MAX_ST];
string Lo, Hi;

ll rec(int pos, bool tight_lo, bool tight_hi, bool leading_zero, int state) {
    if (pos == sz(Hi)) return !leading_zero && accept(state);

    ll &ret = dp [pos][tight_lo][tight_hi][leading_zero][state];
    bool &seen = vis[pos][tight_lo][tight_hi][leading_zero][state];
    if (seen) return ret;
    seen = true, ret = 0;

    int lo_digit = tight_lo ? Lo[pos] - '0' : 0;
    int hi_digit = tight_hi ? Hi[pos] - '0' : 9;

    for (int digit = lo_digit; digit <= hi_digit; digit++) {
        bool new_lz = leading_zero && digit == 0;
        int  new_state = new_lz ? INIT_ST : transit(state, digit);
        ret += rec(
            pos + 1,
            tight_lo && digit == lo_digit,
            tight_hi && digit == hi_digit,
            new_lz,
            new_state
        );
    }
    return ret;
}

ll solve(ll l, ll r) {
    Lo = to_string(l);
    Hi = to_string(r);
    if (sz(Lo) < sz(Hi))
        Lo = string(sz(Hi) - sz(Lo), '0') + Lo;
    memset(vis, false, sizeof(vis));
    return rec(0, true, true, true, INIT_ST);
}

void Solve() {
    ll l, r;
    cin >> l >> r;
    cout << solve(l, r) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int test_cases = 1;
    // cin >> test_cases;
    for (int tc = 1; tc <= test_cases; tc++) {
        // cout << "Case #" << tc << ": ";
        Solve();
    }
    return 0;
}
