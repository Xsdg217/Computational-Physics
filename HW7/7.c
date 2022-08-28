#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h> 

#define NUM 114      //data.txt中共有NUM对数据
#define N 10000000   //取10^7个点抽样 

double x[120],px[120],p[120],y[120];//直接抽样所用的存储数组 
int count[120];      //直接抽样中用来计数第k个自变量取过多少次 
double Sigma = 0;


double X[N+1],Y[N+1];//舍选抽样所用的存储数组 
int Count[120];      //舍选抽样中用来计数第k个自变量取过多少次 

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
void Init(){
	FILE *fp;
	fp = fopen("data.TXT","r");
	char s[10];
	fscanf(fp,"%s",s);fscanf(fp,"%s",s);      
	for(int i=1;i<=NUM;++i){							//读取data.txt中的能量和数目数据，分别存储在x[i],px[i]中 
		fscanf(fp,"%s",s);
		x[i] = atoi(s);
		fscanf(fp,"%s",s);
		px[i] = (double)atoi(s);
		Sigma += px[i];								//Sigma是px[i]求和 
	}
	fclose(fp);
	for(int i=1;i<=NUM;++i)
		p[i] = px[i] / Sigma;						//p[i]是概率，这里归一化 
	y[0] = 0;
	y[1] = p[1];
	for(int i=2;i<=NUM;++i)
		y[i] = y[i-1] + p[i];       				//y[i]是累积分布函数 
}
void Direct(int I){
	int a=16807,m=2147483647,q=127773,r=2836,t;
	double xi; 
	for(int i=1;i<=N;++i){   //产生N个[0,1]中均匀分布的点\xi 
		t = a*(I%q)-r*(I/q);
		if(t<0) t += m;
		I = t;
		xi = (double)I/m;
		for(int k=1;k<=NUM;k++)//找到满足$y_{k-1}<\xi\leq y_{k}$的k值 
			if(y[k-1]<xi&&xi<=y[k])
				count[k]++;
	}
	FILE *fp;
	fp = fopen("direct.txt","w");    //将抽样结果导出到direct.txt文件中 
	for(int i=1;i<=NUM;++i)
		fprintf(fp,"%g %d\n",x[i],count[i]);
	fclose(fp);
}
double W(double z){			//返回函数W(z):具体意义在报告中说明了 
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
double F(double x){//返回比较函数F(x) 
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
	for(int i=1;i<=N;++i){   //产生N个[0,1]中均匀分布的点 用于产生X[i] 
		t = a*(I%q)-r*(I/q);
		if(t<0) t += m;
		I = t;
		z = (double)I/m*731762;//产生[0,731762]中均匀分布的点 z
		X[i] = W(z);  //X[i]存横坐标，W(z)是反函数  
	}
	for(int i=1;i<=N;++i){   //产生N个[0,1]中均匀分布的点 用于产生Y[i] 
		t = a*(I%q)-r*(I/q);
		if(t<0) t += m;
		I = t;
		z = (double)I/m;
		Y[i] = z*F(X[i]);
	}
	int Select_Num=0;   //存储选取的个数 
	for(int i=1;i<=N;++i){
		if(Y[i]<px[(int)floor(X[i])-2900+1]){  //在面积区内就选取 
			Select_Num++;
			Count[(int)floor(X[i])-2900+1]++;     //第k个自变量的计数加一
		}		
	}
	FILE *fp;
	fp = fopen("selective.txt","w");    //将抽样结果导出到direct.txt文件中 
	fprintf(fp,"抽样效率=%lf\n",(double)Select_Num/N);
	for(int i=1;i<=NUM;++i)
		fprintf(fp,"%g %d\n",x[i],Count[i]);
	fclose(fp);
} 
int main(){
	Init();
	Direct(GetSeed());
	Selective(GetSeed()); 
}
