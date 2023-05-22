#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

//���̿��ƿ�
struct PCB {
	//������
	char name[10];
	//ָ��
	struct PCB* next;
	//Ҫ������ʱ��
	int time;
	//������
	int priority;
	//״̬
	char status;
};
typedef struct PCB* Ptr;

//����������
int parr[5];
//��¼�����д���
int cnt = 0;

//��ʼ��
Ptr init_PCB();
//��ӡ����
void Print(Ptr head);
//����������ȼ�����ָ��
Ptr Find(Ptr head, int max);
//��鲢��ǽ�������
bool Over(Ptr head);
//���ȼ����򡪡�����
void Sort(int arr[5]);
//��������
void QuickSort(int arr[], int left, int right);
//����һ������
void run_once(Ptr head/*,int arr[]*/);
//���̵���
void run(Ptr head);


int main() {
	srand((unsigned)time(NULL));
	//��ʼ���������
	Ptr head = init_PCB();
	//��ӡ����״̬
	printf("��ʼ״̬���£�\n");
	Print(head);
	//����
	run(head);
	system("pause");
	return 0;
}


//��ʼ��
Ptr init_PCB() {
	Ptr head = NULL,back = NULL ;
	int i = 0;
	for (; i < 5; i++) {
		//ÿ������һ��PCB
		Ptr pcb = (Ptr)malloc(sizeof(struct PCB));

		printf("�������%d�����̵�����: ", i + 1);
		char n[10];
		scanf("%s", n);
		//����PCB����
		strcpy(pcb->name, n);
		//����������
		pcb->priority = rand() % 5 + 1;
		parr[i] = pcb->priority;
		//��������ʱ��
		pcb->time = rand() % 6 + 1;
		//����״̬(����)
		pcb->status = 'R';
		//����
		if (head == NULL) {
			head = pcb;
			back = pcb;
			back->next = NULL;
		}
		else {
			back->next = pcb;
			back = pcb;
			back->next = NULL;
		}
	}
	return head;
}
//��ӡ
void Print(Ptr head) {
	Ptr p = head;
	printf("%-10s %-12s %-8s %-10s %s\n", "������", "����ʱ��", "������", "״̬", "��һ������");
	while (p->next != NULL) {
		printf("%-10s %-12d %-8d %-10c %s\n", 
			p->name, p->time, p->priority, p->status, p->next->name);
		p = p->next;
	}
	//���һ������һ����
	printf("%-10s %-12d %-8d %-10c\t��\t\n", p->name, p->time, p->priority, p->status);
}

void run(Ptr head) {
	while (true) {
		//����
		Sort(parr);
		//���Ҳ����������������Ӧ��ָ��
		Ptr r = Find(head, parr[0]);
		if (r) {
			//����һ������
			run_once(r/*, parr*/);
			cnt++;
			//��ӡ�˴ν������н��
			printf("********����%s��������**********\n", r->name);
			printf("�� %d �����н����\n", cnt);
			Print(head);

			//������н��
			bool flag = Over(head);
			if (flag) {
				break;
			}
		}
		else {
			//û�ҵ������������Ӧ��ָ��
			printf("�����������\n%d\n�������������Ӧ��ָ��\n", parr[0]);
			break;
		}
	}
}
//����һ������
void run_once(Ptr r/*int arr[5]*/) {
	//1.����������Ҫ������ʱ�䶼��Ϊ0 ������ʱ��-1 ������-1 
	if (r->time != 0 && r->priority != 0) {
		r->time--;
		r->priority--;
		parr[0]--;//�������洢����������� Ҳִ��-1����
	}
	//2.��Ҫ������ʱ�䲻������ ���������Ѿ�Ϊ0 ��ֻ������-1
	else if (r->time != 0 && r->priority == 0) {
		r->time--;
	}else if (r->time == 0) {
		//1��2������Ҫ��ʱ���Ϊ0ʱ ���д˲���
		r->priority = -1;  //��������Ϊ��һ
		parr[0] = -1;
		r->status = 'E';
	} 
}
bool Over(Ptr head) {
	Ptr p = head;
	while (p) {
		if (p->status == 'R') {
			return false;
		}
		else {
			p = p->next;
		}
	}
	return true;
	
}
Ptr Find(Ptr head, int max){
	Ptr p = head;
	while (p) {
		//�ҵ������������Ӧ�Ľ���
		if (p->priority == max) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}
//��������
void QuickSort(int arr[], int left, int right) {
    if (left >= right) return;
    int pivot = arr[left];
    int l = left, r = right;
    while (l < r) {
        while (l < r && arr[r] <= pivot) --r;
        arr[l] = arr[r];
        while (l < r && arr[l] >= pivot) ++l;
        arr[r] = arr[l];
    }
    arr[l] = pivot;
    QuickSort(arr, left, l - 1);
    QuickSort(arr, l + 1, right);
}
//���øÿ�������
void Sort(int arr[5]) {
    QuickSort(arr, 0, 4);
}
