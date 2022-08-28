#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

#define Init_Seed 1950975620   //���ڲ���������ĳ�ʼ���� 
#define alpha 1.5 //alpha
#define beta 2//beta
#define N 1000000 //NΪȡ���� 

double x[N];
int a=16807,m=2147483647,q=127773,w=2836; 
int Random(int I){//16807����������� 
	int t;
	t = a*(I%q)-w*(I/q);
	if(t<0) t += m;
	return t;
}
double min(double x1,double x2){return x1>x2?x2:x1;}//����x1 x2�е�min 
void x_data_output(double gamma){//���gammaֵ�µ�x������ 
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
		x_t = -gamma*log(R1);//���ɷ��� 
		r = pow(x_t/x[i],alpha-1)*exp(-(x_t-x[i])/beta)*exp((x_t-x[i])/gamma);//r���ݸ����Ĺ�ʽ���� 
		I =Random(I);
		R2 = (double)I/m;
		if(R2<min(1,r)){//R2<min(1,r)��ѡȡ������count+1
			x[i+1] = x_t;
			count++;
		}	
		else 
			x[i+1] = x[i];
		fprintf(fp,"%lf\n",x[i+1]);//����ó����� 
	}
	fclose(fp);
}
int main() {
	FILE *fp;
	//fp = fopen("data1.txt","w");//gammaȡֵ��[0,40] 
	fp = fopen("data2.txt","w"); //gammaȡֵ��[0,10] 
	for(double gamma = 0.1;gamma<=10;gamma+=0.1){
		double I = Init_Seed;
		double R1,R2;//��������� 
		double x_t,r;//xt���¹��������r��p(xt)/p(xi) 
		double count = 0;//����ѡ��Ч�ʵ�count�� 
		x[0] = 1;
		for(int i=0;i<N;++i){
			I = Random(I);
			R1 = (double)I/m;
			x_t = -gamma*log(R1);//���ɷ��� 
			r = pow(x_t/x[i],alpha-1)*exp(-(x_t-x[i])/beta)*exp((x_t-x[i])/gamma);//r���ݸ����Ĺ�ʽ���� 
			I =Random(I);
			R2 = (double)I/m;
			if(R2<min(1,r)){//��R2<min(1,r)��ѡȡ������count+1 
				x[i+1] = x_t;
				count++;
			}	
			else 
				x[i+1] = x[i];
		}
		double ans = 0,percent;//ans�ǻ���ֵ��percent�������� 
		for(int i=1;i<=N;++i)
			ans += (x[i]-alpha*beta)*(x[i]-alpha*beta);
		ans /= N;
		percent = fabs(ans-alpha*beta*beta)/(alpha*beta*beta);	
		fprintf(fp,"%g %lf %lf%% %lf\n",gamma,ans,percent*100,(double)count/N);	//�����gamma������I�������Ч�� 
	}
	fclose(fp);
	//x_data_output(0.3);
	//x_data_output(3);
	//x_data_output(300);
	return 0;
}
