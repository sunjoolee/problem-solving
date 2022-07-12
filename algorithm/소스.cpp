#include <vector>
#include <iostream>
using namespace std;

typedef long long ll;

int n;
vector<int> vec;
vector<int> tmp;

//���� ���� �ϸ� swap Ƚ�� ī��Ʈ
ll swapCnt(int start, int end) {
	//���� �����ϰ��� �ϴ� �迭�� ���� 0
	if (start == end) return 0;

	//���� �����ϰ��� �ϴ� �迭�� ���� 1
	if (start + 1 == end) {
		if (vec[start] > vec[end]) {
			swap(vec[start], vec[end]);
			return 1;
		}
		else return 0;
	}


	//���� �����ϰ��� �ϴ� �迭�� ���� 2 �̻�
	ll cnt = 0;
	int mid = (start + end) / 2;
	
	//�迭 ������ ������ ���ȣ��(Divide and Conquer)
	cnt += swapCnt(start, mid);
	cnt += swapCnt(mid + 1, end);

	//���� ���� �ϸ� swap Ƚ�� ī��Ʈ = inversion counting ����
	int idx1 = start;
	int idx2 = mid + 1;

	//�� �迭�� ���ڰ� �� �迭�� ���ں��� �տ� ���� ��� 1 ����
	ll inversion = 0;

	while ((idx1 != mid + 1) && (idx2 != end + 1)) {
		if (vec[idx1] > vec[idx2]) {
			tmp.push_back(vec[idx2]);
			idx2++;
			inversion++;
		}
		else {
			tmp.push_back(vec[idx1]);
			idx1++;
			cnt += inversion;
		}
	}

	//������ ���� �迭�� �ڷ� ��
	while (idx1 != mid + 1) {
		if(vec[idx2-1])
		tmp.push_back(vec[idx1]);
		idx1++;
		cnt += inversion;
	}

	//������ ���� �迭�� �ڷ� ��
	while (idx2 != end + 1) {
		tmp.push_back(vec[idx2]);
		idx2++;
	}

	for (int i = 0; i < tmp.size(); ++i) {
		vec[start + i] = tmp[i];
	}
	tmp.clear();

	return cnt;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		vec.push_back(input);
	}

	cout << swapCnt(0, n - 1);

	return 0;
}