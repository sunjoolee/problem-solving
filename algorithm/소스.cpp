#include <iostream>
#include <vector>
#include <climits>
#include <math.h>
#include <algorithm>
using namespace std;

typedef long long int ll;

int bitCount(ll x) {
	if (x == 0) return 0;
	return (x % 2) + bitCount(x / 2);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int t;
	cin >> t;
	while(t--) {
		int k;
		cin >> k;

		vector<pair<ll,ll>> dots;

		for (int i = 0; i < k; ++i) {
			ll x, y;
			cin >> x >> y;
			dots.push_back({ x,y });
		}

		ll minVec = LLONG_MAX;
		for (ll set = 0; set < (1 << k) - 1; set++) {
			if (bitCount(set) != (k / 2)) continue;

			ll x = 0; ll y = 0;
			for (int i = 0; i < k; ++i) {
				if (set & (1 << i)) {
					x += dots[i].first;
					y += dots[i].second;
				}
				else {
					x -= dots[i].first;
					y -= dots[i].second;
				}
			}

			ll resultVec = (x*x) + (y*y);
			minVec = min(minVec, resultVec);
		}

		cout << fixed;
		cout.precision(7);
		cout << sqrt(double(minVec)) << "\n";
	}

	return 0;
}