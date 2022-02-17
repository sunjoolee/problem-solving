#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

typedef long long ll;
const int INF = 987654321;

//N: 보석 진열대의 길이
int N;

//보석 진열대
vector<string> arr;

struct SegmentTree {
	vector<set<string>> tree;

	//보석 진열대 구간 내 보석의 종류
	set <string> merge(set<string> left, set<string> right) {
		set <string> result;

		result.insert(left.begin(), left.end());
		result.insert(right.begin(), right.end());

		return result;
	}

	//---------------------------------------

	//node: Segment Tree의 노드의 번호
	//nodeLeft ~ nodeRight: 해당 노드가 저장하고 있는 구간

	set<string> buildRecursive(int node, int nodeLeft, int nodeRight) {

		//리프노드에 도달한 경우
		if (nodeLeft == nodeRight) {
			set<string> leaf;
			leaf.insert(arr[nodeLeft]);
			return tree[node] = leaf;
		}

		//리프노드가 아닌 경우 구간 반으로 나누어 Recursive call
		//노드의 구간의 오른쪽 반: 노드의 오른쪽 자식이 저장
		//노드의 구간의 왼쪽 반: 노드의 왼쪽 자식이 저장

		int mid = (nodeLeft + nodeRight) / 2;
		set<string> leftVal = buildRecursive(node * 2, nodeLeft, mid);
		set<string> rightVal = buildRecursive(node * 2 + 1, mid + 1, nodeRight);

		return tree[node] = merge(leftVal, rightVal);
	}

	void build() {
		tree.resize(N * 4);
		//루트 노드부터 제귀적으로 빌드
		buildRecursive(1, 0, N - 1);
	}

	//---------------------------------------

	//left ~ right: 쿼리의 구간
	//node: Segment Tree의 노드의 번호
	//nodeLeft ~ nodeRight: 해당 노드가 저장하고 있는 구간

	set<string> queryRecursive(int left, int right, int node, int nodeLeft, int nodeRight) {

		//쿼리의 구간에 포함되지 않는 구간인 경우 default 값 반환 
		//default 값은 merge 연산에 따라 다르다
		if (right < nodeLeft || nodeRight < left) {
			set<string> emptySet;
			return emptySet;
		}

		//쿼리의 구간에 포함되는 구간인 경우
		if (left <= nodeLeft && nodeRight <= right)
			return tree[node];

		//쿼리의 구간에 부분적으로 포함되는 구간인 경우
		//구간 반으로 나누어 Recursive call
		int mid = (nodeLeft + nodeRight) / 2;
		set<string> leftVal = queryRecursive(left, right, node * 2, nodeLeft, mid);
		set<string> rightVal = queryRecursive(left, right, node * 2 + 1, mid + 1, nodeRight);

		return merge(leftVal, rightVal);
	}

	set<string> query(int left, int right) {
		// 루트 노드부터 제귀적으로 쿼리 구간의 합 계산
		return queryRecursive(left, right, 1, 0, N - 1);
	}

};


vector<int> solution(vector<string> gems) {
	vector<int> answer;

	N = gems.size();
	arr = gems;

	SegmentTree segmentTree;
	segmentTree.build();

	//총 보석의 개수 = 전체 구간의 쿼리 값 set<string> 의 크기
	int totalGems = segmentTree.query(0, gems.size() - 1).size();

	//가능한 진열대 구간의 길이 이분 탐색
	int lo = 0, hi = gems.size() + 1;

	int minLen = INF;
	int minStart = INF;

	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;

		bool flag = false;
		for (int start = 0; start + mid - 1 < gems.size(); ++start) {
			if (segmentTree.query(start, start + mid - 1).size() == totalGems) {
				flag = true;

				if (minLen >= mid) {
					minLen = mid;
					minStart = start;
					break;
				}
			}
		}

		if (flag) hi = mid;
		else lo = mid;
	}

	answer.push_back(minStart + 1);
	answer.push_back(minStart + minLen);

	return answer;
}


