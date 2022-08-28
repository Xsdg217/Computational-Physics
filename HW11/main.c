#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#define num 100000
int a=16807,m=2147483647,q=127773,r=2836; 
int Random(int I){//16807随机数产生器 
	int x;
	x = a*(I%q)-r*(I/q);
	if(x<0) x += m;
	return x;
}
int GetSeed(){//根据课本上随机数产生的方法得到初始种子I_{0} 
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
	return y+70*(m+12*(d+31*(h+23*(n+59*s))));
}
void d1(int N){				//d=1_RW 
	int x[num+1]={0};//初始时粒子在原点 
	int res=0;//res存储返回原点粒子的个数 
	double P;//P表示返回原点的概率 
	int I = GetSeed();
	FILE *fp;
	fp=fopen("d1.txt","w");
	fprintf(fp,"Initial Seed Value:%d\n",I);
	for(int step=1;step<=N;++step){
		res=0;
		for(int i=1;i<=num;++i){
			I = Random(I);
			if((double)I/m<0.5) x[i]++;
			else x[i]--;
			if(x[i]==0)//若在原点则计数加一 
				res++; 
		}
		P = (double)res/num;
		if(step%2==0)//奇数步数几率必为零，只输出偶数步数
			fprintf(fp,"%d %lf\n",step,P);
	}
	fclose(fp);
}
void d2(int N){      		//d=2_RW
	int x[num+1]={0};//初始时粒子在原点 
	int y[num+1]={0};//初始时粒子在原点
	int res=0;//res存储返回原点粒子的个数 
	double P;//P表示返回原点的概率 
	int I = GetSeed();
	FILE *fp;
	fp=fopen("d2.txt","w");
	fprintf(fp,"Initial Seed Value:%d\n",I);
	for(int step=1;step<=N;++step){
		res=0;
		for(int i=1;i<=num;++i){
			I = Random(I);
			if((double)I/m<0.5) x[i]++;
			else x[i]--;
			I = Random(I);
			if((double)I/m<0.5) y[i]++;
			else y[i]--;
			if(x[i]==0&&y[i]==0)//若在原点则计数加一 
				res++; 
		}
		P = (double)res/num;
		if(step%2==0)//奇数步数几率必为零，只输出偶数步数
			fprintf(fp,"%d %lf\n",step,P);
	}
	fclose(fp);
}
void d3(int N){				//d=3_RW
	int x[num+1]={0};//初始时粒子在原点 
	int y[num+1]={0};//初始时粒子在原点
	int z[num+1]={0};//初始时粒子在原点
	int res=0;//res存储返回原点粒子的个数 
	double P;//P表示返回原点的概率 
	int I = GetSeed();
	FILE *fp;
	fp=fopen("d3.txt","w");
	fprintf(fp,"Initial Seed Value:%d\n",I);
	for(int step=1;step<=N;++step){
		res=0;
		for(int i=1;i<=num;++i){
			I = Random(I);
			if((double)I/m<0.5) x[i]++;
			else x[i]--;
			I = Random(I);
			if((double)I/m<0.5) y[i]++;
			else y[i]--;
			I = Random(I);
			if((double)I/m<0.5) z[i]++;
			else z[i]--;
			if(x[i]==0&&y[i]==0&&z[i]==0)//若在原点则计数加一 
				res++; 
		}
		P = (double)res/num;
		if(step%2==0)//奇数步数几率必为零，只输出偶数步数
			fprintf(fp,"%d %lf\n",step,P);
	}
	fclose(fp);
}
int main() {
	d1(800);//一维800步 
	d2(200);//二维200步 
	d3(100);//三维100步 
	return 0;
}
