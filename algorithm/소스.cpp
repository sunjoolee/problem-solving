#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

vector<int> vec;

const int ROOT = 1;
vector<pair<int, int>> segmentTree;

//curNode: curStart ~ curEnd 구간 <최댓값, 최솟값>을 저장하는 노드 번호 
pair<int, int> buildRecursive(int curNode, int curStart, int curEnd) {
	//리프 노드
	if (curStart == curEnd) {
		return segmentTree[curNode] = { vec[curStart], vec[curStart] };
	}

	int mid = (curStart + curEnd) / 2;
	pair<int, int> rightChildNode = buildRecursive(curNode * 2, curStart, mid);
	pair<int, int> leftChildNode =buildRecursive((curNode * 2) + 1, mid + 1, curEnd);
	return segmentTree[curNode] = { max(leftChildNode.first,rightChildNode.first), min(leftChildNode.second,rightChildNode.second) };
}


pair<int, int> queryRecursive(int curNode, int curStart, int curEnd, int qStart, int qEnd) {
	//쿼리 구간에 포함되지 않음
	if (curEnd < qStart || qEnd < curStart) return { 0 , 987654321};
	
	//쿼리 구간에 완전히 포함됨
	if (qStart <= curStart && curEnd <= qEnd) return segmentTree[curNode];

	//쿼리 구간에 부분적으로 포함됨
	int mid = (curStart + curEnd) / 2;
	pair<int, int> rightQuery = queryRecursive(curNode * 2, curStart, mid, qStart, qEnd);
	pair<int, int> leftQuery = queryRecursive((curNode * 2) + 1, mid + 1, curEnd, qStart, qEnd);
	return { max(rightQuery.first,leftQuery.first), min(rightQuery.second,leftQuery.second) };
}

pair<int, int> updateRecursive(int updateNode, int updateVal, int curNode, int curStart, int curEnd) {
	//리프노드 
	if (curStart == curEnd) {
		//업데이트 할 노드인 경우 값 업데이트
		if (curStart == updateNode)
			segmentTree[curNode] = { updateVal, updateVal };

		return segmentTree[curNode];
	}

	//업데이트 할 노드가 포함되지 않음 -> 구간합 그대로
	if (curEnd < updateNode || updateNode < curStart) {
		return segmentTree[curNode];
	}

	//업데이트 할 노드가 포함됨 -> 구간합 업데이트
	int mid = (curStart + curEnd) / 2;
	pair<int, int> rightUpdate = updateRecursive(updateNode, updateVal, curNode * 2, curStart, mid);
	pair<int, int> leftUpdate = updateRecursive(updateNode, updateVal, (curNode * 2) + 1, mid + 1, curEnd);
	return segmentTree[curNode] = { max(rightUpdate.first, leftUpdate.first), min(rightUpdate.second, leftUpdate.second) };
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	int T;
	cin >> T;
	while (T--) {
		vec.clear();
		segmentTree.clear();

		int n, k;
		cin >> n >> k;
		for (int i = 0; i < n; ++i) {
			vec.push_back(i);
		}

		segmentTree.resize(n * 4);
		buildRecursive(ROOT, 0, n - 1);

		for (int i = 0; i < k; ++i) {
			int Q;
			cin >> Q;
			//DVD 바꿔낌
			if (Q == 0) {
				int A, B;
				cin >> A >> B;
				updateRecursive(A, vec[B], ROOT, 0, n - 1);
				updateRecursive(B, vec[A], ROOT, 0, n - 1);
				swap(vec[A], vec[B]);
			}
			//DVD 가져옴
			else {
				int r, l;
				cin >> r >> l;
				pair<int, int> queryResult = queryRecursive(ROOT, 0, n - 1, r, l);
				if ((queryResult.first == l) && (queryResult.second == r))
					cout << "YES\n";
				else
					cout << "NO\n";
			}

		}
	}
	return 0;
}