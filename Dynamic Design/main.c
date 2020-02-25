/*
 * Dynamic Design.c
 *
 * Created: 2/24/2020 9:35:01 AM
 * Author : Khaled
 */ 

#include "SERVICE/TMU/TMU.h"

void t1 (void);
void t2 (void);
void t3 (void);
void t4 (void);
int c = 0;

extern str_TMU_InitConfig_t init;
int main(void)
{
    
	 SET_BIT(PORTA_DIR,BIT0);
	 SET_BIT(PORTA_DIR,BIT1);
	 SET_BIT(PORTA_DIR,BIT2);
	 SET_BIT(PORTA_DIR,BIT3);
	 SET_BIT(PORTA_DIR,BIT6);

	 TMU_Init(&init);
	 
	 TMU_Start(10,1,0,t1);
	 TMU_Start(3,1,0,t2);
	 TMU_Start(4,3,0,t3);
	 TMU_Start(5,4,0,t4);
	 
	 /* Replace with your application code */
    while (1) 
    {
	    TMU_Dispatch();
    }
}

void t1 (void)
{
   TOGGLE_BIT(PORTA_DATA,BIT0);
	c++;
	if (c == 100)
	{
	   TMU_Stop(1,t2);
	}
	if (c == 200)
	{
		TMU_Stop(3,t3);
	}
	if (c == 500)
	{
		TMU_Start(3,1,0,t2);
	}
	if (c == 800)
	{
		TMU_Stop(1,t2);
	}

	if (c == 1000)
	{
		TMU_Stop(1,t1);
	}
}
void t2 (void)
{
   TOGGLE_BIT(PORTA_DATA,BIT1);
}
void t3 (void)
{
	TOGGLE_BIT(PORTA_DATA,BIT2);
}
void t4 (void)
{
	TOGGLE_BIT(PORTA_DATA,BIT3);
}