#include <iostream>
#include <vector>
#include <math.h>
#include <utility>
#include <algorithm>
using namespace std;

typedef pair<int, int> dot;
typedef vector<dot> polygon;

double norm(dot a) {
	return hypot(a.first, a.second);
}

int ccw(dot a, dot b) {
	int cross = a.first * b.second - a.second * b.first;

	if (cross > 0) return 1;
	else if (cross < 0) return -1;
	else return 0;
}

int ccw(dot p, dot a, dot b) {
	a.first -= p.first; a.second -= p.second;
	b.first -= p.first; b.second -= p.second;
	return ccw(a, b);
}

int segmentIntersects(dot a, dot b, dot c, dot d) {
	int ab = ccw(a, b, c) * ccw(a, b, d);
	int cd = ccw(c, d, a) * ccw(c, d, b);

	if (ab == 0 && cd == 0) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}

polygon giftWrap(const vector<dot>& points) {
	int n = points.size();
	polygon hull;

	dot pivot = *min_element(points.begin(), points.end());
	hull.push_back(pivot);
	while (true) {
		dot ph = hull.back();
		dot next = points[0];
		for (int i = 1; i < n; ++i) {
			int cross = ccw(ph, next, points[i]);
			double dist = norm(make_pair(next.first - ph.first, next.second - ph.second)) - norm(make_pair(points[i].first - ph.first, points[i].second - ph.second));

			if (cross > 0 || (cross == 0 && dist < 0))
				next = points[i];
		}
		if (next == pivot) break;
		hull.push_back(next);
	}
	return hull;
}

bool isInside(dot q, const polygon& p) {
	int crosses = 0;
	for (int i = 0; i < p.size(); ++i) {
		int j = (i + 1) % p.size();
		if (p[i].second > q.second != p[j].second > q.second) {
			double atX = (p[j].first - p[i].first)*(q.second - p[i].second) / (p[j].second - p[i].second) + p[i].first;
			if (q.first < atX) {
				++crosses;
			}
		}
	}
	return crosses % 2 > 0;
}

bool polygonIntersects(const polygon& p, const polygon& q) {
	int n = p.size();
	int m = q.size();
	if (isInside(p[0], q) || isInside(q[0], p)) return true;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (segmentIntersects(p[i], p[(i + 1) % n], q[j], q[(j + 1) % m]))
				return true;
		}
	}

	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;

	while (T--) {
		vector<dot> black;
		vector<dot> white;

		int n, m;
		cin >> n >> m;

		for (int i = 0; i < n; ++i) {
			int a, b;
			cin >> a >> b;
			black.push_back(make_pair(a, b));
		}
		for (int i = 0; i < m; ++i) {
			int a, b;
			cin >> a >> b;
			white.push_back(make_pair(a, b));
		}

		polygon convex_hull1 = giftWrap(black);
		polygon convex_hull2 = giftWrap(white);

		if (polygonIntersects(convex_hull1, convex_hull2))
			cout << "NO\n";
		else
			cout << "YES\n";
	}

	return 0;
}