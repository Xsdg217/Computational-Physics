//����2,4,8,16,32,64�����ڷֲ���lambdaֵ 
#include<stdio.h>
#include<math.h>
#include<float.h>
#define pi 3.1415926
#define M 129
#define initx 0.1
#define eps 0.000001
double x;
double a,b,h;   
int T;
double ans;
int iteration_times = 100000;//��������Ϊ10^5 
int main() {
	double old_x;
	printf("Input a,b and T.T means the length of the cycle:T to 2T.\n");//������ΧΪ[a,b]���ҵ���T��2T�ķֲ� 
	scanf("%lf %lf %d",&a,&b,&T);
	h = 0.000001;//�������� 
	ans=0;
	for(double lambda=a;lambda<=b;lambda+=h){
		x = initx;//x����ֵ 
		for(int i=1;i<=iteration_times;i++)//���и����������� 
			x = lambda*sin(pi*x);
		old_x = x;//��¼��ǰ��xֵ����ȶ� 
		for(int i=1;i<=M;++i){
			x = lambda*sin(pi*x);
			if(i==T&&fabs(x-old_x)>=eps&&ans==0)//�ֲ�ʱx!=old_x 
			{
				ans = lambda;
				printf("lambda_m %lf\n",ans);
				return 0;
			}
		}
	}
}
/*
Input             Output
0.7197 0.72 1 --> 0.719942
0.8330 0.85 2 --> 0.833258
0.850  0.86 4 --> 0.858606
0.863  0.87 8 --> 0.864083
0.865  0.88 16 --> 0.865259
0.865  0.88 32 --> 0.865511
*/
