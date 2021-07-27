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
	cin >> n;

	//코딩력
	vector<int> X;
	vector<int> tournament;

	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		X.push_back(input);
		tournament.push_back(input);

	}

	//코딩력 오름차순 정렬
	sort(X.begin(), X.end());

	//지루함의 합
	long long sum = 0;

	for (int i = 0; i < n - 1; ++i) {
		//가장 못하는 사람의 코딩력
		int worst = X[i];

		for (auto it = tournament.begin(); it != tournament.end(); ++it) {
			if (*it == worst) {
				//토너먼트의 맨 왼쪽
				if (it == tournament.begin()) {
					int right = *(it + 1);
					sum += abs(worst - right);;
				}
				//토너먼트의 맨 왼쪽
				else if (it == tournament.end() - 1) {
					int left = *(it - 1);
					sum += abs(worst - left);
				}
				//토너먼트의 중간
				else {
					int right = *(it + 1);
					int left = *(it - 1);
					sum += min(abs(worst - right), abs(worst - left));
				}

				tournament.erase(it);
				break;
			}
		}
	}

	cout << sum;
	return 0;
}