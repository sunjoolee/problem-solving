#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//���� M, �� N
int M, N;

vector<vector<int>> intBoard;
vector<vector<int>> eraseBoard;

bool inRange(int r, int w) {
	if (r < 0 || r >= M) return false;
	if (w < 0 || w >= N) return false;
	return true;
}

//(r, w)(r, w+1)
//(r+1, w)(r+1, w+1)
// 2x2 ���簢���� ��ǥ intBoard���� ��� ������ Ȯ��
bool findSquare(int r, int w) {
	if (!inRange(r, w + 1) || !inRange(r + 1, w) || !inRange(r + 1, w + 1)) return false;
	
	int cur = intBoard[r][w];
	if ((cur == intBoard[r][w + 1]) && (cur == intBoard[r + 1][w]) && (cur == intBoard[r + 1][w + 1])) return true;
	else return false;
}


//(r, w)(r, w+1)
//(r+1, w)(r+1, w+1)
// 2x2 ���簢���� ��ǥ eraseBoard�� üũ�ϸ�, ���Ӱ� üũ�� ĭ�� �� ������ ��ȯ
int eraseSquare(int r, int w) {
	int cnt = 0;
	
	if (eraseBoard[r][w] == 0) cnt++;
	if (eraseBoard[r][w+1] == 0) cnt++;
	if (eraseBoard[r+1][w] == 0) cnt++;
	if (eraseBoard[r+1][w+1] == 0) cnt++;

	eraseBoard[r][w] = eraseBoard[r][w+1] = eraseBoard[r+1][w] = eraseBoard[r+1][w+1] = 1;

	return cnt;
}

//(r, w)�� ������ ��� ȣ�� 
void moveBoardDown(int r, int w) {
	for (int i = r; i > 0 ; --i) {
		intBoard[i][w] = intBoard[i - 1][w];
	}
	intBoard[0][w] = -1;
	return;
}

int solution(int m, int n, vector<string> board) {

	//�������� �ʱ�ȭ
	M = m;
	N = n;
	for (int i = 0; i < M; ++i) {
		vector<int> boardBuff;
		vector<int> eraseBuff;
		for (int j = 0; j < N; ++j) {
			boardBuff.push_back(board[i][j]);
			eraseBuff.push_back(0);
		}
		intBoard.push_back(boardBuff);
		eraseBoard.push_back(eraseBuff);
	}


	int answer = 0;

	while (true) {
		int eraseCnt = 0;
		//intBoard ��ȸ�ϸ� 2x2 ĭ ã��
		for (int r = 0; r < M; ++r) {
			for (int w = 0; w < N; ++w) {
				// intBoard ��ĭ�� ��� ��ŵ
				if (intBoard[r][w] == -1) continue;

				// 2x2 ĭ�� ��� ������ �˻�
				// ��� ���ٸ� eraseBoard�� �������� ĭ üũ & ���Ӱ� üũ�� ĭ�� �� �� ���� ���
				if (findSquare(r, w)) eraseCnt += eraseSquare(r, w);
			}
		}

		//������ ĭ ���� ��� ���� ����
		if (eraseCnt == 0) break;
		else answer += eraseCnt;

		//intBoard ĭ ��ġ ����
		for (int w = 0; w < N; ++w) {
			for (int r = 0; r < M; ++r) {
				if (eraseBoard[r][w] == 1) {
					moveBoardDown(r, w);
					eraseBoard[r][w] = 0;
				}
			}
		}
	}

	return answer;
}

/*
int main() {
	vector<string> v = { "CCBDE", "AAADE", "AAABF", "CCBBF" };
	solution(4, 5, v);
}
*/