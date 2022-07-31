#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int N, M;
	cin >> N >> M;
	
	vector<int> card;
	for (int i = 0; i < N; ++i) {
		int input;
		cin >> input;
		card.push_back(input);
	}

	vector<int> sum;
	for (int i = 0; i < N - 2; ++i) {
		for (int j = i + 1; j < N - 1; ++j) {
			for (int k = j + 1; k < N; ++k) {
				sum.push_back(card[i] + card[j] + card[k]);
			}
		}
	}
	sort(sum.begin(), sum.end());

	//M�� ���� �����鼭 M�� �ִ��� ����� ī��3���� ��
	int left = 0;
	int right = sum.size() - 1;
	while (left < right) {
		int mid = (left + right + 1) / 2;
		if (sum[mid] > M) right = mid - 1;
		else left = mid;
	}

	cout << sum[right];
	return 0;
}