#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;

//n���� ���� �迭
vector<int> num;

//<����, �󵵼�>
map<int, int> freq;

bool compare(pair<int, int>& a, const pair<int, int>& b) {
	//�󵵼� ������������ ����
	if (a.second > b.second) return true;

	//�󵵼� ������ ���� ũ�� ������������ ���� 
	if (a.second == b.second) 
		return a.first < b.first;

	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;


	int sum = 0;
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		num.push_back(input);

		//input�� ���� �󵵼� ���
		freq[input]++;

		//���� �迭�� �� ���
		sum += input;
	}

	sort(num.begin(), num.end());

	//1. ������ ���
	//floor(�Ǽ� + 0.5): �Ǽ� �ݿø�
	cout << floor(((double)sum / (double)n) + 0.5) << "\n";

	//2. �߾Ӱ� ���
	cout << num[n / 2] << "\n";

	//3. �ֺ� ���
	vector<pair<int, int>> v(freq.begin(), freq.end());

	//�󵵼��� ū ���� �տ� ������,
	//���� �󵵼���� ũ�Ⱑ ���� ���� ���� �տ� ������ ����
	sort(v.begin(), v.end(), compare);
	
	//�ֺ��� �� ���� ���
	if (v.size() == 1 || v[0].second > v[1].second)
		cout << v[0].first << "\n";
	//�ֺ��� ���� ���� ��� �� ��°�� ���� �� ���
	else if(v[0].second == v[1].second)
		cout << v[1].first << "\n";

	//4. ���� ���
	cout << num[n - 1] - num[0] << "\n";


	return 0;
}