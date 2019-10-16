#include<stdio.h>
#include<stdlib.h>
/*
	说明：这是死锁的模拟，银行家算法。
			我是按照老师文档的截图信息，模仿了一样的界面 
	作者：cenjianfeng
	学号：3117001905
	Q  Q: 1191741965 
	时间：2019/10/16 23:57
	GitHub地址：https://github.com/1191741965/Banker-algorithm 
	
*/ 
//函数声明
void Request(struct resouce *r);	//请求系统资源 
int Security(struct resouce *r, int A, int B, int C);	//安全检测 


struct resouce {
	int Avialable[3];
	int Max[5][3];
	int Allocation[5][3];
	int MaxS[3];	//用于记录初始化时系统各种资源的最大数 
};

//求进程的个数函数 
int GetPidNumber(struct resouce *r) {
	int flag = 0;
	for(int i = 0; i < 5 ; i++){
		int sum = r->Max[i][0] + r->Max[i][1] + r->Max[i][2];
		if(sum !=0) {
			flag++;
		}
	}
	return flag;
} 

//这是用作初始化数据的函数 
void InterData(struct resouce *r) {
	printf("初始化数据！\n"); 
	
	for(int i = 0;i < 3; i++) {
		printf("请输入 Avialable[%d]:",i);
		scanf("%d",&r->Avialable[i]);
	}
	
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 3; j++) {
			printf("请输入 Max[%d][%d]:",i,j);
			scanf("%d", &r->Max[i][j]);
		}
	}
	
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 3; j++) {
			printf("请输入 Allocation[%d][%d]:",i,j);
			scanf("%d", &r->Allocation[i][j]);
		}
	}
	//获得各种资源的最大数(固定) 
	for(int j = 0; j < 3; j++){
		r->MaxS[j] = r->Allocation[0][j] + r->Allocation[1][j] + r->Allocation[2][j] + r->Allocation[3][j] + r->Allocation[4][j] + r->Avialable[j];
		printf("%d\n",r->MaxS[j]);
	}
	//获得进程个数 
    int flag = GetPidNumber(r);
    printf(" 进程个数：%d   资源个数：3\n\n", flag);
}

//更新视图，打印出表 
void UpdateView(struct resouce *r) {
	printf("正在更新数据...\n");
	printf("|------|----------|------------|----------|------------|\n");
	printf("|      | 最大需求 | 已分配矩阵 | 需求矩阵 |  可用资源  |\n");
	printf("| 资源 |   MAX    | Allocation |   Need   |  Available |\n");
	printf("|      | A  B  C  |  A  B  C   | A  B  C  |   A   B  C |\n");
	printf("| 进程 |          |            |          |            |\n");
	printf("|------|----------|------------|----------|------------|\n");
	//这个for循环是为了将数据打印在表的对应位置 
	for(int i = 0; i < 5 ; i++) {
		if(i == 0) {
			printf("|  p%d  | %d  %d  %d  |  %d  %d  %d   | %d  %d  %d  |   %d   %d  %d |\n",i, r->Max[i][0],  r->Max[i][1],  r->Max[i][3],
		 r->Allocation[i][0],  r->Allocation[i][2],  r->Allocation[i][1],
		 r->Max[i][0]-r->Allocation[i][0], r->Max[i][1]-r->Allocation[i][1], r->Max[i][2]-r->Allocation[i][2], 
		 r->Avialable[0], r->Avialable[1], r->Avialable[2]);
		}else{
			printf("|  p%d  | %d  %d  %d  |  %d  %d  %d   | %d  %d  %d  |            |\n",i, r->Max[i][0],  r->Max[i][1],  r->Max[i][3],
		 r->Allocation[i][0],  r->Allocation[i][2],  r->Allocation[i][1],
		 r->Max[i][0]-r->Allocation[i][0], r->Max[i][1]-r->Allocation[i][1], r->Max[i][2]-r->Allocation[i][2]);
		}
	}
	printf("|------|----------|------------|----------|------------|\n");
	printf("更新完成...\n\n\n");
	printf("是否进入实验？(y|Y:进入   n|N:退出)：");
	char ch;
	scanf(" %c",&ch);
	if(ch =='y' || ch == 'Y'){
		printf("开始进入实验,请稍后...\n");
		//进入请求函数 
		Request(r);
	}else{
		printf("退出系统...\n");
	}
	
}


