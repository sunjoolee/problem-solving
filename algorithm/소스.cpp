#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

const int VEC_SIZE = 1000001;

vector<int> vec (VEC_SIZE, 0);

const int ROOT = 1;

//이진 트리 구조
//루트 노드 번호: 1 (ROOT)
//오른쪽 자식 노드 번호: 부모 노드 * 2
//왼쪽 자식 노드 번호: (부모 노드 * 2) + 1
vector<int> segmentTree;

//curNode: curStart ~ curEnd 구간합을 저장하는 노드 번호 
int buildRecursive(int curNode, int curStart, int curEnd) {
	//리프 노드
	if (curStart == curEnd) {
		 return segmentTree[curNode] = vec[curStart];
	}

	int mid = (curStart + curEnd) / 2;
	int rightChildNode = buildRecursive(curNode * 2, curStart, mid);
	int leftChildNode =buildRecursive((curNode * 2) + 1, mid + 1, curEnd);
	return segmentTree[curNode] = leftChildNode + rightChildNode;
}


int queryRecursive(int curNode, int curStart, int curEnd, int qStart, int qEnd) {
	//쿼리 구간에 포함되지 않음
	if (curEnd < qStart || qEnd < curStart) return 0LL;
	
	//쿼리 구간에 완전히 포함됨
	if (qStart <= curStart && curEnd <= qEnd) return segmentTree[curNode];

	//쿼리 구간에 부분적으로 포함됨
	int mid = (curStart + curEnd) / 2;
	int rightQuery = queryRecursive(curNode * 2, curStart, mid, qStart, qEnd);
	int leftQuery = queryRecursive((curNode * 2) + 1, mid + 1, curEnd, qStart, qEnd);
	return rightQuery + leftQuery;
}

int updateRecursive(int updateNode, int updateVal, int curNode, int curStart, int curEnd) {
	//리프노드 
	if (curStart == curEnd) {
		//업데이트 할 노드인 경우 값 업데이트
		if (curStart == updateNode)
			segmentTree[curNode] += updateVal;

		return segmentTree[curNode];
	}

	//업데이트 할 노드가 포함되지 않음 -> 구간합 그대로
	if (curEnd < updateNode || updateNode < curStart) {
		return segmentTree[curNode];
	}

	//업데이트 할 노드가 포함됨 -> 구간합 업데이트
	int mid = (curStart + curEnd) / 2;
	int rightUpdate = updateRecursive(updateNode, updateVal, curNode * 2, curStart, mid);
	int leftUpdate = updateRecursive(updateNode, updateVal, (curNode * 2) + 1, mid + 1, curEnd);
	return segmentTree[curNode] = rightUpdate + leftUpdate;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	segmentTree.resize(VEC_SIZE * 4);
	buildRecursive(ROOT, 1, VEC_SIZE - 1);

	int n;
	cin >> n;
	while (n--) {
		int A, B, C;
		cin >> A;
		if (A == 1) {
			cin >> B;
			//순위가 B인 사탕 꺼내기
			int high = VEC_SIZE - 1;
			int low = 1;
			//같은 원소들 중 가장 왼쪽에 있는 원소에 최종적으로 접근하도록 이분탐색
			while (low  < high) {
				int mid = (high + low) / 2;
				if (queryRecursive(ROOT, 1, VEC_SIZE - 1, 1, mid) < B) low = mid + 1;
				else high = mid;
			}
			cout << high << "\n";
			updateRecursive(high, -1, ROOT, 1, VEC_SIZE - 1);
		}
		else {
			cin >> B >> C;
			//맛이 B인 사탕 C개 넣기/빼기
			updateRecursive(B, C, ROOT, 1, VEC_SIZE - 1);
		}
	}

	return 0;
}