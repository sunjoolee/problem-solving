#include <string>
#include <vector>

using namespace std;
typedef long long ll;

int rSize;
int cSize;
vector<vector<ll>> Board;

//skill {type, r1, c1, r2, c2, degree}
void useSkill(vector<int> skill) {
	int type = skill[0];
	int r1 = skill[1];
	int c1 = skill[2];
	int r2 = skill[3];
	int c2 = skill[4];
	ll degree = skill[5];
	
	for (int r = r1; r <= r2; ++r) {
		for (int c = c1; c <= c2; ++c) {
			if (type == 1) Board[r][c] -= degree;
			else Board[r][c] += degree;
		}
	}
}

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
	rSize = board.size();
	cSize = board[0].size();

	for (int i = 0; i < rSize; ++i) {
		vector<ll> tmp;
		for (int j = 0; j < cSize; ++j) {
			tmp.push_back(board[i][j]);
		}
		Board.push_back(tmp);
	}

	for (int i = 0; i < skill.size(); ++i) {
		useSkill(skill[i]);
	}
	
	int answer = 0;
	for (int i = 0; i <rSize; ++i) {
		for (int j = 0; j < cSize; ++j) {
			if (Board[i][j] <= 0) ++answer;
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