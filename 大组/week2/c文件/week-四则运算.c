#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node//压栈和出栈都在栈顶进行(这里的栈顶指前一段)
{
    char val;//数据
    struct node* next;//指针
}pnode;
typedef struct seqstack
{
    int size;//记录栈的大小
    pnode* top;//指向栈顶元素
}phead;
phead* initstack()//创建栈
{
    phead* istack = (phead*)malloc(sizeof(phead));//为头节点分配空间
    if (istack != NULL)//健壮性判断
    {
        istack->top = NULL;
        istack->size = 0;
    }
    return istack;
}
int isempty(phead* istack)//判断栈为空
{
    if (istack->top == NULL)
    {
        return 1;//栈为空
    }
    return 0;//栈不为空
}
pnode* seqstack_top(phead* istack)//获取栈顶元素的数据节点
{
    if (istack->size != 0)//栈不为空
    {
        return istack->top;//返回的是栈顶的数据节点而不是栈顶的元素
    }
    return NULL;
}
pnode* seqstack_pop(phead* istack)//弹出栈顶元素
{
    if (isempty(istack) == 0)//栈不为空
    {
        pnode* account = istack->top;//记录栈顶的数据节点
        istack->top = istack->top->next;//指向栈顶下一个元素
        istack->size--;//记录栈的大小
        return account;//返回弹出的数据节点
    }
    return NULL;
}
void seqstack_push(phead* istack, char x)//压栈(入栈)
{
    pnode* temp;//进行压栈的数据节点
    temp = (pnode*)malloc(sizeof(pnode));
    temp->val = x;//填充数据域
    temp->next = istack->top;//连接栈顶的数据节点
    istack->top = temp;//充当栈顶
    istack->size++;//记录栈大小的变化
    return;
}
//下面是中缀表达式转后缀表达式的函数
char buffer[256] = { 0 };//初始化数组
//buffer为结果串
void char_put(char ch)//用来将字符放入放入结果串
{
    static int index = 0;//static定义静态变量,放函数中表示index只初始化一次,只保留index的改变
    buffer[index++] = ch;
}
int priority(char ch)//用来比较优先级
{
    int ret = 0;
    switch (ch)
    {
    case '+'://case穿透
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
int is_number(char ch)//是不是数字
{
    return(ch >= '0' && ch <= '9');//数字返回1，否则返回0
}
int is_operator(char ch)//是不是运算符
{
    return(ch == '+' || ch == '-' || ch == '*' || ch == '/');
}
int is_left(char ch)//是不是左括号
{
    return(ch == '(');
}
int is_right(char ch)//是不是右括号
{
    return(ch == ')');
}
double transform(char str[])//使用const保护数据,函数用来将中缀转换成后缀
{
    phead* istack = initstack();//创建一个栈
    int i = 0;
    int x = 0;//用于判断有没有没带*的乘法，如5(2+3)
    if (str[i] == '-' && i == 0)//若第一位为负数，则加上一个0保证计算正确
    {
        char_put('0');
        char_put(' ');
    }
    while (str[i] != '\0')//遍历整个字符串
    {
        //判断是不是数字
        if (str[i] == '.' && (is_number(str[i-1]) == 0))
        {
            printf("小数点前无整数位\n");
            return 0.0;
        }
        if (is_number(str[i]) == 1)
        {
            if (is_number(str[i + 1]) == 1 )//后面1也是数字,则直接放
            {
                char_put(str[i]);//数字直接放入结果串(即输出)
            }
            else if ( str[i+1] == '.')
            {
                char_put(str[i]);
                char_put(str[i + 1]);
                i++;
            }
            else//后面不是数字,添加一个空格作为分隔符
            {
                char_put(str[i]);
                char_put(' ');
            }
        }
        else if (is_operator((str[i])) == 1)
        {
            if ((is_number(str[i + 1]) == 0) && (is_operator(str[i+1]) == 0) && str[i+1] != '(')
            {
                printf("%c缺少右数\n", str[i]);
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
            if (isempty(istack) == 0)//栈不为空
            {
                while ((isempty(istack) == 0) && (priority(str[i]) <= (priority(seqstack_top(istack)->val))))//栈不为空并且新运算符优先级不高于栈顶
                {
                    char_put(seqstack_pop(istack)->val);//满足条件的栈顶就弹出直到不满足条件
                    char_put(' ');
                }
            }
            seqstack_push(istack, str[i]);//再将该运算符入栈
        }
        else if (is_left(str[i]))//左括号直接入栈
        {
            if (is_number(str[i - 1]) == 1) //用于计数有多少不带*的乘法
            {
                x++;
            }
            seqstack_push(istack, str[i]);
        }
        else if (is_right(str[i]))//判断是不是右括号
        {
            while (is_left(seqstack_top(istack)->val) != 1)//栈顶不是左括号的情况
            {
                char_put(seqstack_pop(istack)->val);//弹出并存储到结果串
                if (isempty(istack) == 1)//栈为空仍未找到左括号
                {
                    printf("没有匹配到左括号\n");
                    return -1.0;
                }
            }
            //此时匹配到了左括号
            seqstack_pop(istack);
            //弹出左括号,这里并不用保存,即两个括号相抵消
            if (x != 0)                //用于计算负数，
            {
                char_put('*');
                x--;
            }
        }
        else
        {
            printf("有不能识别的字符\n");
            return -1.0;
        }
        i++;
    }
    //遍历完了已经
    if (str[i] == '\0')//成功遍历到字符串末尾
    {
        while (isempty(istack) == 0)//弹出全部栈中元素
        {
            if (seqstack_top(istack)->val == '(')//栈顶元素为左括号
            {
                printf("有没有匹配到的'(',缺少')'\n");
                return -1.0;
            }
            char_put(seqstack_pop(istack)->val);//将栈中元素放入最终串
        }
    }
    else
    {
        printf("遍历没有完成！\n");
    }
    return 1.0;
}

//下方为计算后缀表达式需要的函数
typedef struct node1//这里的栈是浮点型栈
{
    double val;//数据
    struct node1* next;//指针
}pnode1;

typedef struct seqstack1
{
    int size;//记录栈的大小
    pnode1* top;//指向栈顶元素
}phead1;

phead1* initstack1()//创建栈
{
    phead1* istack = (phead1*)malloc(sizeof(phead1));//为头节点分配空间
    if (istack != NULL)
    {
        istack->top = NULL;
        istack->size = 0;
    }
    return istack;
}
int isempty1(phead1* istack)//判断栈为空
{
    if (istack->top == NULL)
    {
        return 1;//栈为空
    }
    return 0;//栈不为空
}
double seqstack_top1(phead1* istack)//获取栈顶元素
{
    if (istack->size != 0)//栈不为空
    {
        return istack->top->val;//返回的是栈顶的数据
    }
    return 99999;
}
double seqstack_pop1(phead1* istack)//弹出栈顶元素
{
    if (isempty1(istack) == 0)//栈不为空
    {
        double account = istack->top->val;//记录栈顶的数据节点
        istack->top = istack->top->next;//指向栈顶下一个元素
        istack->size--;//记录栈大小的变化
        return account;//返回节点
    }
    return 99999;
}
void seqstack_push1(phead1* istack, double x)//压栈(入栈)
{
    pnode1* temp;//新建节点
    temp = (pnode1*)malloc(sizeof(pnode1));
    temp->val = x;//填入数据
    temp->next = istack->top;//连接栈顶的数据节点
    istack->top = temp;//更新栈顶
    istack->size++;//记录栈大小的变化
    return;
}
double express(double left, double right, char op)//op为运算符,返回运算结果
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
double calculate(char str[])//计算后缀表达式
{
    phead1* istack2 = initstack1();//创建栈
    int i = 0;
    while (str[i] != '\0')//遍历整个后缀表达式
    {
        char a[10] = { 0 };
        int index = 0;
        if (is_number(str[i]) == 1)
        {
            while ( is_number(str[i]) == 1 || str[i] == '.' )   //读取数字（包括小数）
            {
                a[index] = str[i];
                index++;
                i++;
            }
            //成功读取数字
            seqstack_push1(istack2, atof(a));//将该数入栈
        }
        else if (is_operator(str[i]) == 1)
        {
            double right = seqstack_pop1(istack2);
            double left = seqstack_pop1(istack2);
            double ret = express(left, right, str[i]);
            if (ret == 999.0)//被除数为0了
            {
                printf("ILLEGAL");
                return 999.0;
            }
            seqstack_push1(istack2, ret);//运算结果入栈
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
    char str[1024] = { 0 };//将数组每个元素赋值为'\0'
    printf("请输入四则运算表达式:\n");
    scanf_s("%s", str, 1024);
    double number;
    number = transform(str);
    if (number == -1)
    {
        printf("表达式转换错误:\n");
    }
    else if (number == 1)
    {
        printf("转化后的表达式: %s\n", buffer);
    }
    else
    {
        return 0;
    }
    //成功换成后缀表达式


    //下方计算后缀表达式
    double num = calculate(buffer);
    if (num == 999.0)
    {
        return 0;
    }
    printf("结果是：%.2f\n", num);    //可以通过修改输出的小数位来实现更多小数位的计算
    char test1,test2;
    printf("输入回车退出\n");    //解决exe文件无法看到结果就直接关闭的问题
    test1 = getchar();
    test2 = getchar();
}