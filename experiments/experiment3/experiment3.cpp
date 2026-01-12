#include <iostream>
using namespace std;
class Female;
class Male {
    Female*  pWife;
    public:
        Male() {m_buffer[m_sum++] = this;}
        Female* &getWife() {return pWife;} 
        static  Male* m_buffer[100];  
        //存放当前产生的所有Male类对象。
        static  int m_sum;
};

class Female {
    //无，去掉Male*   pHusband;
    public:
        Male * getHusband();
    // 其它定义不变
};

int Male::m_sum = 0;
Male * Male::m_buffer[100];

Male* Female::getHusband() {
  for (int i = 0; i < Male::m_sum;i++)
     if (Male::m_buffer[i]->getWife() == this)
       return Male::m_buffer[i]; 
  return 0;
}

int main() {
    /*类的调用*/
    Male a,b;  Female c,d;    
    a.getWife()=&c;
    b.getWife()=&d;
    cout << &a <<endl
         <<c.getHusband() << endl
         << &b << endl
         << d.getHusband();
    return 0;
}
