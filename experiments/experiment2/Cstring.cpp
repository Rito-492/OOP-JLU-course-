#include <bits/stdc++.h>
using namespace std;

class Cstring {
	
	char *str;
    int length;
    
    public:
    	friend ostream& operator<<(ostream& os, const Cstring& cstring);
        Cstring();
        Cstring(const char *src);
        Cstring(const Cstring& src);
        ~Cstring(){
        	delete[] str;
		}
        Cstring& operator=(const Cstring src);
        Cstring& operator=(const char* src);
        Cstring operator+(const Cstring& y);
        Cstring operator()(const int org, const int end);
        char operator[](const int index);
        int len();
};

Cstring :: Cstring() {
    length = 1;
    str = new char[length];
    strcpy(str, "");
}

Cstring :: Cstring(const char *src) {
    length = strlen(src) + 1;
    str = new char[length];
    strcpy(str, src);
}

Cstring :: Cstring(const Cstring& src){
	length = strlen(src.str) + 1;
	str = new char[length];
	strcpy(str, src.str);
}

char Cstring :: operator[](const int index) {
    return str[index];
}

Cstring& Cstring :: operator=(const Cstring src){
	length = src.length;
	str = new char[length];
	strcpy(str, src.str);
	return *this;
}

Cstring& Cstring :: operator=(const char* src) {
	length = strlen(src) + 1;
	str = new char[length];
	strcpy(str, src);
	return *this;
}

Cstring Cstring :: operator+(const Cstring& y) {
	Cstring ans;
	ans.length = length + y.length - 1;
	ans.str = new char[length];
	strcpy(ans.str, str), strcat(ans.str, y.str);
	return ans;
}

Cstring Cstring :: operator()(const int org, const int end){
	Cstring ans;
	ans.length = end - org + 1 + 1;
	ans.str = new char[ans.length];
	int index = 0;
	for (int i = org;i <= end && str[i] != 0;i++)
		ans.str[index++] =str[i];
	ans.str[ans.length] = 0; 
	return ans;
}

int Cstring :: len() {
    return length - 1;
}

ostream& operator<<(ostream& os, const Cstring& cstring) {
	cout<< cstring.str;
	return os;
}

int main() {
    Cstring m("software");
    Cstring n(m),o;
    o = m;
    cout << n[4] <<endl;
    cout << n.len() <<endl;
    o = m + n;
    cout << o <<endl;
    o = m(2, 8);
    cout << o <<endl
		 << m <<endl
		 << n <<endl;
    return 0;
}
