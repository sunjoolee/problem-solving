#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

vector<ll> vec;

const int ROOT = 1;
vector<ll> segmentTree;

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
	return rightQuery+leftQuery;
}

ll updateRecursive(int updateNode, ll updateVal, int curNode, int curStart, int curEnd) {
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
	ll rightUpdate = updateRecursive(updateNode, updateVal, curNode * 2, curStart, mid);
	ll leftUpdate = updateRecursive(updateNode, updateVal, (curNode * 2) + 1, mid + 1, curEnd);
	return segmentTree[curNode] = rightUpdate + leftUpdate;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	int n;
	cin >> n;

	vector<ll> A;
	A.push_back(0);
	vec.push_back(0);
	for (int i = 1; i <= n; ++i) {
		ll input;
		cin >> input;
		A.push_back(input);

		vec.push_back(A[i] - A[i - 1]);
	}
	A.push_back(0);
	vec.push_back(0 - A[n]);

	segmentTree.resize(n * 4);
	buildRecursive(ROOT, 1, n);

	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		int qType;
		cin >> qType;
		if (qType == 1) {
			int i, j; ll k;
			cin >> i >> j >> k;

			updateRecursive(i, k, ROOT, 1, n); 
			updateRecursive(j + 1, -k, ROOT, 1, n);
		}
		else {
			int x;
			cin >> x;
			cout << queryRecursive(ROOT, 1, n, 1, x)<<"\n";
		}
	}

	return 0;
}