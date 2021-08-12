#include<stdio.h>
#include<conio.h>

struct Process
{
	char id;
	unsigned int time_brust, time_arrival;
	unsigned int time_reponse;
	unsigned int time_wait;
	unsigned int time_complete;
	int first_time = -1;
};

typedef Process ItemType;

struct Snode
{
	ItemType info;
	Snode* next;
};
struct Slist
{
	Snode* head, * tail;
};

/////////////////////////////////////////////////////////////////////
Snode* create_snode(ItemType x);
int is_empty(Slist sl);
int insert_head(Slist& sl, Snode* p);
int insert_tail(Slist& sl, Snode* p);
//insert q after p
int insert_after(Slist& sl, Snode* p,Snode* q);
int delete_head(Slist& sl, ItemType& x);
int delete_after(Slist& sl, Snode* p, ItemType& x);

////////////////////////////////////////////////////////
Snode* create_snode(ItemType x)
{
	Snode* p = new Snode;
	if (!p) return NULL;
	p->info = x;
	p->next = NULL;
	return p;
}
int is_empty(Slist sl)
{
	return sl.head == NULL;
}
int insert_head(Slist& sl, Snode* p)
{
	if (!p) return 0;
	if (is_empty(sl))
	{
		sl.head = sl.tail = p;
	}
	else
	{
		p->next = sl.head;
		sl.head = p;
	}
	return 1;
}
int insert_tail(Slist& sl, Snode* p)
{

	if (!p) return 0;
	if (is_empty(sl))
	{
		sl.head = sl.tail = p;
	}
	else
	{
		sl.tail->next = p;
		sl.tail = p;
	}
	return 1;
}
int insert_after(Slist& sl, Snode* p, Snode* q)
{
	if (!p || !q) return 0;
	q->next = p->next;
	p->next = q;
	if (sl.tail == p)
		sl.tail = q;
	return 1;
}
int delete_head(Slist& sl, ItemType& x)
{
	if (is_empty(sl)) return 0;
	Snode* p = sl.head;
	sl.head = p->next;
	if (sl.head == NULL) sl.tail = NULL;
	x = p->info;
	delete p;
	return 1;
}
int delete_after(Slist& sl, Snode* p, ItemType& x)
{
	if (!p || !p->next) return 0;
	Snode* q = p->next;
	p->next = q->next;
	if (sl.tail == q)
		sl.tail = p;
	x = q->info;
	delete q;
	return 1;
}