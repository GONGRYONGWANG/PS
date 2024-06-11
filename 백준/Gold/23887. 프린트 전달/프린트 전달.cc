#include<iostream>
#include<iomanip>
#include<cstdio>
#include<string>
#include<vector>
#include<utility>
#include<list>
#include<queue>
#include<stack>
#include<deque>
#include<set>
#include<unordered_set>
#include<map>
#include<unordered_map>
#include<cmath>
#include<algorithm>
#include<bitset>
#include<cstdlib>
#include<ctime> // srand(time(0))
#include<regex> // 정규표현식
#include<random> // rand
#include<complex> // complex number
#include<numeric>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef complex<double> cpx;
#define pq priority_queue
#define endl "\n"

const ll INF = 1e18;
const int inf = 1e9;
const double pi = 3.14159265358979323846;

const string debug = "output: ";

struct VectorHasher {
    int operator()(const vector<int>& V) const {
        int hash = V.size();
        for (auto& i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

ll gcd(ll a, ll b) {
    if (a < b) swap(a, b);
    while (b != 0) {
        ll  n = a % b;
        a = b;
        b = n;
    }
    return a;
}

ll lcm(ll a, ll b) {
    ll g = gcd(a, b);
    return a / g * b;
}

ll powmod(ll x, ll n, ll mod) {
    if (n == 0) return 1;
    if (n % 2) return x * powmod(x, n - 1, mod) % mod;
    ll half = powmod(x, n / 2, mod);
    return half * half % mod;
}

ll modinv(ll x, ll mod) {
    return powmod(x, mod - 2, mod);
}

ll factorial(ll x) {
    ll ret = 1;
    // ret = F[x];
    return ret;
}

ll combination(ll n, ll r, ll mod) {
    return factorial(n) * modinv(factorial(n - r), mod) % mod * modinv(factorial(r), mod) % mod;
}

int ccw(pll a, pll b, pll c) {
    return (b.first - a.first) * (c.second - a.second) - (c.first - a.first) * (b.second - a.second);
}

//int dx[4] = { 0,1,0,-1};
//int dy[4] = { 1,0,-1,0 };
int dx[8] = { -1,-1,-1,0,0,1,1,1 };
int dy[8] = { -1,0,1,-1,1,-1,0,1 };

/////////////////////////////////////////////////////////////////////////////////////



vector<int> child[250001];
vector<int> E[250001];

int board[501][501];

struct cmp {
    bool operator()(pii a, pii b) {
        if (a.second == b.second) return a.first > b.first;
        return a.second > b.second;
    }
};

int ANS[250001];
int ans(int x) {
    if (ANS[x]) return ANS[x];
    int ret = 1;
    for (int nx : child[x]) {
        ret += ans(nx);
    }
    return ret;
}


void solve() {
    int N, M, K;
    cin >> N >> M >> K;
    for (int i = 1; i <= K; i++) {
        int x, y;
        cin >> x >> y;
        board[x][y] = i;
        for (int dir = 0; dir < 8; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (nx <= 0 || nx > N || ny <= 0 || ny > M || !board[nx][ny]) continue;
            E[i].push_back(board[nx][ny]);
            E[board[nx][ny]].push_back(i);
        }
    }


    int s;
    cin >> s;

    vector<bool> visited(K + 1, false);
    pq<pii, vector<pii>, cmp> q;
    q.push({ s,0 });
    visited[s] = true;

    while (!q.empty()) {
        int cur = q.top().first;
        int t = q.top().second;
        q.pop();
        for (int nx : E[cur]) {
            if (visited[nx]) continue;
            visited[nx] = true;
            child[cur].push_back(nx);
            q.push({ nx, t + 1 });
        }
    }


    for (int i = 1; i <= K; i++) {
        if (!visited[i]) {
            cout << -1;
            return;
        }
    }


    for (int i = 1; i <= K; i++) {
        cout << ans(i) << " ";
    }


}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T = 1;
    //cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}
