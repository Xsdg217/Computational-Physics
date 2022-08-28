#include<stdio.h>
#include<math.h>
#define pi 3.1415926
#define initx 0.1
double x;
double a,b,h;
int num;   
int iteration_times = 100000;
void finite_iteration(double lambda,int n){
	FILE *ffp;
	//ffp = fopen("data3.txt","w");
	//ffp = fopen("data4.txt","w");
	ffp = fopen("data5.txt","w");
	x = initx;
	for(int i=1;i<=n;++i){
		x = lambda*sin(pi*x);
		fprintf(ffp,"%d %lf\n", i, x);   
	}
	fclose(ffp);
	return;
}
int main() {
	FILE *fp;
	
	//fp = fopen("data1.txt","w");//data1���ݣ�[a,b,h,num]=[0,10,0.01,150] 
	//fp = fopen("data2.txt","w");//data2���ݣ�[a,b,h,num]=[0,1,0.001,150] 
	//fp = fopen("data6.txt","w");//data6���ݣ�[a,b,h,num]=[0.719,0.866,0.0001,300] 
	///fp = fopen("data7.txt","w");//data7���ݣ�[a,b,h,num]=[0.855,0.866,0.00001,300] 
	fp = fopen("data.txt","w");
	printf("Input a,b,h,num:");//����lambda��Χ[a,b],����h,��ͼ��ĸ���num 
	scanf("%lf %lf %lf %d", &a,&b,&h,&num);
	
	for(double lambda=a;lambda<=b;lambda+=h){
		x = initx;//x����ֵ 
		for(int i=1;i<=iteration_times;i++)//���и����������� 
			x = lambda*sin(pi*x);
		for(int i=1;i<=num;++i){//���num�ε������ 
			x = lambda*sin(pi*x);
			fprintf(fp,"%lf %lf\n", lambda, x);   
		}
	}
	fclose(fp);
	
	//������в�ͬlambdaֵ��ǰn�ε���
	//finite_iteration(0.5,20);
	//finite_iteration(0.73,50);
	//finite_iteration(0.98,60);
	return 0;
}
