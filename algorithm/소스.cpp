#include <string>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
	int answer = 0;

	vector<queue<int>> boardQ(30);
	stack<int> st;

	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board.size(); ++j) {
			if (board[i][j] != 0) boardQ[j].push(board[i][j]);
		}
	}

	for (int m = 0; m < moves.size(); ++m) {
		int pos = moves[m] - 1;
		if (boardQ[pos].empty()) continue;

		int num = boardQ[pos].front();
		boardQ[pos].pop();

		if (!st.empty() && st.top() == num) {
			st.pop();
			answer += 2;
		}
		else st.push(num);
	}

	return answer;
}