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
double p(double x){     //计算函数值 p(x) 
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
	return y+70*(m+12*(d+31*(h+23*(n+59*s))));//返回初始种子 
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
		xi_2 = (double)I/m;     //获取[0,1]上的随机数\xi_1,\xi_2 
		if(M*xi_2<=p(-5+10*xi_1)){    //对满足条件的(\xi_1,\xi_2)，把 X[i]计入数组 
			X[i] = -5+10*xi_1;
			i++;			
		}
	} 
	FILE *fp;                    //把X[i]导出 
	fp = fopen("data.txt","w");
	for(int i=1;i<N;i++)
		fprintf(fp,"%lf\n",X[i]);
	fclose(fp);
}

int main(){
	int I;
	I = GetSeed();//根据课本上随机数产生的方法得到初始种子I_{0} 
	Schrage(I);//16807随机数产生器 ，产生\xi_1,\xi_2，并舍选法得到 X[i] 
}
