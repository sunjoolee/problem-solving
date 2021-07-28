#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int n;

//<���λ絵 �ǰ� ���̻絵 �Ǵ� ���ڿ��� �ִ� ����, ��Ÿ���� Ƚ��>
pair<int, int> getPartialMatch(const vector<ll>& N) {
	vector<int> pi(n, 0);

	//�ִ� ����, ��Ÿ���� Ƚ��
	int maxpi = 0;
	int cnt = 0;

	int begin = 1;
	int matched = 0;
	while (begin + matched < n) {
		if (N[matched] == N[begin + matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
			
			//�ִ� ����, ��Ÿ���� Ƚ�� ����
			if (matched > maxpi) {
				maxpi = matched;
				cnt = 1;
			}
			else if (matched == maxpi) {
				++cnt;
			}
		}
		else {
			if (matched == 0) ++begin;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return make_pair(maxpi, cnt);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;

	vector<ll> num(n, 0);
	for (int i = 0; i < n; ++i) {
		ll input;
		cin >> input;
		num[n - 1 - i] = input;
	}

	pair<ll, ll> res = getPartialMatch(num);

	if (res.first == 0) {
		cout << -1;
		return 0;
	}
	else
		cout << res.first << " " << res.second;

	return 0;
}