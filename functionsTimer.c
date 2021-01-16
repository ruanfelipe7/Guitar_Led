
#include    "dmtimer.h"
#include    "soc_AM335x.h"
#include    "internalMacros.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  DMTimerSetUp
 *  Description:  Configura o timer
 * =====================================================================================
 */

void DMTimerSetUp(void){
    DMTimerReset(SOC_DMTIMER_2_REGS);

    /* Load the counter with the initial count value */
    //DMTimerCounterSet(SOC_DMTIMER_2_REGS, TIMER_INITIAL_COUNT);

    /* Load the load register with the reload count value */
    //DMTimerReloadSet(SOC_DMTIMER_2_REGS, TIMER_RLD_COUNT);

    /* Configure the DMTimer for Auto-reload and compare mode */
    DMTimerModeConfigure(SOC_DMTIMER_2_REGS, DMTIMER_AUTORLD_NOCMP_ENABLE);
}/* -----  end of function DMTimerSetUp ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  delay
 *  Description:  Espera um certo tempo passador por parametro em milissegundos
 *    Parameter:  Tempo em milissegundos
 * =====================================================================================
 */

void delay(volatile unsigned int mSec){
   while(mSec != 0){
        DMTimerCounterSet(SOC_DMTIMER_2_REGS, 0);
        DMTimerEnable(SOC_DMTIMER_2_REGS);
        while(DMTimerCounterGet(SOC_DMTIMER_2_REGS) < TIMER_1MS_COUNT);
        DMTimerDisable(SOC_DMTIMER_2_REGS);
        mSec--;
    }
}/* -----  end of function delay ----- */



