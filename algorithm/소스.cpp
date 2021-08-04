#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;

//n개의 숫자 배열
vector<int> num;

//<숫자, 빈도수>
map<int, int> freq;

bool compare(pair<int, int>& a, const pair<int, int>& b) {
	//빈도수 내림차순으로 정렬
	if (a.second > b.second) return true;

	//빈도수 같으면 수의 크기 오름차순으로 정렬 
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

		//input이 나온 빈도수 계산
		freq[input]++;

		//숫자 배열의 합 계산
		sum += input;
	}

	sort(num.begin(), num.end());

	//1. 산술평균 출력
	//floor(실수 + 0.5): 실수 반올림
	cout << floor(((double)sum / (double)n) + 0.5) << "\n";

	//2. 중앙값 출력
	cout << num[n / 2] << "\n";

	//3. 최빈값 출력
	vector<pair<int, int>> v(freq.begin(), freq.end());

	//빈도수가 큰 수가 앞에 오도록,
	//같은 빈도수라면 크기가 제일 작은 수가 앞에 오도록 정렬
	sort(v.begin(), v.end(), compare);
	
	//최빈값이 한 개인 경우
	if (v.size() == 1 || v[0].second > v[1].second)
		cout << v[0].first << "\n";
	//최빈값이 여러 개인 경우 두 번째로 작은 값 출력
	else if(v[0].second == v[1].second)
		cout << v[1].first << "\n";

	//4. 범위 출력
	cout << num[n - 1] - num[0] << "\n";


	return 0;
}