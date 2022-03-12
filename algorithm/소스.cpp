#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef long long int ll;
const int MAXTIME = 25 * 60;

ll timeToll(string time) {
	ll lltime = 0;
	lltime += stoll(time.substr(0, 2)) * 60;
	lltime += stoll(time.substr(3, 2));
	return lltime;
}

string llTotime(ll lltime) {
	ll hour = lltime / 60;
	ll min = lltime % 60;

	string time = ""; 

	//HH:MM
	if (hour < 10) time = "0" + to_string(hour);
	else time = to_string(hour);
	time += ":";
	if (min < 10) time = "0" + to_string(min);
	else time = to_string(min);

	return time;
}

string solution(int n, int t, int m, vector<string> timetable) {

	vector<ll> crew;

	for (int i = 0; i < timetable.size(); ++i) {
		ll lltime = timeToll(timetable[i]);
		crew.push_back(lltime);
	}
	sort(crew.begin(), crew.end());

	//셔틀을 타고 사무실로 갈 수 있는 도착 시간 중 제일 늦은 시간
	//= 마지막 셔틀을 탈 수 있기 위해 도착해야하는 시간

	ll busTime = timeToll("09:00");

	//마지막 셔틀 전까지 태워보낼 수 있는 크루들 태워 보내기
	while (n > 1) {
		int seats = m;

		for (int i = 0; i < crew.size(); ++i) {
			ll crewTime = crew[i];
			if (crewTime > busTime) break;

			seats--;
			crew[i] = MAXTIME;
			if (seats == 0) break;
		}
		sort(crew.begin(), crew.end());

		busTime += t;
		n--;
	}

	//마지막 셔틀을 기다리는 크루들의 <대기 시간, 명 수>
	vector<pair<ll, int>> lastCrew;

	for (int i = 0; i < crew.size(); ++i) {
		ll crewTime = crew[i];
		if (crewTime > busTime) break;

		bool inLastCrew = false;
		for (int j = 0; j < lastCrew.size(); ++j) {
			if (lastCrew[j].first == crewTime) {
				lastCrew[j].second++;
				inLastCrew = true;
				break;
			}
		}
		if (!inLastCrew) {
			lastCrew.push_back({ crewTime, 1 });
		}
	}

	string answer = "";
	int seats = m;
	for (int i = 0; i < lastCrew.size(); ++i) {
		if (seats - lastCrew[i].second > 1) {
			seats -= lastCrew[i].second;
		}
		else {
			answer = llTotime(lastCrew[i].first - 1);
			return answer;
		}
	}

	answer = llTotime(busTime);
	return answer;

}