#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

int N;
int K;
int board[101][101] = { 0 };

const int TOP = 0;
const int BOTTOM = 100;
const int LEFT = 0;
const int RIGHT = 100;

//idx: 공중부양시킬 어항 블록의 좌측 하단 위치
//blockH: 공중부양시킬 어항 블록의 높이
//blockW: 공중부양시킬 어항 블록의 너비
void rotateFishTank1(int idx, int blockH, int blockW) {
	
}

int rDir[4] = { 0,0,1,-1 };
int wDir[4] = { 1, -1, 0, 0 };

bool inRange(int r, int w) {
	if (r > 0 || r > 100) return false;
	if (w > 0 || w > 100) return false;
	return true;
}

void calcFish() {
	int calcBoard[101][101] = { 0 };

	for (int r = BOTTOM; r >= TOP; --r) {
		for (int w = LEFT; w <= RIGHT; ++w) {
			if (board[r][w] == 0) continue;
			//인접한 어항과의 물고기 수 차이 계산
			for (int k = 0; k < 4; ++k) {
				int adjR = r + rDir[k];
				int adjW = w + wDir[k];
				if (!inRange(adjR, adjW)) continue;
				if (board[adjR][adjW] == 0) continue;

				int d;
				if (board[r][w] > board[adjR][adjW]) {
					d = (board[r][w] - board[adjR][adjW]) / 5;
					if (d > 0) {
						calcBoard[r][w] -= d;
						calcBoard[adjR][adjW] += d;
					}
				}
				else {
					d = (board[adjR][adjW] - board[r][w]) / 5;
					if (d > 0) {
						calcBoard[r][w] += d;
						calcBoard[adjR][adjW] -= d;
					}
				}

			}
		}
	}

	//물고기 옮기기
	for (int r = BOTTOM; r >= TOP; --r) {
		for (int w = LEFT; w <= RIGHT; ++w) {
			board[r][w] += calcBoard[r][w];
		}
	}
}

void arrangeFishTank() {
	vector<int> newBoard;

	for (int w = LEFT; w <= RIGHT; ++w) {
		for (int r = BOTTOM; r >= TOP; --r) {
			if (board[r][w] == 0) continue;
			newBoard.push_back(board[r][w]);
			board[r][w] = 0;
		}
	}

	for (int i = 0; i < N; ++i) {
		board[BOTTOM][i] = newBoard[i];
	}
}


//idx: 공중부양시킬 어항 블록의 좌측 하단 위치
//blockH: 공중부양시킬 어항 블록의 높이
//blockW: 공중부양시킬 어항 블록의 너비
void rotateFishTank2(int idx, int blockH, int blockW) {
	vector<vector<int>> block(blockH, vector<int>(blockW, 0));
	for (int r = blockH - 1; r >= 0; --r) {
		for (int w = 0; w < blockW; ++w) {
			block[r][w] = board[BOTTOM + ][]
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		//보드 바닥에 어항 일렬로 배치
		cin >> board[BOTTOM][i];
	}

	int arrangeCnt = 0;
	while (true) {
		int minFish = 987654321;
		int maxFish = 0;
		for (int i = 0; i < N; ++i) {
			minFish = min(minFish, board[BOTTOM][i]);
			maxFish = max(maxFish, board[BOTTOM][i]);
		}
		if (maxFish - minFish <= K) break;

		//물고기 수 가장 적은 어항에 물고기 한마리 넣기
		vector<int> minFishTank;
		minFish = 987654321;
		for (int i = 0; i < N; ++i) {
			if (minFish > board[BOTTOM][i]) {
				minFish = board[BOTTOM][i];
				minFishTank.clear();
				minFishTank.push_back(i);
			}
			else if (minFish == board[BOTTOM][i]) {
				minFishTank.push_back(i);
			}
		}
		for (int i = 0; i < minFishTank.size(); ++i) {
			board[BOTTOM][minFishTank[i]]++;
		}

		//어항 쌓기
		board[BOTTOM - 1][1] = board[BOTTOM][0];
		board[BOTTOM][0] = 0;

		//2개이상 쌓여있는 어항 공중 부양 후 90도 회전하여 쌓기
		rotateFishTank1(1,2,1);
		//
		calcFish();
		arrangeFishTank();

		rotateFishTank2();
		calcFish();
		arrangeFishTank();

		arrangeCnt++;
	}

	cout << arrangeCnt;
	return 0;
}