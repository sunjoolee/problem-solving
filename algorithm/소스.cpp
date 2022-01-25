#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 200;
const int MAX_M = 200;

//--------------------------------------
//�̺� ��Ī ������ �ذ��ϴ� ���� ��� �˰���

//A�� B�� ������ ����
int n, m;

//adj[i][j] = Ai�� Bj�� ����Ǿ� �ִ°�?
bool adj[MAX_N][MAX_M];

//�� ������ ��Ī�� ��� ������ ��ȣ�� �����Ѵ�
vector<int> aMatch, bMatch;

//dis()�� �湮 ����
vector<bool> visited;

//A�� ������ a���� B�� ��Ī���� ���� �������� ���� ��θ� ã�´�
bool dfs(int a) {
	if (visited[a]) return false;
	visited[a] = true;
	for (int b = 0; b < m; ++b) {
		if (adj[a][b]) {
			//b�� ��Ī�Ǿ� ���� �ʴٸ� bMatch[b]�������� ������ ���� ��θ� ã�´�
			if (bMatch[b] == -1 || dfs(bMatch[b])) {
				//���� ��� �߰� -> a�� b�� ��ġ��Ų��
				aMatch[a] = b;
				bMatch[b] = a;
				return true;
			}
		}
	}
	return false;
}

//aMatch, bMatch �迭�� ����ϰ� �ִ� ��Ī�� ũ�⸦ ��ȯ�Ѵ�
int bipartiteMatch(){
	//ó������ � ������ ����Ǿ� ���� �ʴ�
	aMatch = vector<int>(n, -1);	
	bMatch = vector<int>(m, -1);
	
	int size = 0;
	for (int start = 0; start < n; ++start) {
		visited = vector<bool>(n, false);
		//���� �켱 Ž���� ���� start���� �����ϴ� ���� ��θ� ã�´�
		if (dfs(start))
			++size;
	}
	return size;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	memset(adj, 0, sizeof(adj));

	cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		int num;
		cin >> num;
		
		for (int j = 0; j < num; ++j) {
			int input;
			cin >> input;
			adj[i][input-1] = 1;
		}
	}

	cout << bipartiteMatch();

	return 0;
}