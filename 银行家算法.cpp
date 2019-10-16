#include<stdio.h>
#include<stdlib.h>
/*
	˵��������������ģ�⣬���м��㷨��
			���ǰ�����ʦ�ĵ��Ľ�ͼ��Ϣ��ģ����һ���Ľ��� 
	���ߣ�cenjianfeng
	ѧ�ţ�3117001905
	Q  Q: 1191741965 
	ʱ�䣺2019/10/16 23:57
	GitHub��ַ��https://github.com/1191741965/Banker-algorithm 
	
*/ 
//��������
void Request(struct resouce *r);	//����ϵͳ��Դ 
int Security(struct resouce *r, int A, int B, int C);	//��ȫ��� 


struct resouce {
	int Avialable[3];
	int Max[5][3];
	int Allocation[5][3];
	int MaxS[3];	//���ڼ�¼��ʼ��ʱϵͳ������Դ������� 
};

//����̵ĸ������� 
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

//����������ʼ�����ݵĺ��� 
void InterData(struct resouce *r) {
	printf("��ʼ�����ݣ�\n"); 
	
	for(int i = 0;i < 3; i++) {
		printf("������ Avialable[%d]:",i);
		scanf("%d",&r->Avialable[i]);
	}
	
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 3; j++) {
			printf("������ Max[%d][%d]:",i,j);
			scanf("%d", &r->Max[i][j]);
		}
	}
	
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 3; j++) {
			printf("������ Allocation[%d][%d]:",i,j);
			scanf("%d", &r->Allocation[i][j]);
		}
	}
	//��ø�����Դ�������(�̶�) 
	for(int j = 0; j < 3; j++){
		r->MaxS[j] = r->Allocation[0][j] + r->Allocation[1][j] + r->Allocation[2][j] + r->Allocation[3][j] + r->Allocation[4][j] + r->Avialable[j];
		printf("%d\n",r->MaxS[j]);
	}
	//��ý��̸��� 
    int flag = GetPidNumber(r);
    printf(" ���̸�����%d   ��Դ������3\n\n", flag);
}

//������ͼ����ӡ���� 
void UpdateView(struct resouce *r) {
	printf("���ڸ�������...\n");
	printf("|------|----------|------------|----------|------------|\n");
	printf("|      | ������� | �ѷ������ | ������� |  ������Դ  |\n");
	printf("| ��Դ |   MAX    | Allocation |   Need   |  Available |\n");
	printf("|      | A  B  C  |  A  B  C   | A  B  C  |   A   B  C |\n");
	printf("| ���� |          |            |          |            |\n");
	printf("|------|----------|------------|----------|------------|\n");
	//���forѭ����Ϊ�˽����ݴ�ӡ�ڱ�Ķ�Ӧλ�� 
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
	printf("�������...\n\n\n");
	printf("�Ƿ����ʵ�飿(y|Y:����   n|N:�˳�)��");
	char ch;
	scanf(" %c",&ch);
	if(ch =='y' || ch == 'Y'){
		printf("��ʼ����ʵ��,���Ժ�...\n");
		//���������� 
		Request(r);
	}else{
		printf("�˳�ϵͳ...\n");
	}
	
}


