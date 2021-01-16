#ifndef _FUNCTIONS_INT_
#define _FUNCTIONS_INT_


void gpioAintcConf(void);
int  gpioPinIntConf(unsigned int, unsigned int, unsigned int);
void gpioPinIntEnable(unsigned int, unsigned int, unsigned int);
void gpioIntTypeSet(unsigned int, unsigned int, unsigned int);
void ClearInterrupt(unsigned int module, unsigned int line, unsigned int pin);
void DisableInterrupt(void);
void EnableInterrupt(void);
void EnableInterruptPause(void);
void DisableInterruptPause(void);
void EnableInterrupt7Seg(void);
void DisableInterrupt7Seg(void);

#endif //_FUNCTIONS_INT_