#include <bits/stdc++.h>
using namespace std;

typedef class Bitwise_Operation{
	
	public:
		int bitwise_and(int a,int b){	//按位与 
			return a&b;
		}
		int bitwise_or(int a,int b){	//按位或 
			return a|b;
		}
		int bitwise_xor(int a,int b){	//按位异或 
			return a^b;
		}
		int bitwise_not(int x){			//按位取反 
			return ~x;
		}
		int left_shift(int x,int n){	//左移 
			return x<<n;
		}
		int right_shift(int x,int n){	//右移 
			return x>>n;
		}
}B_O;

class Calculator{
	public:
		int add(int a,int b);
		int subtract(int a,int b);
		int multiply(int a,int b);
};

int Calculator::add(int a,int b){		//模拟加法 
	int sum,carry;
	sum=a^b; 
	carry=(a&b)<<1;			//记录进位 
	while(carry){			//若进位非零,则不断做加法 
		a=sum;
		b=carry;
		sum=a^b;
		carry=(a&b)<<1;
	}
	return sum;
}

int Calculator::subtract(int a,int b){	//模拟减法 
	return add(a,~b+1);		//把减法转化为加法 
}

int Calculator::multiply(int a,int b){	//模拟乘法 
	
	int sign=1;				//记录符号 
	if(a<0)	a=~a+1,sign=~sign+1;
	if(b<0)	b=~b+1,sign=~sign+1;
	
	int ans=0;
	int i=0;
	while(i<b)				//乘法转化为加法 
		ans=add(ans,a),i=add(i,1);
	
	if(sign<0)				//判断符号 
		ans=~ans+1;
	return ans;
}

void test_BO(){				//测试位运算
	B_O bo;
	int x,y;
	cout<<"请输入两个数以测试位运算:";
	cin>>x>>y;
	cout<<x<<" & "<<y<<" = "<<bo.bitwise_and(x,y)<<endl;
	cout<<x<<" | "<<y<<" = "<<bo.bitwise_or(x,y)<<endl;
	cout<<x<<" ^ "<<y<<" = "<<bo.bitwise_xor(x,y)<<endl;
	cout<<"~ "<<x<<" = "<<bo.bitwise_not(x)<<endl;
	cout<<"~ "<<y<<" = "<<bo.bitwise_not(y)<<endl;
	cout<<x<<" << "<<y<<" = "<<bo.left_shift(x,y)<<endl;
	cout<<x<<" >> "<<y<<" = "<<bo.right_shift(x,y)<<endl<<endl;
}

void test_calculator(){		//测试十进制加减乘法
	Calculator cal;
	int x,y;
	cout<<"请输入两个数以测试十进制加减乘法:";
	cin>>x>>y;
	cout<<x<<" + "<<y<<" = "<<cal.add(x,y)<<endl;
	cout<<x<<" - "<<y<<" = "<<cal.subtract(x,y)<<endl;
	cout<<x<<" * "<<y<<" = "<<cal.multiply(x,y)<<endl<<endl;
}

int main(){
	test_BO();
		//测试位运算 
	
	test_calculator();
		//测试十进制加减乘法
	
	return 0;
}

