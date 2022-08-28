#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define Init_Seed 1950975620   //���ڲ���������ĳ�ʼ���� 
#define N 10000 //NΪȡ���� 
#define M 1000000 //MΪģ�ⲽ��
#define v0 500 //��ʼ�ٶȷ�Χ 
#define mp 1.67e-27 //��������
#define k 1.38e-23//������������ 
#define h 200.0//�ٶȸı䲽��
 
int a=16807,m=2147483647,q=127773,w=2836; 
int Random(int I){//16807����������� 
	int t;
	t = a*(I%q)-w*(I/q);
	if(t<0) t += m;
	return t;
}
int I,pos,count=0,avg=0,avg2=0;
double E,Ed,deltaE,v_cur,v_new,T;
double v[N+1];//vΪ���ӵ��ٶ� 
int main(){
	FILE *fp;
	fp = fopen("data_velocity.txt","w");
	//fp = fopen("data_temperature.txt","w");
	//fp = fopen("data_demonE.txt","w");
	//fp = fopen("data_p_Ed.txt","w");
	//fp = fopen("data_velocity_h_500.txt","w");
	//fp = fopen("data_E.txt","w");
	I = Random(Init_Seed);//��ȡ����� 
	Ed = 0;//��ʼdemonΪ0 
	for(int i=0;i<N;++i){
		v[i] = (double)I/m * v0 * 2 - v0;//����ٶ� 
		I = Random(I); 
		E += 0.5 * v[i] *v[i] ;//������� 
		T += mp*v[i]*v[i]/k;
	} 
	T /= N;//�����ʼ�¶� 
	for(int i=0;i<M;++i){
		pos = I % N;//���ѡȡһ������ 
		I = Random(I);
		v_cur = v[pos];//��ǰ�ٶ� 
		v_new = v_cur + h * ((double)I/m *2 - 1);//�ı����ٶ� 
		I = Random(I);
		deltaE = 0.5*(v_new*v_new - v_cur*v_cur);//�����ı��� 
		//printf("%lf %lf\n",v_new,v_cur);
		if(deltaE<=0||deltaE>0&&deltaE<Ed) {//���ܸı������������޲��� 
			v[pos] = v_new;
			Ed -= deltaE;
			E += deltaE;
			count++;//accept+1 
			T = T - mp*(v_cur*v_cur)/(k*N) + mp*(v_new*v_new)/(k*N);//�¶ȸı� 
		}
		//����¶�/����/demon��/demon�ֲ� 
		//if(i%1000==0) fprintf(fp,"%d %lf\n",i,T);
		//if(i%1000==0) fprintf(fp,"%d %e\n",i,E*mp);
		//if(i%1000==0) fprintf(fp,"%d %e\n",i,Ed*mp);
		//if(i%10==0)fprintf(fp,"%e\n",Ed*mp);
	}
	double avg,avg2 =0;
	for(int i=0;i<N;++i){//����ƽ��ֵ��ƽ��ƽ��ֵ���Լ�����ٶȷֲ� 
		avg += fabs(v[i]);
		avg2 += v[i] * v[i];
		fprintf(fp,"%lf\n",v[i]);
	}
	avg /= N;
	avg2 /= N;
	//����ٶ�ƽ��ֵ�����ܵļ��ʣ����ܣ�demon�ܣ��¶� 
	printf("v_avg=%lf, accept rate=%.3lf, E=%e, Ed=%e, T=%lf\n",avg,(double)count/M,mp*E,mp*Ed,mp*avg2/k); 
	fclose(fp);
	return 0; 
}
