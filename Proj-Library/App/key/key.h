#ifndef _key_H
#define _key_H
#include "nb_sys.h"

#define Key_Up PAin(0)

#define Key_Left PEin(2)
#define Key_Down PEin(3)
#define Key_Right PEin(4)

//#define K_U GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)
//#define K_L GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)
//#define K_D GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)
//#define K_R GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)

#define K_U 1
#define K_D 2
#define K_L 3
#define K_R 4

void KEY_Init(void);
u8 KEY_Scan(u8 mode);

#endif