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
	return y+70*(m+12*(d+31*(h+23*(n+59*s))));//���س�ʼ���� 
}
void Schrage(int I){
	int a=16807,m=2147483647,q,r,x;
	q = m / a;
	r = m % a;
	for(int i=1;i<=N;++i){   //A�洢\xi����������� 
		x = a*(I%q)-r*(I/q);
		if(x<0) x += m;
		I = x;
		A[i] = (double)I/m;
	}
	for(int i=1;i<=N;++i){   //B�洢\eta����������� 
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
		theta = acos(1-2*A[i]);   //����theta��varphi 
		varphi = 2*PI*B[i];
		x = sin(theta)*cos(varphi);   //����ֱ������ϵ��x,y,z 
		y = sin(theta)*sin(varphi);
		z = cos(theta);
		fprintf(fp,"%lf %lf %lf\n",x,y,z);
	}
	fclose(fp);
} 
int main(){
	int I;
	I = GetSeed();//���ݿα�������������ķ����õ���ʼ����I_{0} 
	Schrage(I);//16807����������� 
	trans();//�õ�����\theta��\varphi��Ȼ��ת����ֱ�����굼�����ݻ�ͼ 
}
