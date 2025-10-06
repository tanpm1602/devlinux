#include "hal_buttons.h"
#include <stdio.h>

static bool g_modeButtonState = 0;
static bool g_pumpButtonState = 0;

void ModeButton_Init(bool simuValue)
{
    g_modeButtonState = simuValue;
}

bool ModeButton_Read()
{
    return g_modeButtonState;
}

void PumpButton_Init(bool simuValue)
{
    g_pumpButtonState = simuValue;
}

bool PumpButton_Read()
{
    return g_pumpButtonState;
}
