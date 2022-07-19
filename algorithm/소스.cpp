#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int n; //집의 개수
int c; //공유기 개수

vector<int> house;

//가장 인접한 두 공유기 사이의 거리가 dis보다 작아지지 않도록
//c개의 공유기를 설치할 수 있는가 확인
bool check(int dis) {
	int pos = house[0]; //가장 최근에 설치한 공유기 위치
	int cnt = 1; //현재까지 설치한 공유기 수

	for (int i = 1; i < n; ++i) {
		if ((house[i] - pos) >= dis) {
			pos = house[i];
			cnt++;
		}
		else continue;
	}
	return cnt >= c;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n >> c;
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		house.push_back(input);
	}
	sort(house.begin(), house.end());

	//가능한 dis의 최댓값 이분 탐색으로 구하기
	int maxDis = house.back();
	int minDis = 1;
	while (minDis < maxDis) {
		int midDis = (maxDis + minDis + 1) / 2;
		if (check(midDis)) minDis = midDis;
		else maxDis = midDis - 1;
	}

	cout << maxDis;
	return 0;
}