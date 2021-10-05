#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N, M;

//익은 토마토 1, 안익은 토마토 0, 빈칸 -1
int box[1001][1001];

//좌표 발견 여부 저장
int found[1001][1001] = { 0 };

int dirR[4] = { 0, 0, 1, -1 };
int dirC[4] = { 1, -1, 0, 0 };

int bfs() {
	//토마토가 다 익을 때까지 걸리는 날짜
	int day = 0;

	//q<<좌표, 날짜>
	queue<pair<pair<int, int>, int>> q;

	//익은 토마토 큐에 저장
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (box[i][j] == 1) {
				q.push({ {i, j}, 0});
				found[i][j] = 1;
			}
		}
	}

	while (!q.empty()) {

		pair<pair<int, int>, int> here = q.front();
		int hereR = here.first.first;
		int hereC = here.first.second;
		int hereDay = here.second;
		q.pop();

		//토마토 익음
		box[hereR][hereC] = 1;
		day = hereDay;

		for (int i = 0; i < 4; ++i) {
			int nextR = hereR + dirR[i];
			int nextC = hereC + dirC[i];

			if (nextR < 0 || nextR >= N) continue;
			if (nextC < 0 || nextC >= M) continue;

			//인접한 칸의 발견하지 않은 안익은 토마토 큐에 저장
			if (box[nextR][nextC] == 0 && found[nextR][nextC] == 0) {
				q.push({ {nextR, nextC}, hereDay + 1 });
				found[nextR][nextC] = 1;
			}
		}
	}
	
	//모든 토마토 익었는지 검사
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (box[i][j] == 0) return -1;
		}
	}
	return day;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> M >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			cin >> box[i][j];
		}
	}

	cout << bfs();
	return 0;
}