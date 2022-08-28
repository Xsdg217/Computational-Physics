#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

#define num 100000//����һ���̶��ķֲ�ȡ�ֲ��ϵ�10^5���� 

int N;

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
double solve(int N,double f_bar,double mu,double sigma){  //���ļ��޶������ʽ 
	return (f_bar-mu)/(sigma/sqrt(N));
}
void  Uniform(int I,int N){      //���ȷֲ� 
	FILE *fp;
	fp = fopen("1.txt","w");
	double sum = 0;
	int a=16807,m=2147483647,q=127773,r=2836,t;
		for(int i=1;i<=num;++i){     //16807����������� 
			for(int k=1;k<=N;++k){
				t = a*(I%q)-r*(I/q);
				if(t<0) t += m;
				I = t;
				sum+= (double)I/m;   //���ȷֲ��ۼӼ��� 
			}
			fprintf(fp,"%lf\n",solve(N,sum/N,0.5,(double)1/12));  //mu=0.5��sigma=1/12 
			sum = 0;
	}
	fclose(fp);	
}
int C(int n,int k){   //�������C[n,k] 
	double ans = 1;
	for(int i=n;i>=n-k+1;i--)
		ans *= i;
	for(int i=1;i<=k;i++)
		ans /= i;
	return ans;
}
void  Bino(int I,int N,int n,double p){  //����ֲ� 
	FILE *fp;
	fp = fopen("2.txt","w");
	double sum = 0,xi;
	double P[10],Y[10];//Y[i]�洢����\sum_{k=0}^{i}P[k] 
	for(int k=0;k<=n;++k)//�������ֲ���P(X=k) 
		P[k] = (double)C(n,k) * pow(p,k) *pow(1-p,n-k);
	Y[0] = P[0];
	for(int i=0;i<n;++i)
		Y[i+1] = Y[i]+P[i+1];   //Ԥ����Y[i] 
	int a=16807,m=2147483647,q=127773,r=2836,t;
		for(int i=1;i<=num;++i){//16807����������� 
			for(int k=1;k<=N;++k){
				t = a*(I%q)-r*(I/q);
				if(t<0) t += m;
				I = t;
				xi = (double)I/m;
				for(int j=0;j<n;++j){
					if(xi>Y[j]&&xi<=Y[j+1])   //�ҵ�xi���ĸ������ڣ�Ȼ���ָ�����sum 
						sum+=(j+1);
				}
			}
			fprintf(fp,"%lf\n",solve(N,sum/N,n*p,sqrt(n*p*(1-p))));//mu = np ,sigma =sqrt(npq) 
			sum = 0;
	}
	fclose(fp);
}
void Exp(int I,int N,double lambda){
	FILE *fp;
	fp = fopen("3.txt","w");
	double sum = 0;
	int a=16807,m=2147483647,q=127773,r=2836,t;
		for(int i=1;i<=num;++i){//16807����������� 
			for(int k=1;k<=N;++k){
				t = a*(I%q)-r*(I/q);
				if(t<0) t += m;
				I = t;
				sum+= -log((double)I/m)/lambda;    //�ۻ��ֲ������ķ����� 
			}
			fprintf(fp,"%lf\n",solve(N,sum/N,1/lambda,1/lambda));//mu= 1/lambda,sigma=1/lambda 
			sum = 0;
	}
	fclose(fp);
}
int main(){
	printf("����N:\n");
	scanf("%d",&N);  //����N 
	Uniform(GetSeed(),N);//[0,1]�Ͼ��ȷֲ�
	Bino(GetSeed(),N,9,0.5);//n=9,p=0.5�Ķ���ֲ� 
	Exp(GetSeed(),N,1);//\lambda=1��ָ���ֲ� 
	return 0;
}
