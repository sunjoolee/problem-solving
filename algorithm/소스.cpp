#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

//N: ���� ����
//M: ���� ���� Ƚ��
//K: ������ �� ���ϴ� Ƚ��
int N, M, K;
vector<ll> arr;

struct SegmentTree {
	vector<ll> tree;

	//������ �� ���
	ll merge(ll left, ll right) {
		return left + right;
	}

	//---------------------------------------

	//node: Segment Tree�� ����� ��ȣ
	//nodeLeft ~ nodeRight: �ش� ��尡 �����ϰ� �ִ� ����
	ll buildRecursive(int node, int nodeLeft, int nodeRight) {
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
	ll updateRecursive(int index, ll newVal, int node, int nodeLeft, int nodeRight) {
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

	void update(int index, ll newVal) {
		//��Ʈ ������ ���������� ������Ʈ
		updateRecursive(index, newVal, 1, 0, N-1);
	}


	//---------------------------------------

	//left ~ right: ���� ����ϰ����ϴ� ������ ����
	//node: Segment Tree�� ����� ��ȣ
	//nodeLeft ~ nodeRight: �ش� ��尡 �����ϰ� �ִ� ����
	ll queryRecursive(int left, int right, int node, int nodeLeft, int nodeRight) {
		//������ ������ ���Ե��� �ʴ� ������ ��� default �� ��ȯ 
		//default ���� merge ���꿡 ���� �ٸ���
		if (right < nodeLeft || nodeRight < left)
			return 0LL;

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

	ll query(int left, int right) {
		// ��Ʈ ������ ���������� ���� ������ �� ���
		return queryRecursive(left, right, 1, 0, N - 1);
	}

};


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> K;

	for (int i = 0; i < N; ++i) {
		ll input;
		cin >> input;
		arr.push_back(input);
	}

	SegmentTree segmentTree;
	segmentTree.build();

	for (int i = 0; i < M + K; ++i) {
		int operation;
		cin >> operation;
		if (operation == 1) {
			int index; ll newVal;
			cin >> index >> newVal;

			segmentTree.update(index-1, newVal);
		}
		else if (operation == 2) {
			int left, right;
			cin >> left >> right;
			cout << segmentTree.query(left-1, right-1) << "\n";
		}
	}

	return 0;
}