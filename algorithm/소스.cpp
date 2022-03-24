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
			rotateV[j][SIZE - i] = v[i][j];
		}
	}

	return rotateV;
}

vector<ll> toBitmask(vector<vector<int>> intVec) {
	vector<ll> llVec(SIZE, 0LL);

	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (intVec[i][j] == 1) 
				llVec[i] = llVec[i] | (1 << j);
		}
	}

	return llVec;
}

vector<ll> bitmaskMoveUpDown(vector<ll> v, int flag) {
	vector<ll> moveV;

	//up
	if (flag == 0) {
		for (int i = 1; i < SIZE; ++i) {
			moveV.push_back(v[i]);
		}
		moveV.push_back(0LL);
	}
	//down
	else {
		moveV.push_back(0LL);
		for (int i = 0; i < SIZE - 1; ++i) {
			moveV.push_back(v[i]);
		}
	}
	return moveV;
}

vector<ll> toBitmaskMoveRightLeft(vector<ll> v, int flag) {
	vector<ll> moveV;

	for (int i = 0; i < SIZE; ++i) {
		//right
		if (flag == 0)
			moveV.push_back(v[i] >> 1);	
		//left
		else 
			moveV.push_back(v[i] << 1);
	}

	return moveV;
}

bool keyXorLock(vector<ll> k, vector<ll> l) {
	ll correct = (1 << SIZE) - 1;

	for (int i = 0; i < SIZE; ++i) {
		if ((k[i] ^ l[i]) & correct != correct) 
			return false;
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


	for (int rotate = 0; rotate < 4; ++rotate) {
		if (rotate != 0) key = rotateVec(key);
		vector<ll> lockBitmask = toBitmask(lock);

		vector<ll> tmpKey = toBitmask(key);
		vector<ll> tmpTmpKey;

		for (int up = 0; up < SIZE; ++up) {
			if(up != 0) tmpKey = bitmaskMoveUpDown(tmpKey, 0);

			tmpTmpKey = tmpKey;
			for (int left = 0; left < SIZE; ++left) {
				if (left != 0) tmpTmpKey = toBitmaskMoveRightLeft(tmpTmpKey, 1);

				if (keyXorLock(tmpTmpKey, lockBitmask)) return true;
			}
			
			tmpTmpKey = tmpKey;
			for (int right = 0; right < SIZE; ++right) {
				if (right != 0) tmpTmpKey = toBitmaskMoveRightLeft(tmpTmpKey, 0);

				if (keyXorLock(tmpTmpKey, lockBitmask)) return true;
			}
		}

		tmpKey = toBitmask(key);
		for (int down = 0; down < SIZE; ++down) {
			if (down != 0) tmpKey = bitmaskMoveUpDown(tmpKey, 0);

			tmpTmpKey = tmpKey;
			for (int left = 0; left < SIZE; ++left) {
				if (left != 0) tmpTmpKey = toBitmaskMoveRightLeft(tmpTmpKey, 1);

				if (keyXorLock(tmpTmpKey, lockBitmask)) return true;
			}

			tmpTmpKey = tmpKey;
			for (int right = 0; right < SIZE; ++right) {
				if (right != 0) tmpTmpKey = toBitmaskMoveRightLeft(tmpTmpKey, 0);

				if (keyXorLock(tmpTmpKey, lockBitmask)) return true;
			}
		}
	}

	return false;
}