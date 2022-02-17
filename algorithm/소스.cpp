#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

typedef long long ull;

const int INF = 987654321;

//N: 보석 진열대의 길이
int N;

//보석 진열대
vector<string> arr;

//보석 숫자 매핑
map<string, int> gemToInt;

struct SegmentTree {
	vector<ull> tree;

	//보석 진열대 구간 내 보석의 종류
	ull merge(ull left, ull right) {
		return left | right;
	}

	//---------------------------------------

	//node: Segment Tree의 노드의 번호
	//nodeLeft ~ nodeRight: 해당 노드가 저장하고 있는 구간

	ull buildRecursive(int node, int nodeLeft, int nodeRight) {

		//리프노드에 도달한 경우
		if (nodeLeft == nodeRight) {
			return tree[node] = (0LL | (1 << gemToInt[arr[nodeLeft]]));
		}

		//리프노드가 아닌 경우 구간 반으로 나누어 Recursive call
		//노드의 구간의 오른쪽 반: 노드의 오른쪽 자식이 저장
		//노드의 구간의 왼쪽 반: 노드의 왼쪽 자식이 저장

		int mid = (nodeLeft + nodeRight) / 2;
		ull leftVal = buildRecursive(node * 2, nodeLeft, mid);
		ull rightVal = buildRecursive(node * 2 + 1, mid + 1, nodeRight);

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

	ull queryRecursive(int left, int right, int node, int nodeLeft, int nodeRight) {

		//쿼리의 구간에 포함되지 않는 구간인 경우 default 값 반환 
		//default 값은 merge 연산에 따라 다르다
		if (right < nodeLeft || nodeRight < left) {
			return 0LL;
		}

		//쿼리의 구간에 포함되는 구간인 경우
		if (left <= nodeLeft && nodeRight <= right)
			return tree[node];

		//쿼리의 구간에 부분적으로 포함되는 구간인 경우
		//구간 반으로 나누어 Recursive call
		int mid = (nodeLeft + nodeRight) / 2;
		ull leftVal = queryRecursive(left, right, node * 2, nodeLeft, mid);
		ull rightVal = queryRecursive(left, right, node * 2 + 1, mid + 1, nodeRight);

		return merge(leftVal, rightVal);
	}

	ull query(int left, int right) {
		// 루트 노드부터 제귀적으로 쿼리 구간의 합 계산
		return queryRecursive(left, right, 1, 0, N - 1);
	}

};

vector<int> solution(vector<string> gems) {
	vector<int> answer;

	//전역 변수 초기화
	N = gems.size();
	arr = gems;

	//보석 종류 숫자 매핑
	int gemId = 0;
	for (int i = 0; i < gems.size(); ++i) {
		if (gemToInt.find(gems[i]) == gemToInt.end()) {
			gemToInt[gems[i]] = gemId;
			gemId++;
		}
	}
	//총 보석의 개수
	int totalGems = gemId;

	//구간 별 포함된 보석의 종류를 비트마스크로 저장한 세그먼트 트리
	SegmentTree segmentTree;
	segmentTree.build();

	
	//가능한 진열대 구간의 길이 이분 탐색
	int lo = 0, hi = gems.size() + 1;

	int minLen = INF;
	int minStart = INF;

	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;

		bool flag = false;
		for (int start = 0; start + mid - 1 < gems.size(); ++start) {

			ull bitmask = segmentTree.query(start, start + mid - 1);

			if ( bitmask == ((1LL << totalGems) - 1)) {
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

int main() {

	vector<string> in;

	for (int i = 0; i < 5; ++i) {
		string s;
		cin >> s;
		in.push_back(s);
	}

	solution(in);
}