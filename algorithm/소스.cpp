#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(pair<int, double> a, pair<int, double> b) {
	if (a.second > b.second) return true;
	if (a.second == b.second) return a.first < b.first;
	return false;
}

vector<int> solution(int N, vector<int> stages) {
	
	vector<pair<int, double>> failRate;

	for (int stage = 1; stage < N + 1; ++stage) {
		double  sido= 0;
		double  silpae= 0;

		for (int i = 0; i < stages.size(); ++i){ 
			if (stages[i] >= stage) sido++;
			if (stages[i] == stage) silpae++;
		}
		
		if (sido == 0 || silpae == 0) 
			failRate.push_back({ stage, 0 });
		else 
			failRate.push_back({stage, silpae / sido});
	}

	sort(failRate.begin(), failRate.end(), cmp);
	
	vector<int> answer;
	for (int i = 0; i < failRate.size(); ++i){
		answer.push_back(failRate[i].first);
	}
	return answer;
}

int main() {
	solution(4, { 4, 4, 4, 4, 4 });
}