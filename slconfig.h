#ifndef _SLCONFIG__
#define _SLCONFIG__

#ifdef USE_SERIAL3
#define SLSERIAL Serial3
#else
#define SLSERIAL Serial
#endif
#define MAX_COMMAND_COUNT 16
#define MAX_ARGUMENT_LENGTH 32

#endif

