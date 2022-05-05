#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//HH:MM:SS
int time_to_int(string time) {
	string H = time.substr(0, 2);
	string M = time.substr(3, 2);
	string S = time.substr(6, 2);
	return stoi(S) + (60 * stoi(M)) + (360 * stoi(H));
}

string int_to_time(int n) {
	string H = to_string(n / 360);
	n = n % 360;
	if (H.length == 1) H = "0" + H;

	string M = to_string(n / 60);
	n = n % 60;
	if (M.length == 1) M = "0" + M;

	string S = to_string(n);
	if (S.length == 1) S = "0" + S;

	return H + ":" + M + ":" + S;
}


string solution(string play_time, string adv_time, vector<string> logs) {
	vector<pair<int, int>> log_time;
	vector<int> all_time;

	int play_time_int = time_to_int(play_time);
	all_time.push_back(0);
	all_time.push_back(play_time_int);

	//H1:M1:S1-H2:M2:S2
	for (int i = 0; i < logs.size(); ++i) {
		string log_time_start = logs[i].substr(0, 8); 
		int log_time_start_int = time_to_int(log_time_start);

		string log_time_end = logs[i].substr(10, 8);
		int log_time_end_int = time_to_int(log_time_end);

		log_time.push_back({log_time_start_int, log_time_end_int});
		all_time.push_back(log_time_start_int);
		all_time.push_back(log_time_end_int);
	}

	sort(log_time.begin(), log_time.end());
	
	sort(all_time.begin(), all_time.end()); 
	all_time.erase(unique(all_time.begin(), all_time.end()), all_time.end());


	vector<int> all_time_cnt(all_time.size(), 0);
	
	int max_cnt = -1;
	//가장 시청자 수 많은 구간 인덱스
	int all_time_max_idx = -1;

	for (int i = 0; i < all_time.size() - 1; ++i) {
		//i번째 구간 = all_time[i] ~ all_time[i+1]
		//구간 내 시청자 수 계산
		for (int j = 0; j < log_time.size(); ++j) {
			if (all_time[i + 1] <= log_time[j].first) break;

			if (log_time[j].first <= all_time[i] && all_time[i + 1] <= log_time[j].second) {
				all_time_cnt[i]++;
				if (all_time_cnt[i] > max_cnt) {
					max_cnt = all_time_cnt[i];
					all_time_max_idx = i;
				}
			}
		}
	}

	//가장 시청자 수 많은 구간에 광고 배치
	int ans = all_time[all_time_max_idx];

	int adv_time_int = time_to_int(adv_time);
	int time_len = all_time[all_time_max_idx + 1] - all_time[all_time_max_idx];

	while (time_len >= adv_time_int) {
		if()
	}

	string answer = "";
	return answer;
}