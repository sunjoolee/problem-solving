#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

int n;
vector<ll> vec;

const int ROOT = 1;

//���� Ʈ�� ����
//��Ʈ ��� ��ȣ: 1 (ROOT)
//������ �ڽ� ��� ��ȣ: �θ� ��� * 2
//���� �ڽ� ��� ��ȣ: (�θ� ��� * 2) + 1
vector<ll> segmentTree;

//curNode: curStart ~ curEnd �������� �����ϴ� ��� ��ȣ 
ll buildRecursive(int curNode, int curStart, int curEnd) {
	//���� ���
	if (curStart == curEnd) {
		 return segmentTree[curNode] = vec[curStart];
	}

	int mid = (curStart + curEnd) / 2;
	ll rightChildNode = buildRecursive(curNode * 2, curStart, mid);
	ll leftChildNode =buildRecursive((curNode * 2) + 1, mid + 1, curEnd);
	return segmentTree[curNode] = leftChildNode + rightChildNode;
}


ll queryRecursive(int curNode, int curStart, int curEnd, int qStart, int qEnd) {
	//���� ������ ���Ե��� ����
	if (curEnd < qStart || qEnd < curStart) return 0LL;
	
	//���� ������ ������ ���Ե�
	if (qStart <= curStart && curEnd <= qEnd) return segmentTree[curNode];

	//���� ������ �κ������� ���Ե�
	int mid = (curStart + curEnd) / 2;
	ll rightQuery = queryRecursive(curNode * 2, curStart, mid, qStart, qEnd);
	ll leftQuery = queryRecursive((curNode * 2) + 1, mid + 1, curEnd, qStart, qEnd);
	return rightQuery + leftQuery;
}

ll updateRecursive(int updateNode, ll updateVal, int curNode, int curStart, int curEnd) {
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
	ll rightUpdate = updateRecursive(updateNode, updateVal, curNode * 2, curStart, mid);
	ll leftUpdate = updateRecursive(updateNode, updateVal, (curNode * 2) + 1, mid + 1, curEnd);
	return segmentTree[curNode] = rightUpdate + leftUpdate;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//m: ������Ʈ ��
	//k: ���� ��
	int m, k;

	cin >> n >> m >> k;

	for (int i = 0; i < n; ++i) {
		ll input;
		cin >> input;
		vec.push_back(input);
	}

	//���׸�Ʈ Ʈ�� ����
	segmentTree.resize(n * 4);
	buildRecursive(ROOT, 0, n-1);

	for (int i = 0; i < (m + k); ++i) {
		int a;
		cin >> a;
		//������Ʈ
		if (a == 1) {
			int updateNode; ll updateVal;
			cin >> updateNode >> updateVal;

			updateRecursive(updateNode-1, updateVal, ROOT, 0, n - 1);
		}
		//����
		else {
			int qStart, qEnd;
			cin >> qStart >> qEnd;

			cout << queryRecursive(ROOT, 0, n - 1, qStart-1, qEnd-1)<<"\n";
		}
	}

	return 0;
}