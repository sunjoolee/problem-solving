#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

//global places
vector<string> Gplaces;

bool inRange(int r, int w) {
	if (r < 0 || r >= 5) return false;
	if (w < 0 || w >= 5) return false;
	return true;
}

//인접한 상하좌우 
bool check1(int r, int w) {
	if (inRange(r + 1, w) && Gplaces[r + 1][w] == 'P') return false;
	if (inRange(r - 1, w) && Gplaces[r - 1][w] == 'P') return false;
	if (inRange(r, w + 1) && Gplaces[r][w + 1] == 'P') return false;
	if (inRange(r, w - 1) && Gplaces[r][w - 1] == 'P') return false;
	return true;
}

//먼 상하좌우 
bool check2(int r, int w) {
	if (inRange(r + 2, w) && Gplaces[r + 2][w] == 'P') return Gplaces[r + 1][w] == 'X';
	if (inRange(r - 2, w) && Gplaces[r - 2][w] == 'P') return Gplaces[r - 1][w] == 'X';
	if (inRange(r, w + 2) && Gplaces[r][w + 2] == 'P') return Gplaces[r][w + 1] == 'X';
	if (inRange(r, w - 2) && Gplaces[r][w - 2] == 'P') return Gplaces[r][w - 1] == 'X';
	return true;
}

//대각선 
bool check3(int r, int w) {
	if (inRange(r - 1, w - 1) && Gplaces[r - 1][w - 1] == 'P') return (Gplaces[r - 1][w] == 'X' && Gplaces[r][w - 1] == 'X');
	if (inRange(r - 1, w + 1) && Gplaces[r - 1][w + 1] == 'P') return (Gplaces[r - 1][w] == 'X' && Gplaces[r][w + 1] == 'X');
	if (inRange(r + 1, w - 1) && Gplaces[r + 1][w - 1] == 'P') return (Gplaces[r][w - 1] == 'X' && Gplaces[r + 1][w] == 'X');
	if (inRange(r + 1, w + 1) && Gplaces[r + 1][w + 1] == 'P') return (Gplaces[r][w + 1] == 'X' && Gplaces[r + 1][w] == 'X');
	return true;
}

vector<int> solution(vector<vector<string>> places) {
	vector<int> answer;
	
	for (int i = 0; i < 5; ++i) {
		
		Gplaces = places[i];
		bool flag = true;

		for (int j = 0; j < 5; ++j) {
			for (int k = 0; k < 5; ++k) {
				if (Gplaces[j][k] == 'P') {
					if (!check1(j, k)) flag = false;
					else if (!check2(j, k)) flag = false;
					else if (!check3(j, k)) flag = false;
				}
				if (!flag) break;
			}
			if (!flag) break;
		}

		if (flag) answer.push_back(1);
		else answer.push_back(0);
	}
	return answer;
}