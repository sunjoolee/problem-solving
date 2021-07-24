#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;


int N;
int cnt = 0;

//육각형의 좌표
//r+c가 홀수일 때 위로 이동 가능
//r+c가 짝수일 때 아래로 이동 가능
int mp[50][50];

int rdir[4] = {0,0,-1,1};
int cdir[4] = {1,-1,0,0};

void moveAnt(int r, int c, int turn, int prevr, int prevc) {
	//base case
	//탐색을 멈춘 경우
	if (mp[r][c] == 1) {
		if (turn == N) cnt++;
		return;
	}
	//탐색을 멈추지 않았는데 turn수가 N번이 된 경우
	if (turn == N) return;

	//DP
	mp[r][c] = 1;

	for (int i = 0; i < 4; ++i) {
		if ((i == 2) && ((r + c) % 2 == 0))
			continue;
		if ((i == 3) && ((r + c) % 2 == 1))
			continue;

		int nextr = r + rdir[i];
		int nextc = c + cdir[i];

		//직전에 이동해온 변은 선택하지 않는다
		if (nextr == prevr && nextc == prevc)
			continue;

		moveAnt(nextr, nextc, turn + 1, r, c);
	}

	mp[r][c] = 0;
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;

	//개미의 첫 번째 이동은 북쪽 방향이다
	//위로 이동할 수 있기 위해 r+c가 홀수인 임의의 좌표를 시작 위치로 설정
	mp[26][25] = 1;
	moveAnt(25, 25, 0, 26, 25);

	cout << cnt;
	return 0;
}