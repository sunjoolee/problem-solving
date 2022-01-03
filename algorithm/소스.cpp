#include <iostream>
#include  <algorithm>
using namespace std;

typedef long long ll;
const int MAX_V = 400;
const ll INF = 987654321;

//������ ���� 
int V;
//�׷����� ���� ��� ǥ��
//������ ����ġ
ll adj[MAX_V][MAX_V];
//������ ����ġ
ll adjOpposite[MAX_V][MAX_V];

//�÷��̵�-�ͼ� �˰���
void floyd() {
	for (int i = 0; i < V; ++i) {
		adj[i][i] = 0LL; 
		adjOpposite[i][i] = 0LL;
	}

	//i���� -> j�������� �̵��� �� ���İ��� ���� K
	for (int k = 0; k < V; ++k) {
		for (int i = 0; i < V; ++i) {
			for (int j = 0; j < V; ++j) {
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
				adjOpposite[i][j] = min(adjOpposite[i][j], adjOpposite[i][k] + adjOpposite[k][j]);
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
			adjOpposite[i][j] = INF;
		}
	}

	//���İ����� ��
	int k;
	cin >> V >> k;

	for (int i = 0; i < k; ++i) {
		int a, b;
		cin >> a >> b;

		adj[a-1][b-1] = min(adj[a-1][b-1], 1LL);
		adjOpposite[b-1][a-1] = min(adj[b-1][a-1], 1LL);
	}

	floyd();

	//�˰� ���� ���� ����
	int s;
	cin >> s;
	
	for (int i = 0; i < s; ++i) {
		int a, b;
		cin >> a >> b;

		//������ ��� ����
		if (adj[a - 1][b - 1] < INF) cout << "-1\n";
		//������ ��� ����
		else if (adjOpposite[a - 1][b - 1] < INF) cout << "1\n";
		//������ ��ο� ������ ��� �Ѵ� �������� ����
		else cout << "0\n";
	}
	

	return 0;
}