#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_BOX = 1000000;

int N, K, D;

//<<���� ����, �� ����>, ���� ����>
vector<pair<pair<int, int>, int>> rule;

int main(void){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> K >> D;

	for (int i = 0; i < K; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		rule.push_back(make_pair(make_pair(a, b), c));
	}

	int low = 0;
	int hi= MAX_BOX + 1;
	for (int it = 0; it < 100; ++it) {
		int mid = (low + hi) / 2;

		//���� ����: ������ ������ ��ȣ�� x�� �� D���� ���丮�� ��� ���� �� �ִ°�?
		long long cnt = 0;
		for (int i = 0; i < K; i++) {
			int startBox = rule[i].first.first;
			int endBox = rule[i].first.second;
			int gap = rule[i].second;

			if (startBox > mid) continue;
			else cnt += ((min(endBox, mid) - startBox) / gap ) + 1;
		}

		if (cnt >= D) hi = mid;
		else low = mid;
	}

	cout << hi;
	return 0;
}
