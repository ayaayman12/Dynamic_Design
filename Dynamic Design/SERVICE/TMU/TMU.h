/*
 * TMU.h
 *
 * Created: 2/24/2020 3:04:56 PM
 *  Author: Khaled
 */ 


#ifndef TMU_H_
#define TMU_H_

/* Inclusions */
#include "../../MCAL/timers.h"
#include "../std_types.h"
#include "TMU_Cfg.h"
#include "TMU_PbCfg.h"
#include "../Errors.h"
#include "../ERROR/ERROR-STORE.h"

/* Constants */
#define ONE_SHOT 0 
#define PERIODIC 1

/* function declarations*/


/******************************************************************************
* Function        : ERROR_STATUS TMU_Init (const str_TMU_InitConfig_t * pstr_TMU_ConfigPtr );                    
* Type            : public                                                                  
* Input parameters: TMUCfg Structure (u8_Timer_Id, u8_Tmu_Res)              
* Return type     : ERROR_STATUS                                                            
*                                                                               
* Description: initialize the TMU configuration, which initialize the Timer.
*****************************************************************************/
extern ERROR_STATUS TMU_Init (const str_TMU_InitConfig_t * pstr_TMU_ConfigPtr );

/******************************************************************************
* Function        : ERROR_STATUS TMU_Dispatch(void);              
* Type            : public                                                                  
* Input parameters: none   
* Return type     : ERROR_STATUS                                                            
*                                                                               
* Description: check timing to serve the counsumer function.
*****************************************************************************/
extern ERROR_STATUS TMU_Dispatch(void);

/******************************************************************************
* Function        : ERROR_STATUS TMU_Stop(uint8_t Task_Id, void(* Ptr_Func)(void));                   
* Type            : public                                                                  
* Input parameters: Task_Id, void(* Ptr_Func)(void)
* Return type     : ERROR_STATUS                                                            
*                                                                               
* Description: stop TMU for a specific task
*****************************************************************************/
extern ERROR_STATUS TMU_Stop(uint8_t Task_Id, void(* Ptr_Func)(void));

/******************************************************************************
* Function        : ERROR_STATUS TMU_Start (uint16_t Time_Delay,uint8_t Task_Id, uint8_t Repeat, void(* Ptr_Func)(void));                 
* Type            : public                                                                  
* Input parameters: Time_Delay, Task_Id, Repeat, void(* Ptr_Func)(void))
* Return type     : ERROR_STATUS                                                            
*                                                                               
* Description: start TMU
*****************************************************************************/
extern ERROR_STATUS TMU_Start (uint16_t Time_Delay,uint8_t Task_Id, uint8_t Repeat, void(* Ptr_Func)(void));

/******************************************************************************
* Function        : ERROR_STATUS TMU_DeInit (void);               
* Type            : public                                                                  
* Input parameters: none
* Return type     : ERROR_STATUS                                                            
*                                                                               
* Description: start TMU
*****************************************************************************/
 extern ERROR_STATUS TMU_DeInit (void);

#endif /* TMU_H_ */
