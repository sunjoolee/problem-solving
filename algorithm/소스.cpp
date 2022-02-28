#include <string>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
	
	vector<string> answer;
	
	for (int i = 0; i < n; ++i) {
		
		int num = arr1[i] | arr2[i];
		
		stack<char> st;
		while (num > 0) {
			if (num % 2) st.push('#');
			else st.push(' ');
			num /= 2;
		}
		while (st.size() > n) {
			row += " ";
		}

		string row = "";
		answer.push_back(row);
	}

	return answer;
}