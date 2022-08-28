#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#define PI 3.1415926

double LAMBDA = 0.1;//定义步长 
int N=500000;//N个取点 
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


int main(){
	double x=0,y=0,r;
	double xi_1,xi_2,xi_3;
	double theta=0,k;
	printf("input lx ly:\n");//输入纳米棒的长宽 
	double lx,ly;
	scanf("%lf %lf",&lx,&ly);
	printf("input k:\n");//输入液体的粘滞系数 
	scanf("%lf",&k);
	double p = lx/(lx+ly);//取lx的力的概率 
	int I = GetSeed();
	printf("seed:%d\n",I);
	double K = 6*LAMBDA/(k*(lx*lx*lx+ly*ly*ly));//角度变化表达式前面不变的系数记作K 
	FILE *fp1,*fp2;
	
	fp1 =fopen("data_xy.txt","w");
	//计算自相关函数，则写作fp1 =fopen("data_xy_C_calculate.txt","w");
	fp2 =fopen("data_theta.txt","w");
	//计算自相关函数，则写作fp2 =fopen("data_theta_C_calculate.txt","w");
	
	for(int i=1;i<=N;++i){
		xi_1 = (double)I/m;//xi1模拟力在长边or短边 
		I = Random(I);
		xi_2 = (double)I/m;//xi2模拟正方向or负方向 
		I = Random(I);
		//处理平动质心坐标变化 
		if(xi_1<=p){     					//若力作用在lx上 
			r = LAMBDA/(k*sqrt(lx));        //质心平动长度    
			if(xi_2<0.5){
				y -= r*cos(theta);
				x -= r*(-sin(theta));
			}
			else{
				y += r*cos(theta);
				x += r*(-sin(theta));
			}		
		}
		else{								//若力作用在ly上 
			r = LAMBDA/(k*sqrt(ly));        //质心平动长度    
			if(xi_2<0.5){
				x -= r*cos(theta);
				y -= r*sin(theta);
			}
			else{
				x += r*cos(theta);
				y += r*sin(theta);
			}
		}
		//处理角度转动变化
		if(xi_1<=p){
			xi_3 = (double) I/m *lx - lx/2;//xi3模拟力臂(力的作用点的位置) 
			theta += K*sqrt(lx)*xi_3;
		} 
		else{
			xi_3 = (double) I/m *ly - ly/2;
			theta +=K*sqrt(ly)*xi_3;
		}
		if(theta>PI)theta-=2*PI;//若theta超过范围，应纠正回来 
		if(theta<-PI)theta+=2*PI;
		I = Random(I);
		fprintf(fp1,"%lf %lf\n",x,y);
		fprintf(fp2,"%d %lf\n",i,theta);
	} 
	fclose(fp1);
	fclose(fp2);
	return 0;
}
