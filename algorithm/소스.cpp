#include <iostream>
#include <cstring>
using namespace std;

int R, C;

//�� ĭ 0, ����� ĭ 1
int mp[26][26];
int cache[26][26];

int validPath(int r, int c) {
	//base case
	//(R,C)�� ������ ��� ��� �ϳ� �߰�
	if (r == R && c == C) return 1;
	//���� ������ �� ��� ��� X
	if (r < 1 || r > R) return 0;
	if (c < 1 || c > C) return 0;
	//����̰� �ִ� ĭ�� ��� ��� X
	if (mp[r][c] == 1) return 0;

	int& ret = cache[r][c];
	if (ret != -1) return ret;

	//���������� �̵��ϴ� ��� + �Ʒ��� �̵��ϴ� ���
	ret = validPath(r + 1, c) + validPath(r, c + 1);
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	memset(mp, 0, sizeof(mp));
	memset(cache, -1, sizeof(cache));

	cin >> R >> C;
	int k;
	cin >> k;
	for (int i = 0; i < k; ++i) {
		int r, c;
		cin >> r >> c;
		mp[r][c] = 1;
	}

	cout << validPath(1, 1);

	return 0;
}