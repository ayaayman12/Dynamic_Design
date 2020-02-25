/*
 * TMU.h
 *
 * Created: 2/24/2020 3:04:56 PM
 *  Author: Khaled
 */ 


#ifndef TMU_H_
#define TMU_H_

#include "../std_types.h"
#include "TMU_Cfg.h"
#include "TMU_PbCfg.h"
#include "../../MCAL/timers.h"
#include "../Errors.h"



#define ONE_SHOT 0 
#define PERIODIC 1

 ERROR_STATUS TMU_Init (const str_TMU_InitConfig_t * pstr_TMU_ConfigPtr );

 ERROR_STATUS TMU_Dispatch(void);

 ERROR_STATUS TMU_Stop(uint8_t Task_Id, void(* Ptr_Func)(void));

 ERROR_STATUS TMU_Start (uint16_t Time_Delay,uint8_t Task_Id, uint8_t Repeat, void(* Ptr_Func)(void));

#endif /* TMU_H_ */