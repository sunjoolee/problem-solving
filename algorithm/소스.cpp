#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;

int N;
//<숙제 데드라인, 숙제 컵라면>
vector<pair<int, int>> hw;

//총 얻을 수 있는 컵라면의 수
ull cnt = 0;
priority_queue<int> maxheap;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; ++i) {
		int a, b;
		cin >> a >> b;
		hw.push_back(make_pair(a, b));
	}

	sort(hw.begin(), hw.end());

	//deadline N부터 0까지 1씩 감소시키며 숙제 선택
	for (int deadline = N; deadline > 0; --deadline) {

		//hw 데드라인 오름차순으로 정렬됨 -> 역방향으로 순회
		for (int i = hw.size()-1; i >= 0; --i) {
			//데드라인이 deadline인 hw의 컵라면 수 maxheap에 추가
			if (hw[i].first == deadline) {
				maxheap.push(hw[i].second);
				hw.pop_back();
			}
			else break;
		}

		if (!maxheap.empty()) {
			cnt += maxheap.top();
			maxheap.pop();
		}
		
	}
	
	cout << cnt;
	return 0;
}