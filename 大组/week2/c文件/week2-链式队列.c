#include<stdio.h>
#include<stdlib.h>
#define MAXQUEUE 11

//ѭ�����нṹ

typedef struct Aqueue          //��ʽ����
{
    void* data[MAXQUEUE];
    int front;
    int rear;
    int length;
    int type[MAXQUEUE];
} AQueue;

typedef enum                   //�ж�true��false
{
    FALSE = 0,
    TRUE = 1
} Status;

void Init(AQueue* Q);//��ʼ������
void Destory(AQueue* Q);//�ݻٶ���
Status Full(const AQueue* Q);//�ж��Ƿ���
Status Empty(const AQueue* Q);//�ж��Ƿ��
Status GetHead(AQueue* Q);//��ѯͷ�ڵ�
void Length(AQueue* Q);//��ѯ���г���
Status EnAQueue(AQueue* Q, void* data, int s);//���
Status DeAQueue(AQueue* Q);//����
void Clear(AQueue* Q);//��ն���
Status Traverse(const AQueue* Q);//��������
void checkinput(int* r);//�ж�����
void CheckType(AQueue* Q);//�ж���������

void Init(AQueue* Q)//��ʼ������
{
    int i;
    Q->front = 0;//ͷ�ڵ�
    Q->rear = 0;//β�ڵ㰴��������ʼ
    for (i = 0; i < MAXQUEUE; i++) {
        Q->data[i] = (void*)malloc(21);
        if (i < MAXQUEUE - 1)
            CheckType(Q);//��������
    }
    printf("���д����ɹ���\n");
}

void Destory(AQueue* Q)//���ٶ���
{
    if (Q->data[0] == NULL)//�ж϶����Ƿ�������
    {
        printf("�������롾1����������\n");
        return;
    }
    else {
        for (int i = 0; i < MAXQUEUE; i++)
            free(Q->data[i]);//��ն�������
        Q->data[0] = NULL;
        printf("�������ٳɹ���\n");
    }
}

Status Full(const AQueue* Q)//�ж϶����Ƿ���
{
    if (Q->data[0] == NULL)//�޶������
    {
        printf("�������롾1����������\n");
        return FALSE;
    }
    if (Q->length == 0) {//�޶������
        return FALSE;
    }
    if (Q->length == MAXQUEUE - 1)
    {
        printf("����һ�������У�\n");
        return TRUE;
    }
    else {
        printf("�ⲻ��һ�������У�\n");
        return FALSE;
    }
}

Status Empty(const AQueue* Q)//�����Ƿ�Ϊ��
{
    if (Q->data[0] == NULL)//δ��������
    {
        printf("�������롾1����������\n");
        return FALSE;
    }
    else if (Q->length == 0) {
        printf("����һ���ն��У�\n");
        return TRUE;
    }
    else {
        printf("�ⲻ��һ���ն��У�\n");
        return FALSE;
    }
}

Status GetHead(AQueue* Q)//��ȡ��ͷ
{
    if (Q->data[0] == NULL)
    {
        printf("�������롾1����������\n");
        return FALSE;
    }
    else if (Q->length == 0)
    {
        printf("����Ϊ�գ�û�ж�ͷ��\n");
        return FALSE;
    }
    else {
        if (Q->type[Q->front] == 8)
            printf("��ͷԪ���ǣ���%lf��\n", *(double*)Q->data[Q->front]);
        if (Q->type[Q->front] == 1)
            printf("��ͷԪ���ǣ���%c��\n", *(char*)Q->data[Q->front]);
        if (Q->type[Q->front] == 4)
            printf("��ͷԪ���ǣ���%d��\n", *(int*)Q->data[Q->front]);
        if (Q->type[Q->front] == 20)
            printf("��ͷԪ���ǣ���%s��\n", (char*)Q->data[Q->front]);
        return TRUE;
    }
}

void Length(AQueue* Q)//�жϸö��г���
{
    if (Q->data[0] == NULL)
    {
        printf("�������롾1����������\n");
        return FALSE;
    }
    else {
        printf("���г���Ϊ:%d\n", Q->length);
        return;
    }
}

Status EnAQueue(AQueue* Q, void* data, int s)//���
{
    if (Q->length == 0)//��������������ʱ
    {
        Q->data[Q->front] = data;//����λ��
        Q->rear = (Q->rear + 1) % MAXQUEUE;//��βָ�����
        Q->type[Q->front] = s;//�����ж�
        Q->length++;//���г��ȼ���
        printf("��ӳɹ���\n");
        Traverse(Q);
        return TRUE;
    }
    else {
        Q->data[Q->rear] = data;
        Q->type[Q->rear] = s;
        Q->rear = (Q->rear + 1) % MAXQUEUE;
        Q->length++;
        printf("��ӳɹ���\n");
        Traverse(Q);
        return TRUE;
    }
}

