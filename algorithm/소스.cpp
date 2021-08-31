#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> dot;

int N;
vector<dot> dots;

int ccw(dot a, dot b) {
	ll cross = a.first * b.second - a.second * b.first;

	if (cross > 0) return 1;
	else if (cross < 0) return -1;
	else return 0;
}

int ccw(dot p, dot a, dot b) {
	a.first -= p.first; a.second -= p.second;
	b.first -= p.first; b.second -= p.second;
	return ccw(a, b);
}

//ccw���� �̿��Ϸ� ��ȸ�� ���� �˻�
bool leftTurn(dot p, dot a, dot b) {
	return ccw(p, a, b) > 0;
}

//�� ��Ʈ�� ���� �� �Լ�
bool cmp(dot& a, dot& b) {
	dot a0 = make_pair(a.first - dots[0].first, a.second - dots[0].second);
	dot b0 = make_pair(b.first - dots[0].first, b.second - dots[0].second);

	ll cross = a0.first * b0.second - a0.second * b0.first;

	//���� ����� 0�� �ƴ� ��
	//���� ��� ���(�ݽð� ����)�̸� true, ����(�ð� ����)�̸� false ��ȯ
	if (cross != 0)
		return (cross > 0);

	//���� ����� 0�� ��(����) 
	//Y��ǥ�� ������ (���ٸ� X��ǥ�� ������) true ��ȯ
	if (a0.second != b0.second)
		return a0.second < b0.second;
	return a0.first < b0.first;
}

//��� ��带 �������� ���� �ݽð� �������� ����(�� ��Ʈ)
void quickSortByAngle(int first, int last) {
	if (first >= last) return;

	//�� ���� ���ڸ� ����Ʈ�� pivot���� ����
	int pivot = first;
	int i = first + 1;
	int j = last;

	while (i <= j) {
		while (cmp(dots[i], dots[pivot]) && i <= last) i++;
		while (!cmp(dots[j], dots[pivot]) && j > first) j--;

		if (i >= j) break;

		swap(dots[i], dots[j]);
	}
	swap(dots[pivot], dots[j]);

	quickSortByAngle(first, j - 1);
	quickSortByAngle(j + 1, last);
	return;
}

void convexHull() {
	//1. ������ ã��
	//���� Y��ǥ�� ���� (���ٸ� X��ǥ�� ����)���� �������� �Ѵ�
	int minX = 1000000000, minY = 1000000000, minIdx = 0;
	for (int i = 0; i < N; i++) {
		if (minY > dots[i].second || (minY == dots[i].second && minX > dots[i].first)) {
			minX = dots[i].first;
			minY = dots[i].second;
			minIdx = i;
		}
	}
	//dots[0]�� �������� �ǵ��� swap
	swap(dots[minIdx], dots[0]);

	//2. ��� ��带 �������� ���� �ݽð� �������� ����
	quickSortByAngle(1, N - 1);

	//3. ���������� �����ؼ�, ������� ��� ��忡 ���ؼ� ��ȸ�� ���θ� �˻�
	// ��ȸ���� �ش��ϴ� ���и� ã�� �� = Convex Hull
	vector<int> stack(N);
	int idx = -1;
	stack[++idx] = 0;
	stack[++idx] = 1;

	int next = 2;
	while (next < N) {
		while ((idx + 1) >= 2) {
			int second = stack[idx--];
			int first = stack[idx];

			if (leftTurn(dots[first], dots[second], dots[next])) {
				stack[++idx] = second;
				break;
			}
		}
		stack[++idx] = next++;
	}

	//convex hull�� ���Ե� ���� ����
	cout << idx + 1 << "\n";

	return;
}

int main(void) {
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> N;
	for (int i = 0; i < N; i++) {
		ll x, y;
		cin >> x >> y;
		dots.push_back(make_pair(x, y));
	}
	convexHull();
	return 0;
}