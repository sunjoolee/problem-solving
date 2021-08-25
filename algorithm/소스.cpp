#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int N, M, K;

//펜윅 트리의 구현
//펜윅 트리의 인덱스는 1부터 시작
//펜윅 트리를 처음 생성하면 모든 부분합 0으로 초기화된다
//= 모든 원소가 0인 배열 arr를 표현한다 
struct FenwickTree {
	vector<ll> tree;

	FenwickTree(int size): tree(size+1){}

	//1번째 수 ~ pos번째 수의 부분 합 계산
	ll sum(int pos) {
		ll ret = 0LL;
		while (pos > 0) {
			ret += tree[pos];

			//0이 아닌 마지막 비트만큼 빼면서 구간들의 값 변경
			pos -= (pos & -pos);
		}
		return ret;
	}

	//pos번째 수에 val을 더한다
	void add(int pos, ll val) {
		while (pos < tree.size()) {
			tree[pos] += val;
			//0이 아닌 마지막 비트만큼 더하면서 구간들의 값 변경
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