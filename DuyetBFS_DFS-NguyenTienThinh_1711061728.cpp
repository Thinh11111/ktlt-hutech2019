#include<stdio.h>
#include<conio.h>

#define MAX 10 
#define input "D:/test1.txt"

typedef struct DOTHI{
	int n;
	int a[MAX][MAX];
};

void DocMaTran(char TenFile[100],DOTHI &g){
	FILE *f;
	f=fopen(TenFile,"rt");
	if(f==NULL){
		printf("\nKhong mo duoc file!");
	//	return 0;
	}
	fscanf(f,"%d",&g.n);
	for(int i=1;i<=g.n;i++){
		for(int j=1;j<=g.n;j++)
			fscanf(f,"%d",&g.a[i][j]);
	}
	fclose(f);
}
//=========================================
void XuatMaTran(DOTHI g){
	printf("So dinh cua do thi: %d",g.n);
	printf("\nDo thi:\n");
	for(int i=1;i<=g.n;i++){
		for(int j=1;j<=g.n;j++)
		{
			printf("%4d",g.a[i][j]);
		}
		printf("\n");
	}
}
//===================================================
int LuuVet[MAX];
int ChuaXet[MAX];
void DFS(int v,DOTHI g){
	ChuaXet[v]=1;
	for(int i=1;i<=g.n;i++){
		if(g.a[v][i]!=0&&ChuaXet[i]==0){
			LuuVet[i]=v;
			DFS(i,g);
		}
	}
}
void duyetDFS(int S,int F,DOTHI g){
	for(int i=0;i<MAX;i++){
		LuuVet[i]=-1;
		ChuaXet[i]=0;
	}
	DFS(S,g);
	if(ChuaXet[F]==1){
		printf("Duong di tu dinh %d den dinh%d la: \n \t",S,F);
		int i=F;
		printf("%d",F);
		while(LuuVet[i]!=S)
		{
			printf("<-%d",LuuVet[i]);
			i=LuuVet[i];
		}
		printf("<-%d\n",LuuVet[i]);
	}
	else{
		printf("khong co duong di tu dinh %d den dinh %d\n",S,F);
	}
}
//==========================================
int Free[MAX];
int Trace[MAX];
int Stack[MAX];
int n,S,F,Last;
void Push(int v){
	Last++;
	Stack[Last]=v;
}
int Pop(){
	int x=Stack[Last];
	Last--;
	return x;
}
void DFSStack(int S,int F,DOTHI g)
{
	int i,j;
	printf("%d",S);
	Free[S]=1;
	Push(S);
	do{
		i=Pop();
		for(j=1;j<=g.n;j++){
			if(Free[j]==0 && g.a[i][j]>0){
				printf("%d",j);
				Free[j]=1;
				
				
				Trace[j]=i;
				Push(i); Push(j);
				
				break;			
			}
		}
	}while(Last!=0);
}
//=================================================
struct QUEUE{
	int size;
	int array[MAX];
};
void khoiTaoQueue(QUEUE &q){
	q.size=0;
}
int duaVaoQueue(QUEUE &q,int value){
	if(q.size +1>=100)
		return 0;
	q.array[q.size]=value;
	q.size++;
	return 1;
}
int layKhoiQueue(QUEUE &q,int &value){
	int i;
	if(q.size<=0)
		return 0;
	value -q.array[0];
	for(int i=0;i<q.size-1;i++)
		q.array[i]=q.array[i+1];
	q.size--;
	return 1;
}
int KTRong(QUEUE q){
	if(q.size<=0)
		return 1;
	return 0;
}
void BFS(int v,DOTHI g){
	QUEUE q;
	khoiTaoQueue(q);
	duaVaoQueue(q,v);
	while(!KTRong(q)){
		layKhoiQueue(q,v);
		ChuaXet[v]=1;
		for(int u=0;u<g.n;u++)
		{
			if(g.a[v][u]!=0&& ChuaXet[u]==0){
				duaVaoQueue(q,u);
				LuuVet[u]=v;
			}
		}
	}
}
void duyetBFS(int S,int F,DOTHI g){
	for(int i=0;i<MAX;i++){
		LuuVet[i]=-1;
		ChuaXet[i]=0;
	}
	BFS(S,g);
	if(ChuaXet[F]==1){
		printf("\n duong di tu %d den %d:\n",S,F);
		int i=F;
		printf("%d",F);
		while(LuuVet[i]!=S)
		{
			printf("<-%d",LuuVet[i]);
			i=LuuVet[i];
		}
		printf("<-%d\n",LuuVet[i]);
	}
	else{
		printf("\n khong co duong");
	}
}
//=================================================
int main()
{
	DOTHI g;
	
	int d1,d2;
	DocMaTran(input,g);
	XuatMaTran(g);
	printf("\Nhap vao 2 diem ban tim\nd1=");
	scanf("%d",&d1);
	printf("d2=");
	scanf("%d",&d2);
	//duyetDFS(d1,d2,g);
	//DFSStack(d1,d2,g);
	duyetBFS(d1,d2,g);
}
