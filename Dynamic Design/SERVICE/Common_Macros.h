
/*
 * Common_Macros.h
 *
 * Created: 2/16/2020 8:16:17 PM
 *  Author: Khaled
 */ 

 #ifndef COMMON_MACROS_H_
 #define COMMON_MACROS_H_

  #define ZERO              0x00

  #define SHIFT_8_BIT_RIGHT  >> 8
  #define SHIFT_8_BIT_LEFT   <<8

  #define BIT0	0x01
  #define BIT1	0x02
  #define BIT2	0x04
  #define BIT3	0x08
  #define BIT4	0x10
  #define BIT5	0x20
  #define BIT6	0x40
  #define BIT7	0x80

  #define SET_BIT(REG,BIT)    REG |= BIT
  #define CLEAR_BIT(REG,BIT)  REG &= ~(BIT)
  #define TOGGLE_BIT(REG,BIT)     REG ^= BIT

 #endif /* COMMON_MACROS_H_ */