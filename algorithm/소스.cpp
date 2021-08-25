#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

//N: 수의 개수
//Q: 턴의 수
int N, Q;
vector<ll> arr;

struct SegmentTree {
	vector<ll> tree;

	//구간의 합 계산
	ll merge(ll left, ll right) {
		return left + right;
	}

	ll buildRecursive(int node, int nodeLeft, int nodeRight) {
		if (nodeLeft == nodeRight)
			return tree[node] = arr[nodeLeft];

		int mid = (nodeLeft + nodeRight) / 2;
		ll leftVal = buildRecursive(node * 2, nodeLeft, mid);
		ll rightVal = buildRecursive(node * 2 + 1, mid + 1, nodeRight);

		return tree[node] = merge(leftVal, rightVal);
	}

	void build() {
		tree.resize(N * 4);
		buildRecursive(1, 0, N - 1);
	}

	ll updateRecursive(int index, ll newVal, int node, int nodeLeft, int nodeRight) {
		if (index < nodeLeft || nodeRight < index)
			return tree[node];

		if (nodeLeft == nodeRight)
			return tree[node] = newVal;

		int mid = (nodeLeft + nodeRight) / 2;
		ll leftVal = updateRecursive(index, newVal, node * 2, nodeLeft, mid);
		ll rightVal = updateRecursive(index, newVal, node * 2 + 1, mid + 1, nodeRight);

		return tree[node] = merge(leftVal, rightVal);
	}

	void update(int index, ll newVal) {
		updateRecursive(index, newVal, 1, 0, N - 1);
	}


	ll queryRecursive(int left, int right, int node, int nodeLeft, int nodeRight) {
		//쿼리의 구간에 포함되지 않는 구간인 경우 default 값 반환 
		//default 값은 merge 연산에 따라 다르다
		if (right < nodeLeft || nodeRight < left)
			return 0LL;

		//쿼리의 구간에 포함되는 구간인 경우
		if (left <= nodeLeft && nodeRight <= right)
			return tree[node];

		//쿼리의 구간에 부분적으로 포함되는 구간인 경우
		int mid = (nodeLeft + nodeRight) / 2;
		ll leftVal = queryRecursive(left, right, node * 2, nodeLeft, mid);
		ll rightVal = queryRecursive(left, right, node * 2 + 1, mid + 1, nodeRight);

		return merge(leftVal, rightVal);
	}

	ll query(int left, int right) {
		return queryRecursive(left, right, 1, 0, N - 1);
	}

};


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> Q;

	for (int i = 0; i < N; ++i) {
		ll input;
		cin >> input;
		arr.push_back(input);
	}

	SegmentTree segmentTree;
	segmentTree.build();

	for (int i = 0; i < Q; ++i) {
		int x, y;
		cin >> x >> y;
		
		if(x > y) cout << segmentTree.query(y - 1, x - 1) << "\n";
		else cout << segmentTree.query(x-1, y-1) << "\n";

		int a; ll b;
		cin >> a >> b;
		segmentTree.update(a-1, b);
	}

	return 0;
}