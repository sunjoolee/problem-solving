#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

const int VEC_SIZE = 1000001;

vector<int> vec (VEC_SIZE, 0);

const int ROOT = 1;

vector<int> segmentTree;

//curNode: curStart ~ curEnd ���� �ִ��� �����ϴ� ��� ��ȣ 
int buildRecursive(int curNode, int curStart, int curEnd) {
	//���� ���
	if (curStart == curEnd) {
		 return segmentTree[curNode] = vec[curStart];
	}

	int mid = (curStart + curEnd) / 2;
	int rightChildNode = buildRecursive(curNode * 2, curStart, mid);
	int leftChildNode =buildRecursive((curNode * 2) + 1, mid + 1, curEnd);
	return segmentTree[curNode] = max(leftChildNode,rightChildNode);
}


int queryRecursive(int curNode, int curStart, int curEnd, int qStart, int qEnd) {
	//���� ������ ���Ե��� ����
	if (curEnd < qStart || qEnd < curStart) return 0LL;
	
	//���� ������ ������ ���Ե�
	if (qStart <= curStart && curEnd <= qEnd) return segmentTree[curNode];

	//���� ������ �κ������� ���Ե�
	int mid = (curStart + curEnd) / 2;
	int rightQuery = queryRecursive(curNode * 2, curStart, mid, qStart, qEnd);
	int leftQuery = queryRecursive((curNode * 2) + 1, mid + 1, curEnd, qStart, qEnd);
	return max(rightQuery,leftQuery);
}

int updateRecursive(int updateNode, int updateVal, int curNode, int curStart, int curEnd) {
	//������� 
	if (curStart == curEnd) {
		//������Ʈ �� ����� ��� �� ������Ʈ
		if (curStart == updateNode)
			segmentTree[curNode] = updateVal;

		return segmentTree[curNode];
	}

	//������Ʈ �� ��尡 ���Ե��� ���� -> ������ �״��
	if (curEnd < updateNode || updateNode < curStart) {
		return segmentTree[curNode];
	}

	//������Ʈ �� ��尡 ���Ե� -> ������ ������Ʈ
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

	//LIS ���
	//LIS[i]: A[i]���� �����ϴ� LIS�� �ִ� ����
	vector<int> LIS(n, 0);

	//vec[n]: ���� n���� ������ LIS�� �ִ� ����
	//n1 ~ n2 ������ �ش��ϴ� segmentTree ��: vec[n1] ~ vec[n2] �� �ִ� ���� 
	segmentTree.resize(VEC_SIZE * 4);
	buildRecursive(ROOT, 0, VEC_SIZE - 1);

	for (int i = 0; i < n; ++i) {
		LIS[i] = queryRecursive(ROOT, 0, VEC_SIZE - 1, 0, A[i] - 1) + 1;
		updateRecursive(A[i], LIS[i], ROOT, 0, VEC_SIZE - 1);
	}

	cout << segmentTree[ROOT];
	return 0;
}