#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#define N 1000000
#define E_value 0.166667
double A[N+1];
unsigned int B[N+1],C[N+1];
int GetSeed(){
	int y,m,d,h,n,s;
	time_t timep;
	struct tm *p;
	time(&timep);
	p = gmtime(&timep);
	y = p -> tm_year%100;
	m = p -> tm_mon + 1;
	d = p -> tm_mday;
	h = p -> tm_hour;
	n = p -> tm_min;
	s = p -> tm_sec;
	return y+70*(m+12*(d+31*(h+23*(n+59*s))));  //返回一个初始种子 
}
void Schrage(int I){
	int a=16807,m=2147483647,q,r,x;
	q = m / a;
	r = m % a;
	for(int i=1;i<=N;++i){
		x = a*(I%q)-r*(I/q);
		if(x<0) x += m;
		I = x;
		A[i] = (double)I/m;	//A[i]存储16807产生的一系列的随机数 
	}
}
void Proportion(){
	int num=0;
	for (int i=2;i<=N-1;++i){
		if(A[i-1]<A[i+1]&&A[i+1]<A[i])num++;		
	}
	double pro_1 = (double )num/(N-2);// pro_1是16807产生的随机数序列满足关系式的比重 
	printf("%lf,%lf\n",pro_1,pro_1-E_value);	
}
void Fibonacci(int I){
	unsigned int P=250,Q=103,a=16807,m=2147483647,q,r,x;
	q = m / a;
	r = m % a;
	for (int i=1;i<=P;i++){
		x = a*(I%q)-r*(I/q);
		if(x<0) x += m;
		I = x;
		B[i]=I;
		C[i]=I;//先同余法产生前250个初始值表
	}		
	// 加法 
	for(int i=P+1;i<=N;++i)
		B[i]= (B[i-P] + B[i-Q]) % m; //Finonacci延迟产生后面的随机数 		
	int num=0;
	for (int i=2;i<=N-1;++i){
		if(B[i-1]<B[i+1]&&B[i+1]<B[i])num++;		
	}
	double pro_2 = (double )num/(N-2);// pro_2是Fibonacci延迟产生的随机数序列满足关系式的比重 
	printf("%lf,%lf\n",pro_2,pro_2-E_value);
	
	//XOR 
	for(int i=P+1;i<=N;++i)
		C[i]= (C[i-P] ^ C[i-Q]) % m; //Finonacci延迟产生后面的随机数 			
	num=0;
	for (int i=2;i<=N-1;++i){
		if(C[i-1]<C[i+1]&&C[i+1]<C[i])num++;		
	}
	double pro_3 = (double )num/(N-2);// pro_3是Fibonacci延迟产生的随机数序列满足关系式的比重 
	printf("%lf,%lf\n",pro_3,pro_3-E_value);
}
int main(){
	unsigned int I_0;
	printf("N = %d\n",N);
	I_0 = GetSeed();//根据课本上随机数产生的方法得到初始种子I_{0} 
	Schrage(I_0);//Schrage取模 使用16807随机数产生器得到随机数
	Proportion(); //用16807产生器测试随机数序列中满足关系的比重
	Fibonacci(I_0);//Fibonacci延迟产生随机数并计算比重 
}
