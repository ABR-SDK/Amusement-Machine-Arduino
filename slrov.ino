#include <avr/wdt.h>
#include <EEPROM.h>
#include <Arduino.h>
#include "slconfig.h"
#include "command.h"
#include "device.h"
#include "timer.h"

volatile int f_wdt = 0;
volatile int wdt_times = 0;

command cmd;
/**************************************
 *
 *************************************/
void setup_watchdog() {
  cli();
  wdt_reset();
  MCUSR &= ~(1 << WDRF);
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  WDTCSR = 0x00;
  sei();
  cli();
  MCUSR &= ~(1 << WDRF);
  wdt_reset();
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  //8s
  WDTCSR = (~(1 << WDP1) & ~(1 << WDP2)) | ((1 << WDE) | (1 << WDIE) | (1 << WDP3) | (1 << WDP0));
  sei();

}

void setup() {
  setup_watchdog();
  SLSERIAL.begin(115200);

  f_wdt = EEPROM.read(0);

  if (f_wdt == 1) {
    wdt_times = EEPROM.read(1);
    SLSERIAL.println(F("log(\"Watchdog have been trigger\")"));
    SLSERIAL.print(F("log(\"watchdog reset times:"));
    SLSERIAL.print(wdt_times);
    SLSERIAL.println(F("\")"));
    EEPROM.write(0, 0);
  }

  DeviceManager::device_all_setup();
}

void loop() {
  wdt_reset();
  if (cmd.getCommand()) {
    //cmd.debug();
    cmd.dispatch();
  }
  timer::getInstance()->run();
}


/**************************************
 *
 *************************************/
ISR(WDT_vect) {
  EEPROM.write(0, 1);
  EEPROM.write(1, wdt_times + 1);
  while (true);
}

