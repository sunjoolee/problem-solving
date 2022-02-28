#include <string>
#include <vector>
#include <algorithm>

const int INF = 987654321;
using namespace std;

int solution(int cacheSize, vector<string> cities) {
	int answer = 0;

	vector<pair<string, int>> cache;

	for (int i = 0; i < cities.size(); ++i) {
		string city = cities[i];
		transform(city.begin(), city.end(), city.begin(), ::tolower);	
		bool hit = false;
		for (int j = 0; j < cache.size(); ++j) {
			if (cache[j].first == city) {
				//hit
				hit = true;
				answer += 1;
				//캐시 갱신
				cache[j].second = i;
				break;
			}
		}
		if (hit) continue;

		//miss
		answer += 5;
		//캐시에 추가
		if (cache.size() < cacheSize) {
			cache.push_back({ city, i });
		}
		else {
			int minUsed = INF;
			int minIndex;
			for (int j = 0; j < cache.size(); ++j) {
				if (cache[j].second < minUsed) {
					minUsed = cache[j].second;
					minIndex = j;
				}
			}
			cache[minIndex] = { city, i };
		}
	}

	return answer;
}