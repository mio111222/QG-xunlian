#include<stdio.h>
#include<stdlib.h>
#define MAXQUEUE 11

//循环队列结构

typedef struct Aqueue          //链式队列
{
    void* data[MAXQUEUE];
    int front;
    int rear;
    int length;
    int type[MAXQUEUE];
} AQueue;

typedef enum                   //判断true和false
{
    FALSE = 0,
    TRUE = 1
} Status;

void Init(AQueue* Q);//初始化队列
void Destory(AQueue* Q);//摧毁队列
Status Full(const AQueue* Q);//判断是否满
Status Empty(const AQueue* Q);//判断是否空
Status GetHead(AQueue* Q);//查询头节点
void Length(AQueue* Q);//查询队列长度
Status EnAQueue(AQueue* Q, void* data, int s);//入队
Status DeAQueue(AQueue* Q);//出队
void Clear(AQueue* Q);//清空队列
Status Traverse(const AQueue* Q);//遍历队列
void checkinput(int* r);//判断输入
void CheckType(AQueue* Q);//判断输入类型

void Init(AQueue* Q)//初始化队列
{
    int i;
    Q->front = 0;//头节点
    Q->rear = 0;//尾节点按数组排序开始
    for (i = 0; i < MAXQUEUE; i++) {
        Q->data[i] = (void*)malloc(21);
        if (i < MAXQUEUE - 1)
            CheckType(Q);//输入数据
    }
    printf("队列创建成功！\n");
}

void Destory(AQueue* Q)//销毁队列
{
    if (Q->data[0] == NULL)//判断队列是否有数据
    {
        printf("请先输入【1】创建队列\n");
        return;
    }
    else {
        for (int i = 0; i < MAXQUEUE; i++)
            free(Q->data[i]);//清空队列数据
        Q->data[0] = NULL;
        printf("队列销毁成功！\n");
    }
}

Status Full(const AQueue* Q)//判断队列是否满
{
    if (Q->data[0] == NULL)//无队列情况
    {
        printf("请先输入【1】创建队列\n");
        return FALSE;
    }
    if (Q->length == 0) {//无队列情况
        return FALSE;
    }
    if (Q->length == MAXQUEUE - 1)
    {
        printf("这是一个满队列！\n");
        return TRUE;
    }
    else {
        printf("这不是一个满队列！\n");
        return FALSE;
    }
}

Status Empty(const AQueue* Q)//队列是否为空
{
    if (Q->data[0] == NULL)//未填入数据
    {
        printf("请先输入【1】创建队列\n");
        return FALSE;
    }
    else if (Q->length == 0) {
        printf("这是一个空队列！\n");
        return TRUE;
    }
    else {
        printf("这不是一个空队列！\n");
        return FALSE;
    }
}

Status GetHead(AQueue* Q)//读取队头
{
    if (Q->data[0] == NULL)
    {
        printf("请先输入【1】创建队列\n");
        return FALSE;
    }
    else if (Q->length == 0)
    {
        printf("队列为空！没有队头！\n");
        return FALSE;
    }
    else {
        if (Q->type[Q->front] == 8)
            printf("队头元素是：【%lf】\n", *(double*)Q->data[Q->front]);
        if (Q->type[Q->front] == 1)
            printf("队头元素是：【%c】\n", *(char*)Q->data[Q->front]);
        if (Q->type[Q->front] == 4)
            printf("队头元素是：【%d】\n", *(int*)Q->data[Q->front]);
        if (Q->type[Q->front] == 20)
            printf("队头元素是：【%s】\n", (char*)Q->data[Q->front]);
        return TRUE;
    }
}

void Length(AQueue* Q)//判断该队列长度
{
    if (Q->data[0] == NULL)
    {
        printf("请先输入【1】创建队列\n");
        return FALSE;
    }
    else {
        printf("队列长度为:%d\n", Q->length);
        return;
    }
}

Status EnAQueue(AQueue* Q, void* data, int s)//入队
{
    if (Q->length == 0)//当队列内无数据时
    {
        Q->data[Q->front] = data;//数据位置
        Q->rear = (Q->rear + 1) % MAXQUEUE;//队尾指针后移
        Q->type[Q->front] = s;//类型判断
        Q->length++;//队列长度计数
        printf("入队成功！\n");
        Traverse(Q);
        return TRUE;
    }
    else {
        Q->data[Q->rear] = data;
        Q->type[Q->rear] = s;
        Q->rear = (Q->rear + 1) % MAXQUEUE;
        Q->length++;
        printf("入队成功！\n");
        Traverse(Q);
        return TRUE;
    }
}

Status DeAQueue(AQueue* Q)//出队
{
    if (Q->data[0] == NULL)//判断队列是否空
    {
        printf("请先输入【1】创建队列\n");
        return FALSE;
    }
    else if (Q->length == 0)
    {
        printf("队列是空的！出不了队！\n");
        return FALSE;
    }
    else {
        Q->front = (Q->front + 1) % MAXQUEUE;//将front的所指后移
        Q->length--;
        printf("出队成功！\n");
        Traverse(Q);
        return TRUE;
    }
}

void Clear(AQueue* Q)//清除队列
{
    if (Q->data[0] == NULL)
    {
        printf("请先输入【1】创建队列\n");
        return FALSE;
    }
    else if (Q->length == 0)
    {
        printf("队列已经是空的了！\n");
        return;
    }
    else {
        Q->front = Q->rear = 0;
        Q->length = 0;
        printf("队列清空成功！\n");
    }
}

