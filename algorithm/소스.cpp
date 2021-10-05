#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N, M, H;

//���� �丶�� 1, ������ �丶�� 0, ��ĭ -1
int box[101][101][101];

//��ǥ �߰� ���� ����
int found[101][101][101] = { 0 };

int dirR[6] = { 0, 0, 1, -1, 0, 0 };
int dirC[6] = { 1, -1, 0, 0, 0, 0 };
int dirH[6] = { 0, 0, 0, 0, 1, -1 };

struct Tomato {
	int row;
	int col;
	int height;
};

int bfs() {
	//�丶�䰡 �� ���� ������ �ɸ��� ��¥
	int day = 0;

	queue<pair<Tomato, int>> q;

	//���� �丶�� ť�� ����
	for (int k = 0; k < H; ++k) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				if (box[i][j][k] == 1) {
					q.push({ {i, j, k}, 0 });
					found[i][j][k] = 1;
				}
			}
		}
	}

	while (!q.empty()) {

		pair<Tomato, int> here = q.front();
		Tomato hereTomato = here.first;
		int hereR = hereTomato.row;
		int hereC = hereTomato.col;
		int hereH = hereTomato.height;
		int hereDay = here.second;
		q.pop();

		//�丶�� ����
		box[hereR][hereC][hereH] = 1;
		day = hereDay;

		for (int i = 0; i < 6; ++i) {
			int nextR = hereR + dirR[i];
			int nextC = hereC + dirC[i];
			int nextH = hereH + dirH[i];

			if (nextR < 0 || nextR >= N) continue;
			if (nextC < 0 || nextC >= M) continue;
			if (nextH < 0 || nextH >= H) continue;

			//������ ĭ�� �߰����� ���� ������ �丶�� ť�� ����
			if (box[nextR][nextC][nextH] == 0 && found[nextR][nextC][nextH] == 0) {
				q.push({ {nextR, nextC,nextH}, hereDay + 1 });
				found[nextR][nextC][nextH] = 1;
			}
		}
	}
	
	//��� �丶�� �;����� �˻�

	for (int k = 0; k < H; ++k) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				if (box[i][j][k] == 0) return -1;
			}
		}
	}
	return day;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> M >> N >> H;
	for (int k = 0; k < H; ++k) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				cin >> box[i][j][k];
			}
		}
	}

	cout << bfs();
	return 0;
}