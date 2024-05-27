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

int dx[4] = { 0,1,0,-1};
int dy[4] = { 1,0,-1,0 };
//int dx[8] = { -1,-1,-1,0,0,1,1,1 };
//int dy[8] = { -1,0,1,-1,1,-1,0,1 };

/////////////////////////////////////////////////////////////////////////////////////



int board[100][100];
bool visited[100][100][2];

void solve() {
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> board[i][j];
        }
    }

    int l = board[0][0];
    int r = 1e9;

    while (l < r) {
        int m = (l + r) / 2;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                visited[i][j][0] = visited[i][j][1] = false;
            }
        }

        queue<vector<int>> q;
        q.push({ 0,0,0 });
        visited[0][0][0] = true;

        while (!q.empty()) {
            int x = q.front()[0];
            int y = q.front()[1];
            int s = q.front()[2];
            q.pop();
            for (int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                if (nx < 0 || ny < 0 || nx >= N || ny >= M || visited[nx][ny][s] || board[nx][ny] > m) continue;
                visited[nx][ny][s] = true;
                q.push({ nx,ny,s });
            }

            if (s == 1) continue;
            for (int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir] * 2;
                int ny = y + dy[dir] * 2;
                if (nx < 0 || ny < 0 || nx >= N || ny >= M || visited[nx][ny][s] || board[nx][ny]>m) continue;
                visited[nx][ny][1] = true;
                q.push({ nx,ny,1 });
            }
        }
        if (visited[N - 1][M - 1][0] || visited[N - 1][M - 1][1]) r = m;
        else l = m + 1;

    }
    cout << l;


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
