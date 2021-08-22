#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, l, p;
//<�湮 ���� ��ġ, �湮 �������� ���� �� �ִ� ����>
vector<pair<int, int>> stop;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		stop.push_back(make_pair(a, b));
	}
	cin >> l >> p;

	//��� ������ �湮 ������ ����
	stop.push_back(make_pair(0, 0));
	//������ �湮 ������ ����
	stop.push_back(make_pair(l, 0));
	//���� ��ġ ��ǥ �������� ����
	sort(stop.begin(), stop.end());

	//�湮 ������ ��
	int cnt = 0;
	//���� ���� & �����Ŀ� �����鿡�� ���� �� �ִ� ���� ����
	priority_queue<int> pastStop;

	int cur = 0;
	while(cur < stop.size()){
		//���� ��ġ = ���� ��ġ�� �Ǹ� ����
		if (stop[cur].first == l) {
			cout << cnt;
			return 0;
		}

		pastStop.push(stop[cur].second);
		while (true) {
			//���� �������� �̵� ������ ���
			if (stop[cur].first + p >= stop[cur+1].first) {
				p -= (stop[cur + 1].first - stop[cur].first);
				++cur;
				break;
			}
			//���� �������� �̵� �Ұ����� ���
			else {
				if (pastStop.empty()) {
					cout << -1;
					return 0;
				}
				++cnt;
				p += pastStop.top();
				pastStop.pop();
			}
		}
	}

	return 0;
}