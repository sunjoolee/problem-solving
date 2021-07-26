#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <math.h>
#include <algorithm>
using namespace std;

string words[10];

bool compare(long long a, long long b) {
	return a > b;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string words[10];

	//mult[알파벳 - 'A']: 알파벳에 곱해질 숫자
	long long mult[27] = { 0 };

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> words[i];

		int digit = 0;
		//string reverse iterator
		for (auto it = words[i].rbegin(); it != words[i].rend(); ++it)
			mult[*it - 'A'] += pow(10, digit++);
	}
	
	//mult 내림차순 정렬
	sort(mult, mult + 27, compare);

	long long sum = 0;
	int number = 9;

	for (int i = 0; i < 27; ++i) {
		if (mult[i] == 0) break;

		sum += number * mult[i];
		--number;
	}

	cout << sum;
	return 0;
}