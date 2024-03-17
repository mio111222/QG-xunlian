//ʹ��visual studio 2022�༭
#pragma warning(disable:4996) 
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<conio.h>
#include<windows.h>
#define LEN  sizeof(struct one_way)

char MenuText[11][40] = {
	"|[A]  create a list       |",         //��������
	"|[B]  foreach list        |",         //��������
	"|[C]  search a node       |",         //Ѱ�ҽڵ�
	"|[D]  insert a node       |",         //����ڵ�
	"|[E]  detele a node       |",         //ɾ���ڵ�
	"|[F]  destroy a list      |",         //��������
	"|[G]  find the middle     |",         //Ѱ���е�
	"|[H]  judgement loop      |",         //�жϳɻ�
	"|[I]  reverse list        |",         //��ת����
	"|[J]  parity exchange     |",         //��ż����
	"|[K]  Exit                |"          //�˳�
};

void coutmenu(int highlight)
{
	int i;
	printf("����������0��β\n");
	printf("������������ĸ���߷�����������ƶ�\n");
	printf("ѡ�񵽲������Իس���ʼ\n");
	printf("�����ֱ�Ϊ��A.��������;B.��������;C.���ҽڵ�;D.����ڵ�;E.ɾ���ڵ�\n");
	printf("     F.�������;G.Ѱ���е�;H.�жϳɻ�;I.��ת����;J.��ż����;K.����\n");
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

struct one_way* create_one_way();               //��������
void foreach(struct one_way* p);                //��������
void search(struct one_way* p);                 //Ѱ�ҽڵ�
void insert(struct one_way* p);                 //����ڵ�
void delete(struct one_way* p);                 //ɾ���ڵ�
struct one_way* destory(struct one_way* p);     //��������
void middle(struct one_way* p);                 //Ѱ���е�
void judgment_loop(struct one_way* p);          //�жϳɻ�
struct one_way* reversal(struct one_way* p);    //��ת����
void parity(struct one_way* p);                 //��ż����

struct one_way* create_one_way() {                 //��������������0ʱ����������������ͷ
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

void foreach(struct one_way* p) {               //��������
	struct one_way* p5;
	if (p == NULL || p->next==NULL) {
		printf("����ʧ�ܣ�������\n");
		return;
	}
	p5 = p->next;
	while (p5 != NULL) {
		printf("%d ", p5->money);
		p5 = p5->next;
	}
	printf("\n");
	printf("����������\n");
	return;
}

void search(struct one_way* p) {         //Ѱ�ҽڵ�(�����ַ)
	struct one_way* pp;
	int what;                            //�жϲ���
	pp = p->next;
	int cnt = 1, judge = 0,mat;
	printf("�����������1.Ѱ�Ҷ�Ӧ�ڵ㣬2.Ѱ�Ҷ�Ӧֵ,0.����������\n");
	scanf_s("%d", &what);
	if (what == 1) {
		printf("������Ѱ�ҵĽڵ�λ�ã�\n");
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
			printf("�Ѿ�Ѱ�ҵ�%dλ����ӦֵΪ%d\n", mat, pp->money);
		}
		else {
			printf("������%dλ\n",mat);
		}
	}
	if (what == 2) {
		printf("������Ѱ�ҵ�ֵ��\n");
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
			printf("�Ѿ�Ѱ�ҵ�%d���ڵ�%dλ\n", mat, cnt);
		}
		else {
			printf("δѰ�ҵ�%dֵ\n",mat);
		}
	}
	if (what == 0) return;
	search(p);
}

void insert(struct one_way* p) {            //����ڵ�
	struct one_way* p1,* p2,* p3;
	int n, mat;
	int cnt = 1;                  //��Ϊ���λhead�ǿյģ����Դ������ݵ�λ�ÿ�ʼ���һλ
	p1 = p->next;
	p2 = p;
	printf("�����������Լ�����ֵ���ÿո��������\n");
	scanf_s("%d %d", &n, &mat);
	while (p1 != NULL) {
		if (cnt == n) break;
		cnt++;
		p1 = p1->next;
		p2 = p2->next;
	}
	if (cnt != n) {
		printf("�޷��ҵ���Ӧ�ڵ�\n");
		return;
	}
	p3 = (struct one_way*)malloc(sizeof(LEN));
	p2->next = p3;
	p3->money = mat;
	p3->next = p1;
}

void delete(struct one_way* p){              //ɾ���ڵ�(�����ַ��ɾ����λ��)
	int n,cnt=1,judge=0;
	printf("������ɾ���Ľڵ�λ��:\n");
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
		printf("�ɹ�ɾ����%d�ڵ�\n",n);
	}
	else {
		printf("δ�ҵ��ڵ㣬ɾ��ʧ��\n");
	}
	return;
}

struct one_way* destory(struct one_way* p) {             //��������
	struct one_way* head, * p1, * p2;
	head = p;
	if (p == NULL) {
		printf("�������޲���\n");
		return NULL;
	}
	p1 = head->next;
	while (p1 != NULL) {
		p2 = p1->next;
		free(p1);
		p1 = p2;
	}
	free(head);
	printf("�������\n");
	return NULL;
}

void middle(struct one_way* p) {              //Ѱ���е�
	struct one_way* p1;
	int cnt = 0,n;
	if (p->next == NULL) {
		printf("�������޲���\n");
		return;
	}
	p1 = p->next;
	while (p1 != NULL) {
		p1 = p1->next;
		cnt++;
	}
	if (cnt % 2 == 0) {             //ż�����
		printf("����һ����%d���ڵ㣬�е�%d��%d�ֱ�Ϊ�� ",cnt,cnt/2,cnt/2+1);
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
	else {                         //�������
		printf("����һ����%d���ڵ�,�е�%dΪ�� ", cnt, cnt / 2 + 1);
		n = cnt / 2 + 1, cnt = 1 ;
		p1 = p->next;
		while (cnt != n) {
			p1 = p1->next;
			cnt++;
		}
		printf("%d\n", p1->money);
	}
}

void judgment_loop(struct one_way* p) {       //�жϳɻ�
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
		printf("����ɻ�\n");
	}
	else {
		printf("����δ�ɻ�\n");
	}
	return;
}

struct one_way* reversal(struct one_way* p) {            //��ת����
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
	printf("��ת���\n");
	return p;
}

void parity(struct one_way* p) {              //��ż����
	struct one_way* p1=NULL, * p2=NULL, * p3=NULL;
	int cnt = 0;
	if (p ==NULL ||p->next == NULL) {
		printf("������ɷ�ת");
		return;
	}
	if (p->next->next == NULL) {
		printf("��ż��ת���");
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
		printf("��ż��ת���");
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
	printf("��ż��ת���");
}

//int main()
//{
//	struct one_way* test, * pp;
//	//struct one_way* p4 , *p5;                  //����ɻ�������
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
			if (GetAsyncKeyState(VK_UP)) {           //�����������ƶ� 
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
			if (c <= 'z' && c >= 'a')c = c - ('a' - 'A');      //�����ĸ���� 
			if (c <= 'K' && c >= 'A') {
				//��Ӧ����ĳ����
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
					printf("�뿪ʼ���룺\n");
					test = create_one_way();
					system("cls");
					coutmenu(high);
					printf("���������\n");
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
					printf("��������\n");
					break;
				case 4:
				    system("cls");
					coutmenu(high);
					insert(test);
					system("cls");
					coutmenu(high);
					printf("����ɹ�\n");
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
					printf("�������\n");
					return 0;
					break;
				}
			}
		}
	}
}