#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//����ȭ�� ��ȣ ��Ÿ�� ������ ����
//parent[i].first = i�� �θ� ����� ��ȣ
//parent[i].second = i�� ��Ʈ ����� ���, ����Ŭ�� ��� false, ����Ŭ�� �ƴ� ��� true ����
vector<pair<int, bool>> parent;
vector<int> rank_;

int find(int u) {
	if (u == parent[u].first) return u;
	return parent[u].first = find(parent[u].first);
}

void merge(int u, int v) {
	u = find(u); v = find(v);
	if (u == v) { 
		//u�� v�� �̹� ���� ���� ��ҿ� ���ԵǾ� �ִ� ��� = ����Ŭ
		parent[u].second = false;
		parent[v].second = false;
		return; 
	}

	//���� ��� + ����Ŭ = ����Ŭ
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

		//�ʱ�ȭ
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

		//����Ŭ�� �ƴ� ���� ����� ����
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