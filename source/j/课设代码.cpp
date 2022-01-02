#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "time.h"
#define VertexMax 20 //最大顶点数为20
typedef char* VertexType;

typedef struct
{
    VertexType begin;
    VertexType end;
    double weight;
}Edge;//边集数组edge[]的单元

typedef struct
{
    VertexType Vertex[VertexMax];//顶点数组
    Edge edge[VertexMax];//边集数组
    int vexnum;//顶点数
    int edgenum;//边数
}EdgeGraph;

void CreateEdgeGraph(EdgeGraph *E)
{
    int i;
    printf("请输入顶点数和边数:\n");
    printf("顶点数 n=");
    scanf("%d",&E->vexnum);
    printf("边  数 e=");
    scanf("%d",&E->edgenum);
    printf("\n");
    printf("输入顶点:\n");
    for(i=0;i<E->edgenum;i++){
        printf("请输入第%d顶点数:\n",i+1);
        E->Vertex[i]=(VertexType) malloc(sizeof (char ));
        scanf("%s",E->Vertex[i]);
    }
    printf("\n请输入边信息和权值:\n");
    for(i=0;i<E->edgenum;i++)
    {
        E->edge[i].begin=(VertexType) malloc(sizeof (char));
        E->edge[i].end=(VertexType) malloc(sizeof (char));
        printf("请输入第%d边的信息:\n",i+1);
        printf("请输入起始点:\n");
        scanf(" %s",E->edge[i].begin);
        printf("请输入终点:\n");
        scanf("%s",E->edge[i].end);
        printf("请输入该边的权值:\n");
        scanf("%lf",&E->edge[i].weight);
    }
}

void sort(EdgeGraph *E)
{
    int i,j;
    Edge temp;
    for(i=0;i<E->edgenum-1;i++)
    {
        for(j=i+1;j<E->edgenum;j++)
        {
            if(E->edge[i].weight>E->edge[j].weight)
            {
                temp=E->edge[i];
                E->edge[i]=E->edge[j];
                E->edge[j]=temp;
            }
        }
    }
}

int LocateVex(EdgeGraph *E,VertexType v)//查找元素v在一维数组 Vertex[] 中的下标，并返回下标
{
    int i;
    for(i=0;i<E->vexnum;i++)
    {
        if(strcmp(v,E->Vertex[i])==0)
        {
            return i;
        }
    }
    printf("No Such Vertex!\n");
    return -1;
}

int FindRoot(int t,int parent[])//t接收到是结点在Vertex数组中的下标
{
    while(parent[t]> -1)//parent=-1表示没有双亲，即没有根节点
    {
        t=parent[t];//逐代查找根节点
    }
    return t;//将找到的根节点返回，若没有根节点返回自身
}

void MiniSpanTree_Kruskal(EdgeGraph *E)
{
    int i;FILE *fp= fopen("C:/Users/ASUS/Desktop/log.txt","w");
    if(fp==NULL) return;
    int num;//生成边计数器，当num=顶点数-1 就代表最小生成树生成完毕
    int root1,root2;
    int LocVex1,LocVex2;
    int parent[VertexMax];//用于查找顶点的双亲，判断两个顶点间是否有共同的双亲，来判断生成树是否会成环
    //按权值从小到大排序
    sort(E);
    //初始化parent数组
    for(i=0;i<E->vexnum;i++)
    {
        parent[i]=-1;
    }
    printf("\n 最小生成树(Kruskal):\n\n");
    for(num=0,i=0;i<E->edgenum;i++)
    {
        LocVex1=LocateVex(E,E->edge[i].begin);
        LocVex2=LocateVex(E,E->edge[i].end);
        root1=FindRoot(LocVex1,parent);
        root2=FindRoot(LocVex2,parent);
        if(root1!=root2)//若不会成环，则在最小生成树中构建此边
        {
            printf("%s-%s w=%lf\n",E->edge[i].begin,E->edge[i].end,E->edge[i].weight);//输出此边
            fprintf(fp,"%s->",E->edge[i].begin);
            fprintf(fp,"%s",E->edge[i].end);
            fprintf(fp,"%lf\n",E->edge[i].weight);
            parent[root2]=root1;//合并生成树
            num++;
            if(num==E->vexnum-1)//若num=顶点数-1，代表树生成完毕，提前返回
            {
                return;
            }
        }
    }

}

//VertexType getNow() {
//    unsigned long long a = 0;
//    char timeStr[64];
//    time_t timer;
//    struct tm* tblock;
//    time(&timer);
//    tblock = gmtime(&timer);
//    a = (tblock->tm_year + 1900) * 100;
//    a = (a + tblock->tm_mon + 1) * 100;
//    a = (a + tblock->tm_mday) * 100;
//    a = (a + tblock->tm_hour + 8) * 100;
//    a = (a + tblock->tm_min) * 100;
//    a = (a + tblock->tm_sec);
//    sprintf(timeStr, "%llu", a);
//    return timeStr;
//}

//时间戳写入文件
int timetxt()
{
	time_t timeSec = time(NULL); //获取1970.1.1至当前秒数time_t
	struct tm* timeinfo = localtime(&timeSec); //创建TimeDate,并转化为当地时间，
	printf("The current date/time is: %s\n", asctime(timeinfo));//获取年 月 日 时 分 秒 对应的int值：
	printf("%d-%d-%d %d:%d:%d\n", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	FILE* fp = fopen("C:/Users/ASUS/Desktop/log.txt", "a");
	fprintf(fp, "Line connected! %d-%d-%d %d:%d:%d\n", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	return 0;
}

int main()
{
    EdgeGraph E;
    FILE *fp= fopen("C:/Users/ASUS/Desktop/log.txt","w");
    if(fp==NULL) exit(1);
    CreateEdgeGraph(&E);
    MiniSpanTree_Kruskal(&E);
    timetxt();
    return 0;
}
