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

	//i: ù��° ���� �ε���
	//j: �ι�° ���� �ε���
	//k: ����° ���� �ε���
	
	int best = 0;
	for (int i = 0; i < n; ++i) {
		//�������� �˰���
		int j = 0;
		int k = n - 1;

		while (j < k) {
			//i,j,k ���� �ٸ� ī�带 ����Ű���� ��
			if (j == i) {
				j++;
				continue;
			}
			if (k == i) {
				k--;
				continue;
			}

			//i,j,k�� ����Ű�� �� ī���� ��
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