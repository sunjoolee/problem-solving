#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int N, M, K;

//���� Ʈ���� ����
//���� Ʈ���� �ε����� 1���� ����
//���� Ʈ���� ó�� �����ϸ� ��� �κ��� 0���� �ʱ�ȭ�ȴ�
//= ��� ���Ұ� 0�� �迭 arr�� ǥ���Ѵ� 
struct FenwickTree {
	vector<ll> tree;

	FenwickTree(int size): tree(size+1){}

	//1��° �� ~ pos��° ���� �κ� �� ���
	ll sum(int pos) {
		ll ret = 0LL;
		while (pos > 0) {
			ret += tree[pos];

			//0�� �ƴ� ������ ��Ʈ��ŭ ���鼭 �������� �� ����
			pos -= (pos & -pos);
		}
		return ret;
	}

	//pos��° ���� val�� ���Ѵ�
	void add(int pos, ll val) {
		while (pos < tree.size()) {
			tree[pos] += val;
			//0�� �ƴ� ������ ��Ʈ��ŭ ���ϸ鼭 �������� �� ����
			pos += (pos & -pos);
		}
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> K;

	FenwickTree fenwickTree(N);

	for (int i = 1; i <= N; ++i) {
		ll input;
		cin >> input;
		fenwickTree.add(i, input);
	}

	for (int i = 0; i < M + K; ++i) {
		int operation;
		cin >> operation;

		if (operation == 1) {
			int pos; 
			ll val;
			cin >> pos >> val;

			val = val - (fenwickTree.sum(pos) - fenwickTree.sum(pos-1));
			fenwickTree.add(pos, val);
		}

		else if (operation == 2) {
			int left, right;
			cin >> left >> right;

			cout << fenwickTree.sum(right) - fenwickTree.sum(left - 1) << "\n";
		}
	}

	return 0;
}