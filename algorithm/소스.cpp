#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int N = 100;

const int pillarStart = 0;
const int pillarEnd = 1;
const int boStart = 2;
const int boEnd = 3;

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
	vector<vector<int>> answer;

	//map[x][y][0] = 1 : (x,y)가 기둥의 시작 좌표
	//map[x][y][1] = 1:  (x,y)가 기둥의 끝 좌표
	//map[x][y][2] = 1 : (x,y)가 보의 시작 좌표
	//map[x][y][3] = 1 : (x,y)가 보의 끝 좌표
	vector<vector<vector<int>>> map(100, vector<vector<int>>(100, vector<int>(4, 0)));

	for (int i = 0; i < build_frame.size(); ++i) {
		int y = build_frame[i][0]; 
		int x = build_frame[i][1];
		//a = 0 기둥, 1 보
		int a = build_frame[i][2]; 
		//b = 0 삭제, 1 설치
		int b = build_frame[i][3];

		//설치
		if (b == 1) {
			//기둥
			if (a == 0) {
				//바닥 위에 설치하는 경우
				if (x == 0) {
					map[x][y][pillarStart] = 1;
					map[x + 1][y][pillarEnd] = 1;
				}
				//보의 한쪽 끝에 설치하는 경우
				else if (map[x][y][boStart] == 1 || map[x][y][boEnd] == 1) {
					map[x][y][pillarStart] = 1;
					map[x + 1][y][pillarEnd] = 1;
				}
				//기둥 위에 설치하는 경우
				else if (map[x][y][pillarEnd] == 1) {
					map[x][y][pillarStart] = 1;
					map[x + 1][y][pillarEnd] = 1;
				}
			}
			//보
			else {
				//한쪽 끝이 기둥 위인 경우
				if (map[x][y][pillarEnd] == 1 || map[x][y + 1][pillarEnd] == 1) {
					map[x][y][boStart] = 1; 
					map[x][y + 1][boEnd] = 1;
				}
				//양쪽 끝부분이 다른 보와 동시에 연결된 경우
				else if (map[x][y][boEnd] == 1 && map[x][y + 1][boStart] == 1) {
					map[x][y][boStart] = 1;
					map[x][y + 1][boEnd] = 1;
				}
			}
		}
		//삭제
		else {
			//삭제할 기둥이 있는 경우
			if (a == 0 && map[x][y][pillarStart] == 1) {
				//위에 기둥이 설치되어있는 경우 삭제 안됨
				if (map[x + 1][y][pillarStart] == 1) continue;

				//기둥을 삭제했을 때 연결되어있었던 보가 있었다면
				if (map[x + 1][y][boStart] == 1) { //기둥 오른쪽으로 연결된 보
					//(한쪽 끝이 기둥 위에 있어야 함) 또는 (양쪽 끝이 다른 보와 동시에 연결되어있어야 함)
					if ((map[x + 1][y + 1][pillarEnd] != 1) && (map[x + 1][y][boEnd] != 1 || map[x + 1][y + 1][boStart] != 1)) continue;
				}
				if (map[x + 1][y][boEnd] == 1) { //기둥 왼쪽으로 연결된 보
					//(한쪽 끝이 기둥 위에 있어야 함) 또는 (양쪽 끝이 다른 보와 동시에 연결되어있어야 함)
					if ((map[x + 1][y - 1][pillarEnd] != 1) && (map[x + 1][y][boStart] != 1 || map[x + 1][y - 1][boEnd] != 1)) continue;
				}
				//기둥 삭제
				map[x][y][pillarStart] = 0;
				map[x + 1][y][pillarEnd] = 0;
			}
			//삭제할 보가 있는 경우
			else if(map[x][y][boStart] == 1) {
				// 나에게 연결된 보가 양쪽이 보로 연결된 보인 경우 삭제 불가능
				if (map[x][y + 1][boStart] == 1) { //보 오른쪽으로 연결된 보
					if (map[x][y + 1][pillarEnd] == 0 && map[x][y + 2][pillarEnd] == 0) continue;
				}
				if (map[x][y + 1][boStart] == 1) { //보 왼쪽으로 연결된 보
					if (map[x][y][pillarEnd] == 0 && map[x][y -1][pillarEnd] == 0) continue;
				}

				//보 삭제
				map[x][y][boStart] = 0;
				map[x][y + 1][boEnd] = 0;
			}
		}
	}

	for (int x = 0; x <= n; ++x) {
		for (int y = 0; y <= n; ++y) {
			if (map[y][x][pillarStart] == 1) answer.push_back({ x, y, 0 });
			if (map[y][x][boStart] == 1) answer.push_back({ x,y, 1 });
		}
	}

	return answer;
}

int main() {
	solution(5, {
		{0, 0, 0, 1},
		{2, 0, 0, 1},
		{4, 0, 0, 1},
		{0, 1, 1, 1},
		{1, 1, 1, 1},
		{2, 1, 1, 1},
		{3, 1, 1, 1},
		{2, 0, 0, 0},
		{1, 1, 1, 0},
		{2, 2, 0, 1} });
}