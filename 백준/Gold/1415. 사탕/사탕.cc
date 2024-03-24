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

string debug = "output: ";

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

ll fastpow(ll x, ll n, ll mod = INF) {
    if (n == 0) return 1;
    if (n % 2) return x * fastpow(x, n - 1, mod) % mod;
    ll half = fastpow(x, n / 2, mod);
    return half * half % mod;
}




/*
int COMB[100][100];
int comb(int n, int r) {
    if (r == 0) return 1;
    if (n == r) return 1;
    if (COMB[n][r]) return COMB[n][r];
    return COMB[n][r] = comb(n - 1, r) + comb(n - 1, r - 1);
}
*/

//////////////////////////////////////////////////////////////////////////////////////

bool isprime[500001];

void solve() {

    int N;
    cin >> N;

    map<ll, ll> candy;
    for (int i = 0; i < N; i++) {
        ll x;
        cin >> x;
        candy[x] += 1;
    }

    vector<ll> DP(500001, 0);
    DP[0] = 1;
    for (auto iter = candy.begin(); iter != candy.end(); iter++) {
        for (int i = 500000; i >= 0; i--) {
            if ((*iter).first == 0) {
                DP[i] *= (*iter).second + 1;
                continue;
            }
            for (int j = 1; j <= (*iter).second; j++) {
                if (i - j * (*iter).first < 0) continue;
                DP[i] += DP[i - j * (*iter).first];
            }
        }
    }

    ll ans = 0;
    for (int i = 2; i <= 500000; i++) {
        isprime[i] = true;
    }
    for (ll i = 2; i <= 500000; i++) {
        if (!isprime[i]) continue;
        ans += DP[i];
        for (ll j = i * i; j <= 500000; j += i) {
            isprime[j] = false;
        }
    }
    cout << ans;

}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T;
    // cin >> T;
    T = 1;
    while (T--) {
        solve();
    }

    return 0;
}

