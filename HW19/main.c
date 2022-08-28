#include<stdio.h>
#include<math.h>
#include<string.h>
#define INFTY 10000000 //�����������������޴�ֵ 
#define hbar 1//�������ı�ʾ��hbar ������Ϊ1 
#define M 1//�������ı�ʾ������m������Ϊ1 
#define h 0.0001//���Ƽ���Ĳ��� 
#define L 1.0//������[-L,l] 

double E1,E2;//������Χ 
int opt;//��ż��� 
double psi[20000];//������ 
double y[20000];//Numerov����������滻�� 
double Eleft,Eright,Emid,psiN;//���ַ��õ�������ֵ 
double V(double x){//һά���������� 
	if(x>=-L&&x<=L)return 0;
	return INFTY;
}
double f(double x,double E){//f(x)=2m(V-E)/hbar^2 
	return 2*M*(V(x)-E)/(hbar*hbar);
}
void init(){//psi,y�������㣬����opt��ż�������psi��ֵ 
	memset(psi,0,sizeof(psi));
	memset(y,0,sizeof(y)); 
	if(opt == 1){
		psi[0] = 0;
		psi[1] = 1;
	}
	else{
		psi[0] = 1;
		psi[1] = 1;
	} 
}
double Numerov(double E,int N){//Numerov���� 
	init();
	//����y0��y1 
	y[0] = (1-f(0,E)*h*h/12)*psi[0];
	y[1] = (1-f(h,E)*h*h/12)*psi[1];
	double x;
	x = 0;
	//���Ƽ���y_n,psi_n 
	for(int i=1;i<N;++i){
		x += h;
		y[i+1] = 2*y[i] - y[i-1]+ h*h*f(x,E)*psi[i];
		psi[i+1] = y[i+1] / (1-h*h*f(x+h,E)/12);
	}
	//���ر߽紦�Ĳ�����ֵ 
	return psi[N];
}
void reset(int N){
	//��Eleft,Eright����Ϊ����ʱ��E1,E2 
	Eleft = E1;
	Eright = E2;
	Emid = (Eleft+Eright)/2;
	psiN = Numerov(Emid,N);
}
int main(){
	int N = L/h;
	int cnt = 0;
	//����������Χ 
	printf("Input the range of E:\n");
	scanf("%lf %lf",&E1,&E2);
	//�������ҵĲ�����������ƻ���ż��� 
	printf("Input 1 or 0, means odd or even:\n");
	scanf("%d",&opt);
	
	reset(N);
	//���ַ����� 
	while(fabs(psiN)>0.00001){
		//�����cnt�Ǽ���ѭ������
		//��Ϊ��̬��һ����̬���ڶ�����̬��������̬��Щÿ����̬�ı߽��б������б��
		//����ͳ��cnt��ѭ����һ�������ͱ䷽���������������� 
		cnt++;
		if(cnt==500)reset(N);
		if(cnt>=500){
			if(psiN<0){
				Eleft = Emid;
			}
			else if(psiN>0){
				Eright = Emid;
			}
			Emid = (Eleft+Eright)/2;
			psiN = Numerov(Emid,N);
		}
		else {
			if(psiN>0){
				Eleft = Emid;
			}
			else if(psiN<0){
				Eright = Emid;
			}
			Emid = (Eleft+Eright)/2;
			psiN = Numerov(Emid,N);
		}
	}
	printf("%lf ,%lf\n",Emid,psiN);//����ҵ�����������ֵ��߽紦��������ֵ 
	//�������������ͼ�� 
	FILE *fp =fopen("data.txt","w");
	double x;
	double sum = 0;
	//sum��������һ�ĳ��� 
	for(int i=1;i<=N;++i)
		sum += psi[i]*h*psi[i];
	sum = sum*2;
	sum = sqrt(sum);
	//��-L��ʼ��� 
	x = -L;
	for(int i=N;i>=0;--i){
		if(opt == 0){
			fprintf(fp,"%lf %lf\n",x,psi[i]/sum);
		}
		else{
			fprintf(fp,"%lf %lf\n",x,-psi[i]/sum);
		}
		x += h;
	}
	for(int i=1;i<=N;++i){	
		fprintf(fp,"%lf %lf\n",x,psi[i]/sum);
		x+=h;
	}
	fclose(fp);
}
