#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long int ll;


//로그 형식 2016-09-15 03:10:33.020 0.011s

//시:분:초.xxx -> 초.xxx  * 1000
ll timeToll(string time) {
	//time 형식 03:10:33.020

	ll res = 0;
	res += 3600 * stoll(time.substr(0, 2));
	res += 60 * stoll(time.substr(3, 2));
	res += stoll(time.substr(6, 2));
	res *= 1000;
	res += stoll((time.substr(9)));

	return res;
}

//구간: time ~ time + 1000 - 1 
bool inRange(ll time, ll start, ll end) {
	ll timeStart = time;
	ll timeEnd = time + 1000 - 1;

	//구간의 앞에 걸쳐있는 경우
	//start - 구간 시작 - end - 구간 끝
	if (start <= timeStart && timeStart <= end && end <= timeEnd) return true;

	//구간 안에 로그가 포함된 경우
	//구간 시작 - start - end - 구간 끝
	if (timeStart <= start && end <= timeEnd) return true;

	//구간의 뒤에 걸쳐있는 경우
	//구간 시작 - start - 구간 끝 - end
	if (timeStart <= start && start <= timeEnd && timeEnd <= end) return true;

	//로그 안에 구간이 포함된 경우
	//start - 구간 시작 - 구간 끝 - end
	if (start <= timeStart && timeEnd <= end) return true;

	else return false;
}

int solution(vector<string> lines) {
	
	vector<pair<ll, ll>> startEndPair;

	for (int i = 0; i < lines.size(); ++i) {
		//맨 앞 날짜 제거 & 맨 마지막 s 제거
		string log = lines[i].substr(11, 18);

		ll S = timeToll(log.substr(0, 12));
		ll T = stod(log.substr(13)) * 1000;

		//로그 시작 시점이 전날로 넘어간 경우 00:00:00.000에 시작한 것으로 처리
		startEndPair.push_back({ S - T + 1 >= 0 ? S - T + 1 : 0, S });
	}

	sort(startEndPair.begin(), startEndPair.end());

	int answer = 0;

	for (int i = 0; i < startEndPair.size(); ++i) {
		// time에서 시작하는 1초 구간에 포함되는 로그 세기
		int cnt = 0;
		ll time = startEndPair[i].first;
		for (int j = 0; j < startEndPair.size(); ++j) {
			if (inRange(time, startEndPair[j].first, startEndPair[j].second)) {
				++cnt;
			}
		}
		answer = max(answer, cnt);

		cnt = 0;
		time = startEndPair[i].second; 
		for (int j = 0; j < startEndPair.size(); ++j) {
			if (inRange(time, startEndPair[j].first, startEndPair[j].second)) {
				++cnt;
			}
		}
		answer = max(answer, cnt);
	}

	return answer;
}

