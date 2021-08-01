#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


//adj[i] : ���i�� ������ ��� ����
vector<int> adj[200000];

//visited[i] : ��� i�� bfs�� ���� �湮�� Ƚ��
//(adj[i].size() / 2)�� �̻� �湮�Ǹ� ��Ӹ� �ϱ� �����Ѵ�
int visited[200000] = { 0 };

//belive[i]: ��� i�� ��Ӹ� �ϱ� ������ �ð�
int believe[200000];

//<���� ��� ��ġ, ���� �ð�>
//��Ӹ� �ϱ� �����ϸ� ��� ť�� ����
queue<pair<int, int>> q;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int i = 0; i < 200000; ++i)
		believe[i] = -1;

	int n;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		while (true) {
			int input;
			cin >> input;
			if (input == 0) break;

			adj[i].push_back(input - 1);
		}
	}


	//���� ������
	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		int input;
		cin >> input;
		q.push(make_pair(input - 1, 0));
	}

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		int curnode = cur.first;
		int curtime = cur.second;
		q.pop();

		//�ڽ��� ��Ӹ� �ϱ� ������ �ð� ����
		if (believe[curnode] != -1) continue;
		believe[curnode] = curtime;

		//�ڽ��� �ֺ� ��忡 ��� ��Ʈ����
		for (int i = 0; i < adj[curnode].size(); ++i) {
			int adjnode = adj[curnode][i];

			if (believe[adjnode] == -1) {
				visited[adjnode]++;
				if (visited[adjnode] >= ((double)adj[adjnode].size() / 2)) {
					q.push(make_pair(adjnode, curtime + 1));
				}
			}
		}
	}
	
	for (int i = 0; i < n; ++i)
		cout << believe[i] << " ";

	return 0;
}