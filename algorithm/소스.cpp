#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//adj[i][j]: i와 j사이의 간선의 수
vector<vector<int>> adj;
//graph[i][j]: i로 시작해서 j로 끝나는 단어의 목록(= 간선의 목록)
vector<string> graph[26][26];
//indegree[i]: i로 시작하는 단어의 수(= i로 들어가는 간선의 수)
//outdegree[i]: i로 끝나는 단어의 수(= i로부터 나오는 간선의 수)
vector<int> indegree, outdegree;

void makeGraph(const vector<string>& words) {
	//전역 변수 초기화
	for (int i = 0; i < 26; ++i) {
		for (int j = 0; j < 26; ++j) {
			graph[i][j].clear();
		}
	}
	adj = vector<vector<int>>(26, vector<int>(26, 0));
	indegree = outdegree = vector<int>(26, 0);

	//각 단어 그래프에 추가
	for (int i = 0; i < words.size(); ++i) {
		//단어의 첫 글자 a, 마지막 글자 b
		int a = words[i][0] - 'a';
		int b = words[i][words[i].size() - 1] - 'a';

		graph[a][b].push_back(words[i]);
		adj[a][b]++;
		outdegree[a]++;
		indegree[b]++;
	}
}

//방향 그래프의 인접 행렬 adj가 주어졌을 때 오일러 서킷 혹은 트레일 계산
void getEulerCircuit(int here, vector<int>& circuit) {
	for (int there = 0; there < adj.size(); ++there) {
		while (adj[here][there] > 0) {
			adj[here][there]--;
			getEulerCircuit(there, circuit);
		}
	}
	circuit.push_back(here);
}

//현재 그래프의 오일러 트레일이나 서킷 반환
vector<int> getEulerTrailOrCircuit() {
	vector<int> circuit;

	//나가는 간선의 수가 들어오는 간선의 수보다 하나 많은 정점이 있는지 확인
	for (int i = 0; i < adj.size(); ++i) {
		if (outdegree[i] == indegree[i] + 1) {
			//이 정점을 시작점으로 하여 오일러 트레일을 찾는다
			getEulerCircuit(i, circuit);
			return circuit;
		}
	}
	//아무 정점을 시작점으로 하여 오일러 서킷을 찾는다
	for (int i = 0; i < adj.size(); ++i) {
		if (outdegree[i]) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	}
	//모두 실패한 경우 빈 배열을 반환한다
	return circuit;
}

//끝말잇기 문제의 오일러 서킷/트레일 존재 여부 확인
bool checkEuler() {
	//예비 시작점: 나가는 간선이 들어오는 간선보다 하나 큰 점
	//예비 끝점: 나가는 간선이 들어오는 간선보다 하나 작은 점

	//예비 시작점과 예비 끝점의 개수
	int plus1 = 0, minus1 = 0;

	for (int i = 0; i < 26; ++i) {
		int delta = outdegree[i] - indegree[i];
		if (delta < -1 || delta > 1) return false;
		if (delta == 1) plus1++;
		if (delta == -1) minus1++;
	}

	return ((plus1 == 1 && minus1 == 1) || (plus1 == 0 && minus1 == 0));
}

string solve(const vector<string>& words) {
	//끝말잇기 문제의 입력을 그래프로 만들기
	makeGraph(words);
	//끝말잇기 문제의 오일러 서킷/트레일 존재 여부 확인
	if (!checkEuler()) return "IMPOSSIBLE";

	//오일러 서킷/트레일 찾기
	vector<int> circuit = getEulerTrailOrCircuit();

	//오일러 서킷/트레일이 되기 위해선 모든 간선이 하나의 컴포넌트에 포함되어야
	//모든 간선을 방문하지 못한 경우 실패
	if (circuit.size() - 1 != words.size()) return "IMPOSSIBLE";

	//방문 순서를 뒤집은 뒤 간선들을 모아 문자열로 만들어 반환
	reverse(circuit.begin(), circuit.end());
	string ret;
	for (int i = 1; i < circuit.size(); ++i) {
		int a = circuit[i - 1], b = circuit[i];

		//반환된 문자열에서 첫 단어가 아닌 경우 " " 추가
		if (ret.size()) ret += " ";

		ret += graph[a][b].back();
		graph[a][b].pop_back();
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int c;
	cin >> c;
	while (c--) {
		int n;
		cin >> n;

		vector<string> words;
		string input;
		for (int i = 0; i < n; ++i) {
			cin >> input;
			words.push_back(input);
		}

		cout << solve(words) << "\n";

	}

	return 0;
}