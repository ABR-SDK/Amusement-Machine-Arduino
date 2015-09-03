#ifndef _SLCONFIG__
#define _SLCONFIG__

#ifdef USE_SERIAL3
#define SLSERIAL Serial3
#else
#define SLSERIAL Serial
#endif
#define MAX_COMMAND_COUNT 16
#define MAX_ARGUMENT_LENGTH 32

#define HAS_MS5803_14BA (1)
#define MS5803_14BA_I2C_ADDRESS 0x76
#define HAS_MPU9150 (1)
#define MPU9150_EEPROM_START 2
#endif

