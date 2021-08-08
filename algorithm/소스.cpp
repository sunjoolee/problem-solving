#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int n, s, d;

//����
vector<int> edge[100001];

//��� �湮 ����
int visited[100001];

//toLeaf[i]: ��� i ~ ���� �������� �ִ� ����
int toLeaf[100001] = { 0 };

//������̰� �̵��� �Ÿ�(��)
int path = 0;

int getToLeaf(int curnode) {
	
	//��� �湮 ǥ��
	visited[curnode] = 1;

	//�ڽ� ��� ���� ��� ���� �������� �ִ� ���� = 0
	int maxdep = 0;

	for (int i = 0; i < edge[curnode].size(); ++i) {
		int nextnode = edge[curnode][i];

		if (visited[nextnode] == 0)
			maxdep = max(maxdep, 1 + getToLeaf(nextnode));
	}
	
	toLeaf[curnode] = maxdep;
	return maxdep;
}

void moveMotorcycle(int curnode) {

	//��� �湮 ǥ��
	visited[curnode] = 1;

	//DFS
	for (int i = 0; i < edge[curnode].size(); ++i) {
		int nextnode = edge[curnode][i];

		if (visited[nextnode] == 0) {
			//toLeaf > d�� ��� ������̰� �̵�
			if (toLeaf[nextnode] >= d) path++;

			moveMotorcycle(nextnode);
		}
	}

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> s >> d;

	for (int i = 1; i < n; ++i) {
		int x, y;
		cin >> x >> y;

		edge[x].push_back(y);
		edge[y].push_back(x);
	}

	//�� = 0�� ��� ��� ������ �� �̵��ؾ��Ѵ�
	if (d == 0){
		cout << 2 * (n - 1);
		return 0;
	}

	memset(visited, 0, sizeof(visited));
	getToLeaf(s);

	memset(visited, 0, sizeof(visited));
	moveMotorcycle(s);

	//������̰� �̵��� �Ÿ�(�պ�)
	cout << 2 * path;

	return 0;
}