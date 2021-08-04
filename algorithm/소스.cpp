#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, k;
	cin >> n >> k;

	queue<int> circle;
	for (int i = 1; i <= n; ++i)
		circle.push(i);

	
	int seq = 1;
	vector<int> josephus;

	while (!circle.empty()) {
		if (seq == k) {
			josephus.push_back(circle.front());
			circle.pop();
			seq = 1;
		}
		else {
			circle.push(circle.front());
			circle.pop();
			seq++;
		}
	}

	cout << "<" << josephus[0];
	for (int i = 1; i < n; ++i)
		cout << ", " << josephus[i];
	cout << ">";
	
	return 0;
}