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
	return y+70*(m+12*(d+31*(h+23*(n+59*s))));  //����һ����ʼ���� 
}
void Schrage(int I){
	int a=16807,m=2147483647,q,r,x;
	q = m / a;
	r = m % a;
	for(int i=1;i<=N;++i){
		x = a*(I%q)-r*(I/q);
		if(x<0) x += m;
		I = x;
		A[i] = (double)I/m;	//A[i]�洢16807������һϵ�е������ 
	}
}
void Proportion(){
	int num=0;
	for (int i=2;i<=N-1;++i){
		if(A[i-1]<A[i+1]&&A[i+1]<A[i])num++;		
	}
	double pro_1 = (double )num/(N-2);// pro_1��16807��������������������ϵʽ�ı��� 
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
		C[i]=I;//��ͬ�෨����ǰ250����ʼֵ��
	}		
	// �ӷ� 
	for(int i=P+1;i<=N;++i)
		B[i]= (B[i-P] + B[i-Q]) % m; //Finonacci�ӳٲ������������� 		
	int num=0;
	for (int i=2;i<=N-1;++i){
		if(B[i-1]<B[i+1]&&B[i+1]<B[i])num++;		
	}
	double pro_2 = (double )num/(N-2);// pro_2��Fibonacci�ӳٲ�������������������ϵʽ�ı��� 
	printf("%lf,%lf\n",pro_2,pro_2-E_value);
	
	//XOR 
	for(int i=P+1;i<=N;++i)
		C[i]= (C[i-P] ^ C[i-Q]) % m; //Finonacci�ӳٲ������������� 			
	num=0;
	for (int i=2;i<=N-1;++i){
		if(C[i-1]<C[i+1]&&C[i+1]<C[i])num++;		
	}
	double pro_3 = (double )num/(N-2);// pro_3��Fibonacci�ӳٲ�������������������ϵʽ�ı��� 
	printf("%lf,%lf\n",pro_3,pro_3-E_value);
}
int main(){
	unsigned int I_0;
	printf("N = %d\n",N);
	I_0 = GetSeed();//���ݿα�������������ķ����õ���ʼ����I_{0} 
	Schrage(I_0);//Schrageȡģ ʹ��16807������������õ������
	Proportion(); //��16807��������������������������ϵ�ı���
	Fibonacci(I_0);//Fibonacci�ӳٲ����������������� 
}
