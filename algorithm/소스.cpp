#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <memory.h>
#include <map>
#include <algorithm>
using namespace std;

const int MAX_V = 40000;
const int INF = 987654321;
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

	//v에서 u로 가는 간선을 초기화한다 (유령 간선)
	vu->target = u;
	vu->capacity = 0;
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
	vector<string> city;

	//도시의 정점를 in, out 정점으로 쪼갠다
	//도시~도시 연결 간선 = 가중치 INF, 양방향 간선
	//in->out 연결 간선 = 가중치 1, 단방향 간선

	//정점의 번호 짝수 = 도시의 좌표의 번호 & 도시의 정점로 들어가는 in 정점의 번호
	//정점의 번호 홀수 = 도시의 정점에서 나오는 out 정점의 번호
	V = 0;
	vector<vector<int>> id(200, vector<int>(200, -1));

	//도현의 좌표의 아이디 기억하기
	int sId;
	//학교의 좌표의 아이디 기억하기
	int tId;

	for (int i = 0; i < R; ++i) {
		string input;
		cin >> input;
		city.push_back(input);

		//모든 도시의 좌표를 순회하며 도시의 좌표에 번호 붙이기 
		//해당 좌표 정점을 쪼개어 in->out 간선 만들기

		for (int j = 0; j < W; ++j) {
			if (city[i][j] != '#') {
				id[i][j] = V;
				V += 2;

				//in -> out 간선 추가
				addEdge(id[i][j], id[i][j] + 1, 1);
			}
			if (city[i][j] == 'K') sId = id[i][j];
			if (city[i][j] == 'H') tId = id[i][j];
		}
	}


	//모든 칸에 대해 인접한 칸을 순회하며 간선을 연결한다 
	for (int i1 = 0; i1 < R; ++i1) {
		for (int j1 = 0; j1 < W; ++j1) {

			if (city[i1][j1] != '#') {

				for (int k = 0; k < 4; ++k) {
					int i2 = i1 + rDir[k];
					int j2 = j1 + wDir[k];

					if (inRange(i2, j2) && city[i2][j2] != '#') {

						//예외 처리 -> 도현과 학교 인접한 경우
						if ((id[i1][j1] == sId && id[i2][j2] == tId) || (id[i1][j1] == tId && id[i2][j2] == sId)) {
							cout << -1;
							return 0;
						}

						//(i1, j1)out ~ (i2, j2)in 간선 추가
						addEdge(id[i1][j1] + 1, id[i2][j2], INF);
						//(i2, j2)out ~ (i1, j1)in 간선 추가
						addEdge(id[i2][j2] + 1, id[i1][j1], INF);
					}
				}
			}
		}

	}

	//도현 좌표 out -> 학교 좌표 in 경로
	cout << networkFlow(sId + 1, tId);

	return 0;
}