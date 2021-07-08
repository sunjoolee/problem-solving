
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 10;
int n;
//inDegree[i]: ����i�� ���� ������ ��
int inDegree[MAXN] = { 0 };
//vector<int> child[i]: ���i�� ���� ���� �ϴ� ������ ����
vector<int> child[MAXN];
//���� ���� �Լ�
void topologySort() {
	int result[MAXN];
	queue<int> q;
	//���� ���� 0�� ���� ť�� ����
	for (int i = 1; i <= n; ++i)
		if (inDegree[i] == 0) q.push(i);
	//������ ������ ����Ǳ���� n���� ������ �湮�Ѵ�
	for (int i = 1; i <= n; ++i) {
		//n���� ������ �湮�ϱ� ���� ť�� �������� 
		//����Ŭ�� �߻��� ���̴�
		if (q.empty()) return;
		//���� ������ 0�� ���� ����
		int parent = q.front();
		result[i] = parent;
		//���õ� ������ ���⿡ �μӵ� ��� ������ ����
		q.pop();
		for (int i = 0; i < child[parent].size(); ++i) {
			int childnode = child[parent][i];
			//���Ӱ� ���������� 0�� �� ������ ť�� ����
			if (--inDegree[childnode] == 0)
				q.push(childnode);
		}
	}
	//���� ���� ��� ���
	for (int i = 1; i <= n; ++i)
		cout << result[i] << " ";
	return;
}
int main() {
	//������ ��
	n = 7;
	//���� �߰�
	//child[parent].push_back(child);
	//inDegree[child]++;
	child[1].push_back(2);
	inDegree[2]++;
	child[1].push_back(5);
	inDegree[5]++;
	child[2].push_back(3);
	inDegree[3]++;
	child[3].push_back(4);
	inDegree[4]++;
	child[4].push_back(6);
	inDegree[6]++;
	child[5].push_back(6);
	inDegree[6]++;
	child[6].push_back(7);
	inDegree[7]++;
	topologySort();
	return 0;
}