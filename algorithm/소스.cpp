#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

typedef long long ll;
const int INF = 987654321;

//N: ���� �������� ����
int N;

//���� ������
vector<string> arr;

struct SegmentTree {
	vector<set<string>> tree;

	//���� ������ ���� �� ������ ����
	set <string> merge(set<string> left, set<string> right) {
		set <string> result;

		result.insert(left.begin(), left.end());
		result.insert(right.begin(), right.end());

		return result;
	}

	//---------------------------------------

	//node: Segment Tree�� ����� ��ȣ
	//nodeLeft ~ nodeRight: �ش� ��尡 �����ϰ� �ִ� ����

	set<string> buildRecursive(int node, int nodeLeft, int nodeRight) {

		//������忡 ������ ���
		if (nodeLeft == nodeRight) {
			set<string> leaf;
			leaf.insert(arr[nodeLeft]);
			return tree[node] = leaf;
		}

		//������尡 �ƴ� ��� ���� ������ ������ Recursive call
		//����� ������ ������ ��: ����� ������ �ڽ��� ����
		//����� ������ ���� ��: ����� ���� �ڽ��� ����

		int mid = (nodeLeft + nodeRight) / 2;
		set<string> leftVal = buildRecursive(node * 2, nodeLeft, mid);
		set<string> rightVal = buildRecursive(node * 2 + 1, mid + 1, nodeRight);

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

	set<string> queryRecursive(int left, int right, int node, int nodeLeft, int nodeRight) {

		//������ ������ ���Ե��� �ʴ� ������ ��� default �� ��ȯ 
		//default ���� merge ���꿡 ���� �ٸ���
		if (right < nodeLeft || nodeRight < left) {
			set<string> emptySet;
			return emptySet;
		}

		//������ ������ ���ԵǴ� ������ ���
		if (left <= nodeLeft && nodeRight <= right)
			return tree[node];

		//������ ������ �κ������� ���ԵǴ� ������ ���
		//���� ������ ������ Recursive call
		int mid = (nodeLeft + nodeRight) / 2;
		set<string> leftVal = queryRecursive(left, right, node * 2, nodeLeft, mid);
		set<string> rightVal = queryRecursive(left, right, node * 2 + 1, mid + 1, nodeRight);

		return merge(leftVal, rightVal);
	}

	set<string> query(int left, int right) {
		// ��Ʈ ������ ���������� ���� ������ �� ���
		return queryRecursive(left, right, 1, 0, N - 1);
	}

};


vector<int> solution(vector<string> gems) {
	vector<int> answer;

	N = gems.size();
	arr = gems;

	SegmentTree segmentTree;
	segmentTree.build();

	//�� ������ ���� = ��ü ������ ���� �� set<string> �� ũ��
	int totalGems = segmentTree.query(0, gems.size() - 1).size();

	//������ ������ ������ ���� �̺� Ž��
	int lo = 0, hi = gems.size() + 1;

	int minLen = INF;
	int minStart = INF;

	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;

		bool flag = false;
		for (int start = 0; start + mid - 1 < gems.size(); ++start) {
			if (segmentTree.query(start, start + mid - 1).size() == totalGems) {
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


