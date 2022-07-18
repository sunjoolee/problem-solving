#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

const int VEC_SIZE = 1000001;

vector<int> vec (VEC_SIZE, 0);

const int ROOT = 1;

//���� Ʈ�� ����
//��Ʈ ��� ��ȣ: 1 (ROOT)
//������ �ڽ� ��� ��ȣ: �θ� ��� * 2
//���� �ڽ� ��� ��ȣ: (�θ� ��� * 2) + 1
vector<int> segmentTree;

//curNode: curStart ~ curEnd �������� �����ϴ� ��� ��ȣ 
int buildRecursive(int curNode, int curStart, int curEnd) {
	//���� ���
	if (curStart == curEnd) {
		 return segmentTree[curNode] = vec[curStart];
	}

	int mid = (curStart + curEnd) / 2;
	int rightChildNode = buildRecursive(curNode * 2, curStart, mid);
	int leftChildNode =buildRecursive((curNode * 2) + 1, mid + 1, curEnd);
	return segmentTree[curNode] = leftChildNode + rightChildNode;
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
	return rightQuery + leftQuery;
}

int updateRecursive(int updateNode, int updateVal, int curNode, int curStart, int curEnd) {
	//������� 
	if (curStart == curEnd) {
		//������Ʈ �� ����� ��� �� ������Ʈ
		if (curStart == updateNode)
			segmentTree[curNode] += updateVal;

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
			//������ B�� ���� ������
			int high = VEC_SIZE - 1;
			int low = 1;
			//���� ���ҵ� �� ���� ���ʿ� �ִ� ���ҿ� ���������� �����ϵ��� �̺�Ž��
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
			//���� B�� ���� C�� �ֱ�/����
			updateRecursive(B, C, ROOT, 1, VEC_SIZE - 1);
		}
	}

	return 0;
}