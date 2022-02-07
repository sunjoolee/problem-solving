#include <iostream>
#include <vector>
#include <cstring>
#include <limits.h>
#include <algorithm>
using namespace std;

const int MAX_VAL = 2000000000;

int N;
vector<int> arr;

struct treeNode {
	int maxVal;
};

struct SegmentTree {
	vector<treeNode> tree;

	treeNode merge(treeNode left, treeNode right) {
		treeNode mergeNode;
		mergeNode.maxVal = max(left.maxVal, right.maxVal);
		return mergeNode;
	}

	treeNode buildRecursive(int node, int nodeLeft, int nodeRight) {
		if (nodeLeft == nodeRight) {
			treeNode mergeNode;
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


int solution(vector<int> stones, int k) {

	arr = stones;
	N = stones.size();

	SegmentTree segmentTree;
	segmentTree.build();

	int answer = 0;

	int minVal = MAX_VAL;
	for (int i = 0; i <= stones.size() - k; ++i) {		
		treeNode res = segmentTree.query(i, i + k-1);
		minVal = min(minVal, res.maxVal);
	}
	answer = minVal;

	return answer;
}


