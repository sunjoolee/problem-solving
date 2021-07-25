#include <iostream>
#include <queue>
#include <utility>
#include <string>
#include <algorithm>
using namespace std;

const int MAXX = 100;

int n,m;

//이동할 수 없는 칸 0
//이동할 수 있는 칸 1
//이미 방문한 칸 2
string mp[MAXX+1];

int rdir[4] = {-1,0,0,1};
int cdir[4] = { 0,-1,1,0};

int bfs() {
	//<<r, c>, move>
	queue<pair<pair<int,int>, int>> que;

	que.push(make_pair(make_pair(0,0),1));
	
	while (!que.empty()) {
		pair<pair<int, int>, int> cur = que.front();
		int curr = cur.first.first;
		int curc = cur.first.second;
		int move = cur.second;
		que.pop();

		if (curr == (n-1) && curc == (m-1))
			return move;

		if (mp[curr][curc] != '1') 
			continue;
		//방문 표시
		mp[curr][curc] = '2';
		
		for (int i = 0; i < 4; i++) {
			int nextr = curr + rdir[i];
			int nextc = curc + cdir[i];

			if (nextr < 0 || nextr >= n) continue;
			if (nextc < 0 || nextc >= m) continue;

			if (mp[nextr][nextc] == '1')
				que.push(make_pair(make_pair(nextr, nextc), move + 1));
		}
	}
	
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		cin >> mp[i];

	cout << bfs();
	return 0;
}