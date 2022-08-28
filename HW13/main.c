#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

#define Init_Seed 1950975620   //用于产生随机数的初始种子 
#define alpha 1.5 //alpha
#define beta 2//beta
#define N 1000000 //N为取点数 

double x[N];
int a=16807,m=2147483647,q=127773,w=2836; 
int Random(int I){//16807随机数产生器 
	int t;
	t = a*(I%q)-w*(I/q);
	if(t<0) t += m;
	return t;
}
double min(double x1,double x2){return x1>x2?x2:x1;}//返回x1 x2中的min 
void x_data_output(double gamma){//输出gamma值下的x抽样点 
	FILE *fp;
	fp = fopen("x_data.txt","w"); 
	double I = Init_Seed;
	double R1,R2;
	double x_t,r;
	double count = 0;
	x[0] = 1;
	for(int i=0;i<N/10;++i){
		I = Random(I);
		R1 = (double)I/m;
		x_t = -gamma*log(R1);//生成方法 
		r = pow(x_t/x[i],alpha-1)*exp(-(x_t-x[i])/beta)*exp((x_t-x[i])/gamma);//r根据给出的公式计算 
		I =Random(I);
		R2 = (double)I/m;
		if(R2<min(1,r)){//R2<min(1,r)则选取，计数count+1
			x[i+1] = x_t;
			count++;
		}	
		else 
			x[i+1] = x[i];
		fprintf(fp,"%lf\n",x[i+1]);//输出该抽样点 
	}
	fclose(fp);
}
int main() {
	FILE *fp;
	//fp = fopen("data1.txt","w");//gamma取值在[0,40] 
	fp = fopen("data2.txt","w"); //gamma取值在[0,10] 
	for(double gamma = 0.1;gamma<=10;gamma+=0.1){
		double I = Init_Seed;
		double R1,R2;//两个随机数 
		double x_t,r;//xt是新构造的数，r是p(xt)/p(xi) 
		double count = 0;//计算选择效率的count数 
		x[0] = 1;
		for(int i=0;i<N;++i){
			I = Random(I);
			R1 = (double)I/m;
			x_t = -gamma*log(R1);//生成方法 
			r = pow(x_t/x[i],alpha-1)*exp(-(x_t-x[i])/beta)*exp((x_t-x[i])/gamma);//r根据给出的公式计算 
			I =Random(I);
			R2 = (double)I/m;
			if(R2<min(1,r)){//若R2<min(1,r)则选取，计数count+1 
				x[i+1] = x_t;
				count++;
			}	
			else 
				x[i+1] = x[i];
		}
		double ans = 0,percent;//ans是积分值，percent是相对误差 
		for(int i=1;i<=N;++i)
			ans += (x[i]-alpha*beta)*(x[i]-alpha*beta);
		ans /= N;
		percent = fabs(ans-alpha*beta*beta)/(alpha*beta*beta);	
		fprintf(fp,"%g %lf %lf%% %lf\n",gamma,ans,percent*100,(double)count/N);	//输出：gamma，积分I，相对误差，效率 
	}
	fclose(fp);
	//x_data_output(0.3);
	//x_data_output(3);
	//x_data_output(300);
	return 0;
}
