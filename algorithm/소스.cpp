#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//arr[k][n]: k�� nȣ�� ��� �ִ� ����� ��
	int arr[15][15] = { 0 };

	//0�� iȣ���� i���� ����� ����ִ�
	for (int room = 0; room < 15; ++room)
		arr[0][room] = room;

	//1�� ~ 14���� 1 ~ 14ȣ�� ��� �ִ� ��� �� ���
	for (int floor = 1; floor < 15; ++floor) {
		//1ȣ���� �׻� 1���� ����� ��� �ִ�
		arr[floor][0] = arr[floor][1] = 1;

		for (int room = 2; room < 15; ++room)
			arr[floor][room] = arr[floor][room-1]+ arr[floor-1][room];
	}
	
	int T;
	cin >> T;
	while (T--) {
		int k, n;
		cin >> k >> n;
		cout << arr[k][n] << "\n";
	}

	return 0;
}