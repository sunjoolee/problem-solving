#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long ll;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m;
	cin >> n >> m;

	//���� ���Һ��� ��µǴ� �켱���� ť
	priority_queue<ll, vector<ll>, greater<ll>> card;

	for (int i = 0; i < n; ++i) {
		long long input;
		cin >> input;
		card.push(input);
	}

	for (int i = 0; i < m; ++i) {
		long long a = card.top();
		card.pop();
		long long b = card.top();
		card.pop();

		card.push(a + b);
		card.push(a + b);
	}
	 
	long long sum = 0;
	while(!card.empty()) {
		sum += card.top();
		card.pop();
	}
	cout << sum;

	return 0;
}