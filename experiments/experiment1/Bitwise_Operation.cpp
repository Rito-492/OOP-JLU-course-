#include <bits/stdc++.h>
using namespace std;

#define LEN 32

typedef class Bitwise_Operation{
	
	public:
		void print();
			//以位模式输出a,b,ans,用于调试 
		int bitwise_and(int a,int b);
			//与运算 
		int bitwise_or(int a,int b);
			//或运算 
		int bitwise_xor(int a,int b);
			//异或运算 
		int bitwise_not(int x);
			//按位取反 
		int left_shift(int x,int n);
			//左移 
		int right_shift(int x,int n);
			//右移 
	
	private:
		int ans,index;
		int a_bit[LEN],b_bit[LEN],ans_bit[LEN];
		
		void true_form(int a,int b);	
			//取原码 
		void ones_complement();
			//取反码 
		void twos_complement();
			//取补码 
		int to_dec();
			//由位模式转为十进制 
	
}B_O;

class Calculator{
	public:
		int add(int a,int b);
			//十进制加法 
		int subtract(int a,int b);
			//十进制减法 
		int multiply(int a,int b);
			//十进制乘法 
	private:
		B_O bo;
};

void B_O::print(){
	cout<<"a:   ";
	for(int i=0;i<LEN;i++)	cout<<a_bit[i];
	cout<<endl
		<<"b:   ";
	for(int i=0;i<LEN;i++)	cout<<b_bit[i];
	cout<<endl
		<<"ans: ";
	for(int i=0;i<LEN;i++)	cout<<ans_bit[i];
	cout<<endl<<endl;
}

void B_O::true_form(int a,int b){
	int i=LEN;
	
	if(a>0)	a_bit[0]=0;
	else	a_bit[0]=1,a=-a;
	
	if(b>0)	b_bit[0]=0;
	else	b_bit[0]=1,b=-b;
	
	while (i>1){
		i--;
		a_bit[i]=a%2;
		b_bit[i]=b%2;
		ans_bit[i]=0;
		a/=2;
		b/=2;
	}
}

void B_O::ones_complement(){
	if(a_bit[0]==1)
		for(int i=1;i<LEN;i++)
			a_bit[i]=(a_bit[i]==1)?0:1;
			
	if(b_bit[0]==1)
		for(int i=1;i<LEN;i++)
			b_bit[i]=(b_bit[i]==1)?0:1;
			
	if(ans_bit[0]==1)
		for(int i=1;i<LEN;i++)
			ans_bit[i]=(ans_bit[i]==1)?0:1;
}

void B_O::twos_complement(){
	if(a_bit[0]==1){
		a_bit[LEN-1]+=1;
		for(int i=LEN-2;i>=0;i--){
			a_bit[i]+=a_bit[i+1]/2;
			a_bit[i+1]%=2;
		}
		a_bit[0]%=2;
	}
	if(b_bit[0]==1){
		b_bit[LEN-1]+=1;
		for(int i=LEN-2;i>=0;i--){
			b_bit[i]+=b_bit[i+1]/2;
			b_bit[i+1]%=2;
		}
		b_bit[0]%=2;
	}
	if(ans_bit[0]==1){
		ans_bit[LEN-1]+=1;
		for(int i=LEN-2;i>=0;i--){
			ans_bit[i]+=ans_bit[i+1]/2;
			ans_bit[i+1]%=2;
		}
		ans_bit[0]%=2;
	}
}

int B_O::to_dec(){
	ans=0,index=1;
	for(int i=LEN-1;i>0;i--){
		ans+=ans_bit[i]*index;
		index*=2;
	}
	if(ans_bit[0]==1)
		ans=-ans;
	return ans;
}

int B_O::bitwise_and(int a,int b){
	
	true_form(a,b);
	ones_complement();
	twos_complement();
	for(int i=LEN-1;i>=0;i--)
		ans_bit[i]=(a_bit[i]==1&&b_bit[i]==1);
	ones_complement();
	twos_complement();
	return to_dec();
}

int B_O::bitwise_or(int a,int b){
	
	true_form(a,b);
	ones_complement();
	twos_complement();
	for(int i=LEN-1;i>=0;i--)
		ans_bit[i]=!(a_bit[i]==0&&b_bit[i]==0);
	ones_complement();
	twos_complement();
	return to_dec();
}

int B_O::bitwise_xor(int a,int b){
	
	true_form(a,b);
	ones_complement();
	twos_complement();
	for(int i=LEN-1;i>=0;i--)
		ans_bit[i]=(a_bit[i]!=b_bit[i]);
	ones_complement();
	twos_complement();
	return to_dec();
}

int B_O::bitwise_not(int x){
	
	true_form(x,0);
	ones_complement();
	twos_complement();
	for(int i=LEN-1;i>=0;i--)
		ans_bit[i]=(a_bit[i]==1)?0:1;
	ones_complement();
	twos_complement();
	return to_dec();
}

int B_O::left_shift(int x,int n){
	true_form(x,0);
	ones_complement();
	twos_complement();
	int i=0;
	while(i+n<LEN)
		ans_bit[i]=a_bit[i+n],i++;
	while(i<LEN)
		ans_bit[i]=0,i++;
	ones_complement();
	twos_complement();
	return to_dec();
}

int B_O::right_shift(int x,int n){
	true_form(x,0);
	ones_complement();
	twos_complement();
	int i=0;
	while(i<n)
		ans_bit[i]=0,i++;
	while(i<LEN)
		ans_bit[i]=a_bit[i-n],i++;
	ones_complement();
	twos_complement();
	return to_dec();
}

int Calculator::add(int a,int b){		//模拟加法 
	
    int result = 0;  
    for (int i = 0; i < LEN; ++i){
        int carry=bo.bitwise_and(a,1)+bo.bitwise_and(b,1);  
        // 计算当前位的和以及进位  
        result = (result << 1) | (carry & 1);  
        // 更新x和y的值，准备下一轮的加法  
        x >>= 1;  
        y >>= 1;  
        // 如果carry大于1，则有进位需要加到x上  
        if (carry > 1) {  
            x |= 1;  
        }  
    }   
    return result;  
}

int Calculator::subtract(int a,int b){	//模拟减法 
	return add(a,add(bo.bitwise_not(b),1));		//把减法转化为加法 
}

int Calculator::multiply(int a,int b){	//模拟乘法 
	int sign=1;				//记录符号 
	if(a<0)	a=add(bo.bitwise_not(a),1),sign=add(bo.bitwise_not(sign),1);
	if(b<0)	b=add(bo.bitwise_not(b),1),sign=add(bo.bitwise_not(sign),1);
	
	int ans=0;
	int i=0;
	while(i<b)				//乘法转化为加法 
		ans=add(ans,a),i=add(i,1);
	
	if(sign<0)				//判断符号 
		ans=add(bo.bitwise_not(ans),1);
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
	//test_BO();
		//测试位运算 
	
	test_calculator();
		//测试十进制加减乘法
	
	return 0;
}

