#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

const int MAXL = 300;

int L;
int visited[MAXL][MAXL];

int rdir[8] = { -2,-2,-1,-1,1,1,2,2 };
int cdir[8] = { -1,1,-2,2,-2,2,-1,1 };

int bfs(int startr, int startc, int finishr, int finishc) {
	//<<r, c>, move>
	queue<pair<pair<int,int>, int>> que;

	que.push(make_pair(make_pair(startr, startc), 0));
	
	while (!que.empty()) {
		pair<pair<int, int>, int> cur = que.front();
		int curr = cur.first.first;
		int curc = cur.first.second;
		int move = cur.second;
		que.pop();

		if (curr == finishr && curc == finishc)
			return move;

		if (visited[curr][curc]) continue;
		visited[curr][curc] = 1;
		
		for (int i = 0; i < 8; i++) {
			int nextr = curr + rdir[i];
			int nextc = curc + cdir[i];

			if (nextr < 0 || nextr >= L) continue;
			if (nextc < 0 || nextc >= L) continue;

			que.push(make_pair(make_pair(nextr, nextc), move + 1));
		}
	}
	
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		memset(visited, 0, sizeof(visited));

		cin >> L;

		int startr, startc, finishr, finishc;
		cin >> startr >> startc >> finishr >> finishc;

		cout << bfs(startr, startc, finishr, finishc) << "\n";
	}

	return 0;
}