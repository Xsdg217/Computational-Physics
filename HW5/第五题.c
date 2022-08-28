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
	return y+70*(m+12*(d+31*(h+23*(n+59*s))));//���س�ʼ���� 
}
void Schrage(int I){
	int a=16807,m=2147483647,q,r,x;
	double u,v;
	q = m / a;
	r = m % a;
	int i = 1;   //i ��ʾ����������(u,v)�ļ��� 
	while(i<=N){
		x = a*(I%q)-r*(I/q);
		if(x<0) x += m;
		I = x;
		u = (double)I/m;
		u = u * 2 - 1;     //�õ�[-1,1]�е�һ�������u 
		x = a*(I%q)-r*(I/q);
		if(x<0) x += m;
		I = x;
		v = (double)I/m;
		v = v* 2 - 1;		//�õ�[-1,1]�е�һ�������v 
		if(u*u+v*v<=1){      //�� r^2<=1 ����������� U[i],V[i]�� 
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
		r_2 = U[i]*U[i] + V[i]*V[i];  //����r^2
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
	I = GetSeed();//���ݿα�������������ķ����õ���ʼ����I_{0} 
	Schrage(I);//16807����������� ������U[i],V[i]
	Marsaglia();//�� U[i],V[i]ת��ΪMarsaglia�����е�(xyz)	
}
