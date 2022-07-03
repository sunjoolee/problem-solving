#include <algorithm>
#include <vector>
#include <queue>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

int fishR[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int fishC[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

int sharkR[4] = {-1, 0, 1, 0};
int sharkC[4] = {0, -1, 0, 1};

bool inRange(int r, int c) {
	if (r < 0 || r >= 4) return false;
	if (c < 0 || c >= 4) return false;
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
		
	//4x4 ���� ����
	//���� ĭ�� ����� ���� ���� ť
	vector<vector<queue<int>>> fish (vector<vector<queue<int>>>(4, vector<queue<int>>(4, queue<int>())));
	//���� ĭ�� ����� ���� �߻� ���� ���� ť
	vector<vector<queue<int>>> fish_smell (vector<vector<queue<int>>>(4, vector<queue<int>>(4, queue<int>())));

	int m; //����� ��
	int s; //���� ��

	//����� ��ġ
	pair<int, int> shark;

	cin >> m >> s;

	for (int i = 0; i < m; ++i) {
		int x, y, d;
		cin >> x >> y >> d;

		fish[x-1][y-1].push(d-1);
	}

	cin >> shark.first >> shark.second;
	shark.first--;
	shark.second--;

	//���� ����
	int time = 1;
	while (time <= s) {

		//1. ����� ����
		vector<vector<queue<int>>> fish_copy;
		for (int i = 0; i < 4; ++i) {
			vector<queue<int>> fish_row_copy;
			for (int j = 0; j < 4; ++j) {
				fish_row_copy.push_back(fish[i][j]);
			}
			fish_copy.push_back(fish_row_copy);
		}

		//2. ����� �̵�
		vector<vector<queue<int>>> fish_after(vector<vector<queue<int>>>(4, vector<queue<int>>(4, queue<int>())));

		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				while (!fish[i][j].empty()) {
					int fish_dir = fish[i][j].front();
					fish[i][j].pop();

					//��� �������� �̵� �õ�
					bool moved = false;
					for (int k = 0; k < 8; ++k) {
						int moveR = i + fishR[fish_dir];
						int moveC = j + fishC[fish_dir];

						//���� ���� �� �̵� �Ұ�
						//���ĭ �̵� �Ұ�
						//����� ����ĭ �̵� �Ұ�
						if (!inRange(moveR, moveC) || (moveR == shark.first && moveC == shark.second) || !fish_smell[moveR][moveC].empty()) {
							//����� ���� �ݽð� �������� 45�� ȸ�� �� ��õ�
							if (fish_dir == 0) fish_dir = 7;
							else fish_dir--;
							continue;
						}
						
						//�̵�
						moved = true;
						fish_after[moveR][moveC].push(fish_dir);
						break;
					}
					//�̵����� ���� ��� ����� ���ڸ�
					if (moved == false) fish_after[i][j].push(fish_dir);
				}
			}
		}

		//fish = fish_after
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				while (!fish_after[i][j].empty()) {
					fish[i][j].push(fish_after[i][j].front());
					fish_after[i][j].pop();
				}
			}
		}

		//3. ��� ���� 3ĭ �̵�

		//���ܵǴ� ����� ���� �ִ밪
		int maxCntFish = -1;
		//���ܵǴ� ����� ���� �ִ�� �� �� ���������� ���� �ռ��� ����� �̵� ����
		vector<int> sharkDir;

		//����� �̵� ���� ���ϱ�
		for (int d1 = 0; d1 < 4; ++d1) {
			int firstR = shark.first + sharkR[d1];
			int firstC = shark.second + sharkC[d1];

			if (!inRange(firstR, firstC)) continue;

			int firstCntFish = fish[firstR][firstC].size();

			for (int d2 = 0; d2 < 4; ++d2) {
				int secondR = firstR + sharkR[d2];
				int secondC = firstC+ sharkC[d2];

				if (!inRange(secondR, secondC)) continue;
				
				int secondCntFish;
				//�� �̵��ϸ� �̹� �湮�� ������ ��� ������ ����� �̹� ���ܵ�
				if (secondR == firstR && secondC == firstC) secondCntFish = 0;
				else secondCntFish = fish[secondR][secondC].size();

				for (int d3 = 0; d3 < 4; ++d3) {
					int thirdR = secondR + sharkR[d3];
					int thirdC = secondC + sharkC[d3];

					if (!inRange(thirdR, thirdC)) continue;

					int thirdCntFish;
					//�� �̵��ϸ� �̹� �湮�� ������ ��� ������ ����� �̹� ���ܵ�
					if ((thirdR == firstR && thirdC == firstC)|| (thirdR == secondR && thirdC == secondC))
						thirdCntFish = 0;
					else thirdCntFish = fish[thirdR][thirdC].size();

					if (maxCntFish < firstCntFish + secondCntFish + thirdCntFish) {
						sharkDir.clear();
						sharkDir.push_back(d1); 
						sharkDir.push_back(d2);
						sharkDir.push_back(d3);
						maxCntFish = firstCntFish + secondCntFish + thirdCntFish;
					}
				}
			}
		}

		//��� �̵� & ����� ���� & ����� ���� �߰�
		for (int i = 0; i < 3; ++i) {
			shark.first = shark.first + sharkR[sharkDir[i]];
			shark.second = shark.second + sharkC[sharkDir[i]];

			while (!fish[shark.first][shark.second].empty()) {
				fish[shark.first][shark.second].pop();
				fish_smell[shark.first][shark.second].push(time);
			}
		}

		//4. 2�� �� �������� ���� ����� ���� ����
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				while (!fish_smell[i][j].empty()) {
					if (fish_smell[i][j].front() <= (time - 2)) fish_smell[i][j].pop();
					else break;
				}
			}
		}

		//5. ����� ���� �Ϸ�
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				while (!fish_copy[i][j].empty()) {
					fish[i][j].push(fish_copy[i][j].front());
					fish_copy[i][j].pop();
				}
			}
		}

		time++;
	}
	
	//���ڿ� �ִ� ����� �� ���ϱ�
	int ans = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			ans += fish[i][j].size();
		}
	}
	cout << ans;

	return 0;
}