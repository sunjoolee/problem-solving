#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	//��Ʈ -1, ���� -2
	int parent[50];

	for (int i = 0; i < n; ++i) {
		int p;
		cin >> p;
		parent[i] = p;
	}

	//������ ����� ��ȣ
	int x;
	cin >> x;

	//��Ʈ�� ������ ���
	if (parent[x] == -1) {
		cout << 0;
		return 0;
	}

	//��� ���� & �� ��带 �θ�� �ϴ� ��带 �����ϱ� ���� ť�� ����
	queue<int> q;
	q.push(x);

	while (!q.empty()) {
		int p = q.front();
		//��� ����
		parent[p] = -2;
		q.pop();

		for (int i = 0; i < n; ++i) {
			//�� ��带 �θ�� �ϴ� ��� ť�� ����
			if (parent[i] == p) {
				q.push(i);
			}
		}
	}

	//���� ����� ���� Ȯ��
	int leaf = 0;
	for (int i = 0; i < n; ++i) {
		//������ ����� �ǳʶڴ�
		if (parent[i] == -2) continue;

		bool isLeaf = true;
		for (int j = 0; j < n; ++j) {
			//�ڽ��� �θ�� ���� ��尡 �ִٸ� ���� ��尡 �� �� ����
			if (parent[j] == i) {
				isLeaf = false;
				break;
			}
		}

		if (isLeaf) leaf++;
	}

	cout << leaf;
	return 0;
}