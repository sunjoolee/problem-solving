#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n;
	cin >> n;

	vector<int> A;

	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		A.push_back(input);
	}
	
	deque <int> card;
	int num = 1;
	for (int i = n - 1; i >= 0; --i) {
		if (A[i] == 1) {
			card.push_front(num++);
		}
		else if (A[i] == 2) {
			if (card.empty()) {
				card.push_front(num++);
			}
			else {
				int firstCard = card.front();
				card.pop_front();
				card.push_front(num++);
				card.push_front(firstCard);
			}
		}
		else if (A[i] == 3) {
		card.push_back(num++);
		}
		
	}

	for (int i = 0; i < n; ++i) {
		cout << card[i] << " ";
	}
	return 0;
}