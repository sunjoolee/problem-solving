#include <iostream>
#include <cstring>
#include<vector>
#include <set>
using namespace std;

int input[200001];
int parent[200001];

set <int> node;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> input[i];

	memset(parent, -1, sizeof(parent));

	
	for (int i = 0; i < n; ++i) {
		int curnode = input[i];
		node.insert(curnode);

		//���� parent�� �𸣴� ����� ���
		//parent�� ��ο��� �ڽ� �ٷ� �տ� �ִ� ���
		if (parent[curnode] == -1) {
			parent[curnode] = input[i - 1];
		}
	}
	//��Ʈ ���� �θ� ���� -1
	parent[input[0]] = -1;

	//������ ����
	cout << node.size() << "\n";
	for (auto it = node.begin(); it != node.end(); ++it)
		cout << parent[*it] << " ";

	return 0;
}