#include<stdio.h>
#include<math.h>
#include<string.h>
#define INFTY 10000000 //无限深势阱设置无限大值 
#define hbar 1//方便结果的表示，hbar 可以设为1 
#define M 1//方便结果的表示，质量m可以设为1 
#define h 0.0001//递推计算的步长 
#define L 1.0//势阱宽度[-L,l] 

double E1,E2;//能量范围 
int opt;//奇偶宇称 
double psi[20000];//波函数 
double y[20000];//Numerov方法引入的替换量 
double Eleft,Eright,Emid,psiN;//二分法用到的能量值 
double V(double x){//一维无限深势阱 
	if(x>=-L&&x<=L)return 0;
	return INFTY;
}
double f(double x,double E){//f(x)=2m(V-E)/hbar^2 
	return 2*M*(V(x)-E)/(hbar*hbar);
}
void init(){//psi,y数组清零，根据opt奇偶宇称设置psi初值 
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
double Numerov(double E,int N){//Numerov方法 
	init();
	//计算y0，y1 
	y[0] = (1-f(0,E)*h*h/12)*psi[0];
	y[1] = (1-f(h,E)*h*h/12)*psi[1];
	double x;
	x = 0;
	//递推计算y_n,psi_n 
	for(int i=1;i<N;++i){
		x += h;
		y[i+1] = 2*y[i] - y[i-1]+ h*h*f(x,E)*psi[i];
		psi[i+1] = y[i+1] / (1-h*h*f(x+h,E)/12);
	}
	//返回边界处的波函数值 
	return psi[N];
}
void reset(int N){
	//将Eleft,Eright设置为输入时的E1,E2 
	Eleft = E1;
	Eright = E2;
	Emid = (Eleft+Eright)/2;
	psiN = Numerov(Emid,N);
}
int main(){
	int N = L/h;
	int cnt = 0;
	//输入能量范围 
	printf("Input the range of E:\n");
	scanf("%lf %lf",&E1,&E2);
	//输入想找的波函数是奇宇称还是偶宇称 
	printf("Input 1 or 0, means odd or even:\n");
	scanf("%d",&opt);
	
	reset(N);
	//二分法查找 
	while(fabs(psiN)>0.00001){
		//这里的cnt是计数循环次数
		//因为基态第一激发态、第二激发态第三激发态这些每两个态的边界判别条件有变号
		//所以统计cnt，循环到一定次数就变方向来继续二分搜索 
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
	printf("%lf ,%lf\n",Emid,psiN);//输出找到的能量本征值与边界处波函数的值 
	//下面输出波函数图像 
	FILE *fp =fopen("data.txt","w");
	double x;
	double sum = 0;
	//sum是用来归一的常数 
	for(int i=1;i<=N;++i)
		sum += psi[i]*h*psi[i];
	sum = sum*2;
	sum = sqrt(sum);
	//从-L开始输出 
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
