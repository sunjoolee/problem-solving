#include <iostream>
#include <math.h>
#include <utility>
#include <algorithm>
using namespace std;

typedef long long ll;

int ccw(pair<ll, ll> a, pair<ll, ll> b) {
	ll cross = a.first * b.second - a.second * b.first;

	if (cross > 0) return 1;
	else if (cross < 0) return -1;
	else return 0;
}

int ccw(pair<ll, ll> p, pair<ll, ll> a, pair<ll, ll> b) {
	a.first -= p.first; a.second -= p.second;
	b.first -= p.first; b.second -= p.second;
	return ccw(a, b);
}

int segmentIntersects(pair<ll, ll> a, pair<ll, ll> b, pair<ll, ll> c, pair<ll, ll> d) {
	int ab = ccw(a, b, c) * ccw(a, b, d);
	int cd = ccw(c, d, a) * ccw(c, d, b);

	if (ab == 0 && cd == 0) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	ll x1, y1, x2, y2, x3, y3, x4, y4;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
	
	pair<ll, ll> a = make_pair(x1, y1);
	pair<ll, ll> b = make_pair(x2, y2);
	pair<ll, ll> c = make_pair(x3, y3);
	pair<ll, ll> d = make_pair(x4, y4);

	cout << segmentIntersects(a, b, c, d);

	return 0;
}