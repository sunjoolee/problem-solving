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
	//움직일 차례인데 캐릭터의 상하좌우 주변 4칸이 모두 발판이 없거나 보드 밖이라서 이동할 수 없는 경우, 패배
	//두 캐릭터가 같은 발판 위에 있을 때, 상대 캐릭터가 다른 발판으로 이동하여 자신의 캐릭터가 서있던 발판이 사라지게 되면 패배

	bool cantMove = true;

	int minRet = IMPOSSIBLE;
	int maxRet = -1;

	for (int i = 0; i < 4; ++i) {
		int nextR = aloc.first + rMove[i];
		int nextC = aloc.second + cMove[i];

		if (!inRange(nextR, nextC)) continue;
		if (board[nextR][nextC] == 0) continue;
		cantMove = false;

		//무조건 이기는 경우 발생한 경우
		if (aloc.first == bloc.first && aloc.second == bloc.second)
			return { 1, 1 };

		board[aloc.first][aloc.second] = 0;
		pair<int, int> gameResult = game(board, bloc, { nextR, nextC });
		//이긴 경우 최대한 빨리 이기기 위해 플레이
		if (gameResult.first == 0) {
			minRet = min(minRet, 1 + gameResult.second);
		}
		//진 경우 최대한 느리게 지기 위해 플레이
		else {
			maxRet = max(maxRet, 1 + gameResult.second);
		}
		board[aloc.first][aloc.second] = 1;
	}

	if (cantMove) return { 0, 0 };

	//이길 수 있는 경우가 있는 경우
	if (minRet != IMPOSSIBLE) return { 1, minRet};
	//이길 수 있는 경우가 없는 경우
	else return { 0, maxRet };
}

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
	R = board.size();
	C = board[0].size();

	pair<int, int> gameResult = game(board, { aloc[0], aloc[1] }, { bloc[0], bloc[1] });

	int answer = gameResult.second;
	return answer;
}