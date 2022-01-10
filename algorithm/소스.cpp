#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

const int MAX_V = 50;

//ũ�罺Į �ּ� ���д� Ʈ�� �˰���
//Ʈ���� �̿��� ��ȣ ��Ÿ�� ������ �����Ѵ�

struct DisjointSet {
	vector<int> parent, rank;
	DisjointSet(int n) : parent(n), rank(n, 1) {
		for (int i = 0; i < n; ++i)
			parent[i] = i;
	}

	//u�� ���� Ʈ���� ��Ʈ ��ȣ ��ȯ
	int find(int u) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}

	//u�� ���� Ʈ���� v�� ���� Ʈ���� ��ģ��
	void merge(int u, int v) {
		u = find(u); v = find(v);

		//u�� v�� �̹� ���� Ʈ���� ���ϴ� ��� �ɷ���
		if (u == v) return;

		if (rank[u] > rank[v]) swap(u, v);
		parent[u] = v;
		if (rank[u] == rank[v]) ++rank[v];
	}
};

//������ ����
int V;

//�׷����� ���� ����Ʈ (����� ���� ��ȣ, ���� ����ġ) �� ����
vector<pair<int, int>> adj[MAX_V];

//�־��� �׷����� ���� �ּ� ���д� Ʈ�� ����ġ�� ���� ��ȯ�Ѵ�.
int kruskal() {
	int ret = 0;

	//<����ġ, <u, v>>�� ����� ��´�
	vector<pair<int, pair<int, int>>> edges;

	for (int u = 0; u < V; ++u) {
		for (int i = 0; i < adj[u].size(); ++i) {
			int v = adj[u][i].first;
			int cost = adj[u][i].second;
			edges.push_back({ cost, {u, v} });
		}
	}
	//����ġ������ ����
	sort(edges.begin(), edges.end());

	//ó���� ��� ������ ���� �и��Ǿ� �ִ�.
	DisjointSet sets(V);

	for (int i = 0; i < edges.size(); ++i) {
		int cost = edges[i].first;
		int u = edges[i].second.first;
		int v = edges[i].second.second;

		//���� (u, v)�� �˻��Ѵ�.
		//�̹� u�� v�� ����Ǿ����� ���(����Ŭ) ����
		if (sets.find(u) == sets.find(v)) continue;

		sets.merge(u, v);
		ret += cost;
	}

	//��� ��ǻ�� ���� Ȯ��
	bool connected = true;
	for (int i = 0; i < V; ++i) {
		//��� �ϳ��� ���տ� �ִٸ� ��� ���� parent�� ���´�
		if (sets.find(i) != sets.find(0)) {
			connected = false;
			break;
		}
	}

	if (!connected) return -1;
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//���ĺ� ���� ����
	map<char, int> alphaToNum;
	for (int i = 0; i < 26; ++i) {
		char alpha = 97 + i; //�ҹ���
		char alpha2 = 65 + i; //�빮��

		alphaToNum[alpha] = i + 1;
		alphaToNum[alpha2] = i + 27;
	}

	cin >> V;
	int totalLen = 0;

	for (int i = 0; i < V; ++i) {
		string input;
		cin >> input;

		for (int j = 0; j < V; ++j) {
			
			//���� �������� �ʴ� ���
			if (input[j] == '0') continue;

			int len = alphaToNum[input[j]];
			totalLen += len;

			adj[i].push_back({ j, len });
		}
	}
	
	int res = kruskal();

	if (res == -1) cout << "-1";
	else cout << totalLen - res;

	return 0;
}