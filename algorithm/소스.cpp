#include <iostream>
#include <vector>
using namespace std;

const int MAX_V = 1000;
const int INF = 987654321;

//������ ����
int V;
//�׷����� ���� ����Ʈ <����� ���� ��ȣ, ������ ����ġ>
vector<pair<int, int>> adj[MAX_V];

//���� ����Ŭ�� ���� ��� �� �� �迭 ��ȯ
//���� ���� src
vector<int> bellmanFord(int src) {
	//�������� ������ ��� ���������� �ִ� �Ÿ� ���� INF
	vector<int> upper(V, INF);
	upper[src] = 0;
	bool updated;

	//V�� ��ȸ
	for (int iter = 0; iter < V; ++iter) {
		updated = false;
		for (int here = 0; here < V; ++here) {
			for (int i = 0; i < adj[here].size(); ++i) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				//(here, there)������ ���� ��ȭ �õ�
				if (upper[there] > upper[here] + cost) {
					//����
					upper[there] = upper[here] + cost;
					updated = true;
				}
			}
		}
		//��� ������ ���� ��ȭ�� �������� ��� V-1�� �� �ʿ� ���� ���� ����
		if (!updated) break;
	}
	//V��° ��ȸ���� ��ȭ�� �����ߴٸ� ���� ����Ŭ ����
	if (updated) upper.clear();

	return upper;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	return 0;
}