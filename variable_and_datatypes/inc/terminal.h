#ifndef TERMINAL_H
#define TERMINAL_H

#include <stddef.h>

void Terminal_Init(void);

void Terminal_Shutdown(void);

int Terminal_Read(char *buf, size_t maxlen);

#endif // TERMINAL_H
