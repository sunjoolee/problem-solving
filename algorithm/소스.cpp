#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int room;
	cin >> room;

	//1 ~ room������� �������ϴ� ���� ���� = room������ ���Ե� �������� ��ȣ

	//1 ~ 1������� �̵��ϴ� ���
	if (room == 1) {
		cout << 1;
		return 0;
	}

	//�������� ��ȣ
	int hex = 2;
	//�������� ���Ե� ���� ���� ��ȣ
	int start = 2;
	//�������� ���Ե� ���� ����
	int num = 6;

	while (true) {
		//���� �������� ���� ���Ե� ���
		if (start <= room && room <= start + num - 1) {
			cout << hex;
			return 0;
		}
		//���� ���� ���Ե��� �ʾҴٸ� ���� ���������� �̵��ؾ�
		++hex;
		start += num;
		num += 6;
	}

	return 0;
}