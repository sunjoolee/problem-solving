#include <iostream>
#include <algorithm>
using namespace std;

int N, M, B;
int ground[501][501];

//���̸� h�� ���ߴµ� �ɸ��� �ð�
int solve(int h) {
	//������ϴ� ����
	int minus = 0;
	//�׾ƾ��ϴ� ����
	int plus = 0;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (ground[i][j] > h) minus += (ground[i][j] - h);
			if (ground[i][j] < h) plus += (h - ground[i][j]);
		}
	}

	if (plus <= (minus + B)) return minus * 2 + plus;
	return -1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> B;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			cin >> ground[i][j];
		}
	}

	int mintime = 987654321;
	int maxh = 0;
	for (int h = 0; h <= 256; ++h) {
		int time = solve(h);
		if (time == -1) continue;
		else if (time <= mintime) {
			mintime = time;
			maxh = h;
		}
	}

	cout << mintime << " " << maxh;
	return 0;
}