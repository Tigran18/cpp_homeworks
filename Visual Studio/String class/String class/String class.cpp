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

	~String() {};
private:
	vector<char> str;
};

int main() {
	String str1;
	vector<char> ch = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!' };
	for (auto& a:ch) {
		str1.setString(a);
	}
	str1.getString();
	cout<<str1.strLen()<<endl;

	String str2({ 'H', 'e', 'l', 'l', 'o', '!', '\0' });
	str2.getString();
	cout<< str2.strLen()<<endl;

	if (str1.strCmp(str2)) {
		cout << "They are the same" << endl;
	}
	else {
		cout << "They are not the same" << endl;
	}


	return 0;
}