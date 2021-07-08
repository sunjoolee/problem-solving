#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 101;

int n;
int inDegree[MAXN] = { 0 };
int time[MAXN] = { 0 };
vector<int> child[MAXN];

//dp[node]
int dp[MAXN] = { 0 };

int topologySort() {
	//pair<node>
	queue<int> q;

	for (int i = 1; i <= n; ++i)
		if (inDegree[i] == 0) {
			dp[i] = time[i];
			q.push(i);
		}

	for (int i = 1; i <= n; ++i ){
		if (q.empty()) break;

		int parent = q.front();
		q.pop();

		for (int i = 0; i < child[parent].size(); ++i) {
			int childnode = child[parent][i];

			dp[childnode] = max(dp[childnode], dp[parent] + time[childnode]);

			if (--inDegree[childnode] == 0) {
				q.push(childnode);
			}
		}
	}

	int res = 0;
	for (int i = 1; i <= n; ++i)
		res = max(res, dp[i]);

	return res;
}


int main(){

	cin >> n;

	for (int i = 1; i <= n; ++i) {
		cin >> time[i];
		cin >> inDegree[i];
		for (int j = 0; j < inDegree[i]; ++j) {
			int parent;
			cin >> parent;
			child[parent].push_back(i);
		}
	}

	cout << topologySort();
	return 0;
}