#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int R, C, k;
int cnt = 0;

string mp[6];
int visited[6][6] = { 0 };

int dirr[4] = { 0,0,1,-1 };
int dirc[4] = { 1,-1,0,0 };



//현재 위치 (r, c)이고 이동해온 거리 p인 경우
//거리가 k인 가짓수 반환
void path(int r, int c, int p) {
	//base case
	//오른쪽 위 도착
	if (r == 0 && c == C-1) {
		if (p == k) cnt++;
		return;
	}

	visited[r][c] = 1;
	for (int i = 0; i < 4; ++i) {
		int nextr = r + dirr[i];
		int nextc = c + dirc[i];

		if (nextr >= R || nextr < 0) continue;
		if (nextc >= C || nextc < 0) continue;
		if (visited[nextr][nextc] == 1) continue;
		if (mp[nextr][nextc] == 'T') continue;

		path(nextr, nextc, p + 1);
	}
	visited[r][c] = 0;

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> R >> C >> k;

	for (int i = 0; i < R; ++i)
		cin >> mp[i];

	//경로 계산
	//왼쪽 아래에서 시작
	path(R-1, 0, 1);
	//경로 길이 k인 개수 출력
	cout << cnt++;
	return 0;
}