#ifndef _HAL_BUTTONS_H_
#define _HAL_BUTTONS_H_

#include <stdbool.h>

void ModeButton_Init(bool simuValue);
bool ModeButton_Read();

void PumpButton_Init(bool simuValue);
bool PumpButton_Read();

#endif
