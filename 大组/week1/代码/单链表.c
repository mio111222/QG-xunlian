//使用visual studio 2022编辑
#pragma warning(disable:4996) 
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<conio.h>
#include<windows.h>
#define LEN  sizeof(struct one_way)

char MenuText[11][40] = {
	"|[A]  create a list       |",         //创建链表
	"|[B]  foreach list        |",         //遍历链表
	"|[C]  search a node       |",         //寻找节点
	"|[D]  insert a node       |",         //插入节点
	"|[E]  detele a node       |",         //删除节点
	"|[F]  destroy a list      |",         //销毁链表
	"|[G]  find the middle     |",         //寻找中点
	"|[H]  judgement loop      |",         //判断成环
	"|[I]  reverse list        |",         //反转链表
	"|[J]  parity exchange     |",         //奇偶交换
	"|[K]  Exit                |"          //退出
};

void coutmenu(int highlight)
{
	int i;
	printf("创建链表以0结尾\n");
	printf("操作可以用字母或者方向键上下来移动\n");
	printf("选择到操作后以回车开始\n");
	printf("操作分别为：A.创建链表;B.遍历链表;C.查找节点;D.插入节点;E.删除节点\n");
	printf("     F.清空链表;G.寻找中点;H.判断成环;I.翻转链表;J.奇偶调换;K.结束\n");
	printf("\n");
	printf("\n---------------------------\n");
	for (i = 0; i < 11; i++) {
		if (i == highlight - 1)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x70);
		else
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
		printf("%s\n", MenuText[i]);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("---------------------------\n");

}

struct one_way {
	int money;
	struct one_way* next;
};

struct one_way* create_one_way();               //创建链表
void foreach(struct one_way* p);                //遍历链表
void search(struct one_way* p);                 //寻找节点
void insert(struct one_way* p);                 //插入节点
void delete(struct one_way* p);                 //删除节点
struct one_way* destory(struct one_way* p);     //销毁链表
void middle(struct one_way* p);                 //寻找中点
void judgment_loop(struct one_way* p);          //判断成环
struct one_way* reversal(struct one_way* p);    //反转链表
void parity(struct one_way* p);                 //奇偶交换

struct one_way* create_one_way() {                 //创建链表，当输入0时结束链表并返回链表头
	struct one_way* head, * p1, * p2;
	int cnt = 0;
    p1 = p2 = (struct one_way*)malloc(LEN);
	head = (struct one_way*)malloc(LEN);
	head->money = 0, head->next = p2;
	scanf_s("%d", &p2->money);
	cnt++;
	while (p2->money != 0) {
		p1 = p2;
		p2 = (struct one_way*)malloc(LEN);
		p1->next = p2;
		scanf_s("%d", &p2->money);
		cnt++;
	}
	if (cnt == 1) 
		return NULL;
	free(p2);
	p1->next = NULL;
	return head;
}

void foreach(struct one_way* p) {               //遍历链表
	struct one_way* p5;
	if (p == NULL || p->next==NULL) {
		printf("遍历失败，空链表\n");
		return;
	}
	p5 = p->next;
	while (p5 != NULL) {
		printf("%d ", p5->money);
		p5 = p5->next;
	}
	printf("\n");
	printf("链表遍历完毕\n");
	return;
}

void search(struct one_way* p) {         //寻找节点(链表地址)
	struct one_way* pp;
	int what;                            //判断操作
	pp = p->next;
	int cnt = 1, judge = 0,mat;
	printf("请输入操作（1.寻找对应节点，2.寻找对应值,0.结束操作）\n");
	scanf_s("%d", &what);
	if (what == 1) {
		printf("请输入寻找的节点位置：\n");
		scanf_s("%d", &mat);
		while (pp != NULL) {
			if (cnt == mat) {
				judge = 1;
				break;
			}
			cnt++;
			pp = pp->next;
		}
		if (judge == 1) {
			printf("已经寻找到%d位，对应值为%d\n", mat, pp->money);
		}
		else {
			printf("不存在%d位\n",mat);
		}
	}
	if (what == 2) {
		printf("请输入寻找的值：\n");
		scanf_s("%d", &mat);
		while (pp != NULL) {
			if (pp->money == mat) {
				judge = 1;
				break;
			}
			cnt++;
			pp = pp->next;
		}
		if (judge == 1) {
			printf("已经寻找到%d，在第%d位\n", mat, cnt);
		}
		else {
			printf("未寻找到%d值\n",mat);
		}
	}
	if (what == 0) return;
	search(p);
}

