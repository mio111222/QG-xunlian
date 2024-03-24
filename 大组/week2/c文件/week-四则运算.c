#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node//ѹջ�ͳ�ջ����ջ������(�����ջ��ָǰһ��)
{
    char val;//����
    struct node* next;//ָ��
}pnode;
typedef struct seqstack
{
    int size;//��¼ջ�Ĵ�С
    pnode* top;//ָ��ջ��Ԫ��
}phead;
phead* initstack()//����ջ
{
    phead* istack = (phead*)malloc(sizeof(phead));//Ϊͷ�ڵ����ռ�
    if (istack != NULL)//��׳���ж�
    {
        istack->top = NULL;
        istack->size = 0;
    }
    return istack;
}
int isempty(phead* istack)//�ж�ջΪ��
{
    if (istack->top == NULL)
    {
        return 1;//ջΪ��
    }
    return 0;//ջ��Ϊ��
}
pnode* seqstack_top(phead* istack)//��ȡջ��Ԫ�ص����ݽڵ�
{
    if (istack->size != 0)//ջ��Ϊ��
    {
        return istack->top;//���ص���ջ�������ݽڵ������ջ����Ԫ��
    }
    return NULL;
}
pnode* seqstack_pop(phead* istack)//����ջ��Ԫ��
{
    if (isempty(istack) == 0)//ջ��Ϊ��
    {
        pnode* account = istack->top;//��¼ջ�������ݽڵ�
        istack->top = istack->top->next;//ָ��ջ����һ��Ԫ��
        istack->size--;//��¼ջ�Ĵ�С
        return account;//���ص��������ݽڵ�
    }
    return NULL;
}
void seqstack_push(phead* istack, char x)//ѹջ(��ջ)
{
    pnode* temp;//����ѹջ�����ݽڵ�
    temp = (pnode*)malloc(sizeof(pnode));
    temp->val = x;//���������
    temp->next = istack->top;//����ջ�������ݽڵ�
    istack->top = temp;//�䵱ջ��
    istack->size++;//��¼ջ��С�ı仯
    return;
}
//��������׺���ʽת��׺���ʽ�ĺ���
char buffer[256] = { 0 };//��ʼ������
//bufferΪ�����
void char_put(char ch)//�������ַ������������
{
    static int index = 0;//static���徲̬����,�ź����б�ʾindexֻ��ʼ��һ��,ֻ����index�ĸı�
    buffer[index++] = ch;
}
int priority(char ch)//�����Ƚ����ȼ�
{
    int ret = 0;
    switch (ch)
    {
    case '+'://case��͸
    case '-':
        ret = 1;
        break;
    case '*':
    case '/':
        ret = 2;
        break;
    default:
        break;
    }
    return ret;
}
int is_number(char ch)//�ǲ�������
{
    return(ch >= '0' && ch <= '9');//���ַ���1�����򷵻�0
}
int is_operator(char ch)//�ǲ��������
{
    return(ch == '+' || ch == '-' || ch == '*' || ch == '/');
}
int is_left(char ch)//�ǲ���������
{
    return(ch == '(');
}
int is_right(char ch)//�ǲ���������
{
    return(ch == ')');
}
double transform(char str[])//ʹ��const��������,������������׺ת���ɺ�׺
{
    phead* istack = initstack();//����һ��ջ
    int i = 0;
    int x = 0;//�����ж���û��û��*�ĳ˷�����5(2+3)
    if (str[i] == '-' && i == 0)//����һλΪ�����������һ��0��֤������ȷ
    {
        char_put('0');
        char_put(' ');
    }
    while (str[i] != '\0')//���������ַ���
    {
        //�ж��ǲ�������
        if (str[i] == '.' && (is_number(str[i-1]) == 0))
        {
            printf("С����ǰ������λ\n");
            return 0.0;
        }
        if (is_number(str[i]) == 1)
        {
            if (is_number(str[i + 1]) == 1 )//����1Ҳ������,��ֱ�ӷ�
            {
                char_put(str[i]);//����ֱ�ӷ�������(�����)
            }
            else if ( str[i+1] == '.')
            {
                char_put(str[i]);
                char_put(str[i + 1]);
                i++;
            }
            else//���治������,���һ���ո���Ϊ�ָ���
            {
                char_put(str[i]);
                char_put(' ');
            }
        }
        else if (is_operator((str[i])) == 1)
        {
            if ((is_number(str[i + 1]) == 0) && (is_operator(str[i+1]) == 0) && str[i+1] != '(')
            {
                printf("%cȱ������\n", str[i]);
                return -1.0;
            }
            if (str[i - 1] == '(' && str[i] == '-')
            {
                char_put('0');
                char_put(' ');
            }
            if (str[i + 1] == '0' && str[i] == '/')
            {
                printf("ILLEGAL");
                return 0.0;
            }
            if (isempty(istack) == 0)//ջ��Ϊ��
            {
                while ((isempty(istack) == 0) && (priority(str[i]) <= (priority(seqstack_top(istack)->val))))//ջ��Ϊ�ղ�������������ȼ�������ջ��
                {
                    char_put(seqstack_pop(istack)->val);//����������ջ���͵���ֱ������������
                    char_put(' ');
                }
            }
            seqstack_push(istack, str[i]);//�ٽ����������ջ
        }
        else if (is_left(str[i]))//������ֱ����ջ
        {
            if (is_number(str[i - 1]) == 1) //���ڼ����ж��ٲ���*�ĳ˷�
            {
                x++;
            }
            seqstack_push(istack, str[i]);
        }
        else if (is_right(str[i]))//�ж��ǲ���������
        {
            while (is_left(seqstack_top(istack)->val) != 1)//ջ�����������ŵ����
            {
                char_put(seqstack_pop(istack)->val);//�������洢�������
                if (isempty(istack) == 1)//ջΪ����δ�ҵ�������
                {
                    printf("û��ƥ�䵽������\n");
                    return -1.0;
                }
            }
            //��ʱƥ�䵽��������
            seqstack_pop(istack);
            //����������,���ﲢ���ñ���,���������������
            if (x != 0)                //���ڼ��㸺����
            {
                char_put('*');
                x--;
            }
        }
        else
        {
            printf("�в���ʶ����ַ�\n");
            return -1.0;
        }
        i++;
    }
    //���������Ѿ�
    if (str[i] == '\0')//�ɹ��������ַ���ĩβ
    {
        while (isempty(istack) == 0)//����ȫ��ջ��Ԫ��
        {
            if (seqstack_top(istack)->val == '(')//ջ��Ԫ��Ϊ������
            {
                printf("��û��ƥ�䵽��'(',ȱ��')'\n");
                return -1.0;
            }
            char_put(seqstack_pop(istack)->val);//��ջ��Ԫ�ط������մ�
        }
    }
    else
    {
        printf("����û����ɣ�\n");
    }
    return 1.0;
}

