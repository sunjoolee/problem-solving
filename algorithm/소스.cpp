#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, H;
     
vector<int> bottom; //����
vector<int> top;    //������

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

	//���˹����� ���ư��� ������ ���� h
	for (double h = 0.5; h < H; ++h) {
		int obstacle = 0;
		
		//������ �Ǵ� ������ ����
		obstacle += bottom.size() - (lower_bound(bottom.begin(), bottom.end(), h) - bottom.begin());
		
		//�����ԵǴ� �������� ����
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