#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define Init_Seed 1950975620   //用于产生随机数的初始种子 
#define N 10000 //N为取点数 
#define M 1000000 //M为模拟步数
#define v0 500 //初始速度范围 
#define mp 1.67e-27 //粒子质量
#define k 1.38e-23//玻尔兹曼常数 
#define h 200.0//速度改变步长
 
int a=16807,m=2147483647,q=127773,w=2836; 
int Random(int I){//16807随机数产生器 
	int t;
	t = a*(I%q)-w*(I/q);
	if(t<0) t += m;
	return t;
}
int I,pos,count=0,avg=0,avg2=0;
double E,Ed,deltaE,v_cur,v_new,T;
double v[N+1];//v为粒子的速度 
int main(){
	FILE *fp;
	fp = fopen("data_velocity.txt","w");
	//fp = fopen("data_temperature.txt","w");
	//fp = fopen("data_demonE.txt","w");
	//fp = fopen("data_p_Ed.txt","w");
	//fp = fopen("data_velocity_h_500.txt","w");
	//fp = fopen("data_E.txt","w");
	I = Random(Init_Seed);//获取随机数 
	Ed = 0;//初始demon为0 
	for(int i=0;i<N;++i){
		v[i] = (double)I/m * v0 * 2 - v0;//随机速度 
		I = Random(I); 
		E += 0.5 * v[i] *v[i] ;//总能求和 
		T += mp*v[i]*v[i]/k;
	} 
	T /= N;//计算初始温度 
	for(int i=0;i<M;++i){
		pos = I % N;//随机选取一个粒子 
		I = Random(I);
		v_cur = v[pos];//当前速度 
		v_new = v_cur + h * ((double)I/m *2 - 1);//改变后的速度 
		I = Random(I);
		deltaE = 0.5*(v_new*v_new - v_cur*v_cur);//能量改变量 
		//printf("%lf %lf\n",v_new,v_cur);
		if(deltaE<=0||deltaE>0&&deltaE<Ed) {//接受改变的情况，否则无操作 
			v[pos] = v_new;
			Ed -= deltaE;
			E += deltaE;
			count++;//accept+1 
			T = T - mp*(v_cur*v_cur)/(k*N) + mp*(v_new*v_new)/(k*N);//温度改变 
		}
		//输出温度/总能/demon能/demon分布 
		//if(i%1000==0) fprintf(fp,"%d %lf\n",i,T);
		//if(i%1000==0) fprintf(fp,"%d %e\n",i,E*mp);
		//if(i%1000==0) fprintf(fp,"%d %e\n",i,Ed*mp);
		//if(i%10==0)fprintf(fp,"%e\n",Ed*mp);
	}
	double avg,avg2 =0;
	for(int i=0;i<N;++i){//计算平均值和平方平均值，以及输出速度分布 
		avg += fabs(v[i]);
		avg2 += v[i] * v[i];
		fprintf(fp,"%lf\n",v[i]);
	}
	avg /= N;
	avg2 /= N;
	//输出速度平均值，接受的几率，总能，demon能，温度 
	printf("v_avg=%lf, accept rate=%.3lf, E=%e, Ed=%e, T=%lf\n",avg,(double)count/M,mp*E,mp*Ed,mp*avg2/k); 
	fclose(fp);
	return 0; 
}
