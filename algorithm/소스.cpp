#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

int dirR[4] = { 0, 0, 1, -1 };
int dirC[4] = { 1, -1, 0, 0 };

bool inRange(int R, int C, int r, int c) {
	if (r < 0 || r >= R) return false;
	if (c < 0 || c >= C) return false;
	return true;
}

vector<vector<int>> moveFish(int R, int C, vector<vector<int>>fishTankBoard) {

	vector<vector<int>> movedFish(R, vector<int>(C, 0));
	
	vector<vector<int>> visited(R, vector<int>(C, 0));
	
	for (int r = 0; r < R; ++r) {
		for (int c = 0; c < C; ++c) {
			if (fishTankBoard[r][c] == 0) continue;

			visited[r][c] = 1;
			for (int dir = 0; dir < 4; ++dir) {
				int adjR = r + dirR[dir];
				int adjC = c + dirC[dir];
				
				if (!inRange(R, C, adjR, adjC) || fishTankBoard[adjR][adjC] == 0 || visited[adjR][adjC]) continue;

				int d;
				if (fishTankBoard[r][c] > fishTankBoard[adjR][adjC]) {
					d = (fishTankBoard[r][c] - fishTankBoard[adjR][adjC]) / 5;
					if (d > 0) {
						movedFish[r][c] -= d;
						movedFish[adjR][adjC] += d;
					}
				}
				else{
					d = (fishTankBoard[adjR][adjC] - fishTankBoard[r][c]) / 5;
					if (d > 0) {
						movedFish[r][c] += d;
						movedFish[adjR][adjC] -= d;
					}
				}
			}
		}
	}

	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			fishTankBoard[i][j] = fishTankBoard[i][j] + movedFish[i][j];
		}
	}

	return fishTankBoard;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//������ ��
	int n;
	//������ ����� �� ����
	int k;

	//����
	vector<stack<int>> fishTank(100, stack<int>());

	cin >> n >> k;

	for (int i = 0; i < n; ++i) {
		int fish;
		cin >> fish;
		fishTank[i].push(fish);
	}

	int time = 1;
	while (true) {
		//1. ����� �� ���� ���� ���׿� ����� �Ѹ����� 
		vector<int> minFishTank;
		int minFish = 987654321;
		for (int i = 0; i < n; ++i) {
			int fish = fishTank[i].top();

			if (fish < minFish) {
				minFish = fish;
				minFishTank.clear();
				minFishTank.push_back(i);
			}
			else if (fish == minFish) {
				minFishTank.push_back(i);
			}
		}

		for (int i = 0; i < minFishTank.size(); ++i) {
			int idx = minFishTank[i];
			fishTank[idx].pop();
			fishTank[idx].push(minFish + 1);

		}

		//2. ���� ���ߺξ� & �ð���� 90�� ȸ�� & �ױ�
		
		//�� ���ʿ� �ִ� ���� ������ ���� ���� �ױ�
		fishTank[1].push(fishTank[0].top());
		fishTank[0].pop();

		while (true) {

			//���� �ξ��Ų ���� �� ���� �����ʿ� �ִ� ������ �Ʒ��� 
			//�ٴڿ� �ִ� ������ ���� ��� ����
			int stackHeight;
			int startFishTank= - 1;

			for (int i = 0; i < n; ++i) {
				if (fishTank[i].size() > 1) {
					stackHeight = fishTank[i].size();
				}
				if (fishTank[i].size() == 1) {
					startFishTank = i;
					break;
				}
			}

			if (startFishTank == -1 || startFishTank + stackHeight - 1 >= n) break;

			//2�� �̻� �׿��ִ� ���� ���ߺξ�
			stack<int> floatTank;

			for (int i = 0; i < n; ++i) {
				if (fishTank[i].size() > 1) {
					while (!fishTank[i].empty()) {
						floatTank.push(fishTank[i].top());
						fishTank[i].pop();
					}
				}
				if (fishTank[i].size() == 1) break;
			}

			//�ð���� 90�� ȸ�� & �ױ�
			while (!floatTank.empty()) {
				for (int h = 0; h < stackHeight; ++h) {
					fishTank[startFishTank + h].push(floatTank.top());
					floatTank.pop();
				}
			}
		}

		//3. ���׿� �ִ� ������� �� ����

		//vector<stack<int>> -> vector<vector<int>>
		int R = 0;
		int C = 0;
		int startFishTank = -1;

		for (int i = 0; i < n; ++i) {
			if (fishTank[i].empty()) continue;
			else if (startFishTank == -1) startFishTank = i;

			if(R < fishTank[i].size()) R = fishTank[i].size();
			C++;
		}

		vector<vector<int>> fishTankBoard1(R, vector<int>(C, 0));
		
		for (int c = 0; c < C; ++c) {
			if (fishTank[c + startFishTank].size() == 1) {
				fishTankBoard1[R - 1][c] = fishTank[c + startFishTank].top();
				fishTank[c + startFishTank].pop();
				continue;
			}

			for (int r = 0; r < R; ++r) {
				fishTankBoard1[r][c] = fishTank[c + startFishTank].top();
				fishTank[c + startFishTank].pop();
			}
		}

		fishTankBoard1 = moveFish(R, C, fishTankBoard1);

		//4. �ٽ� ������ �ٴڿ� �Ϸķ� ����

		//vector<vector<int>> -> vector<stack<int>>
		int fishTankIdx = 0;
		for (int c = 0; c < C; ++c) {
			for (int r = R - 1; r >= 0; --r) {
				if (fishTankBoard1[r][c] == 0) break;
				fishTank[fishTankIdx].push(fishTankBoard1[r][c]);
				fishTankIdx++;
			}
		}

		//5. ����� �߽����� ���� n/2�� ���ߺξ� & �ð���� 180�� ȸ�� & �ױ�
		//1ȸ
		stack<int> floatTank1;
		for (int i = 0; i < n / 2; ++i) {
			floatTank1.push(fishTank[i].top());
			fishTank[i].pop();
		}
		for (int i = n / 2; i < n; ++i) {
			fishTank[i].push(floatTank1.top());
			floatTank1.pop();
		}
		//2ȸ
		stack<int> floatTank2;
		for (int i = n / 2; i < n / 2 + n / 4; ++i) {
			floatTank1.push(fishTank[i].top());
			fishTank[i].pop(); 
			floatTank2.push(fishTank[i].top());
			fishTank[i].pop();
		}
		for (int i = n / 2 + n / 4; i < n; ++i) {
			fishTank[i].push(floatTank1.top());
			floatTank1.pop();
			fishTank[i].push(floatTank2.top());
			floatTank2.pop();
		}

		//6. ���׿� �ִ� ������� �� ����

		//vector<stack<int>> -> vector<vector<int>>
		R = 0;
		C = 0;
		startFishTank = -1;

		for (int i = 0; i < n; ++i) {
			if (fishTank[i].empty()) continue;
			if (startFishTank == -1) startFishTank = i;

			if (R < fishTank[i].size()) R = fishTank[i].size();
			C++;
		}

		vector<vector<int>> fishTankBoard2(R, vector<int>(C, 0));

		for (int c = 0; c < C; ++c) {
			if (fishTank[c + startFishTank].size() == 1) {
				fishTankBoard2[R - 1][c] = fishTank[c + startFishTank].top();
				fishTank[c + startFishTank].pop();
				continue;
			}

			for (int r = 0; r < R; ++r) {
				fishTankBoard2[r][c] = fishTank[c + startFishTank].top();
				fishTank[c + startFishTank].pop();
			}
		}
		fishTankBoard2 = moveFish(R, C, fishTankBoard2);

		//7. �ٽ� ������ �ٴڿ� �Ϸķ� ����

		//vector<vector<int>> -> vector<stack<int>>
		fishTankIdx = 0;
		for (int c = 0; c < C; ++c) {
			for (int r = R - 1; r >= 0; --r) {
				if (fishTankBoard2[r][c] == 0) break;
				fishTank[fishTankIdx].push(fishTankBoard2[r][c]);
				fishTankIdx++;
			}
		}

		
		//8. ���� �� �ִ� ����� ���� �ּ� ����� ���� ���� k ���ϸ� break 
		minFish = 987654321;
		int maxFish = 0;

		for (int i = 0; i < n; ++i) {
			if (minFish > fishTank[i].top()) minFish = fishTank[i].top();
			if(maxFish < fishTank[i].top()) maxFish = fishTank[i].top();
		}
		if (maxFish - minFish <= k) break;

		time++;
	}

	cout << time;
	return 0;
}