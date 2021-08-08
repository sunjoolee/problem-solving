#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//<����� ���, �����ϴ� ������ ���̳ʸ���Ʈ ��>
vector<pair<int, int>> edge[1001];
//��� �湮 ����
int visited[1001];

int getMinCost(int curnode, int curcost) {

	//��� �湮 ǥ��
	visited[curnode] = 1;
	
	//���� ����� ��� 
	//�ּ� ���̳ʸ���Ʈ ���� = �ڽ��� ������ ���̳ʸ���Ʈ ��
	if (curnode != 1 && edge[curnode].size() == 1)
		return curcost;

	//���� ��� �ƴ� ���
	//1. �ڽ� ������ �ּ� ���̳ʸ���Ʈ ������ �� ���
	int sum = 0;
	for (int i = 0; i < edge[curnode].size(); ++i) {
		int nextnode = edge[curnode][i].first;
		int nextcost = edge[curnode][i].second;

		if (nextnode != 1 && visited[nextnode] == 0)
			sum += getMinCost(nextnode, nextcost);
	}
	//2. min(�ڽ��� ������ ���̳ʸ���Ʈ ��, �ڽ� ������ �ּ� ���̳ʸ���Ʈ ������ ��)
	return min(curcost, sum);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		//�ʱ�ȭ
		for (int i = 0; i < 1001; ++i) {
			edge[i].clear();
			visited[i] = 0;
		}

		int n, m;
		cin >> n >> m;

		//�� �ϳ� ���� ���
		if (n == 1) {
			cout << 0;
			continue;
		}

		for (int i = 0; i < m; ++i) {
			int a, b, d;
			cin >> a >> b >> d;

			edge[a].push_back(make_pair(b, d));
			edge[b].push_back(make_pair(a, d));
		}
		
		//��Ʈ ��� 1�� ����� ������ ���� ���� ���
		int ans = 0;
		for (int i = 0; i < edge[1].size(); ++i) {
			int firstnode = edge[1][i].first;
			int firstcost = edge[1][i].second;
			ans += getMinCost(firstnode, firstcost);
		}

		cout << ans << "\n";
	}

	return 0;
}