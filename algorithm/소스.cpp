#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//adj[i][j]: i�� j������ ������ ��
vector<vector<int>> adj;
//graph[i][j]: i�� �����ؼ� j�� ������ �ܾ��� ���(= ������ ���)
vector<string> graph[26][26];
//indegree[i]: i�� �����ϴ� �ܾ��� ��(= i�� ���� ������ ��)
//outdegree[i]: i�� ������ �ܾ��� ��(= i�κ��� ������ ������ ��)
vector<int> indegree, outdegree;

void makeGraph(const vector<string>& words) {
	//���� ���� �ʱ�ȭ
	for (int i = 0; i < 26; ++i) {
		for (int j = 0; j < 26; ++j) {
			graph[i][j].clear();
		}
	}
	adj = vector<vector<int>>(26, vector<int>(26, 0));
	indegree = outdegree = vector<int>(26, 0);

	//�� �ܾ� �׷����� �߰�
	for (int i = 0; i < words.size(); ++i) {
		//�ܾ��� ù ���� a, ������ ���� b
		int a = words[i][0] - 'a';
		int b = words[i][words[i].size() - 1] - 'a';

		graph[a][b].push_back(words[i]);
		adj[a][b]++;
		outdegree[a]++;
		indegree[b]++;
	}
}

//���� �׷����� ���� ��� adj�� �־����� �� ���Ϸ� ��Ŷ Ȥ�� Ʈ���� ���
void getEulerCircuit(int here, vector<int>& circuit) {
	for (int there = 0; there < adj.size(); ++there) {
		while (adj[here][there] > 0) {
			adj[here][there]--;
			getEulerCircuit(there, circuit);
		}
	}
	circuit.push_back(here);
}

//���� �׷����� ���Ϸ� Ʈ�����̳� ��Ŷ ��ȯ
vector<int> getEulerTrailOrCircuit() {
	vector<int> circuit;

	//������ ������ ���� ������ ������ ������ �ϳ� ���� ������ �ִ��� Ȯ��
	for (int i = 0; i < adj.size(); ++i) {
		if (outdegree[i] == indegree[i] + 1) {
			//�� ������ ���������� �Ͽ� ���Ϸ� Ʈ������ ã�´�
			getEulerCircuit(i, circuit);
			return circuit;
		}
	}
	//�ƹ� ������ ���������� �Ͽ� ���Ϸ� ��Ŷ�� ã�´�
	for (int i = 0; i < adj.size(); ++i) {
		if (outdegree[i]) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	}
	//��� ������ ��� �� �迭�� ��ȯ�Ѵ�
	return circuit;
}

//�����ձ� ������ ���Ϸ� ��Ŷ/Ʈ���� ���� ���� Ȯ��
bool checkEuler() {
	//���� ������: ������ ������ ������ �������� �ϳ� ū ��
	//���� ����: ������ ������ ������ �������� �ϳ� ���� ��

	//���� �������� ���� ������ ����
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
	//�����ձ� ������ �Է��� �׷����� �����
	makeGraph(words);
	//�����ձ� ������ ���Ϸ� ��Ŷ/Ʈ���� ���� ���� Ȯ��
	if (!checkEuler()) return "IMPOSSIBLE";

	//���Ϸ� ��Ŷ/Ʈ���� ã��
	vector<int> circuit = getEulerTrailOrCircuit();

	//���Ϸ� ��Ŷ/Ʈ������ �Ǳ� ���ؼ� ��� ������ �ϳ��� ������Ʈ�� ���ԵǾ��
	//��� ������ �湮���� ���� ��� ����
	if (circuit.size() - 1 != words.size()) return "IMPOSSIBLE";

	//�湮 ������ ������ �� �������� ��� ���ڿ��� ����� ��ȯ
	reverse(circuit.begin(), circuit.end());
	string ret;
	for (int i = 1; i < circuit.size(); ++i) {
		int a = circuit[i - 1], b = circuit[i];

		//��ȯ�� ���ڿ����� ù �ܾ �ƴ� ��� " " �߰�
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