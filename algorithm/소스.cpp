#include <iostream>
#include <vector>
#include  <algorithm>
using namespace std;

typedef long long ll;
const int MAX_V = 100;
const ll INF = 987654321;

//ȸ�� ������ �� 
int V;
//�׷����� ���� ��� ǥ��
//������ ����ġ
ll adj[MAX_V][MAX_V];

//�÷��̵�-�ͼ� �˰���
void floyd() {
	for (int i = 0; i < V; ++i) {
		adj[i][i] = 0LL; 
	}

	//i���� -> j�������� �̵��� �� ���İ��� ���� K
	for (int k = 0; k < V; ++k) {
		for (int i = 0; i < V; ++i) {
			for (int j = 0; j < V; ++j) {
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//adj �ʱ�ȭ
	for (int i = 0; i < MAX_V; ++i) {
		for (int j = 0; j < MAX_V; ++j) {
			adj[i][j] = INF;
		}
	}

	//������ ���� ���� ��
	int M;
	cin >> V >> M;

	for (int i = 0; i < M; ++i) {
		int a, b;
		cin >> a >> b;

		//�����
		adj[a - 1][b - 1] = min(adj[a - 1][b - 1], 1LL);
		adj[b - 1][a - 1] = min(adj[b - 1][a - 1], 1LL);
	}

	floyd();

	//����ȸ�� ��
	int groupCnt = 0;

	//group[������] = �Ҽӵ� ����ȸ ��ȣ (�Ҽӵ��� ���� ��� -1)
	int group[MAX_V];

	//maxTime[������] = �����ڰ� ����ȸ ��ǥ�� ��� �ִ� �ǻ����޽ð�
	ll maxTime[MAX_V];

	//�迭 �ʱ�ȭ
	for (int i = 0; i < MAX_V; ++i) {
		group[i] = maxTime[i] = -1;
	}

	//�ƴ� ���� ���� ����ȸ�� ���ϵ��� ����
	for (int i = 0; i < V; ++i) {
		//�Ҽӵ� ����ȸ ���� ��� ����ȸ ����
		if (group[i] == -1) {
			groupCnt++;
			group[i] = groupCnt;
		}

		for (int j = 0; j < V; ++j) {
			//��� �����ϴ� ��� �ƴ� ���� -> ���� ����ȸ �Ҽ�
			if (adj[i][j] < INF) {
				group[j] = group[i];

				//�ִ� �ǻ����޽ð� ���
				maxTime[i] = max(maxTime[i], adj[i][j]);
			}
		}

	}
	cout << groupCnt << "\n";

	//����ȸ ��ǥ ����
	vector<int> vec;
	for (int n = 1; n <= groupCnt; ++n) {
		int minPerson;
		ll minTime = INF;

		for (int i = 0; i < V; ++i) {
			if (group[i] != n) continue;
			
			if (minTime > maxTime[i]) {
				minTime = maxTime[i];
				minPerson = i;
			}
		}
		vec.push_back(minPerson);
	}

	sort(vec.begin(), vec.end());
	for (int i = 0; i < vec.size(); ++i)
		cout << vec[i] << "\n";

	return 0;
}