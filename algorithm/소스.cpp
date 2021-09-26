#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//알파벳의 각 글자에 대한 인접 행렬 표현
//adj[i][j]: 글자 i가 글자 j보다 먼저 와야함을 나타낸다
vector<vector<int>> adj;

void makeGraph(const vector<string>& words) {
	//adj 초기화
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

//깊이 우선 탐색을 이용한 위상 정렬
vector<int> seen, order;

//깊이 우선 탐색을 진행하며 dfs종료 순서 기록
void dfs(int here) {
	seen[here] = 1;
	for (int there = 0; there < 26; ++there) {
		if (adj[here][there] && !seen[there])
			dfs(there);
	}
	order.push_back(here);
}

//adj에 주어진 그래프 위상 정렬한 결과 반환
//그래프가 DAG가 아니라면 빈 벡터 반환
vector<int> topologicalSort() {
	int n = adj.size();
	seen = vector<int>(n, 0);
	order.clear();

	//dfsAll
	for (int i = 0; i < n; ++i) {
		if (!seen[i]) dfs(i);
	}
	//dfs 종료 역순으로 뒤집기
	reverse(order.begin(), order.end());

	//만약 정렬 결과에 역방향 간선이 있다면 DAG가 아니다
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