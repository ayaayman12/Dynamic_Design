/*
 * Timers.c
 *
 * Created: 2/16/2020 11:39:14 AM
 *  Author: Khaled
 */ 

 
 #include "timers.h"



 // for timer 0
 #define  T0_NORMAL_MODE                 0

 #define  T0_OC0_DIS                     0

 #define  T0_POLLING                     0
 #define  T0_INTERRUPT_NORMAL            0x01

 #define  T0_NO_CLOCK                    0xF8
 #define  T0_PRESCALER_NO                0x01
 #define  T0_PRESCALER_8                 0x02
 #define  T0_PRESCALER_64                0x03
 #define  T0_PRESCALER_256               0x04
 #define  T0_PRESCALER_1024              0x05

 #define TOV0  (TIFR & BIT0)
 #define RESETTOV0  (TIFR |= BIT0)

 #define TIMER0_MAX_NUMBER_OF_COUNTS     256
/*****************************************************************************************************************/

 // for timer 1
 #define  T1_NORMAL_MODE                 0x0000

 #define  T1_OC1_DIS                     0

 #define  T1_POLLING                     0
 #define  T1_INTERRUPT_NORMAL            0x04

 #define  T1_NO_CLOCK                    0x00
 #define  T1_PRESCALER_NO                0x01
 #define  T1_PRESCALER_8                 0x02
 #define  T1_PRESCALER_64                0x03
 #define  T1_PRESCALER_256               0x04
 #define  T1_PRESCALER_1024              0x05

 #define  TCCR1A_VALUE_FOR_NORMAL_MODE    0xFC
 #define  TCCR1B_VALUE_FOR_NORMAL_MODE    0xE7
 #define  DISABLE_TIMER_1_ALL_INTERRUPTS  0xC3
 #define  TCCR1A_VALUE_FOR_OC1_DISCONNECT 0x0F
 #define  TCCR1B_VALUE_TO_STOP_TIMER1     0xF8

 #define TOV1  (TIFR & BIT2)
 #define RESETTOV1  (TIFR |= BIT2)


 #define TIMER1_MAX_NUMBER_OF_COUNTS     65536
 /*****************************************************************************************************************************/
 // for timer 2
 #define  T2_NORMAL_MODE                 0

 #define  T2_OC2_DIS                     0

 #define  NO_CLOCK                       0xF8

 #define  T2_POLLING                     0
 #define  T2_INTERRUPT_NORMAL            0x40

 #define  T2_NO_CLOCK                    0xF8
 #define  T2_PRESCALER_NO                0x01
 #define  T2_PRESCALER_8                 0x02
 #define  T2_PRESCALER_32                0x03
 #define  T2_PRESCALER_64                0x04
 #define  T2_PRESCALER_128               0x05
 #define  T2_PRESCALER_256               0x06
 #define  T2_PRESCALER_1024              0x07

 #define SET_AS2       (TIFR |= BIT3)
 #define CLEAR_AS2     (TIFR &= 0xF7)

 #define TOV2  (TIFR & BIT6)
 #define RESETTOV2  (TIFR |= BIT6)

 #define TIMER2_MAX_NUMBER_OF_COUNTS     256
