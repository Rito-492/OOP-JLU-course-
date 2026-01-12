#include <iostream>
#include <windows.h>
#include <thread>
using namespace std;

void fun1() {
    string a;
    cin >> a;
    if (a == "fun1")
    cout << a << endl;
}

void fun2() {
    string a;
    cin >> a;
    if (a == "fun2")
        cout << a << endl;
}

int main() {
    thread t1(fun1);
    thread t2(fun2);
    t1.join();
    t2.join();
    return 0;
}