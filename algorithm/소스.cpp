#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

//��ü �л� ��
int n;

//�� �л��� �� ���� �л��� ������ �� �ִ�
//adj[i]: �л� i�� ������ �л�
vector<int> adj;

//����Ŭ�� ���Ե� �л� ��
int inCycle;

int counter;
vector<int> discovered, finished;

//there -> ... -> here -> there ����Ŭ �� ���Ե� ������ �� ��� 
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

	//���� �湮�� �� ���ٸ� �湮�Ѵ�
	if (discovered[there] == -1) solve(there);
	
	//������ ������ ��� ����Ŭ�� ���Ե� ���� �� ����
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

		//�ʱ�ȭ
		inCycle = 0;
		counter = 0;
		adj = vector<int>(n);
		discovered = vector<int>(n, -1);
		finished = vector<int>(n, 0);

		for (int i = 0; i < n; ++i) {
			int input;
			cin >> input;

			//�ڱ� �ڽ��� ������ ��� ��ó��
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