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

//idx: ���ߺξ��ų ���� ����� ���� �ϴ� ��ġ
//blockH: ���ߺξ��ų ���� ����� ����
//blockW: ���ߺξ��ų ���� ����� �ʺ�
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
			//������ ���װ��� ����� �� ���� ���
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

	//����� �ű��
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


//idx: ���ߺξ��ų ���� ����� ���� �ϴ� ��ġ
//blockH: ���ߺξ��ų ���� ����� ����
//blockW: ���ߺξ��ų ���� ����� �ʺ�
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
		//���� �ٴڿ� ���� �Ϸķ� ��ġ
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

		//����� �� ���� ���� ���׿� ����� �Ѹ��� �ֱ�
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

		//���� �ױ�
		board[BOTTOM - 1][1] = board[BOTTOM][0];
		board[BOTTOM][0] = 0;

		//2���̻� �׿��ִ� ���� ���� �ξ� �� 90�� ȸ���Ͽ� �ױ�
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