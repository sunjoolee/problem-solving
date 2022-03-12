#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long int ll;


//�α� ���� 2016-09-15 03:10:33.020 0.011s

//��:��:��.xxx -> ��.xxx  * 1000
ll timeToll(string time) {
	//time ���� 03:10:33.020

	ll res = 0;
	res += 3600 * stoll(time.substr(0, 2));
	res += 60 * stoll(time.substr(3, 2));
	res += stoll(time.substr(6, 2));
	res *= 1000;
	res += stoll((time.substr(9)));

	return res;
}

//����: time ~ time + 1000 - 1 
bool inRange(ll time, ll start, ll end) {
	ll timeStart = time;
	ll timeEnd = time + 1000 - 1;

	//������ �տ� �����ִ� ���
	//start - ���� ���� - end - ���� ��
	if (start <= timeStart && timeStart <= end && end <= timeEnd) return true;

	//���� �ȿ� �αװ� ���Ե� ���
	//���� ���� - start - end - ���� ��
	if (timeStart <= start && end <= timeEnd) return true;

	//������ �ڿ� �����ִ� ���
	//���� ���� - start - ���� �� - end
	if (timeStart <= start && start <= timeEnd && timeEnd <= end) return true;

	//�α� �ȿ� ������ ���Ե� ���
	//start - ���� ���� - ���� �� - end
	if (start <= timeStart && timeEnd <= end) return true;

	else return false;
}

int solution(vector<string> lines) {
	
	vector<pair<ll, ll>> startEndPair;

	for (int i = 0; i < lines.size(); ++i) {
		//�� �� ��¥ ���� & �� ������ s ����
		string log = lines[i].substr(11, 18);

		ll S = timeToll(log.substr(0, 12));
		ll T = stod(log.substr(13)) * 1000;

		//�α� ���� ������ ������ �Ѿ ��� 00:00:00.000�� ������ ������ ó��
		startEndPair.push_back({ S - T + 1 >= 0 ? S - T + 1 : 0, S });
	}

	sort(startEndPair.begin(), startEndPair.end());

	int answer = 0;

	for (int i = 0; i < startEndPair.size(); ++i) {
		// time���� �����ϴ� 1�� ������ ���ԵǴ� �α� ����
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

