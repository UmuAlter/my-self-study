#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

//进程控制块
struct PCB {
	//进程名
	char name[10];
	//指针
	struct PCB* next;
	//要求运行时间
	int time;
	//优先数
	int priority;
	//状态
	char status;
};
typedef struct PCB* Ptr;

//优先数数组
int parr[5];
//记录总运行次数
int cnt = 0;

//初始化
Ptr init_PCB();
//打印进程
void Print(Ptr head);
//根据最大优先级返回指针
Ptr Find(Ptr head, int max);
//检查并标记结束进程
bool Over(Ptr head);
//优先级排序——降序
void Sort(int arr[5]);
//快速排序
void QuickSort(int arr[], int left, int right);
//进行一次运行
void run_once(Ptr head/*,int arr[]*/);
//进程调度
void run(Ptr head);


int main() {
	srand((unsigned)time(NULL));
	//初始化五个进程
	Ptr head = init_PCB();
	//打印进程状态
	printf("初始状态如下：\n");
	Print(head);
	//调度
	run(head);
	system("pause");
	return 0;
}


//初始化
Ptr init_PCB() {
	Ptr head = NULL,back = NULL ;
	int i = 0;
	for (; i < 5; i++) {
		//每次生成一个PCB
		Ptr pcb = (Ptr)malloc(sizeof(struct PCB));

		printf("请输入第%d个进程的名字: ", i + 1);
		char n[10];
		scanf("%s", n);
		//设置PCB名字
		strcpy(pcb->name, n);
		//设置优先数
		pcb->priority = rand() % 5 + 1;
		parr[i] = pcb->priority;
		//设置运行时间
		pcb->time = rand() % 6 + 1;
		//设置状态(就绪)
		pcb->status = 'R';
		//连接
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
//打印
void Print(Ptr head) {
	Ptr p = head;
	printf("%-10s %-12s %-8s %-10s %s\n", "进程名", "运行时间", "优先数", "状态", "下一个进程");
	while (p->next != NULL) {
		printf("%-10s %-12d %-8d %-10c %s\n", 
			p->name, p->time, p->priority, p->status, p->next->name);
		p = p->next;
	}
	//最后一个无下一进程
	printf("%-10s %-12d %-8d %-10c\t空\t\n", p->name, p->time, p->priority, p->status);
}

void run(Ptr head) {
	while (true) {
		//排序
		Sort(parr);
		//查找并返回最大优先数对应的指针
		Ptr r = Find(head, parr[0]);
		if (r) {
			//进行一次运行
			run_once(r/*, parr*/);
			cnt++;
			//打印此次进程运行结果
			printf("********进程%s正在运行**********\n", r->name);
			printf("第 %d 次运行结果：\n", cnt);
			Print(head);

			//检查运行结果
			bool flag = Over(head);
			if (flag) {
				break;
			}
		}
		else {
			//没找到最大优先数对应的指针
			printf("最大优先数是\n%d\n无最大优先数对应的指针\n", parr[0]);
			break;
		}
	}
}
//进行一次运行
void run_once(Ptr r/*int arr[5]*/) {
	//1.若优先数和要求运行时间都不为0 则运行时间-1 优先数-1 
	if (r->time != 0 && r->priority != 0) {
		r->time--;
		r->priority--;
		parr[0]--;//数组里面储存的是优先数 也执行-1操作
	}
	//2.若要求运行时间不等于零 而优先数已经为0 则只优先数-1
	else if (r->time != 0 && r->priority == 0) {
		r->time--;
	}else if (r->time == 0) {
		//1、2操作若要求时间变为0时 进行此操作
		r->priority = -1;  //优先数置为负一
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
		//找到最大优先数对应的进程
		if (p->priority == max) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}
//快速排序
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
//调用该快速排序
void Sort(int arr[5]) {
    QuickSort(arr, 0, 4);
}
