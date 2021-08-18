#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

//���� ��, �湮 ��
int N, K;

//edge[i]: ���� i�� <x��ǥ, y��ǥ>
vector<pair<int, int>> edge;

//dist[i]: i�� �ٸ� ������ ���� �Ÿ� 
vector<int> dist[1002];

int visited[1002];

//�� �������� �Ÿ� ���
int d(pair<int, int>a, pair<int, int> b) {
	double x1 = a.first; double y1 = a.second;
	double x2 = b.first; double y2 = b.second;
	
	//�Ÿ� �ø�
	return ceil(sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) + 0.5);
}

//������ x������ �� ������ K�� ���� �湮�Ͽ� ���������� ������ �� �ִ°�?
bool bfs(int x) {
	memset(visited, 0, sizeof(visited));

	//<���� ��ȣ, �湮 Ƚ��>
	queue<pair<int, int>> q;
	q.push(make_pair(0, 0));

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		int curNode = cur.first;
		int curCnt = cur.second;
		q.pop();

		//�̹� �湮�� �����̸� �ǳʶٱ�
		if (visited[curNode]) continue;
		visited[curNode] = 1;

		//���� �湮 Ƚ�� K�� �̻��� ��� �ǳʶٱ�
		if (curCnt > K + 1) continue;

		//���� ���� ����
		if (edge[curNode].first == 10000 && edge[curNode].second == 10000)
			return true;

		for (int i = 0; i < edge.size(); ++i) {
			//���� �湮���� �ʾҰ�, x����� �� �� �ִ� �Ÿ�(10 km/l) �� ������ ���
			if (visited[i] == 0) {
				if (dist[curNode][i] <= 10 * x) {
					q.push(make_pair(i, curCnt + 1));
				}
			}
		}
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> N >> K;

	//��� ���� �߰�
	edge.push_back(make_pair(0, 0));
	for (int i = 0; i < N; ++i) {
		int x, y;
		cin >> x >> y;
		edge.push_back(make_pair(x, y));
	}
	//���� ���� �߰�
	edge.push_back(make_pair(10000, 10000));

	//��� ������ ���� ���� ���� �Ÿ� ����
	for (int i = 0; i < edge.size(); ++i) {
		for (int j = 0; j < edge.size(); ++j) {

			//dist[i][j]: i�� ������ j�� ���� ���� �Ÿ�
			dist[i].push_back(d(edge[i], edge[j]));
		}
	}

	int lo = 0;
	int hi = 10000 * 2;
	for (int it = 0; it < 100; ++it) {
		int mid = (hi + lo) / 2;

		if (bfs(mid)) hi = mid;
		else lo = mid;
	}

	cout << hi;
	return 0;
}