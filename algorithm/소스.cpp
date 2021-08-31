#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> dot;
typedef vector<dot> polygon;

int ccw(dot p, dot a, dot b) {
	a.first -= p.first; a.second -= p.second;
	b.first -= p.first; b.second -= p.second;
	
	ll cross = a.first * b.second - a.second * b.first;

	if (cross > 0LL) return 1;
	else if (cross < 0LL) return -1;
	else return 0;
}

bool isInside(dot q, polygon& p){
	int n = p.size();

	//1. 점 q가 p내부에 있기 위한 첫번째 조건
	if (ccw(p[0], p[1], q) < 0) return false;
	if (ccw(p[0], p[n-1], q) > 0) return false;

	//2. 점 q가 p의 내부 중 어느 구간에 있는지 이분 탐색
	int lo = 1, hi = n - 1;
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;

		if (ccw(p[0],p[mid], q) > 0) 
			lo = mid;
		else 
			hi = mid;
	}

	//3. 점 q가 p내부에 있기 위한 마지막 조건
	return ccw(p[lo], q, p[hi]) < 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m, k;
	cin >> n >> m >> k;

	//다각형의 점 반시계 방향으로 주어진다
	polygon a, b;
	ll x, y;
	for (int i = 0; i < n; ++i) {
		cin >> x >> y;
		a.push_back({ x, y });
	}
	for (int i = 0; i < m; ++i) {
		cin >> x >> y;
		b.push_back({ x, y });
	}

	int wrong = 0;
	for (int i = 0; i < k; ++i) {
		cin >> x >> y;
		dot q = { x, y };

		if (!isInside(q, a) || isInside(q, b)) ++wrong;
	}

	if (wrong == 0) cout << "YES";
	else cout << wrong;

	return 0;
}