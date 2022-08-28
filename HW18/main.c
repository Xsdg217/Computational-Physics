#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#define Init_Seed 1052319784 //初始种子 
#define BOXCOUNT_R 9//盒计数法的上限Range
#define SANDBOX_R  450 //sandbox法的上限Range 
#define M 512       //二维平面是512*512的
 
int curnum=1;//curnum是当前已经聚集的粒子个数
int totalnum;//totalnum是要聚集的粒子个数 
int map[M+2][M+2] = {};//map即该研究的二维平面，粒子存在的位置为1，无粒子存在为0 
typedef struct particle{//定义粒子的状态：坐标(x,y) 
	int x;
	int y;
}particle;
int I;

//16807随机数产生器
int a=16807,m=2147483647,q=127773,w=2836; 
int Random(){ 
	I = a*(I%q)-w*(I/q);
	if(I<0) I += m;
	return I;
}


//随机游走一步 
particle Random_Walk(particle p) {
	int index = Random() % 4;
	switch(index){
		case 0: p.x++;break;
		case 1: p.x--;break;
		case 2: p.y++;break;
		case 3: p.y--;break;
	}
	return p;
}

//随机在边界上生成一个粒子
particle Random_Generation(){
	int index = Random() % 4;
	particle p;
	switch(index){
		case 0: {
			p.x = Random()%M+1;
			p.y = 1;
			break;
		}
		case 1: {
			p.x = M;
			p.y = Random()%M+1;
			break;
		}
		case 2: {
			p.x = Random()%M+1;
			p.y = M;
			break;
		}
		case 3: {
			p.x = 1;
			p.y = Random()%M+1;
			break;
		}
	}
	return p;
}

//检查当前粒子的状态：0：在生成的路上；1：聚集；2：出界舍弃
int Check(particle p){
	int x=p.x;
	int y=p.y;
	if(x<1||y<1||x>M||y>M) return 2;//出界 
	if(map[x][y+1]||map[x][y-1]||map[x+1][y]||map[x-1][y]) return 1;//聚集 
	return 0;
} 

//盒计数法 
int find1(int n){ 
	int i,j,ii,jj;
	int flag;
	int range = M/n;
	int count = 0;
	//分块 
	for(i=1;i<=M;i+=range){
		for(j=1;j<=M;j+=range){
            flag = 0;
            //在(i,j)块中用ii,jj作为坐标索引遍历 
            for(ii=i;ii<i+range;ii++){
                for(jj=j;jj<j+range;++jj){
                    if(map[ii][jj]){
                        flag = 1;
                        break;
                    }
                }
                if(flag){
                    count++;
                    break;
                }
            }
        }
    }
    return count;
}
void BoxCount(){
	double N[BOXCOUNT_R+2];
	for(int i=0;i<=BOXCOUNT_R;++i){
		N[i] = find1(pow(2,i));// epsilon 取 2^i 
	}
	FILE *fp1;
	fp1 = fopen("boxcount.txt","w");
	for(int i=0;i<=BOXCOUNT_R;++i){//输出双对数图 
		fprintf(fp1,"%lf %lf\n",log(pow(2,i)),log(N[i]));
	} 
	fclose(fp1);
} 

//Sandbox 计数
int find2(int r){//查找以r的框内有多少粒子 
	int startx,starty,endx,endy;//起始位置，结束位置 
    int i,j;
    int count = 0;
    startx = (M/2)-(r/2);
    starty = (M/2)-(r/2);
    endx = (M/2)+(r/2);
    endy = (M/2)+(r/2);
    //统计map中存在的粒子数 
    for(i=startx;i<=endx;++i)
    	for(j=starty;j<=endy;++j)
    		count+=map[i][j];
    return count;
}
void Sandbox(){
	double N[SANDBOX_R+2];
	for(int i=1;i<=SANDBOX_R;i+=4){
		N[i] = find2(i);//查找以i为r的框内有多少粒子 
	}
	FILE *fp2;
	fp2 = fopen("sandbox.txt","w");
	for(int i=1;i<=SANDBOX_R;i+=4){//输出双对数图 
		fprintf(fp2,"%lf %lf\n",log(i),log(N[i]));
	} 
	fclose(fp2);
}

int main() {
	FILE *fp;
	//fp = fopen("map_1000.txt","w");
	//fp = fopen("map_5000.txt","w");
	fp = fopen("map_11000.txt","w");
	//fp = fopen("map_12500.txt","w");
	printf("Please input the number of the particles to gather:\n");
	scanf("%d",&totalnum);
	I = Init_Seed; 
	map[M/2][M/2] = 1;//在正方形的正中央放置一个粒子作为生长核心 
	int count = 0;
	while (curnum<totalnum){
		particle p = Random_Generation();//生成一个新粒子
		count++;
		int flag = 1;//判断循环的flag 
		while(flag) {
			//printf("%d\n",Check(p));
			if(Check(p)==0){//如果p粒子没有逃离也没有聚集 
				p = Random_Walk(p);//继续RW 
				//printf("%d :%d :%d %d\n",curnum,count,p.x,p.y);
			}
			else if(Check(p)==1){//如果p聚集到核心 
				curnum++;//数目加一 
				map[p.x][p.y]=1;
				//printf("%d %d\n",p.x,p.y);
				//当前到哪个粒子了 
				if(curnum*100%totalnum==0)
					printf("%d particles are ok!\n",curnum);
				flag = 0;
			} 
			else{//如果p粒子被舍弃 
				flag = 0; //退出循环 
			} 
		}		
	}
	
	BoxCount();//盒计数法 
	Sandbox();//sandbox计数法
	
	//输出map 
	for(int i=1;i<=M;++i)
		for(int j=1;j<=M;++j)
			if(map[i][j])
				fprintf(fp,"%d %d\n",i,j);
	fclose (fp);
	return 0;
}
