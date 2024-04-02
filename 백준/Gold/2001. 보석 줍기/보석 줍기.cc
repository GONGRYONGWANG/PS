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

//int dx[4] = { 1,-1,0,0 };
//int dy[4] = { 0,0,1,-1 };
//int dx[8] = { 1,1,1,-1,-1,-1,0,0 };
//int dy[8] = { 1,0,-1,1,0,-1,1,-1 };

const ll INF = 1e18;
const int inf = 1e9;
const double pi = 3.14159265358979323846;

const string debug = "output: ";

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

ll fastpow(ll x, ll n, ll mod) {
    if (n == 0) return 1;
    if (n % 2) return x * fastpow(x, n - 1, mod) % mod;
    ll half = fastpow(x, n / 2, mod);
    return half * half % mod;
}

ll modinv(ll x, ll mod) {
    return fastpow(x, mod - 2, mod);
}

ll factorial(ll x) {
    ll ret= 1;
    // ret = F[x];
    return ret;
}

ll combination(ll n, ll r, ll mod) {
    return factorial(n) * modinv(factorial(n - r), mod) % mod * modinv(factorial(r), mod) % mod;
}




//////////////////////////////////////////////////////////////////////////////////////


int jew[101];
vector<pii> E[101];

int visited[101][(1 << 14)];


void solve() {

    int N, M, K;
    cin >> N >> M >> K;
    for (int i = 0; i < K; i++) {
        int x;
        cin >> x;
        jew[x] = (1 << i);
    }
    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        E[a].push_back({ b,c });
        E[b].push_back({ a,c });
    }
    visited[1][0] = 1;
    queue<pii> q;
    q.push({ 1,0 });
    while (!q.empty()) {
        int cur = q.front().first;
        int gem = q.front().second;
        q.pop();
        if (jew[cur] && !visited[cur][gem|jew[cur]]) {
            q.push({ cur, gem | jew[cur] });
            visited[cur][gem | jew[cur]] = visited[cur][gem] + 1;
        }
        for (int i = 0; i < E[cur].size(); i++) {
            int nx = E[cur][i].first;
            int tolerance = E[cur][i].second;
            if (visited[nx][gem]) continue;
            if (visited[cur][gem] > tolerance + 1) continue;
            q.push({ nx, gem });
            visited[nx][gem] = visited[cur][gem];
        }
    }

    int ans = 0;

    for (int i = 0; i < (1 << K); i++) {
        ans = max(ans, visited[1][i] - 1);
    }
    cout << ans;

}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}
