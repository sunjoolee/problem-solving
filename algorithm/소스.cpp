#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

//전체 학생 수
int n;

//각 학생은 한 명의 학생만 지목할 수 있다
//adj[i]: 학생 i가 지목한 학생
vector<int> adj;

//사이클에 포함된 학생 수
int inCycle;

int counter;
vector<int> discovered, finished;

//there -> ... -> here -> there 사이클 속 포함된 정점의 수 계산 
int countCycle(int here, int there) {
	int cnt = 1; //there 
	while (there != here) {
		there = adj[there];
		cnt++;
	}
	return cnt;
}

void solve(int here) {
	discovered[here] = counter++;

	int there = adj[here];

	//아직 방문한 적 없다면 방문한다
	if (discovered[there] == -1) solve(there);
	
	//역방향 간선인 경우 사이클에 포함된 정점 수 세기
	else if (discovered[here] > discovered[there] && finished[there] == 0) 
		inCycle += countCycle(here, there);
	
	finished[here] = 1;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		cin >> n;

		//초기화
		inCycle = 0;
		counter = 0;
		adj = vector<int>(n);
		discovered = vector<int>(n, -1);
		finished = vector<int>(n, 0);

		for (int i = 0; i < n; ++i) {
			int input;
			cin >> input;

			//자기 자신을 선택한 경우 전처리
			if (i == input - 1) {
				discovered[i] = counter++;
				finished[i] = 1;
				inCycle++;
			}

			else adj[i] = input - 1;
		}

		//solve all
		for (int i = 0; i < n; ++i) {
			if (discovered[i] == -1)
				solve(i);
		}

		cout << n - inCycle<<"\n";

	}
	return 0;
}