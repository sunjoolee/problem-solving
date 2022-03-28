#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int N = 105;

const int pillarStart = 0;
const int pillarEnd = 1;
const int boStart = 2;
const int boEnd = 3;

//map[x][y][0] = 1 : (x,y)가 기둥의 시작 좌표
//map[x][y][1] = 1:  (x,y)가 기둥의 끝 좌표
//map[x][y][2] = 1 : (x,y)가 보의 시작 좌표
//map[x][y][3] = 1 : (x,y)가 보의 끝 좌표
vector<vector<vector<int>>> map(N, vector<vector<int>>(N, vector<int>(4, 0)));

//잘 설치되었는지 확인하는 조건은 문제에 나와있대로 하면 됨
//그러나, 삭제해도 되는 구조물인지 확인하는 조건은 직접 생각해야함 & 경우의 수가 많아 짜기 어려움
//따라서, 삭제해도 되는지 안되는지 확인하려 하지 말고, 일단 삭제하고 나머지 구조물들이 잘 설치되었는지 확인하자


//map에 설치된 모든 구조물들이 잘 설치되었는지 확인
bool check(int n) {

	for (int x = 0; x <=n ; ++x) {
		for (int y = 0; y <= n; ++y) {

			//기둥
			if (map[x][y][pillarStart] == 1) {
				//바닥 위에 설치되어있는 경우
				if (x == 0) continue;
				//보의 한쪽 끝에 설치되어있는 경우
				else if (map[x][y][boStart] == 1 || map[x][y][boEnd] == 1) continue;
				//기둥 위에 설치되어있는 경우
				else if (map[x][y][pillarEnd] == 1) continue;

				//조건 만족 못함 
				return false;
			}
			//보
			else if(map[x][y][boStart] == 1) {
				//한쪽 끝이 기둥 위인 경우
				if (map[x][y][pillarEnd] == 1 || map[x][y + 1][pillarEnd] == 1) continue;
				//양쪽 끝부분이 다른 보와 동시에 연결된 경우
				else if (map[x][y][boEnd] == 1 && map[x][y + 1][boStart] == 1) continue;

				//조건 만족 못함
				return false;
			}
		}
	}
	return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
	vector<vector<int>> answer;

	for (int i = 0; i < build_frame.size(); ++i) {
		int y = build_frame[i][0]; 
		int x = build_frame[i][1];
		//a = 0 기둥, 1 보
		int a = build_frame[i][2]; 
		//b = 0 삭제, 1 설치
		int b = build_frame[i][3];

		//설치
		if (b == 1) {
			//기둥 설치
			if (a == 0) {
				map[x][y][pillarStart] = 1;
				map[x+1][y][pillarEnd] = 1;
				if (check(n)) continue;
				map[x][y][pillarStart] = 0;
				map[x + 1][y][pillarEnd] = 0;
			}
			//보 설치
			else {
				map[x][y][boStart] = 1;
				map[x][y + 1][boEnd] = 1;
				if (check(n)) continue;
				map[x][y][boStart] = 0;
				map[x][y + 1][boEnd] = 0;
			}
			
		}
		//삭제
		else {
			//삭제할 기둥이 있는 경우
			if (a == 0 && map[x][y][pillarStart] == 1){
				map[x][y][pillarStart] = 0;
				map[x + 1][y][pillarEnd] = 0;
				if (check(n)) continue;
				map[x][y][pillarStart] = 1;
				map[x + 1][y][pillarEnd] = 1;
			}
			//삭제할 보가 있는 경우
			else if(map[x][y][boStart] == 1) {
				map[x][y][boStart] = 0;
				map[x][y + 1][boEnd] = 0;
				if (check(n)) continue;
				map[x][y][boStart] = 1;
				map[x][y + 1][boEnd] = 1;
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
	solution(100, { {2, 0, 0, 1},{100, 0, 0, 1},{100, 1, 1, 1},{99, 1, 1, 1},{99, 1, 0, 1},{99, 0, 0, 1} });
}