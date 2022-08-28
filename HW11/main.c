#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#define num 100000
int a=16807,m=2147483647,q=127773,r=2836; 
int Random(int I){//16807����������� 
	int x;
	x = a*(I%q)-r*(I/q);
	if(x<0) x += m;
	return x;
}
int GetSeed(){//���ݿα�������������ķ����õ���ʼ����I_{0} 
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
	int x[num+1]={0};//��ʼʱ������ԭ�� 
	int res=0;//res�洢����ԭ�����ӵĸ��� 
	double P;//P��ʾ����ԭ��ĸ��� 
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
			if(x[i]==0)//����ԭ���������һ 
				res++; 
		}
		P = (double)res/num;
		if(step%2==0)//�����������ʱ�Ϊ�㣬ֻ���ż������
			fprintf(fp,"%d %lf\n",step,P);
	}
	fclose(fp);
}
void d2(int N){      		//d=2_RW
	int x[num+1]={0};//��ʼʱ������ԭ�� 
	int y[num+1]={0};//��ʼʱ������ԭ��
	int res=0;//res�洢����ԭ�����ӵĸ��� 
	double P;//P��ʾ����ԭ��ĸ��� 
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
			if(x[i]==0&&y[i]==0)//����ԭ���������һ 
				res++; 
		}
		P = (double)res/num;
		if(step%2==0)//�����������ʱ�Ϊ�㣬ֻ���ż������
			fprintf(fp,"%d %lf\n",step,P);
	}
	fclose(fp);
}
void d3(int N){				//d=3_RW
	int x[num+1]={0};//��ʼʱ������ԭ�� 
	int y[num+1]={0};//��ʼʱ������ԭ��
	int z[num+1]={0};//��ʼʱ������ԭ��
	int res=0;//res�洢����ԭ�����ӵĸ��� 
	double P;//P��ʾ����ԭ��ĸ��� 
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
			if(x[i]==0&&y[i]==0&&z[i]==0)//����ԭ���������һ 
				res++; 
		}
		P = (double)res/num;
		if(step%2==0)//�����������ʱ�Ϊ�㣬ֻ���ż������
			fprintf(fp,"%d %lf\n",step,P);
	}
	fclose(fp);
}
int main() {
	d1(800);//һά800�� 
	d2(200);//��ά200�� 
	d3(100);//��ά100�� 
	return 0;
}
