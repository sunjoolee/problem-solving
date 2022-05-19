#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 1001;

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
		if (q.empty()) {
			cout << "0";
			return;
		}

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
	for (int i = 1; i <= n; ++i) {
		cout << result[i] << " ";
	}
	return;
}


int main() {
	//������ ��
	cin >> n;
	
	//���� ���� �Է¹ޱ�
	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		int len;
		cin >> len;

		vector<int> seq;
		for(int j = 0; j< len; ++j){
			int input;
			cin >> input;
			seq.push_back(input);
		}

		//seq = {1, 4, 3}
		//child[1] = {4, 3}
		//child[4] = {3}
		for (int j = 0; j < len - 1; ++j) {
			int parent = seq[j];
			for (int k = j + 1; k < len; ++k) {
				child[parent].push_back(seq[k]);
				inDegree[seq[k]]++;
			}
		}
	}

	topologySort();
	return 0;
}