//请求函数 
void Request(struct resouce *r) {
	printf("已成功进入实验...\n");
	printf("请输入发起请求的进程号（0-4）：");
	int pid;
	scanf("%d", &pid);
	printf("您输入的是：p[%d] 进程\n",pid);
	printf("该进程的需求量分别为:  %d  %d  %d\n",r->Max[pid][0] - r->Allocation[pid][0], r->Max[pid][1] - r->Allocation[pid][1], r->Max[pid][2] - r->Allocation[pid][2]);
	printf("请输入请求资源的数目（请输入三个不小于需求量的数字。例如：1 0 2 ）：");
	int A,B,C;
	scanf("%d %d %d", &A, &B, &C);
	printf("开始执行银行家算法，下面进行试分配...\n");
	int flag = Security(r,A,B,C);
	if(flag){
		printf("已通过安全性测试。\n");
		if((A <= r->Max[pid][0] - r->Allocation[pid][0]) && (B <= r->Max[pid][1] - r->Allocation[pid][1]) && (C <= r->Max[pid][2] - r->Allocation[pid][2])) {
			if((A <= r->Avialable[0]) && (A <= r->Avialable[1]) && (A <= r->Avialable[2]) ) {
				printf("开始为 p[%d] 进程分配资源！\n", pid);
				r->Allocation[pid][0] += A;
				r->Allocation[pid][1] += B;
				r->Allocation[pid][2] += C;
				r->Avialable[0] = r->MaxS[0] - r->Allocation[0][0] - r->Allocation[1][0] - r->Allocation[2][0] - r->Allocation[3][0] - r->Allocation[4][0];
				r->Avialable[1] = r->MaxS[1] - r->Allocation[0][1] - r->Allocation[1][1] - r->Allocation[2][1] - r->Allocation[3][1] - r->Allocation[4][1];
				r->Avialable[2] = r->MaxS[2] - r->Allocation[0][2] - r->Allocation[1][2] - r->Allocation[2][2] - r->Allocation[3][2] - r->Allocation[4][2];
				printf("分配完成！\n正在返回资源表...\n\n\n");
				GetPidNumber(r);
				UpdateView(r);
			} else {
				printf("需求多大！拒绝分配...\n正在返回资源表...\n\n");
				UpdateView(r);
			}
		} else {
			printf("需求过大！拒绝分配...\n正在返回资源表...\n\n");
			UpdateView(r);
		}
	} else {
		printf("无法通过安全性测试！拒绝分配...\n正在返回资源表...\n\n");
		UpdateView(r);
	} 
} 

//进行安全检测的函数 
int Security(struct resouce *r, int A, int B , int C) {
	int Need_p[5];
	//获得需求总数 
	for(int i = 0; i < 5 ; i++){
		Need_p[i] = r->Max[i][0] + r->Max[i][1] + r->Max[i][2] - r->Allocation[i][0] - r->Allocation[i][1] - r->Allocation[i][2];
	}
	//这个数组用作记录对应进程号的下标 
	int num[5] = {0, 1, 2, 3, 4};
	int temp = 0;
	//根据需求总数排行，小到大 
	for(int i = 0; i < 5 ; i++){
		for(int j = 0; j < 4 ; j++){
			if(Need_p[j] > Need_p[j+1]){
				temp = Need_p[j +1];
				Need_p[j + 1] = Need_p[j];
				Need_p[j] = temp;
				temp = num[j+1];
				num[j+1] = num[j];
				num[j] = temp;
			}	
		}
	}
	//将剩余资源赋值，在free，以便安全序列校验 
	int free[3] = {r->Avialable[0], r->Avialable[1], r->Avialable[2]};
	for(int i = 0 ; i < 5 ; i++) {
		free[0] += r->Allocation[ num[i] ][0];
		free[1] += r->Allocation[ num[i] ][1];
		free[2] += r->Allocation[ num[i] ][2];
	}
	//判断是否有进程 
	if(GetPidNumber(r)) {
		if(free[0] > r->MaxS[0]) {
		printf("不存在安全序列，拒绝分配...\n");
		return 0;
		} else {
			if(free[1] > r->MaxS[1]){
			printf("不存在安全序列，拒绝分配...\n");
			return 0;
			} else {
				if(free[2] > r->MaxS[2]) {
					printf("不存在安全序列，拒绝分配...\n");
					return 0;
				} else {
					printf("存在安全序列...\n");
					printf("安全序列为：p%d -> p%d -> p%d -> p%d -> p%d",num[0],num[1],num[2],num[3],num[4]);
					return 1;
				}
			}
		}
	} else {
		printf("无进程存在，拒绝分配...\n");
		return 0;
	}
	
}

int main(void) {
	struct resouce *r;
	r = (struct resouce*)malloc(sizeof(struct resouce));
	InterData(r);
	UpdateView(r);
}