void insert(struct one_way* p) {            //插入节点
	struct one_way* p1,* p2,* p3;
	int n, mat;
	int cnt = 1;                  //因为零号位head是空的，所以从有数据的位置开始算第一位
	p1 = p->next;
	p2 = p;
	printf("请输入插入点以及插入值（用空格隔开）：\n");
	scanf_s("%d %d", &n, &mat);
	while (p1 != NULL) {
		if (cnt == n) break;
		cnt++;
		p1 = p1->next;
		p2 = p2->next;
	}
	if (cnt != n) {
		printf("无法找到对应节点\n");
		return;
	}
	p3 = (struct one_way*)malloc(sizeof(LEN));
	p2->next = p3;
	p3->money = mat;
	p3->next = p1;
}

void delete(struct one_way* p){              //删除节点(链表地址和删除的位置)
	int n,cnt=1,judge=0;
	printf("请输入删除的节点位置:\n");
	scanf_s("%d", &n);
	struct one_way* p1, * p2;
	p1 = p->next;
	p2 = p;
	while (p1 != NULL) {
		if (cnt == n) {
			judge = 1;
			break;
		}
		p2 = p2->next;
		cnt++;
		p1 = p1->next;
	}
	if (judge == 1) {
		p2->next = p1->next;
		free(p1);
		printf("成功删除第%d节点\n",n);
	}
	else {
		printf("未找到节点，删除失败\n");
	}
	return;
}

struct one_way* destory(struct one_way* p) {             //销毁链表
	struct one_way* head, * p1, * p2;
	head = p;
	if (p == NULL) {
		printf("空链表，无操作\n");
		return NULL;
	}
	p1 = head->next;
	while (p1 != NULL) {
		p2 = p1->next;
		free(p1);
		p1 = p2;
	}
	free(head);
	printf("销毁完成\n");
	return NULL;
}

void middle(struct one_way* p) {              //寻找中点
	struct one_way* p1;
	int cnt = 0,n;
	if (p->next == NULL) {
		printf("空链表，无操作\n");
		return;
	}
	p1 = p->next;
	while (p1 != NULL) {
		p1 = p1->next;
		cnt++;
	}
	if (cnt % 2 == 0) {             //偶数情况
		printf("链表一共有%d个节点，中点%d和%d分别为： ",cnt,cnt/2,cnt/2+1);
		n = cnt / 2,cnt=1;
		p1 = p->next;
		while (cnt != n) {
			p1 = p1->next;
			cnt++;
		}
		printf("%d ", p1->money);
		p1 = p1->next;
		printf("%d\n", p1->money);
	}
	else {                         //奇数情况
		printf("链表一共有%d个节点,中点%d为： ", cnt, cnt / 2 + 1);
		n = cnt / 2 + 1, cnt = 1 ;
		p1 = p->next;
		while (cnt != n) {
			p1 = p1->next;
			cnt++;
		}
		printf("%d\n", p1->money);
	}
}

void judgment_loop(struct one_way* p) {       //判断成环
	struct one_way* p1, * p2;
	int judge = 0;
	p1 = p;
	p2 = p->next;
	while (p2 != NULL) {
		p1 = p1->next;
		p2 = p2->next;
		if (p2 != NULL) p2 = p2->next;
		if (p1 == p2) {
			judge = 1;
			break;
		}
	}
	if (judge == 1) {
		printf("链表成环\n");
	}
	else {
		printf("链表未成环\n");
	}
	return;
}

struct one_way* reversal(struct one_way* p) {            //反转链表
	struct one_way* p1, * p2, * p3;
	p1 = NULL;
	p2 = p->next;
	while (p2 ) {
		p3 = p2->next;
		p2->next = p1;
		p1 = p2;
		p2 = p3;
	}
	p->next = p1;
	printf("翻转完毕\n");
	return p;
}

