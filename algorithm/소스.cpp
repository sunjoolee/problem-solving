#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//최적화된 상호 배타적 집합의 구현
//parent[i].first = i의 부모 노드의 번호
//parent[i].second = i가 루트 노드일 경우, 사이클인 경우 false, 사이클이 아닌 경우 true 저장
vector<pair<int, bool>> parent;
vector<int> rank_;

int find(int u) {
	if (u == parent[u].first) return u;
	return parent[u].first = find(parent[u].first);
}

void merge(int u, int v) {
	u = find(u); v = find(v);
	if (u == v) { 
		//u와 v가 이미 같은 연결 요소에 포함되어 있는 경우 = 사이클
		parent[u].second = false;
		parent[v].second = false;
		return; 
	}

	//연결 요소 + 사이클 = 사이클
	if (parent[u].second == false) parent[v].second = false;
	if (parent[v].second == false) parent[u].second = false;

	if (rank_[u] > rank_[v]) swap(u, v);
	parent[u].first = v;
	if (rank_[u] == rank_[v]) ++rank_[v];
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int caseNo = 1;
	while (true) {
		int n, m;
		cin >> n >> m;
		if (n == 0 && m == 0) break;

		//초기화
		parent.clear();
		rank_.clear();
		for (int i = 0; i < n; ++i) {
			parent.push_back(make_pair(i, true));
			rank_.push_back(1);
		}

		for (int i = 0; i < m; ++i) {
			int a, b;
			cin >> a >> b;
			merge(a - 1, b - 1);
		}

		//사이클이 아닌 연결 요소의 개수
		int cnt = 0;
		for (int node = 0; node < n; ++node) {
			if (node == parent[node].first && parent[node].second) ++cnt;
		}

		cout << "Case "<<caseNo<<": ";
		if (cnt == 0) cout << "No trees.\n";
		else if (cnt == 1) cout << "There is one tree.\n";
		else cout << "A forest of " << cnt << " trees.\n";

		++caseNo;
	}

	return 0;
}