#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <memory.h>

using namespace std;

const int MAX_N = 25;
const int INF = 987654321;


//�޸������̼�
int arr[25][25][4];

vector<vector<int>> boardG;
int N;

//���� 0, 1, 2, 3
int dirR[4] = { 1, -1, 0, 0 };
int dirW[4] = { 0, 0, 1, -1 };

bool inRange(int r, int w) {
	if (r < 0 || r >= N) return false;
	if (w < 0 || w >= N) return false;
	return true;
}

//(curR, curW) -> (N-1, N-1) �̵� �ּ� ��� ��ȯ
//curDir : ���� �̵��ؿ� ���� (0, 1, 2, 3)
int getMinCost(int curR, int curW, int prevDir) {

	//������ ����
	if (curR == N - 1 && curW == N - 1) {
		return 0;
	}

	int& minCost = arr[curR][curW][prevDir];
	if (minCost != -1) {
		return arr[curR][curW][prevDir];
	}
	minCost = INF;

	//���� ��ġ���� �̵� ������ ���� �ľ�
	for (int dir = 0; dir < 4; ++dir) {
		int nextR = curR + dirR[dir];
		int nextW = curW + dirW[dir];
		if (inRange(nextR, nextW) == false || boardG[nextR][nextW] == 1) continue;

		if (dir == prevDir)
			minCost = min(minCost, 100 + getMinCost(nextR, nextW, dir));
		else
			minCost = min(minCost, 600 + getMinCost(nextR, nextW, dir));
	}

	return minCost;
}

int solution(vector<vector<int>> board) {
	N = board.size();
	boardG = board;

	int answer = INF;
	if (boardG[1][0] == 0) {
		memset(arr, -1, sizeof(arr));
		answer = min(answer, 100 + getMinCost(1, 0, 0));
	}
	if (boardG[0][1] == 0) {
		memset(arr, -1, sizeof(arr));
		answer = min(answer, 100 + getMinCost(0, 1, 3));
	}
	return answer;
}



int main() {
	vector<vector<int>> in(4, vector<int> (4, 1));

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			cin >> in[i][j];
		}
	}

	cout << solution(in);

}