#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#define PI 3.1415926
#define N 500000//N个取点 

double LAMBDA = 0.1;//定义步长 

double avg[N+1];

int main(){
	FILE *fp;
	int x;
	double theta,c;//c=cos(theta) 
	double total =0;
	fp=fopen("data_theta_C_calculate","r");//读入main.c产生的数据，注意这里文件名每次后面加数字123 
	for(int i=1;i<=N;++i){
		fscanf(fp,"%d %lf",&x,&theta);
		c = cos(theta); 
		total += c;//将cos函数值求和 
		avg[i]=total/i;//得到自相关函数 
	} 
	fclose(fp);
	fp = fopen("answer.txt","w");//输出产生的数据，注意这里文件名可以每次后面加数字123 
	for(int i=1;i<=N;++i){
		fprintf(fp,"%d %lf\n",i,avg[i]);
	}
	fclose(fp);
	return 0;
}
