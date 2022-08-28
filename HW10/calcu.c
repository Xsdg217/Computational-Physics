#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#define PI 3.1415926
#define N 500000//N��ȡ�� 

double LAMBDA = 0.1;//���岽�� 

double avg[N+1];

int main(){
	FILE *fp;
	int x;
	double theta,c;//c=cos(theta) 
	double total =0;
	fp=fopen("data_theta_C_calculate","r");//����main.c���������ݣ�ע�������ļ���ÿ�κ��������123 
	for(int i=1;i<=N;++i){
		fscanf(fp,"%d %lf",&x,&theta);
		c = cos(theta); 
		total += c;//��cos����ֵ��� 
		avg[i]=total/i;//�õ�����غ��� 
	} 
	fclose(fp);
	fp = fopen("answer.txt","w");//������������ݣ�ע�������ļ�������ÿ�κ��������123 
	for(int i=1;i<=N;++i){
		fprintf(fp,"%d %lf\n",i,avg[i]);
	}
	fclose(fp);
	return 0;
}
