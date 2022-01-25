#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
#include <algorithm>
using namespace std;

//네트워크 유량 문제를 해결하는 포드-폴커슨 알고리즘의 구현

const int MAX_V = 210;
const int INF = 987654321;
int V;

//cost[u][v] = u에서 v로 보내는게 드는 비용
//capacity[u][v] = u에서 v로 보낼 수 있는 용량
//flow[u][v] = u에서 v로 흘러가는 유량 (반대 방향인 경우 음수)
int cost[MAX_V][MAX_V], capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];


int networkFlow(int source, int sink) {
	
	//flow를 0으로 초기화한다.
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;

	//총 배송비
	int totalCost = 0;
	
	
	while (true) {

		//BFS로 증가 경로를 찾는다
		//dist[i][j] : i->j 경로의 최소 비용

		vector<int> parent(MAX_V, -1);
		vector<int> dist(MAX_V, INF);
		vector<bool> inQ(MAX_V, false);
		queue<int> q;

		parent[source] = source;
		dist[source] = 0;

		q.push(source);
		inQ[source] = true;

		while (!q.empty() && parent[sink] == -1) {
			int here = q.front();
			q.pop();
			inQ[here] = false;

			for (int there = 0; there < V; ++there) {
				//잔여 용량이 남아있는 간선 탐색
				if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
					
					//최소 비용 계산
					if (dist[here] + cost[here][there] < dist[there]) {
						dist[there] = dist[here] + cost[here][there];

						parent[there] = here;

						if (!inQ[there]) {
							q.push(there);
							inQ[there] = true;
						}
					}
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

			//보내는 경로의 배송비 계산
			totalCost += amount * cost[parent[p]][p];
		}
		totalFlow += amount;
	}

	return totalCost;
}


//그래프 구현
//source 0번
//서점 1번 ~ M번
//사람 1+M번 ~ M + N번
//sink M + N + 1번

//사람 수, 서점 수
int N, M;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;

	//점점 수 = 사람 수 + 서점 수 + source + sink
	V = N + M + 2;

	for (int i = 0; i < V; ++i) {
		for (int j = 0; j < V; ++j) {
			cost[i][j] = 0;
			capacity[i][j] = INF;
		}
	}

	//사람이 구매하고 싶은 책의 수
	//= 사람 -> sink 간선의 용량
	for (int i = 0; i < N; ++i) {
		cin >> capacity[1 + M + i][M+N+1];
	}
	//서점이 가지고 있는 책의 수
	//= source -> 서점 간선의 용량
	for (int i = 0; i < M; ++i) {
		cin >> capacity[0][1 + i];
	}

	//서점 i -> 사람 j 로 보내는 배송비
	//= 서점 i -> 사람 j로 보내는 비용
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> cost[1+i][1+M+j];
		}
	}

	cout << networkFlow(0,M+N+1);

	return 0;
}