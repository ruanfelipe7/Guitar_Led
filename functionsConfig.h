#ifndef _FUNCTIONS_CONFIG_
#define _FUNCTIONS_CONFIG_

void initModuleClock(int module, int value, bool action);
void initModuleClockGpio0(int module, int value, bool action);
void configMux(int pin, int value, bool action);
void watchdog(bool action);

#endif //_FUNCTIONS_CONFIG_