#include <iostream>
#include <cstring>
#include <queue>
#include <string>
using namespace std;

typedef unsigned long long int ull;

const ull MOD = 2147483648 - 1; //2^31 - 1

int n;
//�� ĭ '.', ��ֹ� ĭ '#'
string mp[1001];

//dp - Right & Down
ull cache[1001][1001];

ull dp(int r, int c) {
	//base case
	//(R,C)�� ������ ��� ��� �ϳ� �߰�
	if (r == n - 1 && c == n - 1) return 1;

	//���� ������ �� ��� ��� X
	if (r < 0 || r > n-1) return 0;
	if (c < 0 || c > n-1) return 0;

	//��ֹ��� �ִ� ĭ�� ��� ��� X
	if (mp[r][c] == '#') return 0;

	ull& ret = cache[r][c];
	if (ret != -1) return ret;

	ret = dp(r + 1, c) % MOD;
	ret += dp(r, c + 1) % MOD;
	return ret;
}


//bfs - Right & Left & Up & Down
int dirr[4] = { 1,-1,0,0 };
int dirc[4] = { 0,0,1,-1 };
bool visited[1001][1001];

bool bfs() {
	queue<pair<int, int>> q;
	q.push(make_pair(0, 0));

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		int curr = cur.first;
		int curc = cur.second;
		q.pop();
	
		//(R,C)�� ������ ��� ��� �߰�
		if (curr == n - 1 && curc == n - 1) 
			return true;

		if (visited[curr][curc]) continue;
		visited[curr][curc] = true;

		for (int i = 0; i < 4; i++) {
			int nextr = curr + dirr[i];
			int nextc = curc + dirc[i];

			if (nextr < 0 || nextr > n - 1) continue;
			if (nextc < 0 || nextc > n - 1) continue;
			if (visited[nextr][nextc]) continue;
			if (mp[nextr][nextc] == '#') continue;

			q.push(make_pair(nextr, nextc));
		}
	}

	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int i = 0; i < 1001; ++i)
		for (int j = 0; j < 1001; ++j) {
			cache[i][j] = -1;
			visited[i][j] = false;
		}

	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> mp[i];

	//Right & Down ����� ����
	ull path = dp(0, 0);
	if (path != 0) {
		cout << path;
		return 0;
	}

	//Right & Left & Up & Down ��� ����
	if (bfs()) cout << "THE GAME IS A LIE";
	else cout << "INCONCEIVABLE";

	return 0;
}