#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h> 

#define NUM 114      //data.txt�й���NUM������
#define N 10000000   //ȡ10^7������� 

double x[120],px[120],p[120],y[120];//ֱ�ӳ������õĴ洢���� 
int count[120];      //ֱ�ӳ���������������k���Ա���ȡ�����ٴ� 
double Sigma = 0;


double X[N+1],Y[N+1];//��ѡ�������õĴ洢���� 
int Count[120];      //��ѡ����������������k���Ա���ȡ�����ٴ� 

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
void Init(){
	FILE *fp;
	fp = fopen("data.TXT","r");
	char s[10];
	fscanf(fp,"%s",s);fscanf(fp,"%s",s);      
	for(int i=1;i<=NUM;++i){							//��ȡdata.txt�е���������Ŀ���ݣ��ֱ�洢��x[i],px[i]�� 
		fscanf(fp,"%s",s);
		x[i] = atoi(s);
		fscanf(fp,"%s",s);
		px[i] = (double)atoi(s);
		Sigma += px[i];								//Sigma��px[i]��� 
	}
	fclose(fp);
	for(int i=1;i<=NUM;++i)
		p[i] = px[i] / Sigma;						//p[i]�Ǹ��ʣ������һ�� 
	y[0] = 0;
	y[1] = p[1];
	for(int i=2;i<=NUM;++i)
		y[i] = y[i-1] + p[i];       				//y[i]���ۻ��ֲ����� 
}
void Direct(int I){
	int a=16807,m=2147483647,q=127773,r=2836,t;
	double xi; 
	for(int i=1;i<=N;++i){   //����N��[0,1]�о��ȷֲ��ĵ�\xi 
		t = a*(I%q)-r*(I/q);
		if(t<0) t += m;
		I = t;
		xi = (double)I/m;
		for(int k=1;k<=NUM;k++)//�ҵ�����$y_{k-1}<\xi\leq y_{k}$��kֵ 
			if(y[k-1]<xi&&xi<=y[k])
				count[k]++;
	}
	FILE *fp;
	fp = fopen("direct.txt","w");    //���������������direct.txt�ļ��� 
	for(int i=1;i<=NUM;++i)
		fprintf(fp,"%g %d\n",x[i],count[i]);
	fclose(fp);
}
double W(double z){			//���غ���W(z):���������ڱ�����˵���� 
	if(z>=0&&z<92000)
		return (z/2000)+2900;
	else
		if(z>=92000&&z<267832)
			return (z-92000)/5672+2946;
		else
			if(z>=267832&&z<301832)
				return (z-267832)/2000+2977;
			else
				if(z>=301832&&z<715762)
					return (z-301832)/37630+2994;
				else
					return (z-715762)/2000+3005;
	
} 
double F(double x){//���رȽϺ���F(x) 
	if(x>=2946&&x<2977)
		return 5672;
	else 
		if(x>=2994&&x<3005)
			return 37630;
		else 
			return 2000;
}
void Selective(int I){
	int a=16807,m=2147483647,q=127773,r=2836,t;
	double z; 
	for(int i=1;i<=N;++i){   //����N��[0,1]�о��ȷֲ��ĵ� ���ڲ���X[i] 
		t = a*(I%q)-r*(I/q);
		if(t<0) t += m;
		I = t;
		z = (double)I/m*731762;//����[0,731762]�о��ȷֲ��ĵ� z
		X[i] = W(z);  //X[i]������꣬W(z)�Ƿ�����  
	}
	for(int i=1;i<=N;++i){   //����N��[0,1]�о��ȷֲ��ĵ� ���ڲ���Y[i] 
		t = a*(I%q)-r*(I/q);
		if(t<0) t += m;
		I = t;
		z = (double)I/m;
		Y[i] = z*F(X[i]);
	}
	int Select_Num=0;   //�洢ѡȡ�ĸ��� 
	for(int i=1;i<=N;++i){
		if(Y[i]<px[(int)floor(X[i])-2900+1]){  //��������ھ�ѡȡ 
			Select_Num++;
			Count[(int)floor(X[i])-2900+1]++;     //��k���Ա����ļ�����һ
		}		
	}
	FILE *fp;
	fp = fopen("selective.txt","w");    //���������������direct.txt�ļ��� 
	fprintf(fp,"����Ч��=%lf\n",(double)Select_Num/N);
	for(int i=1;i<=NUM;++i)
		fprintf(fp,"%g %d\n",x[i],Count[i]);
	fclose(fp);
} 
int main(){
	Init();
	Direct(GetSeed());
	Selective(GetSeed()); 
}
