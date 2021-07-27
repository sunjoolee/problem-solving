#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	vector<int> tournament;

	cin >> n;
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		tournament.push_back(input);
	}

	int sum = 0;
	for (int worst = n; worst > 1; worst--) {
		for (auto it = tournament.begin(); it != tournament.end(); ++it) {
			if (*it == worst) {
				//토너먼트의 맨 왼쪽
				if (it == tournament.begin()) {
					int right = *(it + 1);

					sum += abs(worst - right);
					tournament.erase(it);
					break;
				}
				//토너먼트의 맨 오른쪽
				else if (it == tournament.end() - 1) {
					int left = *(it - 1);

					sum += abs(worst - left);
					tournament.erase(it);
					break;
				}
				//토너먼트의 중간
				else {
					int right = *(it + 1);
					int left = *(it - 1);

					sum += min(abs(worst - right), abs(worst - left));
					tournament.erase(it);
					break;
				}
			}
		}
	}

	cout << sum;
	return 0;
}