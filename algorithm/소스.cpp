#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <memory.h>
#include <map>
#include <algorithm>
using namespace std;

//네트워크 유량 문제를 해결하는 포드-폴커슨 알고리즘의 구현

//정점의 최대 개수 = 도시의 크기 NxM
const int MAX_V = 10000;
const int INF = 987654321;
int V;

//capacity[u][v] = u에서 v로 보낼 수 있는 용량
//flow[u][v] = u에서 v로 흘러가는 유량 (반대 방향인 경우 음수)
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];


int networkFlow(int source, int sink) {
	
	//---------------------------------
	//포드-폴커슨 알고리즘 


	//flow를 0으로 초기화한다.
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;
	
	while (true) {
		//BFS로 증가 경로를 찾는다
		vector<int> parent(MAX_V, -1);
		queue<int> q;

		parent[source] = source;
		q.push(source);

		while (!q.empty() && parent[sink] == -1) {
			int here = q.front();
			q.pop();

			for (int there = 0; there < V; ++there) {
				//잔여 용량이 남아있는 간선 탐색
				if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
					q.push(there);
					parent[there] = here;
				}
			}
		}

		//증가 경로가 없는 경우 종료
		if (parent[sink] == -1) break;
		
		//증가 경로를 통해 유량을 얼마나 보낼지 결정한다
		int amount = INF;
		for (int p = sink; p != source; p = parent[p]) {
			int r = capacity[parent[p]][p] - flow[parent[p]][p];
			amount = min(r, amount);
		}
		//증가 경로를 통해 유량을 보낸다
		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		totalFlow += amount;
	}

	//---------------------------------
	//최대 용량 최대 유량 정리

	//source를 시작 정점으로하여 bfs를 하여 S를 구한다

	//bfs 이후 visited[정점] = 1 라면 이 정점은 S에 포함되고
	//visited[정점] = 0 라면 이 정점은 T에 포함된다

	vector<int> visited(V, 0);
	queue<int> qq;

	qq.push(source);

	while (!qq.empty()) {
		int here = qq.front();
		qq.pop();

		if (visited[here] == 1) continue;

		visited[here] = 1;

		for (int there = 0; there < V; ++there) {
			if (capacity[here][there] != 0 && visited[there] == 0) {
				//here -> there 간선의 잔여 용량 계산
				int r = capacity[here][there] - flow[here][there];
				
				//here = source인 경우 무조건 잔여 용량 있다고 가정
				if (here == source || r > 0) {
					qq.push(there);
				}
			}
		}
	}

	//컷S,T의 용량 = S->T를 연결하는 간선들의 용량의 합을 구한다
	int totalCapacity = 0;
	for (int i = 0; i < V; ++i) {
		for (int j = 0; j < V; ++j) {
			if (visited[i] == 1 && visited[j] == 0) {
				totalCapacity += capacity[i][j];
			}
		}
	}

	return totalCapacity;
}

//도시 크기
int R, W;

//인접한 좌표 계산을 위한 배열
const int rDir[4] = { 1, -1, 0, 0 };
const int wDir[4] = { 0, 0, 1, -1 };

bool inRange(int r, int w) {
	if (r < 0 || r >= R) return false;
	if (w < 0 || w >= W) return false;
	return true;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> R >> W;

	//도시
	vector<string> map;

	//좌표[r][w]의 i번호 = id[r][w]
	//이동할 수 없는 좌표인 경우 -1
	vector<vector<int>> id(100, vector<int>(100, -1));

	//도현이와 학교의 아이디
	int sId, tId;

	for (int i = 0; i < R; ++i) {
		string input;
		cin >> input;
		map.push_back(input);

		//각 칸을 순회하며 번호를 매긴다
		for (int j = 0; j < W; ++j) {
			if (map[i][j] != '#') id[i][j] = V++;

			if (map[i][j] == 'K') sId = id[i][j];
			if (map[i][j] == 'H') tId = id[i][j];
		}
	}


	//capacity를 0으로 초기화한다.
	memset(capacity, 0, sizeof(capacity));

	//그래프 모델링
	//모든 칸에 대해 인접한 칸 
	for (int i1 = 0; i1 < R; ++i1) {
		for (int j1 = 0; j1 < W; ++j1) {
			if (map[i1][j1] != '#') {
				for (int k = 0; k < 4; ++k) {
					int i2 = i1 + rDir[k];
					int j2 = j1 + wDir[k];
					if (inRange(i2, j2) && map[i2][j2] != '#') {
						//양방향, 가중치 1
						capacity[id[i1][j1]][id[i2][j2]] = 1;
						capacity[id[i2][j2]][id[i1][j1]] = 1;
					}
				}
			}
		}
		
	}

	//예외 -> 도현과 학교 인접한 경우
	if (capacity[sId][tId] != 0) {
		cout << -1;
		return 0;
	}


	cout << networkFlow(sId, tId);

	return 0;
}