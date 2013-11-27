#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>



typedef void (*TASK_PTR)(void);

typedef struct{
	TASK_PTR task;
	uint8_t ready;
	uint16_t togo;
	uint16_t periodic;
}TASK;

TASK tasks[10];
unsigned char t=0;


void manager(void);
void addTASK(TASK_PTR, uint16_t , uint16_t);

void taskInit(void)
{
	for(int i=0;i<10;i++)
	{
		tasks[i].task = 0;
		tasks[i].ready=0;
		tasks[i].togo=0;
		tasks[i].periodic=0;
	}

}
void settings(void)
{
	TIMSK|=(1<<OCIE0);
	TCCR0|= (0<<WGM00)|(1<<WGM01)|(0<<CS02)|(1<<CS01)|(1<<CS00)|(0<<COM01)|(0<<COM00);
	OCR0=250;
}


void manager(void)
{
	int tmp=0;

	while(1)
	{
		if(tasks[tmp].ready>0)
		{
			tasks[tmp].ready--;
			tasks[tmp].task();
			tmp=0;
		}
		else
		{
			if(tmp+1<t)
			tmp++;
			else
			tmp=0;
		}
	}
}

void addTASK(TASK_PTR tsk, uint16_t period, uint16_t zaile)
{
	tasks[t].task=tsk;
	tasks[t].periodic=period;
	tasks[t].togo=zaile;
	t++;
}

ISR(TIMER0_COMP_vect)
{
	for(int i=0;i<t;i++)
	{
		if(tasks[i].togo==0)
		{
			tasks[i].ready++;
			tasks[i].togo=tasks[i].periodic;
		}
		else
		{
			tasks[i].togo--;
		}
	}
}

int a=0;
int b=0;
int c=0;
void t1(void)
{
	a++;
}
void t2(void)
{
	b++;
}
void t3(void)
{
	c++;
}

int main(void)
{
	taskInit();
	addTASK(&t1,1,0);
	addTASK(&t2,2,1);
	addTASK(&t3,3,2);

	settings();
	sei();
	manager();
}