Status Traverse(const AQueue* Q)//遍历队列
{
    if (Q->data[0] == NULL)//判断是否空
    {
        printf("请先输入【1】创建队列\n");
        return FALSE;
    }
    else if (Q->length == 0)
    {
        printf("队列里面什么都没有!\n");
        return FALSE;
    }
    else {
        printf("队列为：\n");//输出队列
        printf("【head】");
        for (int i = Q->front; i < Q->front + Q->length; i++) {
            printf(" -> ");
            if (Q->type[i] == 8)
                printf("【%lf】", *(double*)Q->data[i]);
            if (Q->type[i] == 1)
                printf("【%c】", *(char*)Q->data[i]);
            if (Q->type[i] == 4)
                printf("【%d】", *(int*)Q->data[i]);
            if (Q->type[i] == 20)
                printf("【%s】", (char*)Q->data[i]);
        }
        printf("\n");
        return TRUE;
    }
}

void checkinput(int* r) {//检查输入，避免在输入类型时输入了别的数
    int error, i = 0;
    char c[50] = { 0 };
    do {
        gets(c);
        error = 0;
        for (i = 0; c[i] != '\0'; i++) {
            if (i == 0 && c[i] == '-')
            {
                continue;
            }
            if (c[i] < '0' || c[i]>'9')
                error = 1;
        }
        if (error) {
            printf("输入错误，请重新输入！\n");
        }
    } while (error);
    *r = atoi(c);//将字符转为int
}

void CheckType(AQueue* Q) {//输入数据，并且进行类型的选择
    printf("|---------------------|\n");
    printf("|    数据类型选择     |\n");
    printf("|    1---整型         |\n");
    printf("|    2---字符型       |\n");
    printf("|    3---浮点型       |\n");
    printf("|    4---字符串       |\n");
    printf("|---------------------|\n");
    int t = 1, s;//t确定类型，s将类型的字节大小放入type中区分
    printf("你想入队哪种类型？:\n");
    checkinput(&t);//判断类型
    if (t > 0 && t < 5) {
        switch (t)
        {
        case 1: {//整型
            int* a = (int*)malloc(sizeof(int));
            s = 4;
            printf("请输入【整型数据】：\n");
            checkinput(a);
            EnAQueue(Q, a, s);
            break;
        }
        case 2: {//字符型
            char* a = (char*)malloc(sizeof(char));
            s = 1;
            printf("请输入【字符型数据】：\n");
            scanf_s("%c", a);
            getchar();
            EnAQueue(Q, a, s);
            break;
        }
        case 3: {//浮点型
            double* a = (double*)malloc(sizeof(double));
            s = 8;
            printf("请输入【浮点型数据】：\n");
            scanf_s("%lf", a);
            getchar();
            EnAQueue(Q, a, s);
            break;
        }
        case 4: {//字符串型
            char* a = (char*)malloc(20 * sizeof(char));
            s = 20;
            printf("请输入【字符串型数据】（最大长度为20）：\n");
            gets(a);
            EnAQueue(Q, a, s);
            break;
        }
        }
    }
    else
    {
        printf("应输入在[1,4]之间的整数！\n");
        CheckType(Q);
    }
    return;
}
int main() {
    int num = 0;
    AQueue* Q = (AQueue*)malloc(sizeof(AQueue));
    Q->length = 0;
    Q->data[0] = NULL;
    while (1) {
        system("cls");
        printf("|-----------------------------|\n");
        printf("|      1---建立队列           |\n");
        printf("|      2---销毁队列           |\n");
        printf("|      3---判断满队列         |\n");
        printf("|      4---判断空队列         |\n");
        printf("|      5---获得队头元素       |\n");
        printf("|      6---获得队列长度       |\n");
        printf("|      7---入队               |\n");
        printf("|      8---出队               |\n");
        printf("|      9---清空队列           |\n");
        printf("|      10---遍历打印队列      |\n");
        printf("|      11---退出              |\n");
        printf("|-----------------------------|\n");
        printf("请选择操作:\n");
        checkinput(&num);
        if (num >= 1 && num <= 11) {
            switch (num) {
            case 1: {//选择
                if (Q->data[0] != NULL) {
                    printf("\n已存在一个队列，请先销毁此链表！\n");
                }
                else {
                    Init(Q);
                }
                break;
            }
            case 2: {
                Destory(Q);
                break;
            }
            case 3: {
                Full(Q);
                break;
            }
            case 4: {
                Empty(Q);
                break;
            }
            case 5: {
                GetHead(Q);
                break;
            }
            case 6: {
                Length(Q);
                break;
            }
            case 7: {
                if (Q->data[0] == NULL) {
                    printf("\n请先输入【1】创建链队列\n");
                }
                else if (Q->length == MAXQUEUE - 1)
                {
                    printf("队列满了！不能再入队了！\n");
                }
                else {
                    CheckType(Q);
                }
                break;
            }
            case 8: {
                DeAQueue(Q);
                break;
            }
            case 9: {
                Clear(Q);
                break;
            }
            case 10: {
                Traverse(Q);
                break;
            }
            case 11:
                system("cls");
                exit(0);
                break;
            }
        }
        else
        {
            printf("请输入正确的数字。\n");    //错误提醒
        }
        system("pause");
    }
    return 0;
}