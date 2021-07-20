#include <iostream>
#include <queue>
#include <utility>
using namespace std;

const int MAXN = 100;

int n;
int time= 0;

//���ڸ� 0, �� 1, ��� 2
int board[MAXN+2][MAXN+2] = { 0 };

//���� �����ϰ� �ִ� ��ǥ 
queue <pair<int, int>> snake; 

//<���� ���� �ð����κ��� x��, c�������� ȸ��>
queue <pair<int, char>> moves;

//�̵� ����
int Rdir[4] = {0, 1, 0, -1};
int Cdir[4] = {1, 0, -1, 0};

int game() {
	//<r, c>: ���� ���� �Ӹ��� ��ǥ
	int r = 1;
	int c = 1;
	int dir = 0;
	
	while (true) {
		time++;
		r += Rdir[dir];
		c += Cdir[dir];

		if (r < 1 || r > n) break;
		if (c < 1 || c > n) break;

		if (board[r][c] == 1) 
			break;
		
		else if (board[r][c] == 2) {
			//�Ӹ� �ø���
			board[r][c] = 1;
			snake.push(make_pair(r, c));
		}

		else{
			//�Ӹ� �ø���
			board[r][c] = 1;
			snake.push(make_pair(r, c));
			//���� ���̱�
			pair<int, int> tail = snake.front();
			board[tail.first][tail.second] = 0;
			snake.pop();
		}

		
		if (!moves.empty()) {
			pair<int, char> nextMove = moves.front();
			
			if (nextMove.first == time) {
				//�ݽð�������� ȸ��
				if (nextMove.second == 'L') {
					if (dir == 0) dir = 3;
					else --dir;
				}
				//�ð�������� ȸ��
				else {
					if (dir == 3) dir = 0;
					else ++dir;
				}
				moves.pop();
			}
		}

	}

	return time;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;

	//���
	int k;
	cin >> k;
	for (int i = 0; i < k; ++i) {
		int r, c;
		cin >> r >> c;
		board[r][c] = 2;
	}

	//�̵� ��� 
	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		int x; 
		char c;
		cin >> x >> c;
		moves.push(make_pair(x,c));
	}

	//���� ����
	board[1][1] = 1;
	snake.push(make_pair(1,1));
	cout << game();
	return 0;
}