//�·�Ϊ�����׺���ʽ��Ҫ�ĺ���
typedef struct node1//�����ջ�Ǹ�����ջ
{
    double val;//����
    struct node1* next;//ָ��
}pnode1;

typedef struct seqstack1
{
    int size;//��¼ջ�Ĵ�С
    pnode1* top;//ָ��ջ��Ԫ��
}phead1;

phead1* initstack1()//����ջ
{
    phead1* istack = (phead1*)malloc(sizeof(phead1));//Ϊͷ�ڵ����ռ�
    if (istack != NULL)
    {
        istack->top = NULL;
        istack->size = 0;
    }
    return istack;
}
int isempty1(phead1* istack)//�ж�ջΪ��
{
    if (istack->top == NULL)
    {
        return 1;//ջΪ��
    }
    return 0;//ջ��Ϊ��
}
double seqstack_top1(phead1* istack)//��ȡջ��Ԫ��
{
    if (istack->size != 0)//ջ��Ϊ��
    {
        return istack->top->val;//���ص���ջ��������
    }
    return 99999;
}
double seqstack_pop1(phead1* istack)//����ջ��Ԫ��
{
    if (isempty1(istack) == 0)//ջ��Ϊ��
    {
        double account = istack->top->val;//��¼ջ�������ݽڵ�
        istack->top = istack->top->next;//ָ��ջ����һ��Ԫ��
        istack->size--;//��¼ջ��С�ı仯
        return account;//���ؽڵ�
    }
    return 99999;
}
void seqstack_push1(phead1* istack, double x)//ѹջ(��ջ)
{
    pnode1* temp;//�½��ڵ�
    temp = (pnode1*)malloc(sizeof(pnode1));
    temp->val = x;//��������
    temp->next = istack->top;//����ջ�������ݽڵ�
    istack->top = temp;//����ջ��
    istack->size++;//��¼ջ��С�ı仯
    return;
}
double express(double left, double right, char op)//opΪ�����,����������
{
    switch (op)
    {
    case '+':
        return left + right;
    case '-':
        return left - right;
    case '*':
        return left * right;
    case '/':
        if (right == 0)
        {
            return 999.0;
        }
        return left / right;
    default:
        break;
    }
    return -1.0;
}
int getsize(phead1* stack)
{
    return stack->size;
}
double calculate(char str[])//�����׺���ʽ
{
    phead1* istack2 = initstack1();//����ջ
    int i = 0;
    while (str[i] != '\0')//����������׺���ʽ
    {
        char a[10] = { 0 };
        int index = 0;
        if (is_number(str[i]) == 1)
        {
            while ( is_number(str[i]) == 1 || str[i] == '.' )   //��ȡ���֣�����С����
            {
                a[index] = str[i];
                index++;
                i++;
            }
            //�ɹ���ȡ����
            seqstack_push1(istack2, atof(a));//��������ջ
        }
        else if (is_operator(str[i]) == 1)
        {
            double right = seqstack_pop1(istack2);
            double left = seqstack_pop1(istack2);
            double ret = express(left, right, str[i]);
            if (ret == 999.0)//������Ϊ0��
            {
                printf("ILLEGAL");
                return 999.0;
            }
            seqstack_push1(istack2, ret);//��������ջ
        }
        else if (str[i] == ' ')
        {

        }
        else
        {
            printf("error\n");
            break;
        }
        i++;
    }
    if (str[i] == '\0' && getsize(istack2))
    {
        return seqstack_top1(istack2);
    }
    return 0;
}
int main()
{
    char str[1024] = { 0 };//������ÿ��Ԫ�ظ�ֵΪ'\0'
    printf("����������������ʽ:\n");
    scanf_s("%s", str, 1024);
    double number;
    number = transform(str);
    if (number == -1)
    {
        printf("���ʽת������:\n");
    }
    else if (number == 1)
    {
        printf("ת����ı��ʽ: %s\n", buffer);
    }
    else
    {
        return 0;
    }
    //�ɹ����ɺ�׺���ʽ


    //�·������׺���ʽ
    double num = calculate(buffer);
    if (num == 999.0)
    {
        return 0;
    }
    printf("����ǣ�%.2f\n", num);    //����ͨ���޸������С��λ��ʵ�ָ���С��λ�ļ���
    char test1,test2;
    printf("����س��˳�\n");    //���exe�ļ��޷����������ֱ�ӹرյ�����
    test1 = getchar();
    test2 = getchar();
}