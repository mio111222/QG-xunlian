//ʹ��visual studio 2022�༭
#pragma warning(disable:4996) 
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<conio.h>
#include<windows.h>
#define LEN  sizeof(struct two_way)

char MenuText[8][40] = {
	"|[A]  create a list       |",         //��������
	"|[B]  foreach list        |",         //��������
	"|[C]  search a node       |",         //Ѱ�ҽڵ�
	"|[D]  insert a node(head) |",         //ͷ��
	"|[E]  insert a node(end)  |",         //β��
	"|[F]  detele a node       |",         //ɾ���ڵ�
	"|[G]  destroy a list      |",         //��������
	"|[H]  Exit                |"
};

void coutmenu(int highlight)
{
	int i;
	printf("����������0��β\n");
	printf("������������ĸ���߷�����������ƶ�\n");
	printf("ѡ�񵽲������Իس���ʼ\n");
	printf("�����ֱ�Ϊ��A.��������;B.��������;C.���ҽڵ�;D.ͷ��ڵ�;E.β��ڵ�;F.ɾ���ڵ�;G.��������;H.����\n");
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

struct two_way* create_two_way();            //����
void foreach(struct two_way* p);             //����
void search(struct two_way* p);              //����
void insert_head(struct two_way* p);         //ͷ��
void insert_end(struct two_way* p);          //β��
void delete(struct two_way* p);              //ɾ��ĳ��
void destroy (struct two_way* p);            //����

struct two_way* create_two_way() {                      //������0ʱ����
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

void foreach(struct two_way* p) {                //��������
	struct two_way * p1, * p2;
	if (p != NULL && p->next!=NULL ) {
		p1 = p2 = p->next;
	}
	else {
		printf("����ʧ�ܣ�������\n");
		return;
	}
	printf("˳������� ");
	while (p1 != NULL) {
		printf("%d ", p1->money);
		p2 = p1;
		p1 = p1->next;
	}
	printf("\n");
	printf("��������� ");
	while (p2 != NULL && p2->money != 0) {
		printf("%d ", p2->money);
		p2 = p2->front;
	}
	return;
}

void search(struct two_way* p) {         //Ѱ�ҽڵ�(�����ַ)
	struct two_way* pp;
	int what;                            //�жϲ���
	pp = p->next;
	int cnt = 1, judge = 0, mat;
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
			printf("������%dλ\n", mat);
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
			printf("δѰ�ҵ�%dֵ\n", mat);
		}
	}
	if (what == 0) return;
	search(p);
}

void insert_head(struct two_way* p) {         //ͷ��
	struct two_way* p1, * p2, * p3;
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
	p3 = (struct two_way*)malloc(sizeof(LEN));
	p2->next = p3;
	p3->front = p2;
	p3->money = mat;
	p3->next = p1;
	p1->front = p3;
	return;
}

void insert_end(struct two_way* p) {          //β��
	struct two_way* p1,* p2,* p3;
	p1 = p->next;
	p2 = p;
	while (p1 != NULL) {
		p2 = p2->next;
		p1 = p1->next;
	}
	int n, mat,cnt=2;
	printf("�����������Լ�����ֵ���ÿո��������\n");
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
		printf("�޷��ҵ���Ӧ�ڵ�\n");
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

void delete(struct two_way* p) {              //ɾ���ڵ�
	int n, cnt = 1, judge = 0;
	printf("������ɾ���Ľڵ�λ��:\n");
	scanf_s("%d", &n);
	struct two_way* p1, * p2, *p3;
	p1 = p;
	p2 = p->next;
	if (p2->next == NULL) {
		if (n == 1) {
			p->next = NULL;
			printf("�ɹ�ɾ����%d�ڵ�\n", n);
			free(p2);
		}
		else {
			printf("δ�ҵ��ڵ㣬ɾ��ʧ��\n");
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
		printf("��");
	}
	if (cnt==n) {
		p1->next = p3;
		p3->front = p1;
		free(p2);
		printf("�ɹ�ɾ����%d�ڵ�\n", n);
	}
	else {
		printf("δ�ҵ��ڵ㣬ɾ��ʧ��\n");
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
			if (GetAsyncKeyState(VK_UP)) {           //�����������ƶ� 
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
			if (c <= 'z' && c >= 'a')c = c - ('a' - 'A');      //�����ĸ���� 
			if (c <= 'H' && c >= 'A') {
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
					printf("�뿪ʼ���룺\n");
					test = create_two_way();
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
					system("cls");
					coutmenu(high);
					printf("��������\n");
					break;
				case 4:
					system("cls");
					coutmenu(high);
					insert_head(test);
					printf("����ɹ�\n");
					break;
				case 5:
					system("cls");
					coutmenu(high);
					insert_end(test);
					printf("����ɹ�\n");
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
					                 
					printf("�������\n");
					return 0;
					break;
				}
			}
		}
	}
}