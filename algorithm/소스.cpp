#include <iostream>
#include <queue>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;


bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
	bool answer;

	//����� �� 
	vector<vector<int>> bidirPath(n, vector<int>());

	for (int i = 0; i < path.size(); ++i) {
		for (int j = 0; j < path[i].size(); ++j) {
			int u = i;
			int v = path[i][j];

			bidirPath[u].push_back(v);
			bidirPath[v].push_back(u);
		}
	}

	//first -> second ������ �湮�ؾ��ϴ� ���
	//reverseOrderMap[second] = first
	map<int, int> reverseOrderMap;

	for (int i = 0; i < order.size(); ++i) {
		for (int j = 0; j < order[i].size(); ++j) {
			int first = i;
			int second = order[i][j];
			reverseOrderMap[second] = first;
		}
	}

	//bfs�� Ʈ�� ����
	queue <int> q;
	vector<int> visited(n, 0);
	
	//bfs �ݺ� Ƚ��
	int trial = 1;

	while (true) {
		bool noChange = true;

		q.push(0);
		while (!q.empty()) {
			int cur = q.front();
			q.pop();

			if (visited[cur] == trial) continue;
			visited[cur] = trial;

			for (int i = 0; i < bidirPath[cur].size(); ++i) {
				int next = bidirPath[cur][i];

				//�̹� �湮�� ������� Ȯ��
				if (visited[next]!= trial){

					//���� �湮�ؾ� �� ������ �湮 �Ǿ����� Ȯ��
					if ((reverseOrderMap.find(next) != reverseOrderMap.end()) && (visited[reverseOrderMap[next]] == 0)) 
						continue;

					//trial��° bfs���� ó������ �湮�� ��� 
					if(visited[next] == 0) noChange = false;
					
					q.push(next);
				}
			}
		}

		trial++;

		if (noChange) {
			answer = true;

			//��� ���� ��ȸ ���� Ȯ��
			for (int i = 0; i < n; ++i) {
				if (visited[i] == 0) {
					answer = false;
				}
			}

			break;
		}
	}

	return answer;
}

int main() {
	int n = 9;

	vector<vector<int>> path(9, vector<int>());
	vector<vector<int>> order(9, vector<int>());
	
	for (int i = 0; i < 8; ++i) {
		int a, b;
		cin >> a >> b;
		path[a].push_back(b);
	}
	for (int i = 0; i < 3; ++i) {
		int a, b;
		cin >> a >> b;
		order[a].push_back(b);
	}

	cout << solution(n, path, order);

}