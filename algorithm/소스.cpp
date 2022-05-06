#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
using namespace std;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//n: ��Ƽ�� ������ ����
	//k: �����ǰ �� ��� Ƚ��
	int n, k;
	cin >> n >> k;

	//�����ǰ ��� ���� 
	vector<int> vec;

	//vecmap[�����ǰ]: �����ǰ ���Ǵ� ���� ����� queue
	//��ü�� �����ǰ�� ������ �� ���� ���߿� ���Ǵ� �����ǰ�� �������� ���� ����
	//���� �����ǰ�� ����� �� queue pop ���� 
	map<int, queue<int>> vecmap;

	//�����ǰ ��� ���� �Է� �ޱ�
	int num;
	for (int i = 0; i < k; ++i) {
		cin >> num;
		vec.push_back(num);
		
		//�����ǰ ��� ���� ����

		if (vecmap.find(num) == vecmap.end())
			vecmap[num] = queue<int>();

		vecmap[num].push(vec.size() - 1);
	}

	//��Ƽ�ǿ� �����ִ� �����ǰ 
	vector<int> plug;

	//�ּ� ��ü Ƚ��
	int answer = 0;

	//�����ǰ ��� ���� ��ȸ
	for (int i = 0; i < k; ++i) {
		num = vec[i];
		
		//��Ƽ�ǿ� �����ִ��� Ȯ��
		bool flag = false;
		for (int i = 0; i < plug.size(); ++i) {
			if (plug[i] == num) {
				flag = true;
				break;
			}
		}
		//�����ִ� ��� �״�� ���
		if (flag) {
			vecmap[num].pop();
			continue;
		}

		//�������� �ʴ� ���

		//��Ƽ�� �ڸ� ������ �ȴ´�
		if (plug.size() < n) {
			plug.push_back(num);
			vecmap[num].pop();
			continue;
		}

		//��Ƽ�� �ڸ� ������ �����ǰ ��ü�ؾ���

		//���� ���߿� ���Ǵ� �����ǰ�� ��Ƽ�� ��ġ
		int maxIdx = 0;
		//���� ���߿� ���Ǵ� �����ǰ�� ���Ǵ� ���� 
		int maxpos = -1;

		//��Ƽ�ǿ� �����ִ� �����ǰ �� ���� ���߿� ���Ǵ� �� ã��
		for (int i = 0; i < plug.size(); ++i) {

			//�����ǰ�� ���Ǵ� ����
			//���� ������ �����ǰ�� ���� ������ ���ٸ� k�� ���� 
			int pos;
			if (vecmap[plug[i]].empty()) {
				pos = k;
			}
			else pos = vecmap[plug[i]].front();

			if (pos > maxpos) {
				maxpos = pos;
				maxIdx = i;
			}
		}

		//���� ���߿� ���Ǵ� �����ǰ�� ��ü
		// -> ���� ���߿� ���Ǵ� �����ǰ�� ��Ƽ�� ��ġ�� �ȴ´� 
		plug[maxIdx] = num;
		vecmap[num].pop();

		++answer;
	}

	cout << answer;
	return 0;
}