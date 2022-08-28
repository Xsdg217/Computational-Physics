#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#define N 1000 
#define PI 3.1415926
double A[N+1],B[N+1];
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
	q = m / a;
	r = m % a;
	for(int i=1;i<=N;++i){   //A存储\xi的随机数数列 
		x = a*(I%q)-r*(I/q);
		if(x<0) x += m;
		I = x;
		A[i] = (double)I/m;
	}
	for(int i=1;i<=N;++i){   //B存储\eta的随机数数列 
		x = a*(I%q)-r*(I/q);
		if(x<0) x += m;
		I = x;
		B[i] = (double)I/m;
	}
}
void trans(){
	FILE *fp;
	fp = fopen("data.txt","w"); 
	double theta,varphi,x,y,z;
	for(int i=1;i<=N;++i){
		theta = acos(1-2*A[i]);   //计算theta和varphi 
		varphi = 2*PI*B[i];
		x = sin(theta)*cos(varphi);   //计算直角坐标系下x,y,z 
		y = sin(theta)*sin(varphi);
		z = cos(theta);
		fprintf(fp,"%lf %lf %lf\n",x,y,z);
	}
	fclose(fp);
} 
int main(){
	int I;
	I = GetSeed();//根据课本上随机数产生的方法得到初始种子I_{0} 
	Schrage(I);//16807随机数产生器 
	trans();//得到抽样\theta和\varphi，然后转换成直角坐标导出数据画图 
}
