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

		//��� ������ �߿䵵 ����
		vector<int> importance;
		//������ť <���� ��ȣ, ���� �߿䵵>
		queue<pair<int, int>> printor;

		for (int i = 0; i < n; ++i) {
			int input;
			cin >> input;

			printor.push(make_pair(i, input));
			importance.push_back(input);
		}

		//��� ������ �߿䵵 ����
		sort(importance.begin(), importance.end());

		//������ ����Ʈ�� ����
		int seq = 1;
		while (true) {
			pair<int, int> document = printor.front();

			//���� ������ �߿䵵�� 
			//������ ��� ������ �߿䵵 �� ���� ū ���� ���� ���
			if (document.second == importance.back()) {
				//�ñ��ߴ� ������ ��� 
				if (document.first == m) {
					//����Ʈ�� ���� ��� �� ����
					cout << seq<<"\n";
					break;
				}
				//���� ����Ʈ & ������ �߿䵵 ���Ϳ��� ����
				printor.pop();
				importance.pop_back();
				seq++;
			}
			//���� ������ �߿䵵�� 
			//������ ��� ������ �߿䵵 �� ���� ū ������ ���� ���
			else {
				//���� ���� ������ ť�� �ڷ� �̵�
				printor.push(document);
				printor.pop();
			}
		}
	}
	return 0;
}