#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#define N 100   //ÿ��������ı�N��ֵ 
double avg[6];
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
	return y+70*(m+12*(d+31*(h+23*(n+59*s)))); //����һ����ʼ���� 
}
void Schrage(int I){
	FILE *fp;
	fp = fopen("data.txt","w"); 
	int a=16807,m=2147483647,q,r,x;
	q = m / a;
	r = m % a;
	for(int i=1;i<=2*N;++i){   //Schrageȡģ����������������� 
		x = a*(I%q)-r*(I/q);
		if(x<0) x += m;
		I = x;
		fprintf(fp,"%lf\n",(double)I/m);
	}
	fclose(fp);
}
void K_Moment(){
	FILE *fp;
	double x;	
	for(int k=1;k<=4;++k){
		fp = fopen("data.txt","r");
		avg[k]=0;
		while(fscanf(fp,"%lf",&x)!=EOF)  //����k�׾� 
			avg[k] += pow(x,k);			//x^{k}��� 
		avg[k] /= 2*N;					//�������� 
		printf("k=%d,avg(x^k)=%lf\n",k,avg[k]);	
		fclose(fp);
	}	
}
void C_l(){
	int n =2*N+2;
	double *X = (double*)malloc(n * sizeof(double));
	FILE *fp;
	double x,avg_nl,Cl;
	int p=0;
	fp = fopen("data.txt","r");	
	while(fscanf(fp,"%lf",&x)!=EOF)
		X[++p]=x;	
	fclose(fp);
	for(int l=1;l<=8;l++){				//ȡ10^8������������ϵ��C(l) 
		avg_nl = 0;
		for (int i=1;i<=2*N-l;i++)
			avg_nl += X[i] * X[i+l];
		avg_nl /= (2*N-l);
		Cl = (avg_nl-pow(avg[1],2))/(avg[2]-pow(avg[1],2));//���빫ʽ 
		printf("l=%d,C(l)=%lf\n",l,Cl);	
	}
}
int main(){
	int I;
	I = GetSeed();//���ݿα�������������ķ����õ���ʼ����I_{0} 
	Schrage(I);//ʹ��Schrage����ȡģ 
	K_Moment();//����k�׾� 
	C_l();//ȡ10^8������������ϵ��C(l) 
}
