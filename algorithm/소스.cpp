#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(string new_id) {
	
	//1
	transform(new_id.begin(), new_id.end(), new_id.begin(), ::tolower);
	//2
	string tmp = "";
	for (int i = 0; i < new_id.length(); ++i) {
		if ('a' <= new_id[i] && new_id[i] <= 'z') 
			tmp += new_id[i];
		else if(new_id[i] == '.' || new_id[i] == '-' || new_id[i] == '_')
			tmp += new_id[i];
	}
	new_id = tmp;
	//3
	tmp = "";
	bool period = false;
	for (int i = 0; i < new_id.length(); ++i) {
		if (new_id[i] == '.') {
			if (!period) tmp += '.';
			period = true;
		}
		else {
			tmp += new_id[i];
			period = false;
		}
	}
	new_id = tmp;
	//4
	if (new_id != "" && new_id[0] == '.') {
		if(new_id.length() > 1) new_id = new_id.substr(1);
		else new_id = "";
	}
	if (new_id != "" && new_id[new_id.length() - 1]=='.') {
		if (new_id.length() > 1) new_id = new_id.substr(0, new_id.length() - 1);
		else new_id = "";
	}
	//5
	if (new_id == "") new_id = "a";
	//6
	if(new_id.length() > 15) new_id = new_id.substr(0, 15);
	if (new_id != "" && new_id[new_id.length() - 1]== '.') {
		if (new_id.length() > 1) new_id = new_id.substr(0, new_id.length() - 1);
		else new_id = "";
	}
	//7
	while (new_id.length() < 3) {
		new_id += new_id[new_id.length() - 1];
	}

	return new_id;
}

int main() {
	solution("...!@BaT#*..y.abcdefghijklm");
}