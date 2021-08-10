#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

//����ȭ ����: M���� ��緹�̷� ��� ������ ��ȭ�� �� �ִ� ��緹���� ũ�� �� �ּڰ��� ���ض�
//���� ����:  ũ�� x Ȥ�� x������ ��緹�� M���� ��� ������ ��ȭ�� �� �ִ°�?

int n, m;
vector<int> lesson;

bool decision(double x) {
	//��� ������ ��ȭ�ϱ� ���� �ʿ��� ��緹���� ����
	int cnt = 1;

	//�ϳ��� ��緹�̿� �� ������ ������ ��
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		if (sum + lesson[i] > x) {
			cnt++;
			sum = lesson[i];
		}
		else sum += lesson[i];
	}

	return cnt <= m;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;

	//���� ���̰� �� ������ ����
	int longestlesson = 0;
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		lesson.push_back(input);

		longestlesson = max(longestlesson, input);
	}
	
	double hi = 10000;
	double lo = longestlesson;
	for (int it = 0; it < 100; ++it) {
		double mid = (hi + lo) / 2;

		if (decision(mid)) hi = mid;
		else lo = mid;
	}

	cout << lo;

	return 0;
}