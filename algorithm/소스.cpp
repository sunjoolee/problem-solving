#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

//지점 수, 방문 수
int N, K;

//edge[i]: 지점 i의 <x좌표, y좌표>
vector<pair<int, int>> edge;

//dist[i]: i와 다른 지점들 간의 거리 
vector<int> dist[1002];

int visited[1002];

//두 지점간의 거리 계산
int d(pair<int, int>a, pair<int, int> b) {
	double x1 = a.first; double y1 = a.second;
	double x2 = b.first; double y2 = b.second;
	
	//거리 올림
	return ceil(sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) + 0.5);
}

//연료통 x리터일 때 지점을 K번 이하 방문하여 목적지까지 도착할 수 있는가?
bool bfs(int x) {
	memset(visited, 0, sizeof(visited));

	//<지점 번호, 방문 횟수>
	queue<pair<int, int>> q;
	q.push(make_pair(0, 0));

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		int curNode = cur.first;
		int curCnt = cur.second;
		q.pop();

		//이미 방문한 지점이면 건너뛰기
		if (visited[curNode]) continue;
		visited[curNode] = 1;

		//지점 방문 횟수 K번 이상인 경우 건너뛰기
		if (curCnt > K + 1) continue;

		//도착 지점 도착
		if (edge[curNode].first == 10000 && edge[curNode].second == 10000)
			return true;

		for (int i = 0; i < edge.size(); ++i) {
			//아직 방문하지 않았고, x연료로 갈 수 있는 거리(10 km/l) 내 지점인 경우
			if (visited[i] == 0) {
				if (dist[curNode][i] <= 10 * x) {
					q.push(make_pair(i, curCnt + 1));
				}
			}
		}
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> N >> K;

	//출발 지점 추가
	edge.push_back(make_pair(0, 0));
	for (int i = 0; i < N; ++i) {
		int x, y;
		cin >> x >> y;
		edge.push_back(make_pair(x, y));
	}
	//도착 지점 추가
	edge.push_back(make_pair(10000, 10000));

	//모든 지점들 간의 서로 간의 거리 저장
	for (int i = 0; i < edge.size(); ++i) {
		for (int j = 0; j < edge.size(); ++j) {

			//dist[i][j]: i번 지점과 j번 지점 간의 거리
			dist[i].push_back(d(edge[i], edge[j]));
		}
	}

	int lo = 0;
	int hi = 10000 * 2;
	for (int it = 0; it < 100; ++it) {
		int mid = (hi + lo) / 2;

		if (bfs(mid)) hi = mid;
		else lo = mid;
	}

	cout << hi;
	return 0;
}