/**********************************************************************************************************************************/

 


 static uint8_t gu8_PreScaler_T0       = ZERO;
 static uint8_t gu8_PreScaler_T1       = ZERO;
 static uint8_t gu8_PreScaler_T2       = ZERO;
 static uint8_t au8_Temp_For_Low_Bit   = ZERO;
 static uint8_t au8_Temp_For_Hight_Bit = ZERO;
 static void (*ptr_CBF)(void) = NULL;

 uint8_t Timer_Init (Timer_Cfg_ST *Timer_Info)
 {
    /*variable to store errors*/
	 uint8_t Error = E_OK;
	 /*if the timer info equal NULL return error*/
	 if (NULL == Timer_Info)
	 {
	    Error |= E_NOK;
	 }
	 
	 else
	 {
	    switch (Timer_Info->Timer_Ch)
	    {
		    case Timer_0:
		    /*set TCCR0 to zero to clear any old value */
			 TCCR0 = ZERO;

		    //set timer0 in normal mode
		    TCCR0 = TCCR0 | T0_NORMAL_MODE;

		    //disconnect Output Compare 0 pin
		    TCCR0 = TCCR0 | T0_OC0_DIS;

		    /*store timer0 prescaler value in global variable according to info structure*/
			 switch (Timer_Info->Timer_PreScaler)
			 {
			    case PRESCALER_1:
			    gu8_PreScaler_T0 = T0_PRESCALER_NO;
			    break;

		   	 case PRESCALER_8:
		       gu8_PreScaler_T0 = T0_PRESCALER_8;
			    break;

			    case PRESCALER_64:
			    gu8_PreScaler_T0 = T0_PRESCALER_64;
			    break;

				 case PRESCALER_256:
				 gu8_PreScaler_T0 = T0_PRESCALER_256;
			    break;

			  	 case PRESCALER_1024:
				 gu8_PreScaler_T0 = T0_PRESCALER_1024;
			    break;

				 default:
				 Error |= E_NOK;
				 break;
			 }

		    //set timer0 interrupt mode according to info structure
		    switch (Timer_Info->Timer_Interrupt_Mode)
		    {
			    case TIMER_MODE_POLLING:
			    TIMSK |= T0_POLLING;
			    break;

			    case TIMER_MODE_INTERRUPT:
				 ptr_CBF = Timer_Info->Ptr_TCB_Function;
			    TIMSK |= T0_INTERRUPT_NORMAL;
				 SET_BIT (SREG,BIT7);
			    break;

			    default:
			    Error |= E_NOK;
			    break;
		    }

		    break;


		    /*********************************************************************************************************************************/
		    case Timer_1:
			 /*clear TCCR1 (A&B) to clear any old value from previews initialize */
		    TCCR1A = ZERO;
		    TCCR1B = ZERO;

		    //set timer1 in normal mode
		    TCCR1A &= TCCR1A_VALUE_FOR_NORMAL_MODE ;
		    TCCR1B &= TCCR1B_VALUE_FOR_NORMAL_MODE ;

		    //disconnect Output Compare 1(A&B) pins
		    TCCR1A &= TCCR1A_VALUE_FOR_OC1_DISCONNECT ;

		    /*store timer1 prescaler value in global variable according to info structure*/
		    switch (Timer_Info->Timer_PreScaler)
		    {
			    case PRESCALER_1:
			    gu8_PreScaler_T1 = T1_PRESCALER_NO;
			    break;

			    case PRESCALER_8:
			    gu8_PreScaler_T1 = T1_PRESCALER_8;
			    break;

			    case PRESCALER_64:
			    gu8_PreScaler_T1 = T1_PRESCALER_64;
			    break;

			    case PRESCALER_256:
			    gu8_PreScaler_T1 = T1_PRESCALER_256;
			    break;

			    case PRESCALER_1024:
			    gu8_PreScaler_T1 = T1_PRESCALER_1024;
			    break;

			    default:
			    Error |= E_NOK;
			    break;
		    }


		    //set timer1 interrupt mode according to info structure
		    TIMSK &= DISABLE_TIMER_1_ALL_INTERRUPTS;
		    switch (Timer_Info->Timer_Interrupt_Mode)
		    {
			    case TIMER_MODE_POLLING:
			    TIMSK |= T1_POLLING;
			    break;

			    case TIMER_MODE_INTERRUPT:
			    TIMSK |= T1_INTERRUPT_NORMAL;
			    break;

			    default:
			    Error |= E_NOK;
			    break;
		    }

		    break;


		    /************************************************************************************************************************************/
		    case Timer_2:
		    /*clear TCCR2 to clear any old value from previews initialize */
			 TCCR2 = ZERO;

		    TCCR2 |= T2_NORMAL_MODE;

		    TCCR2 |= T2_OC2_DIS;

			 /*store timer2 prescaler value in global variable according to info structure*/
		    switch (Timer_Info->Timer_PreScaler)
		    {
			    case PRESCALER_1:
			    gu8_PreScaler_T2 = T2_PRESCALER_NO;
			    break;

			    case PRESCALER_8:
			    gu8_PreScaler_T2 = T2_PRESCALER_8;
			    break;

				 case PRESCALER_32:
				 gu8_PreScaler_T2 = T2_PRESCALER_32;
				 break;

			    case PRESCALER_64:
			    gu8_PreScaler_T2 = T2_PRESCALER_64;
			    break;

				 case PRESCALER_128:
				 gu8_PreScaler_T2 = T2_PRESCALER_128;
				 break;

			    case PRESCALER_256:
			    gu8_PreScaler_T2 = T2_PRESCALER_256;
			    break;

			    case PRESCALER_1024:
			    gu8_PreScaler_T2 = T2_PRESCALER_1024;
			    break;

			    default:
			    Error |= E_NOK;
			    break;
		    }

			 /*Timer/Counter 2 is clocked from the I/O clock, clkI/O*/ 
		    CLEAR_AS2;

			 //set timer2 interrupt mode according to info structure
		    switch (Timer_Info->Timer_Interrupt_Mode)
		    {
			    case TIMER_MODE_POLLING:
			    TIMSK |= T2_POLLING;
			    break;

			    case TIMER_MODE_INTERRUPT:
			    TIMSK |= T2_INTERRUPT_NORMAL;
			    break;

			    default:
			    Error |= E_NOK;
			    break;
		    }

		    break;
			 /*****************************************************************************************/
		    default:
		    Error |= E_NOK;
		    break;
	    }
	 }

	 return  Error;
 }



 uint8_t Timer_Start (uint8_t Timer_Chan, uint16_t Timer_Count_No)
 {
    /*variable to store errors*/
	 uint8_t Error = E_OK;
	 switch (Timer_Chan)
	 {
	    
		 case Timer_0:
		 /*check if number of count suitable for the timer */
		 if (TIMER0_MAX_NUMBER_OF_COUNTS >= Timer_Count_No)
		 {
		    /*calculate the TCNT value that achieve the number of counts*/
			 TCNT0 = TIMER0_MAX_NUMBER_OF_COUNTS - Timer_Count_No;

			 /*start the Timer using Prescaler that initialized in init function*/
			 TCCR0 |= gu8_PreScaler_T0;
		 }

		 /*if the number of counts doesn't fit with timer return error*/
		 else
		 {
		    Error |= E_NOK;
		 }
		 break;
		 /*************************************************************************************************************************/
		 case Timer_1:
		 /*check if number of count suitable for the timer */
		 if (TIMER1_MAX_NUMBER_OF_COUNTS >= Timer_Count_No)
		 {
			 /*calculate the TCNT value that achieve the number of counts*/
			 au8_Temp_For_Low_Bit   = TIMER1_MAX_NUMBER_OF_COUNTS - Timer_Count_No;
			 au8_Temp_For_Hight_Bit = ((TIMER1_MAX_NUMBER_OF_COUNTS - Timer_Count_No) SHIFT_8_BIT_RIGHT);

			 TCNT1H = au8_Temp_For_Hight_Bit;
			 TCNT1L = au8_Temp_For_Low_Bit;
			 
			 /*start the Timer using Prescaler that initialized in init function*/
			 TCCR1B |= gu8_PreScaler_T1;
		 }
		 /*if the number of counts doesn't fit with timer return error*/
		 else
		 {
			 Error |= E_NOK;
		 }
		 break;
		 /*************************************************************************************************************************/
		 case Timer_2:
		 /*check if number of count suitable for the timer */
		 if (TIMER2_MAX_NUMBER_OF_COUNTS >= Timer_Count_No)
		 {
			 /*calculate the TCNT value that achieve the number of counts*/
			 TCNT2 = TIMER2_MAX_NUMBER_OF_COUNTS - Timer_Count_No;
			 
			 /*start the Timer using Prescaler that initialized in init function*/
			 TCCR2 |= gu8_PreScaler_T2;
		 }
		 /*if the number of counts doesn't fit with timer return error*/
		 else
		 {
			 Error |= E_NOK;
		 }
		 break;
		 /*************************************************************************************************************************/
		 default:
		 Error |= E_NOK;
		 break;
	 }

	 return Error;
 }


 uint8_t Timer_Stop (uint8_t Timer_Chan)
 {
    /*variable to store errors*/
	 uint8_t Error = E_OK;
	 switch (Timer_Chan)
	 {
	    case Timer_0:
		 TCCR0 = TCCR0 & T0_NO_CLOCK;
		 break;

		 case Timer_1:
		 TCCR1B &= TCCR1B_VALUE_TO_STOP_TIMER1 ;
		 break;

		 case Timer_2:
		 TCCR2 &= T2_NO_CLOCK;
		 break;

		 default:
		 Error |= E_NOK;
		 break;
	 }

	 return Error;
 }


 uint8_t Timer_Get_Value (uint8_t Timer_Chan, uint16_t *Timer_Value)
 {
    /*variable to store errors*/
	 uint8_t Error = E_OK;
	 /*check if the given pointer is NULL return error */
	 if (NULL == Timer_Value)
	 {
	 Error |= E_NOK;
	 }

	 else
	 {
	    switch (Timer_Chan)
		 {
		    case Timer_0:
			 *Timer_Value = TCNT0;
			 break;

			 case Timer_1:
			 //stop timer 1 to get true value
			 TCCR1B &= TCCR1B_VALUE_TO_STOP_TIMER1 ;

			 //read the timer 1 value first low byte then higher byte
			 au8_Temp_For_Low_Bit   = TCNT1L;
			 au8_Temp_For_Hight_Bit = TCNT1H;

			 //start timer 1 to complete it's cycle
			 TCCR1B |= gu8_PreScaler_T1;

			 *Timer_Value = (au8_Temp_For_Low_Bit | (au8_Temp_For_Hight_Bit SHIFT_8_BIT_LEFT));
			 break;

			 case Timer_2:
			 *Timer_Value = TCNT2;
			 break;

			 default:
			 Error |= E_NOK;
			 break;
		 }
	 }
	 return Error;
 }


 uint8_t Timer_Set_Value (uint8_t Timer_Chan, uint16_t Timer_Value)
 {
    /*variable to store errors*/
	 uint8_t Error = E_OK;
	 
	 switch (Timer_Chan)
    {
	    case Timer_0:
	    TCNT0 = Timer_Value;
	    break;

	    case Timer_1:
	    au8_Temp_For_Low_Bit   = Timer_Value;
	    au8_Temp_For_Hight_Bit = (Timer_Value SHIFT_8_BIT_RIGHT);
	    
	    //stop timer 1 
	    TCCR1B &= TCCR1B_VALUE_TO_STOP_TIMER1 ;

	    TCNT1H = au8_Temp_For_Hight_Bit;
	    TCNT1L = au8_Temp_For_Low_Bit;

	    //start timer 1
	    TCCR1B |= gu8_PreScaler_T1;
	    break;

	    case Timer_2:
	    TCNT2 = Timer_Value;
	    break;

	    default:
	    Error |= E_NOK;
	    break;
    }

	 return Error;
 }


 uint8_t Timer_Get_Status (uint8_t Timer_Chan, uint8_t *Timer_Status)
 {
    /*variable to store errors*/
	 uint8_t Error = E_OK;
	 
	 switch (Timer_Chan)
    {
	    case Timer_0:
	    *Timer_Status = TOV0;
		 
		 RESETTOV0 ;
	    break;

	    case Timer_1:
	    *Timer_Status = TOV1;

		 RESETTOV1 ;
	    break;

	    case Timer_2:
	    *Timer_Status = TOV2;

		 RESETTOV2 ;
	    break;

	    default:
	    Error |= E_NOK;
	    break;
    }

	 return Error;
 }

 

 Inturrept_Function (TIMER0_OVF_vect)
 {
    ptr_CBF();
 }