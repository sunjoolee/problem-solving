#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n;
priority_queue<int, vector<int>, less<int>> maxheap;
priority_queue<int, vector<int>, greater<int>> minheap;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;

		//규칙 1
		if (maxheap.size() == minheap.size()) maxheap.push(input);
		else minheap.push(input);

		//규칙 2
		if ((!minheap.empty()) && (maxheap.top() > minheap.top())) {
			int mx = maxheap.top();
			int mn = minheap.top();

			maxheap.pop();
			minheap.pop();

			maxheap.push(mn);
			minheap.push(mx);
		}

		//중간값 출력
		if (maxheap.size() % 2 == 1) cout << maxheap.top() << "\n";
		else cout << min(maxheap.top(), minheap.top()) << "\n";
	}

	return 0;
}