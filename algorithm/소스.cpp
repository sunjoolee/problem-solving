#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

vector<int> vec;

const int ROOT = 1;
vector<pair<int, int>> segmentTree;

//curNode: curStart ~ curEnd ���� <�ִ�, �ּڰ�>�� �����ϴ� ��� ��ȣ 
pair<int, int> buildRecursive(int curNode, int curStart, int curEnd) {
	//���� ���
	if (curStart == curEnd) {
		return segmentTree[curNode] = { vec[curStart], vec[curStart] };
	}

	int mid = (curStart + curEnd) / 2;
	pair<int, int> rightChildNode = buildRecursive(curNode * 2, curStart, mid);
	pair<int, int> leftChildNode =buildRecursive((curNode * 2) + 1, mid + 1, curEnd);
	return segmentTree[curNode] = { max(leftChildNode.first,rightChildNode.first), min(leftChildNode.second,rightChildNode.second) };
}


pair<int, int> queryRecursive(int curNode, int curStart, int curEnd, int qStart, int qEnd) {
	//���� ������ ���Ե��� ����
	if (curEnd < qStart || qEnd < curStart) return { 0 , 987654321};
	
	//���� ������ ������ ���Ե�
	if (qStart <= curStart && curEnd <= qEnd) return segmentTree[curNode];

	//���� ������ �κ������� ���Ե�
	int mid = (curStart + curEnd) / 2;
	pair<int, int> rightQuery = queryRecursive(curNode * 2, curStart, mid, qStart, qEnd);
	pair<int, int> leftQuery = queryRecursive((curNode * 2) + 1, mid + 1, curEnd, qStart, qEnd);
	return { max(rightQuery.first,leftQuery.first), min(rightQuery.second,leftQuery.second) };
}

pair<int, int> updateRecursive(int updateNode, int updateVal, int curNode, int curStart, int curEnd) {
	//������� 
	if (curStart == curEnd) {
		//������Ʈ �� ����� ��� �� ������Ʈ
		if (curStart == updateNode)
			segmentTree[curNode] = { updateVal, updateVal };

		return segmentTree[curNode];
	}

	//������Ʈ �� ��尡 ���Ե��� ���� -> ������ �״��
	if (curEnd < updateNode || updateNode < curStart) {
		return segmentTree[curNode];
	}

	//������Ʈ �� ��尡 ���Ե� -> ������ ������Ʈ
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
			//DVD �ٲ㳦
			if (Q == 0) {
				int A, B;
				cin >> A >> B;
				updateRecursive(A, vec[B], ROOT, 0, n - 1);
				updateRecursive(B, vec[A], ROOT, 0, n - 1);
				swap(vec[A], vec[B]);
			}
			//DVD ������
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