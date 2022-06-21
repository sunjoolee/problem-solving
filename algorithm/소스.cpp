#include <string>
#include <algorithm>
#include <vector>

using namespace std;

const int IMPOSSIBLE = 987654321;

int R;
int C;

int rMove[4] = { 0, 0, 1, -1 };
int cMove[4] = { 1, -1, 0, 0 };

bool inRange(int r, int c) {
	if (r < 0 || r >= R) return false;
	if (c < 0 || c >= C) return false;
	return true;
}


//<win, moves>
pair<int,int> game(vector<vector<int>> board, pair<int, int> aloc, pair<int, int> bloc) {
	//������ �����ε� ĳ������ �����¿� �ֺ� 4ĭ�� ��� ������ ���ų� ���� ���̶� �̵��� �� ���� ���, �й�
	//�� ĳ���Ͱ� ���� ���� ���� ���� ��, ��� ĳ���Ͱ� �ٸ� �������� �̵��Ͽ� �ڽ��� ĳ���Ͱ� ���ִ� ������ ������� �Ǹ� �й�

	bool cantMove = true;

	int minRet = IMPOSSIBLE;
	int maxRet = -1;

	for (int i = 0; i < 4; ++i) {
		int nextR = aloc.first + rMove[i];
		int nextC = aloc.second + cMove[i];

		if (!inRange(nextR, nextC)) continue;
		if (board[nextR][nextC] == 0) continue;
		cantMove = false;

		//������ �̱�� ��� �߻��� ���
		if (aloc.first == bloc.first && aloc.second == bloc.second)
			return { 1, 1 };

		board[aloc.first][aloc.second] = 0;
		pair<int, int> gameResult = game(board, bloc, { nextR, nextC });
		//�̱� ��� �ִ��� ���� �̱�� ���� �÷���
		if (gameResult.first == 0) {
			minRet = min(minRet, 1 + gameResult.second);
		}
		//�� ��� �ִ��� ������ ���� ���� �÷���
		else {
			maxRet = max(maxRet, 1 + gameResult.second);
		}
		board[aloc.first][aloc.second] = 1;
	}

	if (cantMove) return { 0, 0 };

	//�̱� �� �ִ� ��찡 �ִ� ���
	if (minRet != IMPOSSIBLE) return { 1, minRet};
	//�̱� �� �ִ� ��찡 ���� ���
	else return { 0, maxRet };
}

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
	R = board.size();
	C = board[0].size();

	pair<int, int> gameResult = game(board, { aloc[0], aloc[1] }, { bloc[0], bloc[1] });

	int answer = gameResult.second;
	return answer;
}