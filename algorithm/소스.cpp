#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

//N: 정수의 개수
//K: 라운드 수
int N, K;
//arr의 값은 1, 0, -1 중 하나를 갖는다
vector<int> arr;

struct SegmentTree {
	vector<int> tree;

	//구간의 곱 계산
	int merge(int left, int right) {
		return left * right;
	}

	//---------------------------------------

	//node: Segment Tree의 노드의 번호
	//nodeLeft ~ nodeRight: 해당 노드가 저장하고 있는 구간
	int buildRecursive(int node, int nodeLeft, int nodeRight) {
		//리프노드에 도달한 경우
		if (nodeLeft == nodeRight)
			return tree[node] = arr[nodeLeft];
		
		//리프노드가 아닌 경우 구간 반으로 나누어 Recursive call
		//노드의 구간의 오른쪽 반: 노드의 오른쪽 자식이 저장
		//노드의 구간의 왼쪽 반: 노드의 왼쪽 자식이 저장
		int mid = (nodeLeft + nodeRight) / 2;
		int leftVal = buildRecursive(node * 2, nodeLeft, mid);
		int rightVal = buildRecursive(node * 2 + 1, mid + 1, nodeRight);

		return tree[node] = merge(leftVal, rightVal);
	}

	void build() {
		tree.resize(N * 4);
		//루트 노드부터 제귀적으로 빌드
		buildRecursive(1, 0, N - 1);
	}

	//---------------------------------------

	//index: newVal 값으로 업데이트할 노드의 번호
	//node: Segment Tree의 노드의 번호
	//nodeLeft ~ nodeRight: 해당 노드가 저장하고 있는 구간
	int updateRecursive(int index, int newVal, int node, int nodeLeft, int nodeRight) {
		//업데이트할 노드가 포함되지 않은 구간인 경우
		if (index < nodeLeft || nodeRight < index)
			return tree[node];

		//업데이트할 노드에 도달한 경우 = 리프노드에 도달한 경우
		if (nodeLeft == nodeRight)
			return tree[node] = newVal;

		//업데이트할 노드가 포함된 범위이지만 리프노드에 도달하지 못한 경우
		//구간 반으로 나누어 Recursive call
		int mid = (nodeLeft + nodeRight) / 2;
		int leftVal = updateRecursive(index, newVal, node * 2, nodeLeft, mid);
		int rightVal = updateRecursive(index, newVal, node * 2 + 1, mid + 1, nodeRight);

		return tree[node] = merge(leftVal, rightVal);
	}

	void update(int index, int newVal) {
		//루트 노드부터 제귀적으로 업데이트
		updateRecursive(index, newVal, 1, 0, N-1);
	}


	//---------------------------------------

	//left ~ right: 곱을 계산하고자하는 쿼리의 구간
	//node: Segment Tree의 노드의 번호
	//nodeLeft ~ nodeRight: 해당 노드가 저장하고 있는 구간
	int queryRecursive(int left, int right, int node, int nodeLeft, int nodeRight) {
		//쿼리의 구간에 포함되지 않는 구간인 경우 default 값 반환 
		//default 값은 merge 연산에 따라 다르다
		if (right < nodeLeft || nodeRight < left)
			return 1;

		//쿼리의 구간에 포함되는 구간인 경우
		if (left <= nodeLeft && nodeRight <= right) 
			return tree[node];
		
		//쿼리의 구간에 부분적으로 포함되는 구간인 경우
		//구간 반으로 나누어 Recursive call
		int mid = (nodeLeft + nodeRight) / 2;
		int leftVal = queryRecursive(left, right, node * 2, nodeLeft, mid);
		int rightVal = queryRecursive(left, right, node * 2 + 1, mid + 1, nodeRight);

		return merge(leftVal, rightVal);
	}

	int query(int left, int right) {
		// 루트 노드부터 제귀적으로 쿼리 구간의 합 계산
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

			//변경
			if (operation == 'C') {
				int index, input;
				cin >> index >> input;

				if (input > 0) segmentTree.update(index - 1, 1);
				else if (input == 0) segmentTree.update(index - 1, 0);
				else if (input < 0) segmentTree.update(index - 1, -1);
			}

			//곱셈
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