//������ 
void Request(struct resouce *r) {
	printf("�ѳɹ�����ʵ��...\n");
	printf("�����뷢������Ľ��̺ţ�0-4����");
	int pid;
	scanf("%d", &pid);
	printf("��������ǣ�p[%d] ����\n",pid);
	printf("�ý��̵��������ֱ�Ϊ:  %d  %d  %d\n",r->Max[pid][0] - r->Allocation[pid][0], r->Max[pid][1] - r->Allocation[pid][1], r->Max[pid][2] - r->Allocation[pid][2]);
	printf("������������Դ����Ŀ��������������С�������������֡����磺1 0 2 ����");
	int A,B,C;
	scanf("%d %d %d", &A, &B, &C);
	printf("��ʼִ�����м��㷨����������Է���...\n");
	int flag = Security(r,A,B,C);
	if(flag){
		printf("��ͨ����ȫ�Բ��ԡ�\n");
		if((A <= r->Max[pid][0] - r->Allocation[pid][0]) && (B <= r->Max[pid][1] - r->Allocation[pid][1]) && (C <= r->Max[pid][2] - r->Allocation[pid][2])) {
			if((A <= r->Avialable[0]) && (A <= r->Avialable[1]) && (A <= r->Avialable[2]) ) {
				printf("��ʼΪ p[%d] ���̷�����Դ��\n", pid);
				r->Allocation[pid][0] += A;
				r->Allocation[pid][1] += B;
				r->Allocation[pid][2] += C;
				r->Avialable[0] = r->MaxS[0] - r->Allocation[0][0] - r->Allocation[1][0] - r->Allocation[2][0] - r->Allocation[3][0] - r->Allocation[4][0];
				r->Avialable[1] = r->MaxS[1] - r->Allocation[0][1] - r->Allocation[1][1] - r->Allocation[2][1] - r->Allocation[3][1] - r->Allocation[4][1];
				r->Avialable[2] = r->MaxS[2] - r->Allocation[0][2] - r->Allocation[1][2] - r->Allocation[2][2] - r->Allocation[3][2] - r->Allocation[4][2];
				printf("������ɣ�\n���ڷ�����Դ��...\n\n\n");
				GetPidNumber(r);
				UpdateView(r);
			} else {
				printf("�����󣡾ܾ�����...\n���ڷ�����Դ��...\n\n");
				UpdateView(r);
			}
		} else {
			printf("������󣡾ܾ�����...\n���ڷ�����Դ��...\n\n");
			UpdateView(r);
		}
	} else {
		printf("�޷�ͨ����ȫ�Բ��ԣ��ܾ�����...\n���ڷ�����Դ��...\n\n");
		UpdateView(r);
	} 
} 

//���а�ȫ���ĺ��� 
int Security(struct resouce *r, int A, int B , int C) {
	int Need_p[5];
	//����������� 
	for(int i = 0; i < 5 ; i++){
		Need_p[i] = r->Max[i][0] + r->Max[i][1] + r->Max[i][2] - r->Allocation[i][0] - r->Allocation[i][1] - r->Allocation[i][2];
	}
	//�������������¼��Ӧ���̺ŵ��±� 
	int num[5] = {0, 1, 2, 3, 4};
	int temp = 0;
	//���������������У�С���� 
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
	//��ʣ����Դ��ֵ����free���Ա㰲ȫ����У�� 
	int free[3] = {r->Avialable[0], r->Avialable[1], r->Avialable[2]};
	for(int i = 0 ; i < 5 ; i++) {
		free[0] += r->Allocation[ num[i] ][0];
		free[1] += r->Allocation[ num[i] ][1];
		free[2] += r->Allocation[ num[i] ][2];
	}
	//�ж��Ƿ��н��� 
	if(GetPidNumber(r)) {
		if(free[0] > r->MaxS[0]) {
		printf("�����ڰ�ȫ���У��ܾ�����...\n");
		return 0;
		} else {
			if(free[1] > r->MaxS[1]){
			printf("�����ڰ�ȫ���У��ܾ�����...\n");
			return 0;
			} else {
				if(free[2] > r->MaxS[2]) {
					printf("�����ڰ�ȫ���У��ܾ�����...\n");
					return 0;
				} else {
					printf("���ڰ�ȫ����...\n");
					printf("��ȫ����Ϊ��p%d -> p%d -> p%d -> p%d -> p%d",num[0],num[1],num[2],num[3],num[4]);
					return 1;
				}
			}
		}
	} else {
		printf("�޽��̴��ڣ��ܾ�����...\n");
		return 0;
	}
	
}

int main(void) {
	struct resouce *r;
	r = (struct resouce*)malloc(sizeof(struct resouce));
	InterData(r);
	UpdateView(r);
}