Status DeAQueue(AQueue* Q)//����
{
    if (Q->data[0] == NULL)//�ж϶����Ƿ��
    {
        printf("�������롾1����������\n");
        return FALSE;
    }
    else if (Q->length == 0)
    {
        printf("�����ǿյģ������˶ӣ�\n");
        return FALSE;
    }
    else {
        Q->front = (Q->front + 1) % MAXQUEUE;//��front����ָ����
        Q->length--;
        printf("���ӳɹ���\n");
        Traverse(Q);
        return TRUE;
    }
}

void Clear(AQueue* Q)//�������
{
    if (Q->data[0] == NULL)
    {
        printf("�������롾1����������\n");
        return FALSE;
    }
    else if (Q->length == 0)
    {
        printf("�����Ѿ��ǿյ��ˣ�\n");
        return;
    }
    else {
        Q->front = Q->rear = 0;
        Q->length = 0;
        printf("������ճɹ���\n");
    }
}

Status Traverse(const AQueue* Q)//��������
{
    if (Q->data[0] == NULL)//�ж��Ƿ��
    {
        printf("�������롾1����������\n");
        return FALSE;
    }
    else if (Q->length == 0)
    {
        printf("��������ʲô��û��!\n");
        return FALSE;
    }
    else {
        printf("����Ϊ��\n");//�������
        printf("��head��");
        for (int i = Q->front; i < Q->front + Q->length; i++) {
            printf(" -> ");
            if (Q->type[i] == 8)
                printf("��%lf��", *(double*)Q->data[i]);
            if (Q->type[i] == 1)
                printf("��%c��", *(char*)Q->data[i]);
            if (Q->type[i] == 4)
                printf("��%d��", *(int*)Q->data[i]);
            if (Q->type[i] == 20)
                printf("��%s��", (char*)Q->data[i]);
        }
        printf("\n");
        return TRUE;
    }
}

void checkinput(int* r) {//������룬��������������ʱ�����˱����
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
            printf("����������������룡\n");
        }
    } while (error);
    *r = atoi(c);//���ַ�תΪint
}

void CheckType(AQueue* Q) {//�������ݣ����ҽ������͵�ѡ��
    printf("|---------------------|\n");
    printf("|    ��������ѡ��     |\n");
    printf("|    1---����         |\n");
    printf("|    2---�ַ���       |\n");
    printf("|    3---������       |\n");
    printf("|    4---�ַ���       |\n");
    printf("|---------------------|\n");
    int t = 1, s;//tȷ�����ͣ�s�����͵��ֽڴ�С����type������
    printf("��������������ͣ�:\n");
    checkinput(&t);//�ж�����
    if (t > 0 && t < 5) {
        switch (t)
        {
        case 1: {//����
            int* a = (int*)malloc(sizeof(int));
            s = 4;
            printf("�����롾�������ݡ���\n");
            checkinput(a);
            EnAQueue(Q, a, s);
            break;
        }
        case 2: {//�ַ���
            char* a = (char*)malloc(sizeof(char));
            s = 1;
            printf("�����롾�ַ������ݡ���\n");
            scanf_s("%c", a);
            getchar();
            EnAQueue(Q, a, s);
            break;
        }
        case 3: {//������
            double* a = (double*)malloc(sizeof(double));
            s = 8;
            printf("�����롾���������ݡ���\n");
            scanf_s("%lf", a);
            getchar();
            EnAQueue(Q, a, s);
            break;
        }
        case 4: {//�ַ�����
            char* a = (char*)malloc(20 * sizeof(char));
            s = 20;
            printf("�����롾�ַ��������ݡ�����󳤶�Ϊ20����\n");
            gets(a);
            EnAQueue(Q, a, s);
            break;
        }
        }
    }
    else
    {
        printf("Ӧ������[1,4]֮���������\n");
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
        printf("|      1---��������           |\n");
        printf("|      2---���ٶ���           |\n");
        printf("|      3---�ж�������         |\n");
        printf("|      4---�жϿն���         |\n");
        printf("|      5---��ö�ͷԪ��       |\n");
        printf("|      6---��ö��г���       |\n");
        printf("|      7---���               |\n");
        printf("|      8---����               |\n");
        printf("|      9---��ն���           |\n");
        printf("|      10---������ӡ����      |\n");
        printf("|      11---�˳�              |\n");
        printf("|-----------------------------|\n");
        printf("��ѡ�����:\n");
        checkinput(&num);
        if (num >= 1 && num <= 11) {
            switch (num) {
            case 1: {//ѡ��
                if (Q->data[0] != NULL) {
                    printf("\n�Ѵ���һ�����У��������ٴ�����\n");
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
                    printf("\n�������롾1������������\n");
                }
                else if (Q->length == MAXQUEUE - 1)
                {
                    printf("�������ˣ�����������ˣ�\n");
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
            printf("��������ȷ�����֡�\n");    //��������
        }
        system("pause");
    }
    return 0;
}