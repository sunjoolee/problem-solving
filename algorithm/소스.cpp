#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
#include <map>
#include <algorithm>
using namespace std;

//네트워크 유량 문제를 해결하는 포드-폴커슨 알고리즘의 구현

//정점의 최대 개수 = 소문자 + 대문자
const int MAX_V = 55;
const int INF = 987654321;
int V;

//capacity[u][v] = u에서 v로 보낼 수 있는 용량
//flow[u][v] = u에서 v로 흘러가는 유량 (반대 방향인 경우 음수)
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];

//flow[]를 계산하고 총 유량을 반환한다.
int networkFlow(int source, int sink) {
	
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

	return totalFlow;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//파이프의 개수
	int N;
	cin >> N;
	
	//파이프와 연결된 알파벳의 번호 매핑
	V = 0;
	map<char, int> id;

	//capacity를 0으로 초기화한다.
	memset(capacity, 0, sizeof(capacity));

	for (int i = 0; i < N; ++i) {
		char node1, node2; int capa;
		cin >> node1 >> node2 >> capa;

		if (id.find(node1) == id.end())
			id[node1] = V++;
		
		if (id.find(node2) == id.end())
			id[node2] = V++;
		
		//양방향 파이프
		capacity[id[node1]][id[node2]] = capa;
		capacity[id[node2]][id[node1]] = capa;
	}

	//A에서 Z까지 최대 유량 출력
	cout << networkFlow(id['A'], id['Z']);
	return 0;
}