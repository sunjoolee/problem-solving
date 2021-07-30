#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <utility>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100 + 1;

int n;
string mp[MAXN];

int visited[MAXN][MAXN] = { 0 };
int rgbvisited[MAXN][MAXN] = { 0 };

int dirr[4] = { 0,0,1,-1 };
int dirc[4] = { 1,-1,0,0 };

//���ϻ��� ���� ��� mp[r][c]�� ���� ���� Ž��
void bfs(int r, int c) {
	char color = mp[r][c];

	queue<pair<int, int>> q;
	q.push(make_pair(r, c));

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		int curr = cur.first;
		int curc = cur.second;
		q.pop();

		//�湮 Ȯ��
		if (visited[curr][curc]) continue;
		visited[curr][curc] = 1;

		for (int i = 0; i < 4; i++) {
			int nextr = curr + dirr[i];
			int nextc = curc + dirc[i];

			//���� Ȯ��
			if (nextr < 0 || nextr >= n) continue;
			if (nextc < 0 || nextc >= n) continue;

			//���� ���� ���� ������ ��ǥ �湮
			if (mp[nextr][nextc] == color)
				q.push(make_pair(nextr, nextc));
		}
	}

	return;
}

//���ϻ��� �ִ� ��� mp[r][c]�� ���� ���� Ž��
void rgbbfs(int r, int c) {
	char color = mp[r][c];

	queue<pair<int, int>> q;
	q.push(make_pair(r, c));

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		int curr = cur.first;
		int curc = cur.second;
		q.pop();

		//�湮 Ȯ��
		if (rgbvisited[curr][curc]) continue;
		rgbvisited[curr][curc] = 1;

		for (int i = 0; i < 4; i++) {
			int nextr = curr + dirr[i];
			int nextc = curc + dirc[i];

			//���� Ȯ��
			if (nextr < 0 || nextr >= n) continue;
			if (nextc < 0 || nextc >= n) continue;

			//���� ���� ���� ������ ��ǥ �湮
			if (color == 'R' || color == 'G') {
				if (mp[nextr][nextc] == 'R' || mp[nextr][nextc] == 'G')
					q.push(make_pair(nextr, nextc));
			}
			else {
				if (mp[nextr][nextc] == 'B')
					q.push(make_pair(nextr, nextc));
			}
		}
	}

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	memset(visited, 0, sizeof(visited));
	memset(rgbvisited, 0, sizeof(rgbvisited));

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> mp[i];

	//���ϻ��� ���� ����� ���� ������ ����
	int cnt = 0;
	//���ϻ��� �ִ� ����� ���� ������ ����
	int rgbcnt = 0;

	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			if (visited[r][c] == 0) {
				bfs(r, c);
				++cnt;
			}
			if (rgbvisited[r][c] == 0) {
				rgbbfs(r, c);
				++rgbcnt;
			}
		}
	}

	cout << cnt << " " << rgbcnt << "\n";
	return 0;
}