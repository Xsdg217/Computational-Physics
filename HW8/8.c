#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h> 

#define EV1 2.689521304816739  //Exact Value 1
#define EV2 5.644080000000002  //Exact Value 2

int GetSeed(){   //根据课本上随机数产生的方法得到I_{0}，作为16807随机数产生器的初始种子
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
long double Problem1(int I,int N){
    //计算积分\int_{0}^{2} d x \sqrt{x+\sqrt{x}} 
    int L = 0,R = 2;
	int t,a=16807,m=2147483647,q,r;
    double x,sum_fx=0;
    for(int i=1;i<=N;++i){
		t = a*(I%q)-r*(I/q);
		if(t<0) t += m;
		I = t; 
        x = (double)I/m*(R-L);                  //得到[0,2]区间内的随机数
        sum_fx += sqrt(x+sqrt(x));
    }
    return sum_fx*(R-L)/N;  //返回sum*(b-a)/N 
}
long double Problem2(int I,int N){
	//计算积分\int_{0}^{9 / 10} d x \int_{0}^{4 / 5} d y \int_{0}^{9 / 10} d z \int_{0}^{2} d u \int_{0}^{13 / 10} d v\left(6-x^{2}-y^{2}-z^{2}-u^{2}-v^{2}\right) 
	int t,a=16807,m=2147483647,q=127773,r=2836;
    double x,y,z,u,v;
	double sum=0;
    for(int i=1;i<=N;++i){
		t = a*(I%q)-r*(I/q);
		if(t<0) t += m;
		I = t; 
        x = (double)I/m*(0.9);                  //得到[0,9/10]区间内的随机数x
        t = a*(I%q)-r*(I/q);
		if(t<0) t += m;
		I = t; 
		y = (double)I/m*(0.8);                  //得到[0,4/5]区间内的随机数y
		t = a*(I%q)-r*(I/q);
		if(t<0) t += m;
		I = t; 
		z = (double)I/m*(0.9);                  //得到[0,9/10]区间内的随机数z
		t = a*(I%q)-r*(I/q);
		if(t<0) t += m;
		I = t; 
		u = (double)I/m*(2.0);                  //得到[0,2]区间内的随机数u
		t = a*(I%q)-r*(I/q);
		if(t<0) t += m;
		I = t; 
		v = (double)I/m*(1.3);                  //得到[0,13/10]区间内的随机数v
        sum += 6-pow(x,2)-pow(y,2)-pow(z,2)-pow(u,2)-pow(v,2); //计算(6-x^{2}-y^{2}-z^{2}-u^{2}-v^{2})的值并累加 
    }
    return (0.9)*(0.8)*(0.9)*(2.0)*(1.3)/N*sum;   //返回sum*(b1-a1)*(b2-a2)*...(b5-a5)/N 
}
int main(){
    double ans1,ans2;
    for(int N=100;N<=10000000;N=N*10){//N取10^2到10^7 
    	printf("N=%d \n",N);
    	ans1 = Problem1(GetSeed(),N);//第一题，其中 GetSeed() 是根据课本上随机数产生的方法得到I_{0}，作为16807随机数产生器的初始种子
    	printf("ans1=%llf DS1=%llf\n",ans1,fabs(ans1/2-EV1/2));
    }
    printf("\n");
    double V = 0.9*0.8*0.9*2*1.3; 
    for(int N=100;N<=10000000;N=N*10){
    	printf("N=%d \n",N);
    	ans2 = Problem2(GetSeed(),N);//第二题
    	printf("ans2=%llf DS2=%llf\n",ans2,fabs(ans2/V-EV2/V));
	}
    return 0;
}

