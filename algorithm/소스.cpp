#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

int n, m;
//set: 균형 이진 트리 구조
set <int> card;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		card.insert(input);
	}

	cin >> m;
	for (int i = 0; i < m; ++i) {
		int input;
		cin >> input;

		if (card.find(input) == card.end())
			cout << "0 ";
		else cout << "1 ";
	}

	return 0;
}