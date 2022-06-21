#include <string>
#include <vector>

using namespace std;
typedef long long ll;

int rSize;
int cSize;
vector<vector<ll>> imosBoard;

//skill {type, r1, c1, r2, c2, degree}
void useImos(vector<int> skill) {
	int type = skill[0];
	int r1 = skill[1];
	int c1 = skill[2];
	int r2 = skill[3];
	int c2 = skill[4];
	ll degree = skill[5];
	
	//공격
	if (type == 1) degree= -degree;

	//imos법 사용
	//좌측상단
	imosBoard[r1][c1] += degree;
	//우측상단
	imosBoard[r1][c2 + 1] -= degree;
	//좌측하단
	imosBoard[r2+1][c1] -= degree;
	//우측하단
	imosBoard[r2+1][c2+1] += degree;
}

void calcImosBoard() {
	//가로 방향으로 휩쓸며 누적합 계산
	for (int i = 0; i < rSize + 1; ++i) {
		ll sum = 0;
		for (int j = 0; j < cSize + 1; ++j) {
			sum += imosBoard[i][j];
			imosBoard[i][j] = sum;
		}
	}
	//세로 방향으로 휩쓸며 누적합 계산
	for (int j = 0; j < cSize + 1; ++j) {
		ll sum = 0;
		for (int i = 0; i < rSize + 1; ++i) {
			sum += imosBoard[i][j];
			imosBoard[i][j] = sum;
		}
	}
}


int solution(vector<vector<int>> board, vector<vector<int>> skill) {
	rSize = board.size();
	cSize = board[0].size();

	//imosBoard 0으로 초기화
	//imosBoard의 크기는 board의 크기보다 가로 세로 1만큼 큼
	for (int i = 0; i < rSize + 1; ++i) {
		vector<ll> tmp(cSize + 1, 0);
		imosBoard.push_back(tmp);
	}

	for (int i = 0; i < skill.size(); ++i) {
		useImos(skill[i]);
	}
	
	
	int answer = 0;

	calcImosBoard();
	for (int i = 0; i <rSize; ++i) {
		for (int j = 0; j < cSize; ++j) {
			board[i][j] += imosBoard[i][j];
			if (board[i][j] > 0) ++answer;
		}
	}
	return answer;
}

int main() {
	solution({ {5, 5, 5, 5, 5},
		{5, 5, 5, 5, 5},
		{5, 5, 5, 5, 5},
		{5, 5, 5, 5, 5} }
		, { {1, 0, 0, 3, 4, 4},
		{1, 2, 0, 2, 3, 2},
		{2, 1, 0, 3, 1, 2},
		{1, 0, 1, 3, 3, 1} });
}