#include <stdio.h>

#ifndef MAIN_H
#define MAIN_H

#define ZIGBEE_DEBUG
#ifdef ZIGBEE_DEBUG
#define DPRINTF(x...) printf("ZIGBEE_DEBUG :" x)
#else
#define DPRINTF(x...)
#endif

#endif