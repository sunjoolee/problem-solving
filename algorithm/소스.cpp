#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

//N: ������ ����
//K: ���� ��
int N, K;
//arr�� ���� 1, 0, -1 �� �ϳ��� ���´�
vector<int> arr;

struct SegmentTree {
	vector<int> tree;

	//������ �� ���
	int merge(int left, int right) {
		return left * right;
	}

	//---------------------------------------

	//node: Segment Tree�� ����� ��ȣ
	//nodeLeft ~ nodeRight: �ش� ��尡 �����ϰ� �ִ� ����
	int buildRecursive(int node, int nodeLeft, int nodeRight) {
		//������忡 ������ ���
		if (nodeLeft == nodeRight)
			return tree[node] = arr[nodeLeft];
		
		//������尡 �ƴ� ��� ���� ������ ������ Recursive call
		//����� ������ ������ ��: ����� ������ �ڽ��� ����
		//����� ������ ���� ��: ����� ���� �ڽ��� ����
		int mid = (nodeLeft + nodeRight) / 2;
		int leftVal = buildRecursive(node * 2, nodeLeft, mid);
		int rightVal = buildRecursive(node * 2 + 1, mid + 1, nodeRight);

		return tree[node] = merge(leftVal, rightVal);
	}

	void build() {
		tree.resize(N * 4);
		//��Ʈ ������ ���������� ����
		buildRecursive(1, 0, N - 1);
	}

	//---------------------------------------

	//index: newVal ������ ������Ʈ�� ����� ��ȣ
	//node: Segment Tree�� ����� ��ȣ
	//nodeLeft ~ nodeRight: �ش� ��尡 �����ϰ� �ִ� ����
	int updateRecursive(int index, int newVal, int node, int nodeLeft, int nodeRight) {
		//������Ʈ�� ��尡 ���Ե��� ���� ������ ���
		if (index < nodeLeft || nodeRight < index)
			return tree[node];

		//������Ʈ�� ��忡 ������ ��� = ������忡 ������ ���
		if (nodeLeft == nodeRight)
			return tree[node] = newVal;

		//������Ʈ�� ��尡 ���Ե� ���������� ������忡 �������� ���� ���
		//���� ������ ������ Recursive call
		int mid = (nodeLeft + nodeRight) / 2;
		int leftVal = updateRecursive(index, newVal, node * 2, nodeLeft, mid);
		int rightVal = updateRecursive(index, newVal, node * 2 + 1, mid + 1, nodeRight);

		return tree[node] = merge(leftVal, rightVal);
	}

	void update(int index, int newVal) {
		//��Ʈ ������ ���������� ������Ʈ
		updateRecursive(index, newVal, 1, 0, N-1);
	}


	//---------------------------------------

	//left ~ right: ���� ����ϰ����ϴ� ������ ����
	//node: Segment Tree�� ����� ��ȣ
	//nodeLeft ~ nodeRight: �ش� ��尡 �����ϰ� �ִ� ����
	int queryRecursive(int left, int right, int node, int nodeLeft, int nodeRight) {
		//������ ������ ���Ե��� �ʴ� ������ ��� default �� ��ȯ 
		//default ���� merge ���꿡 ���� �ٸ���
		if (right < nodeLeft || nodeRight < left)
			return 1;

		//������ ������ ���ԵǴ� ������ ���
		if (left <= nodeLeft && nodeRight <= right) 
			return tree[node];
		
		//������ ������ �κ������� ���ԵǴ� ������ ���
		//���� ������ ������ Recursive call
		int mid = (nodeLeft + nodeRight) / 2;
		int leftVal = queryRecursive(left, right, node * 2, nodeLeft, mid);
		int rightVal = queryRecursive(left, right, node * 2 + 1, mid + 1, nodeRight);

		return merge(leftVal, rightVal);
	}

	int query(int left, int right) {
		// ��Ʈ ������ ���������� ���� ������ �� ���
		return queryRecursive(left, right, 1, 0, N - 1);
	}

};


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while (true) {
		arr.clear();

		cin >> N >> K;
		if (cin.eof()) break;

		for (int i = 0; i < N; ++i) {
			int input;
			cin >> input;

			if (input > 0) arr.push_back(1);
			else if (input == 0) arr.push_back(0);
			else if (input < 0) arr.push_back(-1);
		}

		SegmentTree segmentTree;
		segmentTree.build();

		while (K--) {
			char operation;
			cin >> operation;

			//����
			if (operation == 'C') {
				int index, input;
				cin >> index >> input;

				if (input > 0) segmentTree.update(index - 1, 1);
				else if (input == 0) segmentTree.update(index - 1, 0);
				else if (input < 0) segmentTree.update(index - 1, -1);
			}

			//����
			else if (operation == 'P') {
				int left, right;
				cin >> left >> right;

				int q = segmentTree.query(left - 1, right - 1);

				if (q > 0) cout << "+ ";
				else if (q == 0) cout << "0 ";
				else if (q < 0) cout << "- ";
			}
		}
		cout << "\n";
	}

	return 0;
}