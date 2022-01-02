#include <iostream>
#include  <algorithm>
using namespace std;

const int MAX_V = 500;

//������ ���� 
int V;
//�׷����� ���� ��� ǥ��
//adj[u][v] = u���� v�� ���� ������ ����ġ
int adj[MAX_V][MAX_V];

//�÷��̵�-�ͼ� �˰���
void floyd() {
	for (int i = 0; i < V; ++i) 
		adj[i][i] = 0;

	//i���� -> j�������� �̵��� �� ���İ��� ���� K
	for (int k = 0; k < V; ++k)
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j)
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	return 0;
}