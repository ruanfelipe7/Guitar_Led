/*/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  15/05/2018 20:05:55
 *       Revision:  none
 *       Compiler
 :  arm-none-eabi-gcc-7.2.1
 *
 *         Author:  Equipe Guitar Led
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include    "hw_types.h"
#include    "soc_AM335x.h"
#include    "functionsIO.h"
#include    "internalMacros.h"
#include    "functionsConfig.h"
#include    "functionsTimer.h"
#include    "functionsInit.h"
#include    "functionsIO.h"
#include    "functionsLCD.h"
#include    "uart_irda_cir.h"
#include    "interrupt.h"
#include    "board.h"
#include    "beaglebone.h"
#include    "gpio_v2.h"
#include    "consoleUtils.h"
#include    "dmtimer.h"
#include    "delay.h"
#include    "functionsInterrupt.h"
#include    "functions7segmentos.h"
#include    "functionsPlayGame.h"


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  Inicaliza o programa
 * =====================================================================================
 */
int main(void){


    DMTimerSetUp();
    initSerial();
    IntMasterIRQEnable();

    // ENABLE PIN TO INTERRUPT
    gpioAintcConf();
    InitGpioPinInterrupt();
    watchdog(DOWN);


    InitGPIOClock();
    InitMUXGpio();
    InitConfigPin();
    InitMUXLCD();
    InitConfigPinLCD();

    start_lcd(SOC_GPIO_2_REGS);
    lcd_comand(SOC_GPIO_2_REGS, CLEAR_LCD);

    while (TRUE){

        GameBegin();

    }

    return(0);
} /* ----------  end of function main  ---------- */

