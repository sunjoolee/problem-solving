#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
set<string> name;
vector<string> ans;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;

	//듣도 못한 사람 명단 set 삽입
	for (int i = 0; i < n; ++i) {
		string input;
		cin >> input;
		name.insert(input);
	}

	//보도 못한 사람 명단 set 삽입
	for (int i = 0; i < m; ++i) {
		string input; 
		cin >> input;
			
		//중복된 문자열인 경우 set 삽입 실패 = 듣도 보도 못한 사람
		auto it = name.insert(input);
		if (!it.second) ans.push_back(input);
	}

	//듣도 보도 못한 사람 명단 사전순 정렬
	sort(ans.begin(), ans.end());

	cout << ans.size() << "\n";
	for (int i = 0; i < ans.size(); ++i)
		cout << ans[i] << "\n";

	return 0;
}