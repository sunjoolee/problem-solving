#include <iostream>
#include <cstring>
#include <utility>
#include <algorithm>
using namespace std;

const int MAXNUM = 300001;

int R, C;
int board[501][501];
int result[501][501] = { 0 };
pair<int, int> cache[501][501];

int rdir[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int cdir[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

pair<int, int> getDest(int r, int c) {

	pair<int, int>& ret = cache[r][c];
	if (ret.first != -1) return ret;
	
	int minVal = MAXNUM;
	int minr, minc;
	for (int i = 0; i < 8; ++i) {
		int candr = r + rdir[i];
		int candc = c + cdir[i];
		if (candr < 1 || candr > R) continue;
		if (candc < 1 || candc > C) continue;

		if (minVal > board[candr][candc]) {
			minVal = board[candr][candc];
			minr = candr;
			minc = candc;
		}
	}

	if (minVal > board[r][c]) {
		ret.first = r;
		ret.second = c;
	}
	else
		ret = getDest(minr, minc);

	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int i = 0; i < 501; ++i)
		for (int j = 0; j < 501; ++j)
			cache[i][j].first = -1;

	cin >> R >> C;
	
	for (int r = 1; r <= R; ++r)
		for (int c = 1; c <= C; ++c)
			cin >> board[r][c];

	for (int r = 1; r <= R; ++r)
		for (int c = 1; c <= C; ++c) {
			pair<int, int> dest = getDest(r, c);
			++result[dest.first][dest.second];
		}

	for (int r = 1; r <= R; ++r) {
		for (int c = 1; c <= C; ++c)
			cout << result[r][c] << " ";
		cout << "\n";
	}

	return 0;
}