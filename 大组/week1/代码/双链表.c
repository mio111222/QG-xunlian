//使用visual studio 2022编辑
#pragma warning(disable:4996) 
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<conio.h>
#include<windows.h>
#define LEN  sizeof(struct two_way)

char MenuText[8][40] = {
	"|[A]  create a list       |",         //创建链表
	"|[B]  foreach list        |",         //遍历链表
	"|[C]  search a node       |",         //寻找节点
	"|[D]  insert a node(head) |",         //头插
	"|[E]  insert a node(end)  |",         //尾插
	"|[F]  detele a node       |",         //删除节点
	"|[G]  destroy a list      |",         //销毁链表
	"|[H]  Exit                |"
};

void coutmenu(int highlight)
{
	int i;
	printf("创建链表以0结尾\n");
	printf("操作可以用字母或者方向键上下来移动\n");
	printf("选择到操作后以回车开始\n");
	printf("操作分别为：A.创建链表;B.遍历链表;C.查找节点;D.头插节点;E.尾插节点;F.删除节点;G.销毁链表;H.结束\n");
	printf("\n");
	printf("\n---------------------------\n");
	for (i = 0; i < 8; i++) {
		if (i == highlight - 1)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x70);
		else
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
		printf("%s\n", MenuText[i]);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("---------------------------\n");
}

struct two_way {
	struct two_way* front;
	int money;
	struct two_way* next;
};

struct two_way* create_two_way();            //创建
void foreach(struct two_way* p);             //遍历
void search(struct two_way* p);              //查找
void insert_head(struct two_way* p);         //头插
void insert_end(struct two_way* p);          //尾插
void delete(struct two_way* p);              //删除某点
void destroy (struct two_way* p);            //销毁

struct two_way* create_two_way() {                      //当输入0时结束
	struct two_way* head, * p1, * p2, * p3;
	int cnt = 0;
	head = (struct two_way*)malloc(sizeof(LEN));
	head->front = NULL;
	head->money = 0;
	p3 = head;
	p1 = p2 = (struct two_way*)malloc(sizeof(LEN));
	head->next = p2;
	p2->front = head;
	scanf_s("%d", &p2->money);
	cnt++;
	while (p2->money != 0) {
		p3 = p3->next;
		p1 = p2;
		p2 = (struct two_way*)malloc(LEN);
		p1->next = p2;
		p2->front = p1;
		scanf_s("%d", &p2->money);
		cnt++;
	}
	if (cnt == 1) return NULL;
	else
	p1->next = NULL;
	return head;
}

void foreach(struct two_way* p) {                //遍历链表
	struct two_way * p1, * p2;
	if (p != NULL && p->next!=NULL ) {
		p1 = p2 = p->next;
	}
	else {
		printf("遍历失败，空链表\n");
		return;
	}
	printf("顺序遍历： ");
	while (p1 != NULL) {
		printf("%d ", p1->money);
		p2 = p1;
		p1 = p1->next;
	}
	printf("\n");
	printf("倒序遍历： ");
	while (p2 != NULL && p2->money != 0) {
		printf("%d ", p2->money);
		p2 = p2->front;
	}
	return;
}

void search(struct two_way* p) {         //寻找节点(链表地址)
	struct two_way* pp;
	int what;                            //判断操作
	pp = p->next;
	int cnt = 1, judge = 0, mat;
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
			printf("不存在%d位\n", mat);
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
			printf("未寻找到%d值\n", mat);
		}
	}
	if (what == 0) return;
	search(p);
}

void insert_head(struct two_way* p) {         //头插
	struct two_way* p1, * p2, * p3;
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
	p3 = (struct two_way*)malloc(sizeof(LEN));
	p2->next = p3;
	p3->front = p2;
	p3->money = mat;
	p3->next = p1;
	p1->front = p3;
	return;
}

