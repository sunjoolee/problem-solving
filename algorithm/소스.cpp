#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <memory.h>
#include <map>
#include <algorithm>
using namespace std;

//인접 리스트로 포드-풀커슨 알고리즘 구현하기

const int INF = 987654321;
const int MAX_V = 60;

//정점의 개수
int V;

//간선의 정보를 나타내는 구조체
struct Edge {
	int target, capacity, flow;

	//역방향 간선의 포인터
	Edge* reverse;

	//이 간선의 잔여 용량을 계산한다
	int residualCapacity() const { return capacity - flow; }

	//이 간선을 이용해 amount를 보낸다
	void push(int amount) {
		flow += amount;
		reverse->flow -= amount;
	}
};

//유량 네트워크의 인접 리스트
vector<Edge*> adj[MAX_V];

//u에서 v로 가는 간선을 추가한다
void addEdge(int u, int v, int capacity) {
	Edge* uv = new Edge();
	Edge* vu = new Edge();

	//u에서 v로 가는 간선을 초기화한다
	uv->target = v;
	uv->capacity = capacity;
	uv->flow = 0;
	uv->reverse = vu;

	//v에서 u로 가는 간선을 초기화한다 (양방향 간선)
	vu->target = u;
	vu->capacity = capacity;
	vu->flow = 0;
	vu->reverse = uv;

	adj[u].push_back(uv);
	adj[v].push_back(vu);
}


int networkFlow(int source, int sink) {
	
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

			for (int i = 0; i < adj[here].size(); ++i) {
				Edge* hereToThere = adj[here][i];
				int there = hereToThere->target;

				//잔여 용량이 남아있는 간선 탐색
				if (hereToThere->residualCapacity() > 0 && parent[there] == -1) {
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
			for (int i = 0; i < adj[parent[p]].size(); ++i) {
				Edge* pEdge = adj[parent[p]][i];
				if (pEdge->target == p) {
					amount = min(pEdge->residualCapacity(), amount);
				}
			}
		}

		//증가 경로를 통해 유량을 보낸다
		for (int p = sink; p != source; p = parent[p]) {
			for (int i = 0; i < adj[parent[p]].size(); ++i) {
				Edge* pEdge = adj[parent[p]][i];
				if (pEdge->target == p) {
					pEdge->push(amount);
				}
			}
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

	//만들어야할 간선의 정보 저장
	int makeEdge[MAX_V][MAX_V];
	memset(makeEdge, 0, sizeof(makeEdge));

	for (int i = 0; i < N; ++i) {
		char node1, node2; 
		int capa;
		cin >> node1 >> node2 >> capa;

		if (id.find(node1) == id.end()) {
			id[node1] = V++;
		}
		if (id.find(node2) == id.end()) {
			id[node2] = V++;
		}

		if(id[node1] <= id[node2]) makeEdge[id[node1]][id[node2]] += capa;
		else makeEdge[id[node2]][id[node1]] += capa;
	}


	//간선 만들기
	for (int i = 0; i < V; ++i) {
		for (int j = i; j < V; ++j) {
			//양방향 파이프
			addEdge(i, j, makeEdge[i][j]);
		}
	}

	//A에서 Z까지 최대 유량 출력
	cout << networkFlow(id['A'], id['Z']);

	return 0;
}