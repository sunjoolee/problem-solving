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

	//�ڵ���
	vector<int> X;
	vector<int> tournament;

	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		X.push_back(input);
		tournament.push_back(input);

	}

	//�ڵ��� �������� ����
	sort(X.begin(), X.end());

	//�������� ��
	long long sum = 0;

	for (int i = 0; i < n - 1; ++i) {
		//���� ���ϴ� ����� �ڵ���
		int worst = X[i];

		for (auto it = tournament.begin(); it != tournament.end(); ++it) {
			if (*it == worst) {
				//��ʸ�Ʈ�� �� ����
				if (it == tournament.begin()) {
					int right = *(it + 1);
					sum += abs(worst - right);;
				}
				//��ʸ�Ʈ�� �� ����
				else if (it == tournament.end() - 1) {
					int left = *(it - 1);
					sum += abs(worst - left);
				}
				//��ʸ�Ʈ�� �߰�
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