#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"SigleList.h"



struct Result
{
	unsigned int time_reponse;
	unsigned int time_wait;
	unsigned int time_complete;
	unsigned int first_time;
};

Process* queue;
int num_process;

void swap(Process &a,Process &b)
{
	Process c = a;
	a = b;
	b = c;
}
int compare(const void* a, const void* b)
{
	Process* arg1 = (Process*)a, * arg2 = (Process*)b;
	if ((*arg1).time_arrival < (*arg2).time_arrival) return -1;
	//else if ((*arg1).time_arrival == (*arg2).time_arrival) return 0;
	else return 1;
}
int compare_2(const void* a, const void* b)
{
	Process* arg1 = (Process*)a, * arg2 = (Process*)b;
	if ((*arg1).time_brust < (*arg2).time_brust) return -1;
	//else if ((*arg1).time_arrival == (*arg2).time_arrival) return 0;
	else return 1;
}
void swap(const void* &a, const void* &b)
{
	Process* arg1 = (Process*)a, * arg2 = (Process*)b;
	Process* arg3 = arg1;
	arg1 = arg2;
	arg2 = arg3;
}

void FCFS();
void SJF();
void round_robin(int n);
void xl_Slist(Slist sl,int n);

void docFile();
void main()
{

	int i = 0, time = 0, kt = 0;
	docFile();
	qsort(queue, num_process, sizeof(Process), compare);
	printf("\n info");
	printf("\n+------+--------------+-------------+");
	printf("\n+  ID  + Arrival Time +  Burst Time +");
	printf("\n+------+--------------+-------------+");
	for (int i = 0; i < num_process; i++)
	{
		printf("\n    %-10c%-15d%-10d", queue[i].id, queue[i].time_arrival, queue[i].time_brust);
	}
	

	printf("\n+----------+ FCFS +-----------+");
	FCFS();
	printf("\n+----------+ SJF +-----------+");
	
	SJF();

}
void FCFS()
{
	qsort(queue, num_process, sizeof(Process), compare);
	int time = queue[0].time_arrival , wait = 0, i = 0;
	Result* t;
	t = (Result*)malloc(num_process * sizeof(Process));
	for (int i = 0; i < num_process; i++)
	{
		t[i].time_reponse = time - queue[i].time_arrival;
		time += queue[i].time_brust;
		t[i].time_wait = time - queue[i].time_arrival - queue[i].time_brust;
		t[i].time_complete = time - queue[i].time_arrival;
		printf("\n+  Reponse Time  + Waiting Time +  Complete Time +");
		printf("\n+      %.2d        +     %.2d       +         %.2d     +",t[i].time_reponse,t[i].time_wait,t[i].time_complete);
	}
	
	
}
void docFile()
{
	FILE* f = fopen("Text.txt", "r");
	fscanf(f, "%d", &num_process);
	queue = (Process*)malloc(num_process * sizeof(Process));
	int ch = 'A';
	for (int i = 0; i < num_process; i++)
	{
		queue[i].id = ch++;
		fscanf(f, "%d", &queue[i].time_arrival);
		fscanf(f, "%d", &queue[i].time_brust);

	}
	fclose(f);
}
void SJF()
{
	int i = 0, time = queue[0].time_arrival, n = 0;
	qsort(queue, num_process, sizeof(Process), compare);
	Result* t = (Result*)malloc(num_process * sizeof(Result));
	printf("\n+  Reponse Time  + Waiting Time +  Complete Time +");
	Process* k = (Process*)malloc(num_process * sizeof(Process));
	do
	{
		int z = i;
		while (time >= queue[i].time_arrival)
		{
			
			k[i] = queue[i];
			i++;
			n++;
		}

		for (int u = z; u < i-1; u++)
		{
			for (int u1 = u+1; u1 < i; u1++)
			{
				if (k[u].time_brust > k[u1].time_brust)
					swap(k[u], k[u1]);
			}
		}
		
		for (int u = z; u < i; u++)
		{
			t[u].time_reponse = time - k[u].time_arrival;
			
			time += k[u].time_brust;
			t[u].time_wait = time - k[u].time_arrival - k[u].time_brust;
			t[u].time_complete = time - k[u].time_arrival;
			printf("\n%c+      %.2d        +     %.2d       +         %.2d     +", k[u].id, t[u].time_reponse, t[u].time_wait, t[u].time_complete);
		}
		
	} while (n < num_process);
	

}

