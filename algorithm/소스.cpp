#include <iostream>
#include <queue>
#include <utility>
using namespace std;

const int MAXN = 100;

int n;
int time= 0;

//빈자리 0, 뱀 1, 사과 2
int board[MAXN+2][MAXN+2] = { 0 };

//뱀이 차지하고 있는 좌표 
queue <pair<int, int>> snake; 

//<게임 시작 시간으로부터 x초, c방향으로 회전>
queue <pair<int, char>> moves;

//이동 방향
int Rdir[4] = {0, 1, 0, -1};
int Cdir[4] = {1, 0, -1, 0};

int game() {
	//<r, c>: 현재 뱀의 머리의 좌표
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
			//머리 늘리기
			board[r][c] = 1;
			snake.push(make_pair(r, c));
		}

		else{
			//머리 늘리기
			board[r][c] = 1;
			snake.push(make_pair(r, c));
			//꼬리 줄이기
			pair<int, int> tail = snake.front();
			board[tail.first][tail.second] = 0;
			snake.pop();
		}

		
		if (!moves.empty()) {
			pair<int, char> nextMove = moves.front();
			
			if (nextMove.first == time) {
				//반시계방향으로 회전
				if (nextMove.second == 'L') {
					if (dir == 0) dir = 3;
					else --dir;
				}
				//시계방향으로 회전
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

	//사과
	int k;
	cin >> k;
	for (int i = 0; i < k; ++i) {
		int r, c;
		cin >> r >> c;
		board[r][c] = 2;
	}

	//이동 경로 
	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		int x; 
		char c;
		cin >> x >> c;
		moves.push(make_pair(x,c));
	}

	//게임 시작
	board[1][1] = 1;
	snake.push(make_pair(1,1));
	cout << game();
	return 0;
}