#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef long long ll;

vector<int> solution(vector<string> info, vector<string> query) {

	ll cppBitmask = 0LL;
	ll javaBitmask = 0LL; 
	ll pythonBitmask = 0LL; 
	ll backendBitmask = 0LL;
	ll frontendBitmask = 0LL;
	ll juniorBitmask = 0LL;
	ll seniorBitmask = 0LL;
	ll chickenBitmask = 0LL;
	ll pizzaBitmask = 0LL;
	vector<int> score(info.size());

	for (int i = 0; i < info.size(); ++i) {
		string buffer = "";
		for (int j = 0; j < info[i].length(); ++j) {
			if (info[i][j] == ' ') {
				if(buffer == "cpp") cppBitmask |= (1 << i);
				else if (buffer == "java") javaBitmask |= (1 << i);
				else if (buffer == "python") pythonBitmask |= (1 << i);
				else if (buffer == "backend") backendBitmask |= (1 << i);
				else if (buffer == "frontend") frontendBitmask |= (1 << i);
				else if (buffer == "senior") seniorBitmask |= (1 << i);
				else if (buffer == "junior") juniorBitmask |= (1 << i);
				else if (buffer == "chicken") chickenBitmask |= (1 << i);
				else if (buffer == "pizza") pizzaBitmask |= (1 << i);
				buffer = "";
			}
			else buffer += info[i][j];
		}
		score[i] = stoi(buffer);
	}

	vector<int> answer;
	for (int i = 0; i < query.size(); ++i) {
		
		int cnt = 0;
		ll bitmask = (1 << (info.size())) - 1;

		string buffer = "";
		for (int j = 0; j < query[i].length(); ++j) {
			if (query[i][j] == ' ') {
				if (buffer == "cpp") bitmask &= cppBitmask;
				else if (buffer == "java") bitmask &= javaBitmask;
				else if (buffer == "python") bitmask &= pythonBitmask;
				else if (buffer == "backend")bitmask &= backendBitmask;
				else if (buffer == "frontend") bitmask &= frontendBitmask;
				else if (buffer == "senior")bitmask &= seniorBitmask;
				else if (buffer == "junior") bitmask &= juniorBitmask;
				else if (buffer == "chicken") bitmask &= chickenBitmask;
				else if (buffer == "pizza") bitmask &= pizzaBitmask;
				buffer = "";
			}
			else buffer += query[i][j];
		}
		int X = stoi(buffer);
		for (int j = 0; j < info.size(); ++j) {
			if (bitmask & (1 << j)) {
				if (score[j] >= X) cnt++;
			}
		}

		answer.push_back(cnt);
	}
	return answer;
}