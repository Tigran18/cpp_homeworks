#include <iostream>
#include <vector>

using namespace std;

class String {
public:
	String() = default;

	String(vector<char> ch) : str(ch) {}

	void setString(char ch) {
		this->str.push_back(ch);
	}

	void getString() {
		for (auto& ch:str) {
			cout << ch;
		}
		cout << endl;
	}

	char getchar(int i) {
		return str[i];
		cout << endl;
	}

	bool strCmp(String& obj) {
		int i=0;
		for (auto& ch:str) {
			char new_ch = obj.getchar(i++);
			if (ch!=new_ch) {
				return false;
			}
		}
		return true;
	}

	int strLen() {
		int i = 0;
		for (auto& ch:str) {
			i++;
		}
		return i;
	}

	static friend istream& operator>>(istream& in, String& obj) {
		char ch;
		obj.str.clear();
		while (in.get(ch) && ch != '\n') {
			obj.str.push_back(ch);
		}
		return in;
	}

	~String() {};
private:
	vector<char> str;
};

int main() {
	String str1;
	vector<char> ch = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
	for (auto& a:ch) {
		str1.setString(a);
	}
	str1.getString();
	cout<<str1.strLen()<<endl;

	String str2({ 'H', 'e', 'l', 'l', 'o', '!'});
	str2.getString();
	cout<< str2.strLen()<<endl;

	String str3({ 'H', 'e', 'l', 'l', 'o', '!'});
	cin >> str3;

	str3.getString();
	cout << str3.strLen() << endl;


	if (str1.strCmp(str2)) {
		cout << "They are the same" << endl;
	}
	else {
		cout << "They are not the same" << endl;
	}

	if (str3.strCmp(str2)) {
		cout << "They are the same" << endl;
	}
	else {
		cout << "They are not the same" << endl;
	}

	return 0;
}
