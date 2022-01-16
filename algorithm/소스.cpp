#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//인접 리스트로 포드-풀커슨 알고리즘 구현하기
const int MAX_V = 500;

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

	//v에서 u로 가는 간선을 초기화한다
	//이 간선은 용량이 0인 유령 간선이다
	vu->target = u;
	vu->capacity = 0;
	vu->flow = 0;
	vu->reverse = uv;

	adj[u].push_back(uv);
	adj[v].push_back(vu);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	return 0;
}