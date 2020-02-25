/*
 * TMU_PbCfg.h
 *
 * Created: 2/24/2020 3:05:47 PM
 *  Author: Khaled
 */ 


#ifndef TMU_PBCFG_H_
#define TMU_PBCFG_H_

 #include "../std_types.h"
 #include "../../MCAL/timers.h"

 typedef struct str_TMU_InitConfig_t
 {
	 uint8_t u8_Timer_Id;
	 uint8_t u8_Tmu_Res;
 }str_TMU_InitConfig_t;

 
#endif /* TMU_PBCFG_H_ */