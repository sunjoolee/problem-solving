#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

int n;
vector<ll> vec;

const int ROOT = 1;

//이진 트리 구조
//루트 노드 번호: 1 (ROOT)
//오른쪽 자식 노드 번호: 부모 노드 * 2
//왼쪽 자식 노드 번호: (부모 노드 * 2) + 1
vector<ll> segmentTree;

//curNode: curStart ~ curEnd 구간합을 저장하는 노드 번호 
ll buildRecursive(int curNode, int curStart, int curEnd) {
	//리프 노드
	if (curStart == curEnd) {
		 return segmentTree[curNode] = vec[curStart];
	}

	int mid = (curStart + curEnd) / 2;
	ll rightChildNode = buildRecursive(curNode * 2, curStart, mid);
	ll leftChildNode =buildRecursive((curNode * 2) + 1, mid + 1, curEnd);
	return segmentTree[curNode] = leftChildNode + rightChildNode;
}


ll queryRecursive(int curNode, int curStart, int curEnd, int qStart, int qEnd) {
	//쿼리 구간에 포함되지 않음
	if (curEnd < qStart || qEnd < curStart) return 0LL;
	
	//쿼리 구간에 완전히 포함됨
	if (qStart <= curStart && curEnd <= qEnd) return segmentTree[curNode];

	//쿼리 구간에 부분적으로 포함됨
	int mid = (curStart + curEnd) / 2;
	ll rightQuery = queryRecursive(curNode * 2, curStart, mid, qStart, qEnd);
	ll leftQuery = queryRecursive((curNode * 2) + 1, mid + 1, curEnd, qStart, qEnd);
	return rightQuery + leftQuery;
}

ll updateRecursive(int updateNode, ll updateVal, int curNode, int curStart, int curEnd) {
	//리프노드 
	if (curStart == curEnd) {
		//업데이트 할 노드인 경우 값 업데이트
		if (curStart == updateNode)
			segmentTree[curNode] = updateVal;

		return segmentTree[curNode];
	}

	//업데이트 할 노드가 포함되지 않음 -> 구간합 그대로
	if (curEnd < updateNode || updateNode < curStart) {
		return segmentTree[curNode];
	}

	//업데이트 할 노드가 포함됨 -> 구간합 업데이트
	int mid = (curStart + curEnd) / 2;
	ll rightUpdate = updateRecursive(updateNode, updateVal, curNode * 2, curStart, mid);
	ll leftUpdate = updateRecursive(updateNode, updateVal, (curNode * 2) + 1, mid + 1, curEnd);
	return segmentTree[curNode] = rightUpdate + leftUpdate;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//m: 업데이트 수
	//k: 쿼리 수
	int m, k;

	cin >> n >> m >> k;

	for (int i = 0; i < n; ++i) {
		ll input;
		cin >> input;
		vec.push_back(input);
	}

	//세그먼트 트리 생성
	segmentTree.resize(n * 4);
	buildRecursive(ROOT, 0, n-1);

	for (int i = 0; i < (m + k); ++i) {
		int a;
		cin >> a;
		//업데이트
		if (a == 1) {
			int updateNode; ll updateVal;
			cin >> updateNode >> updateVal;

			updateRecursive(updateNode-1, updateVal, ROOT, 0, n - 1);
		}
		//쿼리
		else {
			int qStart, qEnd;
			cin >> qStart >> qEnd;

			cout << queryRecursive(ROOT, 0, n - 1, qStart-1, qEnd-1)<<"\n";
		}
	}

	return 0;
}