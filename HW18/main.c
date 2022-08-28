#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#define Init_Seed 1052319784 //��ʼ���� 
#define BOXCOUNT_R 9//�м�����������Range
#define SANDBOX_R  450 //sandbox��������Range 
#define M 512       //��άƽ����512*512��
 
int curnum=1;//curnum�ǵ�ǰ�Ѿ��ۼ������Ӹ���
int totalnum;//totalnum��Ҫ�ۼ������Ӹ��� 
int map[M+2][M+2] = {};//map�����о��Ķ�άƽ�棬���Ӵ��ڵ�λ��Ϊ1�������Ӵ���Ϊ0 
typedef struct particle{//�������ӵ�״̬������(x,y) 
	int x;
	int y;
}particle;
int I;

//16807�����������
int a=16807,m=2147483647,q=127773,w=2836; 
int Random(){ 
	I = a*(I%q)-w*(I/q);
	if(I<0) I += m;
	return I;
}


//�������һ�� 
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

//����ڱ߽�������һ������
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

//��鵱ǰ���ӵ�״̬��0�������ɵ�·�ϣ�1���ۼ���2����������
int Check(particle p){
	int x=p.x;
	int y=p.y;
	if(x<1||y<1||x>M||y>M) return 2;//���� 
	if(map[x][y+1]||map[x][y-1]||map[x+1][y]||map[x-1][y]) return 1;//�ۼ� 
	return 0;
} 

//�м����� 
int find1(int n){ 
	int i,j,ii,jj;
	int flag;
	int range = M/n;
	int count = 0;
	//�ֿ� 
	for(i=1;i<=M;i+=range){
		for(j=1;j<=M;j+=range){
            flag = 0;
            //��(i,j)������ii,jj��Ϊ������������ 
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
		N[i] = find1(pow(2,i));// epsilon ȡ 2^i 
	}
	FILE *fp1;
	fp1 = fopen("boxcount.txt","w");
	for(int i=0;i<=BOXCOUNT_R;++i){//���˫����ͼ 
		fprintf(fp1,"%lf %lf\n",log(pow(2,i)),log(N[i]));
	} 
	fclose(fp1);
} 

//Sandbox ����
int find2(int r){//������r�Ŀ����ж������� 
	int startx,starty,endx,endy;//��ʼλ�ã�����λ�� 
    int i,j;
    int count = 0;
    startx = (M/2)-(r/2);
    starty = (M/2)-(r/2);
    endx = (M/2)+(r/2);
    endy = (M/2)+(r/2);
    //ͳ��map�д��ڵ������� 
    for(i=startx;i<=endx;++i)
    	for(j=starty;j<=endy;++j)
    		count+=map[i][j];
    return count;
}
void Sandbox(){
	double N[SANDBOX_R+2];
	for(int i=1;i<=SANDBOX_R;i+=4){
		N[i] = find2(i);//������iΪr�Ŀ����ж������� 
	}
	FILE *fp2;
	fp2 = fopen("sandbox.txt","w");
	for(int i=1;i<=SANDBOX_R;i+=4){//���˫����ͼ 
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
	map[M/2][M/2] = 1;//�������ε����������һ��������Ϊ�������� 
	int count = 0;
	while (curnum<totalnum){
		particle p = Random_Generation();//����һ��������
		count++;
		int flag = 1;//�ж�ѭ����flag 
		while(flag) {
			//printf("%d\n",Check(p));
			if(Check(p)==0){//���p����û������Ҳû�оۼ� 
				p = Random_Walk(p);//����RW 
				//printf("%d :%d :%d %d\n",curnum,count,p.x,p.y);
			}
			else if(Check(p)==1){//���p�ۼ������� 
				curnum++;//��Ŀ��һ 
				map[p.x][p.y]=1;
				//printf("%d %d\n",p.x,p.y);
				//��ǰ���ĸ������� 
				if(curnum*100%totalnum==0)
					printf("%d particles are ok!\n",curnum);
				flag = 0;
			} 
			else{//���p���ӱ����� 
				flag = 0; //�˳�ѭ�� 
			} 
		}		
	}
	
	BoxCount();//�м����� 
	Sandbox();//sandbox������
	
	//���map 
	for(int i=1;i<=M;++i)
		for(int j=1;j<=M;++j)
			if(map[i][j])
				fprintf(fp,"%d %d\n",i,j);
	fclose (fp);
	return 0;
}
