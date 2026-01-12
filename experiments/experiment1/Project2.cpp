#include <bits/stdc++.h>
using namespace std;

#define MAXLEN 5000

typedef class High_Accuracy_Algorithm{
	public:
		void putin(int arr[]);
		int *add(int a[],int b[]);	//高精度加法 
		int *multiply(int a[],int b[]);//高精度乘法
	private:
		int ans[MAXLEN],carry;
		void reset();				//将ans清零 
}HAA;

void HAA :: putin(int arr[]){
	char str[MAXLEN];
	scanf("%s",str);
	arr[0]=strlen(str);
	for(int i=arr[0]-1;i>=0;i--)
		arr[arr[0]-i]=str[i]-'0';
}

void HAA :: reset(){			
	for(int i=0;i<MAXLEN;i++)
		ans[i]=0;
}

int * HAA :: add(int a[],int b[]){
	if(b!=NULL){
		reset();
		int l=max(a[0],b[0]);
		carry=0;
		for(int i=1;i<=l+1;i++){
			ans[i]+=a[i]+b[i]+carry;
			carry=ans[i]/10;
			ans[i]%=10;
		}
		ans[0]=l+(ans[l+1]?1:0);
	}
	else{
		carry=0;
		for(int i=1;i<=a[0]+1;i++){
			ans[i]+=a[i]+carry;
			carry=ans[i]/10;
			ans[i]%=10;
		}
		ans[0]=a[0]+(ans[a[0]+1]?1:0);
	}
	return ans;
}

int * HAA :: multiply(int a[],int b[]){ 
	reset();
	int l=max(a[0],b[0]);
	for(int i=1;i<=a[0];i++){
		carry=0;
		for(int j=1;j<=b[0];j++){
			ans[i+j]+=(a[i]*b[j]+ans[i+j-1])/10;
			ans[i+j-1]=(ans[i+j-1]+a[i]*b[j])%10;
		}
	}
	ans[0]=a[0]+b[0]+(ans[a[0]+b[0]]?0:-1);
	return ans;
}

void test_HAA(){				//测试高精度 
	HAA n;
	int *p,a[MAXLEN],b[MAXLEN];
	fill(a,a+MAXLEN+1,0);
	fill(b,b+MAXLEN+1,0);
	n.putin(a);
	n.putin(b);
	p=n.add(a,b);
	cout<<"和:  ";
	for(int i=p[0];i>0;i--)
		cout<<p[i];
	cout<<endl;
	n.multiply(a,b);
	cout<<"积:  ";
	for(int i=p[0];i>0;i--)
		cout<<p[i];
	cout<<endl;
}

void digit_sum(){				//求整数各位数字之和 
	HAA n;
	int *p,x[MAXLEN],xx[MAXLEN];
	fill(xx,xx+MAXLEN+1,0);
	xx[0]=1;
	cout<<"请输入一个整数以求其各位数字之和:";
	n.putin(x);
	for(int i=1;i<=x[0];i++){
		xx[1]=x[i];
		p=n.add(xx,NULL);
	}
	cout<<"数字和为: ";
	for(int i=p[0];i>0;i--)
		cout<<p[i];
	cout<<endl<<endl<<endl;
}

void factorial_1000(){			//求1000! 
	HAA n;
	int *p,a[MAXLEN],b[MAXLEN],c[MAXLEN];
	fill(a,a+MAXLEN+1,0);
	fill(b,b+MAXLEN+1,0);
	fill(c,c+MAXLEN+1,0);
	a[0]=1;b[0]=1;c[0]=1;
	a[1]=1;b[1]=1;c[1]=1;
	for(int i=1;i<=1000;i++){
		p=n.multiply(a,b);
		for(int i=0;i<=p[0];i++)
			b[i]=p[i];
		p=n.add(a,c);
		for(int i=0;i<=p[0];i++)
			a[i]=p[i];
	}
	cout<<"1000!=";
	for(int i=b[0];i>0;i--)
		cout<<b[i];
}

int main(){
	//test_HAA();			//测试高精度加法和乘法 
	
	digit_sum();			//测试求整数各位和 
	
	factorial_1000();		//测试1000! 
	return 0;
}

