#include <algorithm>
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

typedef long long ll;

//색이 n인 점들의 벡터 = vec[n]
vector<vector<ll>>vec(100000, vector<ll>());

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		ll x;
		int y;
		cin >> x >> y;
		vec[y-1].push_back(x);
	}

	ll sum = 0;
	for (int i = 0; i < n; ++i) {
		if (vec[i].size() < 2) continue;

		sort(vec[i].begin(), vec[i].end());

		for (int j = 0; j < vec[i].size(); ++j) {
			ll minD;
			if (j == 0) {
				minD = abs(vec[i][j] - vec[i][j + 1]);
			}
			else if (j == vec[i].size() - 1) {
				minD = abs(vec[i][j] - vec[i][j - 1]);
			}
			else {
				minD = min(abs(vec[i][j] - vec[i][j + 1]),abs( vec[i][j] - vec[i][j - 1]));
			}
			
			sum += minD;
		}
	}

	cout << sum;
	return 0;
}