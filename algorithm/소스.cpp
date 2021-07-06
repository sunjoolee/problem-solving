#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 10001;

int N;
//index 1~N
vector<vector<int>> work(MAXN, vector<int>(1,0));
int time[MAXN];
int finish[MAXN] = { 0 };

int getFinishTime() {
	int ret = 0;

	for (int i = 1; i <= N; ++i){

		int lastFinish = 0;
		while (!work[i].empty()) {
			lastFinish = max(lastFinish, finish[work[i].back()]);
			work[i].pop_back();
		}
			
		finish[i] = lastFinish + time[i];
		ret = max(ret, finish[i]);
	}


	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> time[i];

		int n; 
		cin >> n;
		for (int j = 1; j <= n; ++j) {
			int w;
			cin >> w;
			work[i].push_back(w);
		}
	}
	
	cout << getFinishTime();
	return 0;
}