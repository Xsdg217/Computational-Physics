#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h> 
#define PI 3.1415926
#define N 100000
#define M 15
#define C 39.1517
double X[N+1];
int num[200];
double p(double x){     //���㺯��ֵ p(x) 
	double ans;
	ans = sqrt(x*x+x+3)*exp(-3*atan((2*x+1)/sqrt(11))/sqrt(11));
	ans /= C;
	return ans ;
}
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
	return y+70*(m+12*(d+31*(h+23*(n+59*s))));//���س�ʼ���� 
}
void Schrage(int I){
	int a=16807,m=2147483647,q,r,x;
	double xi_1,xi_2;
	q = m / a;
	r = m % a;
	int i = 1 ; 
	while(i<=N){
		x = a*(I%q)-r*(I/q);
		if(x<0) x += m;
		I = x;
		xi_1 = (double)I/m;
		x = a*(I%q)-r*(I/q);
		if(x<0) x += m;
		I = x;
		xi_2 = (double)I/m;     //��ȡ[0,1]�ϵ������\xi_1,\xi_2 
		if(M*xi_2<=p(-5+10*xi_1)){    //������������(\xi_1,\xi_2)���� X[i]�������� 
			X[i] = -5+10*xi_1;
			i++;			
		}
	} 
	FILE *fp;                    //��X[i]���� 
	fp = fopen("data.txt","w");
	for(int i=1;i<N;i++)
		fprintf(fp,"%lf\n",X[i]);
	fclose(fp);
}

int main(){
	int I;
	I = GetSeed();//���ݿα�������������ķ����õ���ʼ����I_{0} 
	Schrage(I);//16807����������� ������\xi_1,\xi_2������ѡ���õ� X[i] 
}
