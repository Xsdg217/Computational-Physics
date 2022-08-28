#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h> 
#define PI 3.1415926
#define N 1000000
#define EPS 1e-4    //二分法的精度 
double Q[N+1]; 
int num=0;   //符合条件y<p(x)点的个数 
int GetSeed(){
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
	return y+70*(m+12*(d+31*(h+23*(n+59*s))));//返回初始种子 
}
double W(double x){  //返回 函数 2*atan(1+sqrt(2)*x)-2*atan(1-sqrt(2)*x)+log((x*x+sqrt(2)*x+1)/(x*x-sqrt(2)*x+1)) / 4*sqrt(2) 的值：[-5,5]到[-1.10806,1.10806] 
	return (2*atan(1+sqrt(2)*x)-2*atan(1-sqrt(2)*x)+log((x*x+sqrt(2)*x+1)/(x*x-sqrt(2)*x+1)))/(4*sqrt(2));
}
double H(double x){      //H(x) = W(x) - W(-5)
	return W(x)-W(-5);
}
double FindRoot(double m,double n,double Value)//二分法求根： 不断的取y(m)和y(n)的值找到接近 Value的 x值为止 
{
	double x,y,yl,yr,l,r;
    l=m;  r=n;
    int c=0;
    do{
        x=(l+r)/2;y=H(x)-Value;
        if(fabs(y)<=1e-4) return x;
        yl=H(l)-Value;//在左区间找根
        yr=H(r)-Value;//在右区间找根 
        if(yl*y<0)  r=x;
        if(yr*y<0)  l=x;
    }while(fabs(y)>1e-4); 
}
double F(double x){			//返回F(x) 
	return 1/(1+pow(x,4));
}
double p(double x){			//返回p(x) 
	return 0.398943*exp(-x*x/2);
} 
void A_R_METHOD(int I){//舍选法抽样 
	int a=16807,m=2147483647,q,r,temp;
	double t;
	double xi_1,xi_2,x,y;
	q = m / a;
	r = m % a;
	for(int i=1;i<=N;++i){		
		temp = a*(I%q)-r*(I/q);
		if(temp<0) temp += m;
		I = temp;
		xi_1 = (double)I/m; //生成[0,1]中的随机数 \xi_1 
		t = xi_1 *H(5);			
		x=FindRoot(-5,5,t); //二分法查找xi_1对应的x 
		
		temp = a*(I%q)-r*(I/q);
		if(temp<0) temp += m;
		I = temp;
		xi_2 = (double)I/m; //生成[0,1]中的随机数 \xi_2
		y = xi_2 * F(x); 
				
		if(y<p(x)){  	//若在p(x)面积区内则把x加入Q数组中 
			num++;
			Q[num] = x;
		}		
	}
	printf("效率为：%lf",(double)num/N);//统计效率 
}
void PrintX(){//输出X 
	FILE *fp;
	fp = fopen("data.txt","w");
	for(int i=1;i<=num;++i){
		fprintf(fp,"%lf\n",Q[i]);
	}
	fclose(fp);
} 
int main(){
	int I;
	I = GetSeed();//根据课本上随机数产生的方法得到初始种子I_{0} 
	A_R_METHOD(I);//舍选法抽样 
	PrintX();//输出数据 
}
