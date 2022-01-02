#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef long long ll;

const int MAX_V = 500;
const ll INF = 987654321;
const ll OCHA = 250000;

//정점의 개수
int V;
//간선의 개수
int E;

//그래프의 인접 리스트 <연결된 정점 번호, 간선의 가중치>
vector<pair<int, ll>> adj[MAX_V];

//0번 도시와 연결된 도시인지 체크
vector<int> connected(MAX_V, 0);

void bfs() {
	queue<int> q;
	q.push(0);

	while (!q.empty()) {
		int here = q.front();
		q.pop();

		if (connected[here]) break;
		connected[here] = 1;

		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			if (!connected[there]) q.push(there);
		}
	}
}

//음수 사이클이 있을 경우 텅 빈 배열 반환
//시작 정점 src
vector<ll> bellmanFord(int src) {
	//시작점을 제외한 모든 정점까지의 최단 거리 상한 INF
	vector<ll> upper(V, INF);
	upper[src] = 0;
	bool updated;

	//V번 순회
	for (int iter = 0; iter < V; ++iter) {
		updated = false;
		for (int here = 0; here < V; ++here) {
			for (int i = 0; i < adj[here].size(); ++i) {
				int there = adj[here][i].first;
				ll cost = adj[here][i].second;

				//(here, there)간선을 따라 완화 시도
				if (upper[there] > upper[here] + cost) {
					//성공
					upper[there] = upper[here] + cost;

					//0번 도시와 연결된 도시인 경우 완화 체크
					if(connected[there]) updated = true;
				}
			}
		}
		//모든 간선에 대해 완화가 실패했을 경우 V-1번 돌 필요 없이 곧장 종료
		if (!updated) break;
	}
	//V번째 순회에도 완화가 성공했다면 음수 사이클 존재
	if (updated) upper.clear();

	return upper;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> V >> E;

	for (int i = 0; i < E; ++i) {
		int A, B;
		ll C;
		cin >> A >> B >> C;

		adj[A - 1].push_back({ B - 1, C });
	}

	//0번 도시와 연결된 도시 체크
	bfs();

	vector<ll> res = bellmanFord(0);
	
	if (res.empty()) cout << -1;
	else {
		for (int i = 1; i < res.size(); ++i) {
			if (res[i] < INF - OCHA) cout << res[i] << "\n";
			else cout << -1 << "\n";
		}
	}

	return 0;
}