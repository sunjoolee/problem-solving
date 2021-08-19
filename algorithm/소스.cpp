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

	//1 ~ room번방까지 지나야하는 방의 개수 = room번방이 포함된 육각형의 번호

	//1 ~ 1번방까지 이동하는 경우
	if (room == 1) {
		cout << 1;
		return 0;
	}

	//육각형의 번호
	int hex = 2;
	//육각형에 포함된 방의 시작 번호
	int start = 2;
	//육각형에 포함된 방의 개수
	int num = 6;

	while (true) {
		//현재 육각형에 방이 포함된 경우
		if (start <= room && room <= start + num - 1) {
			cout << hex;
			return 0;
		}
		//현재 방이 포함되지 않았다면 다음 육각형으로 이동해야
		++hex;
		start += num;
		num += 6;
	}

	return 0;
}