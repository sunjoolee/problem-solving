#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> card;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		card.push_back(input);
	}

	sort(card.begin(), card.end());

	//i: 첫번째 수의 인덱스
	//j: 두번째 수의 인덱스
	//k: 세번째 수의 인덱스
	
	int best = 0;
	for (int i = 0; i < n; ++i) {
		//투포인터 알고리즘
		int j = 0;
		int k = n - 1;

		while (j < k) {
			//i,j,k 서로 다른 카드를 가리키도록 함
			if (j == i) {
				j++;
				continue;
			}
			if (k == i) {
				k--;
				continue;
			}

			//i,j,k가 가리키는 세 카드의 합
			int sum = card[i] + card[j] + card[k];

			if (sum > m) {
				k--;
			}
			if(sum == m){
				cout << m;
				return 0;
			}
			if (sum < m) {
				best = max(best, sum);
				j++;
			}
		}
	}

	cout << best;
	return 0;
}