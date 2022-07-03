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
		
	//4x4 격자 정보
	//격자 칸의 물고기 방향 저장 큐
	vector<vector<queue<int>>> fish (vector<vector<queue<int>>>(4, vector<queue<int>>(4, queue<int>())));
	//격자 칸의 물고기 냄새 발생 시점 저장 큐
	vector<vector<queue<int>>> fish_smell (vector<vector<queue<int>>>(4, vector<queue<int>>(4, queue<int>())));

	int m; //물고기 수
	int s; //연습 수

	//상어의 위치
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

	//연습 시작
	int time = 1;
	while (time <= s) {

		//1. 물고기 복제
		vector<vector<queue<int>>> fish_copy;
		for (int i = 0; i < 4; ++i) {
			vector<queue<int>> fish_row_copy;
			for (int j = 0; j < 4; ++j) {
				fish_row_copy.push_back(fish[i][j]);
			}
			fish_copy.push_back(fish_row_copy);
		}

		//2. 물고기 이동
		vector<vector<queue<int>>> fish_after(vector<vector<queue<int>>>(4, vector<queue<int>>(4, queue<int>())));

		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				while (!fish[i][j].empty()) {
					int fish_dir = fish[i][j].front();
					fish[i][j].pop();

					//모든 방향으로 이동 시도
					bool moved = false;
					for (int k = 0; k < 8; ++k) {
						int moveR = i + fishR[fish_dir];
						int moveC = j + fishC[fish_dir];

						//격자 범위 밖 이동 불가
						//상어칸 이동 불가
						//물고기 냄새칸 이동 불가
						if (!inRange(moveR, moveC) || (moveR == shark.first && moveC == shark.second) || !fish_smell[moveR][moveC].empty()) {
							//물고기 방향 반시계 방향으로 45도 회전 후 재시도
							if (fish_dir == 0) fish_dir = 7;
							else fish_dir--;
							continue;
						}
						
						//이동
						moved = true;
						fish_after[moveR][moveC].push(fish_dir);
						break;
					}
					//이동하지 못한 경우 물고기 제자리
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

		//3. 상어 연속 3칸 이동

		//제외되는 물고기 수의 최대값
		int maxCntFish = -1;
		//제외되는 물고기 수가 최대로 될 때 사전순으로 제일 앞서는 상어의 이동 방향
		vector<int> sharkDir;

		//상어의 이동 방향 구하기
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
				//상어가 이동하며 이미 방문한 격자인 경우 격자의 물고기 이미 제외됨
				if (secondR == firstR && secondC == firstC) secondCntFish = 0;
				else secondCntFish = fish[secondR][secondC].size();

				for (int d3 = 0; d3 < 4; ++d3) {
					int thirdR = secondR + sharkR[d3];
					int thirdC = secondC + sharkC[d3];

					if (!inRange(thirdR, thirdC)) continue;

					int thirdCntFish;
					//상어가 이동하며 이미 방문한 격자인 경우 격자의 물고기 이미 제외됨
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

		//상어 이동 & 물고기 제외 & 물고기 냄새 추가
		for (int i = 0; i < 3; ++i) {
			shark.first = shark.first + sharkR[sharkDir[i]];
			shark.second = shark.second + sharkC[sharkDir[i]];

			while (!fish[shark.first][shark.second].empty()) {
				fish[shark.first][shark.second].pop();
				fish_smell[shark.first][shark.second].push(time);
			}
		}

		//4. 2번 전 연습에서 생긴 물고기 냄새 제거
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				while (!fish_smell[i][j].empty()) {
					if (fish_smell[i][j].front() <= (time - 2)) fish_smell[i][j].pop();
					else break;
				}
			}
		}

		//5. 물고기 복제 완료
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
	
	//격자에 있는 물고기 수 구하기
	int ans = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			ans += fish[i][j].size();
		}
	}
	cout << ans;

	return 0;
}