#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#define N 100   //每次在这里改变N的值 
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
	return y+70*(m+12*(d+31*(h+23*(n+59*s)))); //返回一个初始种子 
}
void Schrage(int I){
	FILE *fp;
	fp = fopen("data.txt","w"); 
	int a=16807,m=2147483647,q,r,x;
	q = m / a;
	r = m % a;
	for(int i=1;i<=2*N;++i){   //Schrage取模方法产生随机数序列 
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
		while(fscanf(fp,"%lf",&x)!=EOF)  //计算k阶矩 
			avg[k] += pow(x,k);			//x^{k}求和 
		avg[k] /= 2*N;					//除以总数 
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
	for(int l=1;l<=8;l++){				//取10^8个点计算自相关系数C(l) 
		avg_nl = 0;
		for (int i=1;i<=2*N-l;i++)
			avg_nl += X[i] * X[i+l];
		avg_nl /= (2*N-l);
		Cl = (avg_nl-pow(avg[1],2))/(avg[2]-pow(avg[1],2));//代入公式 
		printf("l=%d,C(l)=%lf\n",l,Cl);	
	}
}
int main(){
	int I;
	I = GetSeed();//根据课本上随机数产生的方法得到初始种子I_{0} 
	Schrage(I);//使用Schrage方法取模 
	K_Moment();//计算k阶矩 
	C_l();//取10^8个点计算自相关系数C(l) 
}
