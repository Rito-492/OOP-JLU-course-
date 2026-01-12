#include <iostream>  
using namespace std;
int fun1(int ) {  
    cout << "One parameter: " << 1 << endl;  
    return 1;  
}  
  
int fun2(const int &) {
    cout << "Two parameters: " << 2 <<endl;
    return 2;
}

int main() {
    // 调用一个参数的函数  
    int result1 = fun1(5);  
  
    // 调用两个参数的函数，但只提供一个参数，因为第二个参数有默认值  
    int result2 = fun2(3);
  
    return 0;  
}