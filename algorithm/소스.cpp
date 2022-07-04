#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <iostream>
using namespace std;

int dirR[4] = { 0, 0, -1, +1 };
int dirC[4] = { 1, -1, 0, 0 };

bool inRange(int R, int C, int x, int y) {
	if (x < 0 || x >= R) return false;
	if (y < 0 || y >= C) return false;
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int R, C, K;
	cin >> R >> C >> K;

	//�� ���� ����
	vector<vector<int>> room(R, vector<int>(C, 0));
	//�� �µ� ����
	vector<vector<int>> roomTemp(R, vector<int>(C, 0));
	//��ǳ�� ��ġ
	vector<pair<int, int>> heaters;
	//�����ؾ��ϴ� �� ��ġ 
	vector<pair<int, int>> checkRooms;

	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			cin >> room[i][j];

			if (room[i][j] > 0 && room[i][j] < 5)
				heaters.push_back({ i,j });
			else if (room[i][j] == 5)
				checkRooms.push_back({ i, j });
		}
	}
	
	//�� ���� ����
	//(x,y) (x-1,y) ��
	set<pair<int, int>> upWalls;
	//(x,y) (x,y+1) ��
	set<pair<int, int>> rightWalls;
	
	int W;
	cin >> W;
	for (int i = 0; i < W; ++i) {
		int x, y, t;
		cin >> x >> y >> t;

		if (t == 0) upWalls.insert({ x-1,y-1 });
		else rightWalls.insert({ x-1,y-1 });
	}

	int chocolate = 0;
	while (true) {
		//1. ��� ��ǳ�⿡�� �ٶ� ����
		for (int i = 0; i < heaters.size(); ++i) {
			int hX = heaters[i].first; 
			int hY = heaters[i].second;
			int hDir = room[hX][hY];

			//��ǳ�� �ٷ� �� ��ǥ(�µ� 5 ����)
			int adjX = hX + dirR[hDir - 1];
			int adjY = hY + dirC[hDir - 1];

			//��ǳ�Ⱑ �ִ� ĭ�� �ٶ��� ������ ���⿡ �ִ� ĭ ���̿��� ���� ����.
			//��ǳ���� �ٶ��� ������ ���⿡ �ִ� ĭ�� �׻� �����Ѵ�.

			/*
			if (!inRange(R, C, adjX, adjY)) continue;

			//��ǳ�� ���� �� �ִ��� �˻�
			//������
			if (hDir == 1 && rightWalls.find({ hX, hY }) != rightWalls.end()) continue;
			//����
			else if (hDir == 2 && rightWalls.find({ adjX, adjY }) != rightWalls.end()) continue;
			//��
			else if (hDir == 3 && (upWalls.find({ hX, hY }) != upWalls.end())) continue;
			//�Ʒ�
			else if (hDir == 4 && (upWalls.find({ adjX, adjY }) != upWalls.end())) continue;
			*/

			vector<vector<int>> tempChange(R, vector<int>(C, 0));

			queue < pair<int, pair<int, int>>> wind;
			wind.push({ 5, {adjX, adjY} });

			while (!wind.empty()) {
				int curTemp = wind.front().first;
				int curX = wind.front().second.first;
				int curY = wind.front().second.second;
				wind.pop();

				if (tempChange[curX][curY] != 0) continue;
				tempChange[curX][curY] = curTemp;

				if (curTemp == 1) continue;

				//��ǳ�� ���⿡ ���� �ٶ� �̵� ����
				int nextX, nextY;
				//������
				if (hDir == 1) {
					//x,y -> x-1,y+1
					nextX = curX - 1;
					nextY = curY + 1;
					if (inRange(R, C, nextX,nextY)) {
						if (upWalls.find({ curX, curY }) == upWalls.end() && rightWalls.find({ curX - 1, curY }) == rightWalls.end())
							wind.push({ curTemp - 1, {nextX, nextY} });
					}

					//x,y -> x,y+1
					nextX = curX;
					nextY = curY + 1;
					if (inRange(R, C, nextX, nextY)) {
						if (rightWalls.find({ curX, curY }) == rightWalls.end())
							wind.push({ curTemp - 1, {nextX, nextY} });
					}

					//x,y -> x+1, y+1
					nextX = curX + 1;
					nextY = curY + 1;
					if (inRange(R, C, nextX, nextY)) {
						if (upWalls.find({ curX + 1, curY }) == upWalls.end() && rightWalls.find({ curX + 1, curY }) == rightWalls.end())
							wind.push({ curTemp - 1, {nextX, nextY} });
					}
				}
				//����
				else if (hDir == 2) {
					//x,y -> x-1,y-1
					nextX = curX - 1;
					nextY = curY - 1;
					if (inRange(R, C, nextX, nextY)) {
						if (upWalls.find({ curX, curY }) == upWalls.end() && rightWalls.find({ curX - 1, curY -1}) == rightWalls.end())
							wind.push({ curTemp - 1, {nextX, nextY} });
					}

					//x,y -> x,y-1
					nextX = curX;
					nextY = curY - 1;
					if (inRange(R, C, nextX, nextY)) {
						if (rightWalls.find({ curX, curY -1}) == rightWalls.end())
							wind.push({ curTemp - 1, {nextX, nextY} });
					}

					//x,y -> x+1, y-1
					nextX = curX + 1;
					nextY = curY - 1;
					if (inRange(R, C, nextX, nextY)) {
						if (upWalls.find({ curX + 1, curY }) == upWalls.end() && rightWalls.find({ curX + 1, curY -1}) == rightWalls.end())
							wind.push({ curTemp - 1, {nextX, nextY} });
					}
				}
				//��
				else if (hDir == 3) {
					//x,y -> x-1,y-1
					nextX = curX - 1;
					nextY = curY - 1;
					if (inRange(R, C, nextX, nextY)) {
						if (upWalls.find({ curX, curY -1}) == upWalls.end() && rightWalls.find({ curX, curY -1}) == rightWalls.end())
							wind.push({ curTemp - 1, {nextX, nextY} });
					}

					//x,y -> x-1,y
					nextX = curX -1;
					nextY = curY;
					if (inRange(R, C, nextX, nextY)) {
						if (upWalls.find({ curX, curY }) == upWalls.end())
							wind.push({ curTemp - 1, {nextX, nextY} });
					}

					//x,y -> x-1, y+1
					nextX = curX - 1;
					nextY = curY + 1;
					if (inRange(R, C, nextX, nextY)) {
						if (upWalls.find({ curX, curY +1}) == upWalls.end() && rightWalls.find({ curX , curY }) == rightWalls.end())
							wind.push({ curTemp - 1, {nextX, nextY} });
					}
				}
				//�Ʒ�
				else if (hDir == 4) {
					//x,y -> x+1,y-1
					nextX = curX + 1;
					nextY = curY - 1;
					if (inRange(R, C, nextX, nextY)) {
						if (upWalls.find({ curX +1, curY-1 }) == upWalls.end() && rightWalls.find({ curX , curY-1 }) == rightWalls.end())
							wind.push({ curTemp - 1, {nextX, nextY} });
					}

					//x,y -> x+1,y
					nextX = curX + 1;
					nextY = curY;
					if (inRange(R, C, nextX, nextY)) {
						if (upWalls.find({ curX +1, curY }) == upWalls.end())
							wind.push({ curTemp - 1, {nextX, nextY} });
					}

					//x,y -> x+1, y+1
					nextX = curX + 1;
					nextY = curY + 1;
					if (inRange(R, C, nextX, nextY)) {
						if (upWalls.find({ curX + 1, curY +1 }) == upWalls.end() && rightWalls.find({ curX , curY }) == rightWalls.end())
							wind.push({ curTemp - 1, {nextX, nextY} });
					}
				}
			}

			for (int i = 0; i < R; ++i) {
				for (int j = 0; j < C; ++j) {
					roomTemp[i][j] += tempChange[i][j];
				}
			}
		}
	

		//2. �µ� ������
		vector<vector<int>> visited(R, vector<int>(C, 0));
		vector<vector<int>> tempChange(R, vector<int>(C, 0));

		for (int r = 0; r < R; ++r) {
			for (int c = 0; c < C; ++c) {
				visited[r][c] = 1;

				for (int dir = 1; dir <= 4; dir++) {
					int adjR = r + dirR[dir - 1];
					int adjC = c + dirC[dir - 1];

					if (!inRange(R, C, adjR, adjC) || visited[adjR][adjC]) continue;

					//���� �� �ִ��� �˻�
					//������
					if (dir == 1 && (rightWalls.find({ r, c }) != rightWalls.end())) continue;
					//����
					else if (dir == 2 && (rightWalls.find({ adjR, adjC }) != rightWalls.end())) continue;
					//��
					else if (dir == 3 && (upWalls.find({ r, c }) != upWalls.end())) continue;
					//�Ʒ�
					else if (dir == 4 && (upWalls.find({ adjR, adjC }) != upWalls.end())) continue;


					if (roomTemp[r][c] > roomTemp[adjR][adjC]) {
						int temp = (roomTemp[r][c] - roomTemp[adjR][adjC]) / 4;

						tempChange[r][c] -= temp;
						tempChange[adjR][adjC] += temp;
					}
					else if (roomTemp[r][c] < roomTemp[adjR][adjC]) {
						int temp = (roomTemp[adjR][adjC] - roomTemp[r][c]) / 4;

						tempChange[r][c] += temp;
						tempChange[adjR][adjC] -= temp;
					}
				}
			}

		}

		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < C; ++j) {
				roomTemp[i][j] = roomTemp[i][j] + tempChange[i][j];
			}
		}

		//3. �µ� 1�̻��� ���� �ٱ��� ĭ �µ� 1�� ����
		//�� �𼭸� ���� for������ ���
		for (int c = 1; c < C-1; ++c) {
			//0��
			if (roomTemp[0][c] > 0) roomTemp[0][c]--;
			//R-1��
			if (roomTemp[R - 1][c] > 0) roomTemp[R - 1][c]--;
		}
		for (int r = 1; r < R-1; ++r) {
			//0��
			if (roomTemp[r][0] > 0) roomTemp[r][0] --;
			//C-1��
			if (roomTemp[r][C - 1] > 0)roomTemp[r][C - 1]--;
		}

		//�� �𼭸� ���
		if (roomTemp[0][0] > 0) roomTemp[0][0]--;
		if (roomTemp[0][C-1] > 0) roomTemp[0][C-1]--;
		if (roomTemp[R-1][0] > 0) roomTemp[R-1][0]--;
		if (roomTemp[R-1][C-1] > 0) roomTemp[R-1][C-1]--;

		//4. ���ݸ� ����
		chocolate++;
		//�Դ� ���ݸ��� ������ 100�� �Ѿ�� 101�� ����Ѵ�
		if (chocolate > 100) break;

		//5. �����ϴ� ��� ĭ�� �µ� K�̻� �Ǿ����� �˻� 
		bool overK = true;
		for (int i = 0; i < checkRooms.size(); ++i) {
			int x = checkRooms[i].first;
			int y = checkRooms[i].second;
			if (roomTemp[x][y] < K) {
				overK = false;
				break;
			}
		}
		if (overK) break;
	}

	cout << chocolate;
	return 0;
}