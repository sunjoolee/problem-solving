#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
	//회의 끝나는 시간 빠른 순으로 정렬
	if(a.second < b.second) return true;
	//회의 끝나는 시간 같은 경우
	//회의 시작하는 시간 빠른 순으로 정렬
	if (a.second == b.second) return a.first < b.first;

	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n;
	cin >> n;

	vector<pair<int, int>> meeting;
	for (int i = 0; i < n; ++i) {
		int start, end;
		cin >> start >> end;
		meeting.push_back({ start, end });
	}
	sort(meeting.begin(), meeting.end(), cmp);

	int cnt = 0;
	int meetingEnd = 0;
	for (int i = 0; i < n; ++i) {
		if (meetingEnd <= meeting[i].first) {
			cnt++;
			meetingEnd = meeting[i].second;
		}
	}
	cout << cnt;
	return 0;
}