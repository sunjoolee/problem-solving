#include <vector>
#include <iostream>
using namespace std;

typedef long long ll;

int n;
vector<int> vec;
vector<int> tmp;

//정렬 수행 하며 swap 횟수 카운트
ll swapCnt(int start, int end) {
	//버블 정렬하고자 하는 배열의 길이 0
	if (start == end) return 0;

	//버블 정렬하고자 하는 배열의 길이 1
	if (start + 1 == end) {
		if (vec[start] > vec[end]) {
			swap(vec[start], vec[end]);
			return 1;
		}
		else return 0;
	}


	//버블 정렬하고자 하는 배열의 길이 2 이상
	ll cnt = 0;
	int mid = (start + end) / 2;
	
	//배열 반으로 나누어 재귀호출(Divide and Conquer)
	cnt += swapCnt(start, mid);
	cnt += swapCnt(mid + 1, end);

	//정렬 수행 하며 swap 횟수 카운트 = inversion counting 문제
	int idx1 = start;
	int idx2 = mid + 1;

	//뒤 배열의 숫자가 앞 배열의 숫자보다 앞에 들어가는 경우 1 증가
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

	//나머지 앞의 배열이 뒤로 감
	while (idx1 != mid + 1) {
		if(vec[idx2-1])
		tmp.push_back(vec[idx1]);
		idx1++;
		cnt += inversion;
	}

	//나머지 뒤의 배열이 뒤로 감
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