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

	//map[x][y][0] = 1 : (x,y)�� ����� ���� ��ǥ
	//map[x][y][1] = 1:  (x,y)�� ����� �� ��ǥ
	//map[x][y][2] = 1 : (x,y)�� ���� ���� ��ǥ
	//map[x][y][3] = 1 : (x,y)�� ���� �� ��ǥ
	vector<vector<vector<int>>> map(100, vector<vector<int>>(100, vector<int>(4, 0)));

	for (int i = 0; i < build_frame.size(); ++i) {
		int y = build_frame[i][0]; 
		int x = build_frame[i][1];
		//a = 0 ���, 1 ��
		int a = build_frame[i][2]; 
		//b = 0 ����, 1 ��ġ
		int b = build_frame[i][3];

		//��ġ
		if (b == 1) {
			//���
			if (a == 0) {
				//�ٴ� ���� ��ġ�ϴ� ���
				if (x == 0) {
					map[x][y][pillarStart] = 1;
					map[x + 1][y][pillarEnd] = 1;
				}
				//���� ���� ���� ��ġ�ϴ� ���
				else if (map[x][y][boStart] == 1 || map[x][y][boEnd] == 1) {
					map[x][y][pillarStart] = 1;
					map[x + 1][y][pillarEnd] = 1;
				}
				//��� ���� ��ġ�ϴ� ���
				else if (map[x][y][pillarEnd] == 1) {
					map[x][y][pillarStart] = 1;
					map[x + 1][y][pillarEnd] = 1;
				}
			}
			//��
			else {
				//���� ���� ��� ���� ���
				if (map[x][y][pillarEnd] == 1 || map[x][y + 1][pillarEnd] == 1) {
					map[x][y][boStart] = 1; 
					map[x][y + 1][boEnd] = 1;
				}
				//���� ���κ��� �ٸ� ���� ���ÿ� ����� ���
				else if (map[x][y][boEnd] == 1 && map[x][y + 1][boStart] == 1) {
					map[x][y][boStart] = 1;
					map[x][y + 1][boEnd] = 1;
				}
			}
		}
		//����
		else {
			//������ ����� �ִ� ���
			if (a == 0 && map[x][y][pillarStart] == 1) {
				//���� ����� ��ġ�Ǿ��ִ� ��� ���� �ȵ�
				if (map[x + 1][y][pillarStart] == 1) continue;

				//����� �������� �� ����Ǿ��־��� ���� �־��ٸ�
				if (map[x + 1][y][boStart] == 1) { //��� ���������� ����� ��
					//(���� ���� ��� ���� �־�� ��) �Ǵ� (���� ���� �ٸ� ���� ���ÿ� ����Ǿ��־�� ��)
					if ((map[x + 1][y + 1][pillarEnd] != 1) && (map[x + 1][y][boEnd] != 1 || map[x + 1][y + 1][boStart] != 1)) continue;
				}
				if (map[x + 1][y][boEnd] == 1) { //��� �������� ����� ��
					//(���� ���� ��� ���� �־�� ��) �Ǵ� (���� ���� �ٸ� ���� ���ÿ� ����Ǿ��־�� ��)
					if ((map[x + 1][y - 1][pillarEnd] != 1) && (map[x + 1][y][boStart] != 1 || map[x + 1][y - 1][boEnd] != 1)) continue;
				}
				//��� ����
				map[x][y][pillarStart] = 0;
				map[x + 1][y][pillarEnd] = 0;
			}
			//������ ���� �ִ� ���
			else if(map[x][y][boStart] == 1) {
				// ������ ����� ���� ������ ���� ����� ���� ��� ���� �Ұ���
				if (map[x][y + 1][boStart] == 1) { //�� ���������� ����� ��
					if (map[x][y + 1][pillarEnd] == 0 && map[x][y + 2][pillarEnd] == 0) continue;
				}
				if (map[x][y + 1][boStart] == 1) { //�� �������� ����� ��
					if (map[x][y][pillarEnd] == 0 && map[x][y -1][pillarEnd] == 0) continue;
				}

				//�� ����
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