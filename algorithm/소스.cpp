#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

deque<int> card;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	if (n == 1) {
		cout << 1;
		return 0;
	}

	for (int i = 1; i <= n; ++i)
		card.push_back(i);

	while (true) {
		card.pop_front();
		if (card.size() == 1) break;

		card.push_back(card.front());
		card.pop_front();
	}

	cout << card.front();
	return 0;
}