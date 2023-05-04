#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>

struct node
{
	int rt,qt;
	char nm[30];
	struct node *next;
}*s[20];

void init()
{
	int i;
	for(i=1;i<=20;i++)
	{
		s[i]=NULL;
	}
}

struct node *createNode()
{
	struct node *p=(struct node *)malloc(sizeof(struct node));
	p->next=NULL;
	return p;
}

struct node *getLastNode(struct node *q)
{
	struct node *p=q;
	while(p->next!=NULL)
		p=p->next;
	return p;
}

int listNo()
{
	int no;
	printf("\nEnter Table Number:");
	scanf("%d",&no);
	return no;
}

void add(struct node **p)
{
	struct node *q=createNode(),*r;
	if(*p==NULL)
		*p=q;
	else
	{
		r=getLastNode(*p);
		r->next=q;
	}
	printf("\nEnter Item:");
	scanf("%s",q->nm);
	printf("\nEnter Quantity:");
	scanf("%d",&q->qt);
	printf("\nEnter Rate:");
	scanf("%d",&q->rt);
}

void display(struct node *t)
{
	int cnt=1;
	while(t)
	{
		printf("%d) Item=%s\tQuantity=%d\tRate=%d\n",cnt++,t->nm,t->qt,t->rt);
		t=t->next;
	}
	getch();
	return;
}

void display1(struct node *t)
{
	int cnt=1;
	while(t)
	{
		printf("%d) Item=%s\tQuantity=%d\tRate=%d\n",cnt++,t->nm,t->qt,t->rt);
		t=t->next;
	}
	return;
}


int total(struct node *t)
{
	int tot=0;
	while(t)
	{
		tot=tot+(t->qt*t->rt);
		t=t->next;
	}
	return tot;
}

int count(struct node *t)
{
	int cnt=0;
	while(t)
	{
		cnt++;
		t=t->next;
	}
	return cnt;
}


void empty()
{
	int i=1;
	printf("\nEmpty Tables:\n");
	for(i=1;i<=20;i++)
	{
		if(s[i]==NULL)
			printf("\t%d",i);
	}
	getch();
}

void deleteQ(struct node **q)
{
	struct node *p=*q,*r,*s;
	int no,cnt=0;
	display(*q);
	printf("\nEnter Sr Number:");
	scanf("%d",&no);
	if(no<1||no>count(*q))
	{
		printf("\nInvalid Sr Number");
		getch();
		return;
	}
	if(no==1)
	{
		r=*q;
		*q=p->next;
		free(r);
		return;
	}
	if(no==count(*q))
	{
		while(no!=cnt+1)
		{
			r=p;
			p=p->next;
			cnt++;
		}
		r->next=p->next;
		free(p);
		return;
	}
	while(no!=cnt)
	{
		r=p;
		p=p->next;
		cnt++;
	}
	r->next=p->next;
	free(p);
}

void modify(struct node **q)
{
	struct node *p=*q,*r,*s;
	int no,cnt=1,w;
	display(*q);
	printf("\nEnter Sr Number:");
	scanf("%d",&no);
	if(no<1||no>count(*q))
	{
		printf("\nInvalid Sr Number");
		getch();
		return;
	}
	while(no!=cnt)
	{
		p=p->next;
		cnt++;
	}
	printf("\nEnter Quantity:");
	scanf("%d",&p->qt);
}

void writeTOfile()
{
	int i,tot=0;
	FILE *f1,*f2;
	struct  time t1;
	struct date d1;
	gettime(&t1);
	getdate(&d1);
	f1=fopen("HotelBill.txt","w");
	f2=fopen("GrandTotal.txt","a");
	fprintf(f1,"\tDate=%d-%d-%d",d1.da_day,d1.da_mon,d1.da_year);
	fprintf(f1,"\tTime=%2d::%02d::%02d",t1.ti_hour,t1.ti_min,t1.ti_sec);
	for(i=1;i<=20;i++)
	{
		fprintf(f1,"\nTable Number=%d\tBill=%d",i,total(s[i]));
		tot=tot+total(s[i]);
	}
	fprintf(f2,"Date=%d-%d-%d",d1.da_day,d1.da_mon,d1.da_year);
	fprintf(f2,"\tTime=%2d::%02d::%02d",t1.ti_hour,t1.ti_min,t1.ti_sec);
	fprintf(f2,"\nTotal Amount:%d",tot);
	fprintf(f2,"\n**********************************");
	fclose(f1);
	fclose(f2);
}


void generate(struct node **q)
{
	display1(*q);
	printf("\nTotal Amount=%d",total(*q));
	getch();
}

int password()
{
	int i=0;
	char un[30],ps[30],c;
	printf("\nEnter User Name:");
	scanf("%s",un);
	printf("\nEnter Password:");
	i=0;
	while(1)
	{
		c=getch();
		if(c==13)
		{
			ps[i]=NULL;
			break;
		}
		printf("*");
		ps[i]=c;
		i++;
	}
	if(strcmp(un,"AMRUT")==0)
	{
		if(strcmp(ps,"amrut")==0)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}


void main()
{
	struct node *p,**q;
	int opt,d,no,tot=0;
	init();
	while(1)
	{
		clrscr();
		printf("\n1.Add Item\n2.Display table Information\n3.Calculate Total\n4.Display Empty Tables\n5.Delete Item From Table\n6.Modify Quantity Of Item\n7.Write to File\n8.Generate Bill\n9.Grand Total\n10.Exit\nEnter Option:");
		scanf("%d",&opt);
		if(opt==10)
			break;
		switch(opt)
		{
			case 1:
				no=listNo();
				if(no<1||no>21)
				{
					printf("\nTable Not Exists");
					getch();
					break;
				}
				q=&s[no];
				display1(*q);
				add(q);
				break;
			case 2:
				no=listNo();
				if(no<1||no>21)
				{
					printf("\nTable Not Exists");
					getch();
					break;
				}
				q=&s[no];
				display(*q);
				break;
			case 3:
				no=listNo();
				if(no<1||no>21)
				{
					printf("\nTable Not Exists");
					getch();
					break;
				}
				q=&s[no];
				display1(*q);
				printf("\n\nTotal=%d",total(*q));
				getch();
				break;
			case 4:
				empty();
				break;
			case 5:
				no=listNo();
				if(no<1||no>21)
				{
					printf("\nTable Not Exists");
					getch();
					break;
				}
				q=&s[no];
				deleteQ(q);
				break;
			case 6:
				no=listNo();
				if(no<1||no>21)
				{
					printf("\nTable Not Exists");
					getch();
					break;
				}
				q=&s[no];
				modify(q);
				break;
			case 7:
				writeTOfile();
				break;
			case 8:
				no=listNo();
				if(no<1||no>21)
				{
					printf("\nTable Not Exists");
					getch();
					break;
				}
				q=&s[no];
				generate(q);
				break;
			case 9:
				no=password();
				if(no==1)
				{
					for(d=1;d<=20;d++)
					{
						tot=tot+(total(s[d]));
					}
					printf("\nGrand Total=%d",tot);
				}
				else
					printf("Access Denied");
				getch();
				break;
		}
	}
	getch();
}
