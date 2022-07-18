#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

const int VEC_SIZE = 1000001;

vector<int> vec (VEC_SIZE, 0);

const int ROOT = 1;

vector<int> segmentTree;

//curNode: curStart ~ curEnd 구간 최댓값을 저장하는 노드 번호 
int buildRecursive(int curNode, int curStart, int curEnd) {
	//리프 노드
	if (curStart == curEnd) {
		 return segmentTree[curNode] = vec[curStart];
	}

	int mid = (curStart + curEnd) / 2;
	int rightChildNode = buildRecursive(curNode * 2, curStart, mid);
	int leftChildNode =buildRecursive((curNode * 2) + 1, mid + 1, curEnd);
	return segmentTree[curNode] = max(leftChildNode,rightChildNode);
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
	return max(rightQuery,leftQuery);
}

int updateRecursive(int updateNode, int updateVal, int curNode, int curStart, int curEnd) {
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
	int rightUpdate = updateRecursive(updateNode, updateVal, curNode * 2, curStart, mid);
	int leftUpdate = updateRecursive(updateNode, updateVal, (curNode * 2) + 1, mid + 1, curEnd);
	return segmentTree[curNode] = max(rightUpdate, leftUpdate);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	int n;
	cin >> n;
	vector<int> A;

	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		A.push_back(input);
	}

	//LIS 계산
	//LIS[i]: A[i]부터 시작하는 LIS의 최대 길이
	vector<int> LIS(n, 0);

	//vec[n]: 숫자 n으로 끝나는 LIS의 최대 길이
	//n1 ~ n2 구간에 해당하는 segmentTree 값: vec[n1] ~ vec[n2] 중 최댓값 저장 
	segmentTree.resize(VEC_SIZE * 4);
	buildRecursive(ROOT, 0, VEC_SIZE - 1);

	for (int i = 0; i < n; ++i) {
		LIS[i] = queryRecursive(ROOT, 0, VEC_SIZE - 1, 0, A[i] - 1) + 1;
		updateRecursive(A[i], LIS[i], ROOT, 0, VEC_SIZE - 1);
	}

	cout << segmentTree[ROOT];
	return 0;
}