void parity(struct one_way* p) {              //奇偶交换
	struct one_way* p1=NULL, * p2=NULL, * p3=NULL;
	int cnt = 0;
	if (p ==NULL ||p->next == NULL) {
		printf("无链表可反转");
		return;
	}
	if (p->next->next == NULL) {
		printf("奇偶反转完成");
		return;
	}
	p1 = p->next;
	while (p1 != NULL) {
		cnt++;
		p1 = p1->next;
	}
	int i;
	p1 = p->next;
	p2 = p1->next;
	p3 = p2->next;
	p->next = p2;
	if (p3 == NULL || p3->next == NULL) {
		p2->next = p1;
		p1->next = p3;
		printf("奇偶反转完成");
		return;
	}
	for (i = 1; i <= cnt / 2; i++) {
		p2->next = p1;
		p2 = p3->next;
		p1->next = p2;
		p1 = p3;
		p3 = p2->next;
		if (p3 == NULL || p3->next == NULL ) {
			break;
		}
	}
	p2->next = p1;
	if (cnt % 2 == 0) {
		p1->next = NULL;
	}
	else {
		p1->next = p3;
		p3->next = NULL;
	}
	printf("奇偶反转完成");
}

//int main()
//{
//	struct one_way* test, * pp;
//	//struct one_way* p4 , *p5;                  //链表成环生成器
//	//test=(struct one_way*)malloc(sizeof(LEN));
//	//p4= (struct one_way*)malloc(sizeof(LEN));
//	//test->money = 0, test->next = p4;
//	//printf("1\n");
//	//p5 = p4;
//	//p4->money = 1;
//	//p4= (struct one_way*)malloc(sizeof(LEN));
//	//p5->next = p4;
//	//p5 = p4;
//	//p4 = (struct one_way*)malloc(sizeof(LEN));
//	//p5->next = p4;
//	//p5 = p4;
//	//p5->next = test;
//	test = create_one_way();
//	foreach(test);
//	//judgment_loop(test);
//	//middle(test);
//	//search(test);
//	//insert(test);
//	//test=destory(test);
//	//test = reversal(test);
//	parity(test);
//	foreach(test);
//	//delete(test);
//	/*if (ceshi != NULL) {
//		pp = ceshi->next;
//	}
//	else return 0;
//	while (pp != NULL) {
//		printf("%d ", pp->money);
//		pp = pp->next;
//	}*/
//}

int main()
{
	int high=1;
	struct one_way* test=NULL;
	char c;
	coutmenu(high);
	for (;;) {
		if (_kbhit()) {
			c = _getch();
			if (GetAsyncKeyState(VK_UP)) {           //检测键盘上下移动 
				high = (high > 1) ? high - 1 : 11;
				Sleep(140);
				system("cls");
				coutmenu(high);
			}
			if (GetAsyncKeyState(VK_DOWN)) {
				high = (high < 11) ? high + 1 : 1;
				Sleep(140);
				system("cls");
				coutmenu(high);
			}
			if (c <= 'z' && c >= 'a')c = c - ('a' - 'A');      //检测字母输入 
			if (c <= 'K' && c >= 'A') {
				//对应处理的程序段
				high = c - 'A' + 1;
				system("cls");
				coutmenu(high);
			}
			else if (c == '\r') {
				switch (high)
				{
					system("Color F1");
					system("cls");
					coutmenu(high);
				case 1:
					system("cls");
					coutmenu(high);
					printf("请开始输入：\n");
					test = create_one_way();
					system("cls");
					coutmenu(high);
					printf("链表创建完成\n");
					break;
				case 2:
					system("cls");
					coutmenu(high);
					foreach(test);
					break;
				case 3:
					system("cls");
					coutmenu(high);
					search(test);
					printf("结束查找\n");
					break;
				case 4:
				    system("cls");
					coutmenu(high);
					insert(test);
					system("cls");
					coutmenu(high);
					printf("插入成功\n");
					break;
				case 5:
					system("cls");
					coutmenu(high);
					delete(test);
					break;
				case 6:
					system("cls");
					coutmenu(high);
					test = destory(test);
					break;
				case 7:
					system("cls");
					coutmenu(high);
					middle(test);
					break;
                 case 8:
					system("cls");
					coutmenu(high);
					judgment_loop(test);
					break;
              case 9:
					system("cls");
					coutmenu(high);
					test = reversal(test);
					break;
              case 10:
					system("cls");
					coutmenu(high);
					parity(test);
					break;
              case 11:
					system("cls");
					coutmenu(high);
					system("cls");
					printf("程序结束\n");
					return 0;
					break;
				}
			}
		}
	}
}