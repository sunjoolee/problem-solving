#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

//열쇠의 크기와 자물쇠 크기 통일
int SIZE;

vector<vector<int>> rotateVec(vector<vector<int>> v) {
	vector<vector<int>> rotateV(SIZE, vector<int>(SIZE, 0));

	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			rotateV[j][SIZE - i - 1] = v[i][j];
		}
	}

	return rotateV;
}


vector<vector<int>> moveUp(vector<vector<int>> v, int n) {
	vector<vector<int>> moveV;

	for (int i = n; i < SIZE; ++i) 
		moveV.push_back(v[i]);
	
	for(int i = 0; i<n; ++i)
		moveV.push_back(vector<int>(SIZE, 0));

	return moveV;
}

vector<vector<int>> moveDown(vector<vector<int>> v, int n) {
	vector<vector<int>> moveV;

	for (int i = 0; i < n; ++i)
		moveV.push_back(vector<int>(SIZE, 0));

	for (int i = 0; i < SIZE - n; ++i)
		moveV.push_back(v[i]);

	return moveV;
}

vector<vector<int>> moveRight(vector<vector<int>> v, int n) {
	vector<vector<int>> moveV(SIZE, vector<int>());

	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < n; ++j) 
			moveV[i].push_back(0);

		for (int j = 0; j < SIZE - n; ++j) 
			moveV[i].push_back(v[i][j]);
	}

	return moveV;
}

vector<vector<int>> moveLeft(vector<vector<int>> v, int n) {
	vector<vector<int>> moveV(SIZE, vector<int>());

	for (int i = 0; i < SIZE; ++i) {
		for (int j = n; j < SIZE; ++j) {
			moveV[i].push_back(v[i][j]);
		}

		for (int j = 0; j < n; ++j)
			moveV[i].push_back(0);
	}

	return moveV;
}

bool xorVec(vector<vector<int>> k, vector<vector<int>> l) {
	
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (k[i][j] == 0 && l[i][j]) return false;
			if (k[i][j] == 1 && l[i][j]) return false;
		}
	}
	return true;
}


bool solution(vector<vector<int>> key, vector<vector<int>> lock) {

	//열쇠와 자물쇠 크기 맞추기
	SIZE = max(key.size(), lock.size());
	
	//key는 여유 공간 0으로 초기화
	if (key.size() < SIZE) {
		for (int i = 0; i < key.size(); ++i) {
			while(key[i].size() < SIZE) key[i].push_back(0);
		}
		while (key.size() < SIZE) {
			key.push_back(vector<int>(SIZE, 0));
		}
	}
	//lock은 여유 공간 1로 초기화
	if (lock.size() < SIZE) {
		for (int i = 0; i < lock.size(); ++i) {
			while (lock[i].size() < SIZE) lock[i].push_back(1);
		}
		while (lock.size() < SIZE) {
			lock.push_back(vector<int>(SIZE, 1));
		}
	}

	vector<vector<int>> tmp = key;
	for (int rotate = 0; rotate < 4; ++rotate) {
		tmp = rotateVec(tmp);

		vector<vector<int>> tmptmp = tmp;
		for (int up = 0; up <= SIZE; ++up) {
			for (int left = 0; left <= SIZE; ++left) {
				tmptmp = moveLeft(moveUp(tmp, up), left);
				if (xorVec(tmptmp, lock)) return true;
			}
			for (int right = 0; right <= SIZE; ++right) {
				tmptmp = moveRight(moveUp(tmp, up), right);
				if (xorVec(tmptmp, lock)) return true;
			}
		}

		for (int down = 0; down <= SIZE; ++down) {
			for (int left = 0; left <= SIZE; ++left) {
				tmptmp = moveLeft(moveDown(tmp, down), left);
				if (xorVec(tmptmp, lock)) return true;
			}
			for (int right = 0; right <= SIZE; ++right) {
				tmptmp = moveRight(moveDown(tmp, down), right);
				if (xorVec(tmptmp, lock)) return true;
			}
		}
	}

	return false;
}

int main() {
	solution({ {0, 0, 0},{1, 0, 0},{0, 1, 1} }, { {1, 1, 1},{1, 1, 0},{1, 0, 1} });
}