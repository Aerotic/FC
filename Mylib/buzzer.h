#ifndef __BUZZER_H__
#define __BUZZER_H__

#include "board.h"

#define  BUZZER_ON      BUZZER_PORT->BSRRL = BUZZER_Pin
#define  BUZZER_OFF     BUZZER_PORT->BSRRH = BUZZER_Pin

void Buzzer_Init(void);

#endif
