#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;


int N;
int cnt = 0;

//�������� ��ǥ
//r+c�� Ȧ���� �� ���� �̵� ����
//r+c�� ¦���� �� �Ʒ��� �̵� ����
int mp[50][50];

int rdir[4] = {0,0,-1,1};
int cdir[4] = {1,-1,0,0};

void moveAnt(int r, int c, int turn, int prevr, int prevc) {
	//base case
	//Ž���� ���� ���
	if (mp[r][c] == 1) {
		if (turn == N) cnt++;
		return;
	}
	//Ž���� ������ �ʾҴµ� turn���� N���� �� ���
	if (turn == N) return;

	//DP
	mp[r][c] = 1;

	for (int i = 0; i < 4; ++i) {
		if ((i == 2) && ((r + c) % 2 == 0))
			continue;
		if ((i == 3) && ((r + c) % 2 == 1))
			continue;

		int nextr = r + rdir[i];
		int nextc = c + cdir[i];

		//������ �̵��ؿ� ���� �������� �ʴ´�
		if (nextr == prevr && nextc == prevc)
			continue;

		moveAnt(nextr, nextc, turn + 1, r, c);
	}

	mp[r][c] = 0;
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;

	//������ ù ��° �̵��� ���� �����̴�
	//���� �̵��� �� �ֱ� ���� r+c�� Ȧ���� ������ ��ǥ�� ���� ��ġ�� ����
	mp[26][25] = 1;
	moveAnt(25, 25, 0, 26, 25);

	cout << cnt;
	return 0;
}