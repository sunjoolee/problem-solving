#include <algorithm>
#include <iostream>
using namespace std;

int n;
int board[15][15] = { 0 };

int col[15] = { 0 };
int dialog1[30] = { 0 };
int dialog2[30] = { 0 };

int cnt = 0;

void nQueen(int curRow) {
	if (curRow == n) {
		cnt++;
		return;
	}

	for (int curCol = 0; curCol < n; ++curCol) {
		if (col[curCol]) continue;
		if (dialog1[curRow - curCol + n -1]) continue;
		if (dialog2[curRow + curCol]) continue;

		col[curCol] = 1;
		dialog1[curRow - curCol + n - 1] = 1;
		dialog2[curRow + curCol] = 1;

		nQueen(curRow + 1);

		col[curCol] = 0;
		dialog1[curRow - curCol + n - 1] = 0;
		dialog2[curRow + curCol] = 0;
	}
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	
	nQueen(0);
	cout << cnt;

	return 0;
}