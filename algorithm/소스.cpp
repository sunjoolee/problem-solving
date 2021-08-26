#include <iostream>
#include <vector>
#include <cstring>
#include <limits.h>
#include <algorithm>
using namespace std;


int N, M;
vector<int> arr;

struct treeNode {
	int minVal;
	int maxVal;
};

struct SegmentTree {
	vector<treeNode> tree;

	treeNode merge(treeNode left, treeNode right) {
		treeNode mergeNode;
		mergeNode.minVal = min(left.minVal, right.minVal);
		mergeNode.maxVal = max(left.maxVal, right.maxVal);
		return mergeNode;
	}

	treeNode buildRecursive(int node, int nodeLeft, int nodeRight) {
		if (nodeLeft == nodeRight) {
			treeNode mergeNode;
			mergeNode.minVal = arr[nodeLeft];
			mergeNode.maxVal = arr[nodeLeft];
			
			return tree[node] = mergeNode;
		}

		int mid = (nodeLeft + nodeRight) / 2;
		treeNode leftNode = buildRecursive(node * 2, nodeLeft, mid);
		treeNode rightNode = buildRecursive(node * 2 + 1, mid + 1, nodeRight);

		return tree[node] = merge(leftNode, rightNode);
	}

	void build() {
		tree.resize(N * 4);
		buildRecursive(1, 0, N - 1);
	}

	treeNode queryRecursive(int left, int right, int node, int nodeLeft, int nodeRight) {
		//쿼리의 구간에 포함되지 않는 구간인 경우 default 값 반환 
		//default 값은 merge 연산에 따라 다르다
		if (right < nodeLeft || nodeRight < left) {
			treeNode defaultNode;
			defaultNode.minVal = INT_MAX;
			defaultNode.maxVal = 0;

			return defaultNode;
		}

		if (left <= nodeLeft && nodeRight <= right)
			return tree[node];

		int mid = (nodeLeft + nodeRight) / 2;
		treeNode leftNode = queryRecursive(left, right, node * 2, nodeLeft, mid);
		treeNode rightNode = queryRecursive(left, right, node * 2 + 1, mid + 1, nodeRight);

		return merge(leftNode, rightNode);
	}

	treeNode query(int left, int right) {
		return queryRecursive(left, right, 1, 0, N - 1);
	}

};


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < N; ++i) {
		int input;
		cin >> input;
		arr.push_back(input);
	}

	SegmentTree segmentTree;
	segmentTree.build();

	for (int i = 0; i < M; ++i) {
		int a, b;
		cin >> a >> b;

		treeNode res = segmentTree.query(a-1, b-1);
		cout << res.minVal << " " << res.maxVal << "\n";
	}

	return 0;
}