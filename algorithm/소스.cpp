#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int n; //���� ����
int c; //������ ����

vector<int> house;

//���� ������ �� ������ ������ �Ÿ��� dis���� �۾����� �ʵ���
//c���� �����⸦ ��ġ�� �� �ִ°� Ȯ��
bool check(int dis) {
	int pos = house[0]; //���� �ֱٿ� ��ġ�� ������ ��ġ
	int cnt = 1; //������� ��ġ�� ������ ��

	for (int i = 1; i < n; ++i) {
		if ((house[i] - pos) >= dis) {
			pos = house[i];
			cnt++;
		}
		else continue;
	}
	return cnt >= c;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n >> c;
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		house.push_back(input);
	}
	sort(house.begin(), house.end());

	//������ dis�� �ִ� �̺� Ž������ ���ϱ�
	int maxDis = house.back();
	int minDis = 1;
	while (minDis < maxDis) {
		int midDis = (maxDis + minDis + 1) / 2;
		if (check(midDis)) minDis = midDis;
		else maxDis = midDis - 1;
	}

	cout << maxDis;
	return 0;
}