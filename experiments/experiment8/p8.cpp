#include <iostream>
#include <string>
using namespace std;

class Component {
public:
    virtual ~Component() { }

};

class Department {
    string name;
    string response;
    int num;
public:
    Department() : name("NULL"), response("NULL"), num(0) { }
    Department(string dprtname, string dprtrspn, int dprtnum) : name(dprtname), response(dprtrspn), num(dprtnum) { }
    string getName() { return name; }
    string getResponse() { return response; }
    int getNum() { return num;}
};

class Company {
    string name;
    Department HRD("Human Resources Department", "", 0);
};

int main() {
    
    return 0;
}