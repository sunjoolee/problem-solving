#include <algorithm>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n, k, m;
	cin >> n >> k >> m;

	deque<int> circle;

	for (int i = 1; i <= n; ++i) {
		circle.push_back(i);
	}

	vector<int> vec;
	bool dirRight = true;

	while (!circle.empty()) {
		if (dirRight) {
			for (int i = 0; i < k - 1; ++i) {
				circle.push_back(circle.front());
				circle.pop_front();
			}
			vec.push_back(circle.front());
			circle.pop_front();
		}
		else {
			for (int i = 0; i < k - 1; ++i) {
				circle.push_front(circle.back());
				circle.pop_back();
			}
			vec.push_back(circle.back());
			circle.pop_back();
		}
		if (vec.size() % m == 0) dirRight = !dirRight;
	}

	for (int i = 0; i < n; ++i) {
		cout << vec[i] << "\n";
	}

	return 0;
}