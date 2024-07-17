#include <bits/stdc++.h>

using namespace std;

#define cin_2d(vec, n, m) for(int i = 0; i < n; i++) for(int j = 0; j < m && cin >> vec[i][j]; j++);
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define fixed(n) fixed << setprecision(n)
#define ceil(n, m) (((n) / (m)) + ((n) % (m) ? 1 : 0))
#define fill(vec, value) memset(vec, value, sizeof(vec));
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

template < typename T = int > struct Point {
    T x, y;
    Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}
    Point(const Point &p) : x(p.x), y(p.y) {}
    Point operator + (const Point &p) const { return Point(x + p.x, y + p.y); }
    Point operator - (const Point &p) const { return Point(x - p.x, y - p.y); }
    Point operator * (T c) const { return Point(x * c, y * c); }
    Point operator / (T c) const { return Point(x / c, y / c); }
    bool operator == (const Point &p) const { return x == p.x && y == p.y; }
    bool operator != (const Point &p) const { return x != p.x || y != p.y; }
    bool operator < (const Point &p) const { return make_pair(y, x) < make_pair(p.y, p.x); }
    bool operator > (const Point &p) const { return make_pair(y, x) > make_pair(p.y, p.x); }
    bool operator <= (const Point &p) const { return make_pair(y, x) <= make_pair(p.y, p.x); }
    bool operator >= (const Point &p) const { return make_pair(y, x) >= make_pair(p.y, p.x); }
    friend istream& operator >> (istream &in, Point &p) { return in >> p.x >> p.y; }
    friend ostream& operator << (ostream &out, const Point &p) { return out << p.x << ' ' << p.y; }
    T dot(const Point &p) const { return x * p.x + y * p.y; }
    T cross(const Point &p) const { return x * p.y - y * p.x; }
    T cross(const Point &a, const Point &b) const { return (a - *this).cross(b - *this); }
    T dist() const { return x * x + y * y; }
    T dist(const Point &p) const { return (*this - p).dist(); }
    double distance() const { return sqrt(1.0 * dist()); }
    double distance(const Point &p) const { return sqrt(1.0 * dist(p)); }
    double angle() const { return atan2(y, x); }
    double angle(const Point &p) const { return atan2(cross(p), dot(p)); }
    Point unit() const { return *this / dist(); }
    Point perp() const { return Point(-y, x); }
    Point rotate(double a) const { return Point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
    Point rotate(const Point &p, double a) const { return (*this - p).rotate(a) + p; }
    Point normal() const { return perp().unit(); }
};
template < typename T = int > struct Convex_Hull {

    typedef Point < T > point;

    // Returns the orientation of the point c with respect to the line a-b
    int orientation(const point& a, const point& b, const point& c) {
        T val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
        if(val < 0) return -1; // clockwise
        if(val > 0) return 1; // counter-clockwise
        return 0; // collinear
    }

    // Returns true if c is on the left side of the line a-b
    bool cw(const point& a, const point& b, const point& c, bool include_collinear) {
        int o = orientation(a, b, c);
        return o < 0 || (include_collinear && o == 0);
    }

    // return if a-b-c are collinear
    bool is_collinear(const point& a, const point& b, const point& c) {
        return orientation(a, b, c) == 0;
    }

    // Returns a list of points on the convex hull
    vector < point > Convex_Points;

    Converx_Hull(vector < point > &points, bool include_collinear = false) {
        point p0 = *min_element(all(points));
        sort(all(points), [&](const point& a, const point& b) {
            int o = orientation(p0, a, b);
            if(o == 0) return p0.dist(a) < p0.dist(b);
            return o < 0;
        });
        // remove redundant points
        points.erase(unique(all(points)), points.end());

        if(include_collinear){
            int idx = sz(points) - 1;
            // remove collinear points from the end
            while(idx > 0 && is_collinear(p0, points[idx], points.back())) idx--;
            reverse(points.begin() + idx + 1, points.end());
        }
        
        for(const point& p : points) {
            while(sz(Convex_Points) > 1 && !cw(Convex_Points[sz(Convex_Points) - 2], Convex_Points.back(), p, include_collinear)) 
                Convex_Points.pop_back();
            Convex_Points.push_back(p);
        }
    }
};

void Solve(){
    
}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--)
        Solve();
    return 0;
}