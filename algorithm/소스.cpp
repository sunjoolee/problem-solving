#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int N = 105;

const int pillarStart = 0;
const int pillarEnd = 1;
const int boStart = 2;
const int boEnd = 3;

//map[x][y][0] = 1 : (x,y)�� ����� ���� ��ǥ
//map[x][y][1] = 1:  (x,y)�� ����� �� ��ǥ
//map[x][y][2] = 1 : (x,y)�� ���� ���� ��ǥ
//map[x][y][3] = 1 : (x,y)�� ���� �� ��ǥ
vector<vector<vector<int>>> map(N, vector<vector<int>>(N, vector<int>(4, 0)));

//�� ��ġ�Ǿ����� Ȯ���ϴ� ������ ������ �����ִ�� �ϸ� ��
//�׷���, �����ص� �Ǵ� ���������� Ȯ���ϴ� ������ ���� �����ؾ��� & ����� ���� ���� ¥�� �����
//����, �����ص� �Ǵ��� �ȵǴ��� Ȯ���Ϸ� ���� ����, �ϴ� �����ϰ� ������ ���������� �� ��ġ�Ǿ����� Ȯ������


//map�� ��ġ�� ��� ���������� �� ��ġ�Ǿ����� Ȯ��
bool check(int n) {

	for (int x = 0; x <=n ; ++x) {
		for (int y = 0; y <= n; ++y) {

			//���
			if (map[x][y][pillarStart] == 1) {
				//�ٴ� ���� ��ġ�Ǿ��ִ� ���
				if (x == 0) continue;
				//���� ���� ���� ��ġ�Ǿ��ִ� ���
				else if (map[x][y][boStart] == 1 || map[x][y][boEnd] == 1) continue;
				//��� ���� ��ġ�Ǿ��ִ� ���
				else if (map[x][y][pillarEnd] == 1) continue;

				//���� ���� ���� 
				return false;
			}
			//��
			else if(map[x][y][boStart] == 1) {
				//���� ���� ��� ���� ���
				if (map[x][y][pillarEnd] == 1 || map[x][y + 1][pillarEnd] == 1) continue;
				//���� ���κ��� �ٸ� ���� ���ÿ� ����� ���
				else if (map[x][y][boEnd] == 1 && map[x][y + 1][boStart] == 1) continue;

				//���� ���� ����
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
		//a = 0 ���, 1 ��
		int a = build_frame[i][2]; 
		//b = 0 ����, 1 ��ġ
		int b = build_frame[i][3];

		//��ġ
		if (b == 1) {
			//��� ��ġ
			if (a == 0) {
				map[x][y][pillarStart] = 1;
				map[x+1][y][pillarEnd] = 1;
				if (check(n)) continue;
				map[x][y][pillarStart] = 0;
				map[x + 1][y][pillarEnd] = 0;
			}
			//�� ��ġ
			else {
				map[x][y][boStart] = 1;
				map[x][y + 1][boEnd] = 1;
				if (check(n)) continue;
				map[x][y][boStart] = 0;
				map[x][y + 1][boEnd] = 0;
			}
			
		}
		//����
		else {
			//������ ����� �ִ� ���
			if (a == 0 && map[x][y][pillarStart] == 1){
				map[x][y][pillarStart] = 0;
				map[x + 1][y][pillarEnd] = 0;
				if (check(n)) continue;
				map[x][y][pillarStart] = 1;
				map[x + 1][y][pillarEnd] = 1;
			}
			//������ ���� �ִ� ���
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