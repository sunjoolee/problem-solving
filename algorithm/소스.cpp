#include <iostream>
#include <vector>
using namespace std;

const int MAX_V = 1000;
const int INF = 987654321;

//정점의 개수
int V;
//그래프의 인접 리스트 <연결된 정점 번호, 간선의 가중치>
vector<pair<int, int>> adj[MAX_V];

//음수 사이클이 있을 경우 텅 빈 배열 반환
//시작 정점 src
vector<int> bellmanFord(int src) {
	//시작점을 제외한 모든 정점까지의 최단 거리 상한 INF
	vector<int> upper(V, INF);
	upper[src] = 0;
	bool updated;

	//V번 순회
	for (int iter = 0; iter < V; ++iter) {
		updated = false;
		for (int here = 0; here < V; ++here) {
			for (int i = 0; i < adj[here].size(); ++i) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				//(here, there)간선을 따라 완화 시도
				if (upper[there] > upper[here] + cost) {
					//성공
					upper[there] = upper[here] + cost;
					updated = true;
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

	return 0;
}