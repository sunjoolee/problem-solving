#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;

	while (t--) {
		int n, m;
		cin >> n >> m;

		//모든 문서의 중요도 저장
		vector<int> importance;
		//프린터큐 <문서 번호, 문서 중요도>
		queue<pair<int, int>> printor;

		for (int i = 0; i < n; ++i) {
			int input;
			cin >> input;

			printor.push(make_pair(i, input));
			importance.push_back(input);
		}

		//모든 문서의 중요도 정렬
		sort(importance.begin(), importance.end());

		//문서가 프린트된 순서
		int seq = 1;
		while (true) {
			pair<int, int> document = printor.front();

			//현재 문서의 중요도가 
			//나머지 모든 문서의 중요도 중 가장 큰 값과 같은 경우
			if (document.second == importance.back()) {
				//궁금했던 문서인 경우 
				if (document.first == m) {
					//프린트된 순서 출력 후 종료
					cout << seq<<"\n";
					break;
				}
				//문서 프린트 & 문서의 중요도 벡터에서 제거
				printor.pop();
				importance.pop_back();
				seq++;
			}
			//현재 문서의 중요도가 
			//나머지 모든 문서의 중요도 중 가장 큰 값보다 작은 경우
			else {
				//현재 문서 프린터 큐의 뒤로 이동
				printor.push(document);
				printor.pop();
			}
		}
	}
	return 0;
}