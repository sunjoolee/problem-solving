#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, H;
     
vector<int> bottom; //석순
vector<int> top;    //종유석

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> H;

	for (int i = 0; i < N; ++i) {
		int input;
		cin >> input;

		if (i % 2 == 0) bottom.push_back(input);
		else top.push_back(input);
	}

	sort(bottom.begin(), bottom.end());
	sort(top.begin(), top.end());

	int minObstacle = N;
	int cnt = 0;

	//개똥벌레가 날아가는 구간의 높이 h
	for (double h = 0.5; h < H; ++h) {
		int obstacle = 0;
		
		//만나게 되는 석순의 개수
		obstacle += bottom.size() - (lower_bound(bottom.begin(), bottom.end(), h) - bottom.begin());
		
		//만나게되는 종유석의 개수
		obstacle += top.size() - (lower_bound(top.begin(), top.end(), H - h) - top.begin());

		if (minObstacle > obstacle) {
			minObstacle = obstacle;
			cnt = 1;
		}
		else if (minObstacle == obstacle) {
			++cnt;
		}
	}

	cout << minObstacle << " " << cnt;
	return 0;
}