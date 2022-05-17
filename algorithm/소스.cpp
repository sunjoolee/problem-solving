#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;


bool isPalindrome(vector<int> v) {
	if (v.empty()) return true;

	int size = v.size();
	if (size % 2 != 0) return false;

	for (int i = 0; i < size / 2; ++i) {
		if (v[i] != v[size - i - 1]) return false;
	}
	return true;
}

int maxCnt = -1;
map<queue<int>, int> cache;

void dp(vector<int> v, queue<int> q, int cnt) {
	if (q.empty()) {
		if (v.empty()) maxCnt = max(maxCnt, cnt);
		return;
	}

	if (cache.find(q) != cache.end()) {
		if (cache[q] > cnt) return;
	}
	else cache[q] = cnt;

	v.push_back(q.front());
	q.pop();
	
	if (isPalindrome(v)) {
		dp(vector<int>(), q, cnt + 1);
	}
	dp(v, q, cnt);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n;
	cin >> n;

	queue<int> q;
	for (int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		q.push(a);
	}

	dp(vector<int>(), q, 0);

	if (maxCnt == 0) cout << -1;
	else cout << maxCnt;

	return 0;
}