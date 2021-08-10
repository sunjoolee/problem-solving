#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

//����ȭ ����: k���� �׷����� ������ �� �� �׷��� ���� ������ �� �� �ּڰ��� �ִ��� ���ض�
//���� ����: �� �׷쿡�� ���� ������ ���� xȤ�� x�̻��� �ǵ��� �������� k���� �׷����� ���� �� �ִ°�?

int n, k;
vector<int> score;

bool decision(double x) {
	int group = 0;

	//�׷쿡�� ���� ������ ������ ��
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += score[i];
		if (sum >= x) {
			sum = 0;
			group++;
		}
	}
	
	return group >= k;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >>k;

	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		score.push_back(input);
	}

	double hi = 20 *100000;
	double lo = 0;
	for (int it = 0; it < 100; ++it) {
		double mid = (hi + lo) / 2;

		if (decision(mid)) lo = mid;
		else hi = mid;
	}

	cout << lo;
	return 0;
}