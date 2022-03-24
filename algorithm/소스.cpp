#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(string s) {

	int answer = s.length();

	for (int len = 1; len <= s.length(); ++len) {
		string res = "";

		int cnt = 1;
		int pos = 0;
		while (pos + len <= s.length()) {
			//현재 문자열 조각
			string now = s.substr(pos, len);

			//다음 문자열 조각 없는 경우
			if (pos + (2 * len) > s.length()) {
				if (cnt == 1) res += now;
				else res += (to_string(cnt) + now);

				//남은 문자열 붙이기
				res += s.substr(pos + len);
				break;
			}

			//다음 문자열 조각
			string next = s.substr(pos + len, len);

			if (now == next) cnt++;
			else {
				if (cnt == 1) res += now;
				else res += (to_string(cnt) + now);
				cnt = 1;
			}
			pos += len;
		}

		if (res.length() < answer) answer = res.length();
	}

	return answer;
}

int main() {
	solution("aabbaccc");
}