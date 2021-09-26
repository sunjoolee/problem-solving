#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//���ĺ��� �� ���ڿ� ���� ���� ��� ǥ��
//adj[i][j]: ���� i�� ���� j���� ���� �;����� ��Ÿ����
vector<vector<int>> adj;

void makeGraph(const vector<string>& words) {
	//adj �ʱ�ȭ
	adj = vector<vector<int>>(26, vector<int>(26, 0));

	for (int j = 1; j < words.size(); ++j) {
		int i = j - 1;
		int len = min(words[i].size(), words[j].size());

		for (int k = 0; k < len; ++k) {
			if (words[i][k] != words[j][k]) {
				int a = words[i][k] - 'a';
				int b = words[j][k] - 'a';
				adj[a][b] = 1;
				break;
			}
		}
	}
}

//���� �켱 Ž���� �̿��� ���� ����
vector<int> seen, order;

//���� �켱 Ž���� �����ϸ� dfs���� ���� ���
void dfs(int here) {
	seen[here] = 1;
	for (int there = 0; there < 26; ++there) {
		if (adj[here][there] && !seen[there])
			dfs(there);
	}
	order.push_back(here);
}

//adj�� �־��� �׷��� ���� ������ ��� ��ȯ
//�׷����� DAG�� �ƴ϶�� �� ���� ��ȯ
vector<int> topologicalSort() {
	int n = adj.size();
	seen = vector<int>(n, 0);
	order.clear();

	//dfsAll
	for (int i = 0; i < n; ++i) {
		if (!seen[i]) dfs(i);
	}
	//dfs ���� �������� ������
	reverse(order.begin(), order.end());

	//���� ���� ����� ������ ������ �ִٸ� DAG�� �ƴϴ�
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (adj[order[j]][order[i]]) return vector<int>();
		}
	}

	return order;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int C;
	cin >> C;
	while (C--) {
		int n;
		cin >> n;

		vector<string> words;
		string input;
		for (int i = 0; i < n; ++i) {
			cin >> input;
			words.push_back(input);
		}

		makeGraph(words);
		vector<int> res = topologicalSort();

		if (res.size() == 0) {
			cout << "INVALID HYPOTHESIS\n";
		}
		else {
			for (auto it = res.begin(); it < res.end(); ++it) 
				cout << (char)(*it + 'a');
			cout << "\n";
		}
	}

	return 0;
}