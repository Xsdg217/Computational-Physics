#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h> 
#define PI 3.1415926
#define N 1000
double U[N+1],V[N+1];
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
	double u,v;
	q = m / a;
	r = m % a;
	int i = 1;   //i 表示满足条件的(u,v)的计数 
	while(i<=N){
		x = a*(I%q)-r*(I/q);
		if(x<0) x += m;
		I = x;
		u = (double)I/m;
		u = u * 2 - 1;     //得到[-1,1]中的一个随机数u 
		x = a*(I%q)-r*(I/q);
		if(x<0) x += m;
		I = x;
		v = (double)I/m;
		v = v* 2 - 1;		//得到[-1,1]中的一个随机数v 
		if(u*u+v*v<=1){      //若 r^2<=1 ，则存入数组 U[i],V[i]中 
			U[i] = u;
			V[i] = v;
			i++;
		}
	} 
}
void Marsaglia(){
	double X[N+1],Y[N+1],Z[N+1],r_2;
	FILE *fp;
	fp = fopen("data.txt","w");
	for(int i=1;i<=N;++i){
		r_2 = U[i]*U[i] + V[i]*V[i];  //计算r^2
		X[i] = 2*U[i] *sqrt(1-r_2);
		Y[i] = 2*V[i] *sqrt(1-r_2);
		Z[i] = 1-2*r_2;
		fprintf(fp,"%lf %lf %lf\n",X[i],Y[i],Z[i]);
		//fprintf(fp,"%lf %lf\n",X[i],Y[i]);
	}
	fclose(fp);
}
int main(){
	int I;
	I = GetSeed();//根据课本上随机数产生的方法得到初始种子I_{0} 
	Schrage(I);//16807随机数产生器 ，产生U[i],V[i]
	Marsaglia();//把 U[i],V[i]转化为Marsaglia方法中的(xyz)	
}
