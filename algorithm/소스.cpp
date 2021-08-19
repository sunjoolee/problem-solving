#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//arr[k][n]: k층 n호에 살고 있는 사람의 수
	int arr[15][15] = { 0 };

	//0층 i호에는 i명의 사람이 살고있다
	for (int room = 0; room < 15; ++room)
		arr[0][room] = room;

	//1층 ~ 14층의 1 ~ 14호에 살고 있는 사람 수 계산
	for (int floor = 1; floor < 15; ++floor) {
		//1호에는 항상 1명의 사람이 살고 있다
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