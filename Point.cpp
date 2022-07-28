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

struct Point {

    double x, y;

    using Vector = Point;

    Point(const double& a, const double& b) : x(a), y(b) { }

    Point(const Point &other) : Point(other.x, other.y) { }

    Point &operator = (const Point &other) {
        x = other.x, y = other.y;
        return *this;
    }

    Point &operator -= (const Point &other) {
        Point(x - other.x, y - other.y);
        return *this;
    }

    Point &operator += (const Point &other) {
        Point(x + other.x, y + other.y);
        return *this;
    }

    Point &operator *= (const Point &other) {
        Point(x * other.x, y * other.y);
        return *this;
    }

    Point operator + (const Point &other) const {
        return Point(x + other.x, y + other.y);
    }

    Point operator - (const Point &other) const {
        return Point(x - other.x, y - other.y);
    }

    Point operator * (const ll factor) const {
        return Point(x * factor, y * factor);
    }

    // factor must be long double
    Point operator / (const ll factor) const {
        assert(factor != 0);
        return Point(x / factor, y / factor);
    }

    Point operator - () const {
        return Point(-x, -y);
    }

    bool operator == (const Point &other) const {
        return (abs(x - other.x) < EPS && abs(y - other.y) < EPS);
    }

    bool operator != (const Point &other) const {
        return !operator == (other);
    }

    bool operator < (const Point &other) const {
        if (abs(x - other.x) < EPS) { //equal
            if (abs(y - other.y) < EPS) return false;
            return y < other.y;
        }
        return x < other.x;
    }

    bool operator <= (const Point &other) const {
        return (operator==(other) || operator<(other));
    }

    bool operator > (const Point &other) const {
        if (abs(x - other.x) < EPS) { //equal
            if (abs(y - other.y) < EPS) return false;
            return y > other.y;
        }
        return x > other.x;
    }

    bool operator >= (const Point &other) const {
        return operator==(other) || operator>(other);
    }

    Point translate(const Vector &t) const {
        return this -> operator + (t);
    }

    // scaling vector c -> p by ratio
    Point scale(const Point &c, const double ratio) {
        // make vector c -> p then scale this vector by ratio
        // then get the new point and return it
        // return new Point p' not new Vector cp'
        return (*this - c) * ratio + c;
    }

    Point scale(const double ratio) const {
        return operator * (ratio); // return new Vector v'
    }

    // rotate point by theta degree counter-clockwise around point c
    Point rotate(const Point &c, const double deg) const {
        double rad = deg / 180.0 * acos(-1);
        Vector vec(*this - c);
        vec = Vector(vec.x * cos(rad) - vec.y * sin(rad), vec.y * cos(rad) + vec.x * sin(rad));
        return vec + c;
    }

    // clockwise
    Point rotate90(const Point &c) const {
        //	vec(x, y) -> vec(y, -x);
        Vector vec(*this - c);
        return Point(vec.y, -vec.x) + c;
    }

    // clockwise
    Point rotate180(const Point &c) const {
        //	vec(x, y) -> vec(-x, -y);
        Vector vec(*this - c);
        vec = -vec;
        return vec + c;
    }

    // clockwise
    Point rotate270(const Point &c) const {
        //	vec(x, y) -> vec(-y, x);
        Vector vec(*this - c);
        return Point(-vec.y, vec.x) + c;
    }

    Point perp() const {
        return this -> rotate270(Point(0, 0));
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