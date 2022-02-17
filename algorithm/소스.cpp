#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

typedef long long ull;

const int INF = 987654321;

//N: ���� �������� ����
int N;

//���� ������
vector<string> arr;

//���� ���� ����
map<string, int> gemToInt;

struct SegmentTree {
	vector<ull> tree;

	//���� ������ ���� �� ������ ����
	ull merge(ull left, ull right) {
		return left | right;
	}

	//---------------------------------------

	//node: Segment Tree�� ����� ��ȣ
	//nodeLeft ~ nodeRight: �ش� ��尡 �����ϰ� �ִ� ����

	ull buildRecursive(int node, int nodeLeft, int nodeRight) {

		//������忡 ������ ���
		if (nodeLeft == nodeRight) {
			return tree[node] = (0LL | (1 << gemToInt[arr[nodeLeft]]));
		}

		//������尡 �ƴ� ��� ���� ������ ������ Recursive call
		//����� ������ ������ ��: ����� ������ �ڽ��� ����
		//����� ������ ���� ��: ����� ���� �ڽ��� ����

		int mid = (nodeLeft + nodeRight) / 2;
		ull leftVal = buildRecursive(node * 2, nodeLeft, mid);
		ull rightVal = buildRecursive(node * 2 + 1, mid + 1, nodeRight);

		return tree[node] = merge(leftVal, rightVal);
	}

	void build() {
		tree.resize(N * 4);
		//��Ʈ ������ ���������� ����
		buildRecursive(1, 0, N - 1);
	}

	//---------------------------------------

	//left ~ right: ������ ����
	//node: Segment Tree�� ����� ��ȣ
	//nodeLeft ~ nodeRight: �ش� ��尡 �����ϰ� �ִ� ����

	ull queryRecursive(int left, int right, int node, int nodeLeft, int nodeRight) {

		//������ ������ ���Ե��� �ʴ� ������ ��� default �� ��ȯ 
		//default ���� merge ���꿡 ���� �ٸ���
		if (right < nodeLeft || nodeRight < left) {
			return 0LL;
		}

		//������ ������ ���ԵǴ� ������ ���
		if (left <= nodeLeft && nodeRight <= right)
			return tree[node];

		//������ ������ �κ������� ���ԵǴ� ������ ���
		//���� ������ ������ Recursive call
		int mid = (nodeLeft + nodeRight) / 2;
		ull leftVal = queryRecursive(left, right, node * 2, nodeLeft, mid);
		ull rightVal = queryRecursive(left, right, node * 2 + 1, mid + 1, nodeRight);

		return merge(leftVal, rightVal);
	}

	ull query(int left, int right) {
		// ��Ʈ ������ ���������� ���� ������ �� ���
		return queryRecursive(left, right, 1, 0, N - 1);
	}

};

vector<int> solution(vector<string> gems) {
	vector<int> answer;

	//���� ���� �ʱ�ȭ
	N = gems.size();
	arr = gems;

	//���� ���� ���� ����
	int gemId = 0;
	for (int i = 0; i < gems.size(); ++i) {
		if (gemToInt.find(gems[i]) == gemToInt.end()) {
			gemToInt[gems[i]] = gemId;
			gemId++;
		}
	}
	//�� ������ ����
	int totalGems = gemId;

	//���� �� ���Ե� ������ ������ ��Ʈ����ũ�� ������ ���׸�Ʈ Ʈ��
	SegmentTree segmentTree;
	segmentTree.build();

	
	//������ ������ ������ ���� �̺� Ž��
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