void insert_end(struct two_way* p) {          //尾插
	struct two_way* p1,* p2,* p3;
	p1 = p->next;
	p2 = p;
	while (p1 != NULL) {
		p2 = p2->next;
		p1 = p1->next;
	}
	int n, mat,cnt=2;
	printf("请输入插入点以及插入值（用空格隔开）：\n");
	scanf_s("%d %d", &n, &mat);
	if (n == 1) {
		p3 = (struct two_way*)malloc(sizeof(LEN));
		p3->money = mat;
		p3->next = NULL;
		p3->front = p2;
		p2->next = p3;
		return;
	}
	p1 = p2;
	p2 = p1->front;
	while (p2 != NULL) {
		if (cnt == n) break;
		cnt++;
		p2 = p2->front;
		p1 = p1->front;
	}
	if (cnt != n) {
		printf("无法找到对应节点\n");
		return;
	}
	p3 = (struct two_way*)malloc(sizeof(LEN));
	p3->money = mat;
	p1->front = p3;
	p3->next = p1;
	p2->next = p3;
	p3->front = p2;
	return;
}

void delete(struct two_way* p) {              //删除节点
	int n, cnt = 1, judge = 0;
	printf("请输入删除的节点位置:\n");
	scanf_s("%d", &n);
	struct two_way* p1, * p2, *p3;
	p1 = p;
	p2 = p->next;
	if (p2->next == NULL) {
		if (n == 1) {
			p->next = NULL;
			printf("成功删除第%d节点\n", n);
			free(p2);
		}
		else {
			printf("未找到节点，删除失败\n");
			return;
		}
	}
	p3 = p2->next;
	while (p3 != NULL) {
		if (cnt == n) {
			break;
		}
		p3 = p3->next;
		p2 = p2->next;
		cnt++;
		p1 = p1->next;
		printf("这");
	}
	if (cnt==n) {
		p1->next = p3;
		p3->front = p1;
		free(p2);
		printf("成功删除第%d节点\n", n);
	}
	else {
		printf("未找到节点，删除失败\n");
	}
	return;
}
//int main()
//{
//	struct two_way* ceshi, * p1, * p2;
//	ceshi = create_two_way();
//	if (ceshi != NULL) {
//		p1 = p2 = ceshi->next;
//	}
//	else return 0;
//	while (p1 != NULL) {
//		printf("%d ", p1->money);
//		p2 = p1;
//		p1 = p1->next;
//	}
//	printf("\n");
//	while (p2 != NULL && p2->money!=0 ) {
//		printf("%d ", p2->money);
//		p2 = p2->front;
//	}
//}

int main()
{
	int high=1;
	char c;
	struct two_way* test=NULL;
	coutmenu(high);
	for (;;) {
		if (_kbhit()) {
			c = _getch();
			if (GetAsyncKeyState(VK_UP)) {           //检测键盘上下移动 
				high = (high > 1) ? high - 1 : 8;
				Sleep(140);
				system("cls");
				coutmenu(high);
			}
			if (GetAsyncKeyState(VK_DOWN)) {
				high = (high < 8) ? high + 1 : 1;
				Sleep(140);
				system("cls");
				coutmenu(high);
			}
			if (c <= 'z' && c >= 'a')c = c - ('a' - 'A');      //检测字母输入 
			if (c <= 'H' && c >= 'A') {
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
					printf("请开始输入：\n");
					test = create_two_way();
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
					system("cls");
					coutmenu(high);
					printf("结束查找\n");
					break;
				case 4:
					system("cls");
					coutmenu(high);
					insert_head(test);
					printf("插入成功\n");
					break;
				case 5:
					system("cls");
					coutmenu(high);
					insert_end(test);
					printf("插入成功\n");
					break;
				case 6:
					system("cls");
					coutmenu(high);
					delete(test);
					break;
				case 7:
					system("cls");
					coutmenu(high);

					printf("finish\n");
					break;
				case 8:
					                 
					printf("程序结束\n");
					return 0;
					break;
				}
			}
		}
	}
}