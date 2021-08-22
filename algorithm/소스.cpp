#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, l, p;
//<방문 지점 위치, 방문 지점에서 얻을 수 있는 연료>
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

	//출발 지점도 방문 지점에 포함
	stop.push_back(make_pair(0, 0));
	//마을도 방문 지점에 포함
	stop.push_back(make_pair(l, 0));
	//지점 위치 좌표 오름차순 정렬
	sort(stop.begin(), stop.end());

	//방문 주유소 수
	int cnt = 0;
	//현재 지점 & 지나쳐온 지점들에서 얻을 수 있는 연료 저장
	priority_queue<int> pastStop;

	int cur = 0;
	while(cur < stop.size()){
		//현재 위치 = 마을 위치가 되면 종료
		if (stop[cur].first == l) {
			cout << cnt;
			return 0;
		}

		pastStop.push(stop[cur].second);
		while (true) {
			//다음 지점으로 이동 가능한 경우
			if (stop[cur].first + p >= stop[cur+1].first) {
				p -= (stop[cur + 1].first - stop[cur].first);
				++cur;
				break;
			}
			//다음 지점으로 이동 불가능한 경우
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