#include	"hw_types.h"
#include	"soc_AM335x.h"
#include 	"internalMacros.h"
#include 	"functionsTimer.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  initModuleClock
 *  Description:  Configura o clock de um determinado modulo
 *    Parameter:  Módulo do clock, valor a ser colocado no registrador,
 *    			  ação de habilitar ou desabilitar
 * =====================================================================================
 */
void initModuleClock(int module, int value, bool action){

	/*-----------------------------------------------------------------------------
	 * configure clock in control module
	 *-----------------------------------------------------------------------------*/
	if(action){
		HWREG(SOC_CM_PER_REGS+module) |= (value);
	}else{
		HWREG(SOC_CM_PER_REGS+module) &= ~(value);
	}

}/* -----  end of function initModuleClock  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  configMux
 *  Description:  Configura o mux do pino
 *    Parameter:  Offset do pino a ser multiplexado, valor a ser colocado no
 *                registrador, ação de setar ou limpar os bits
 * =====================================================================================
 */
void configMux(int pin, int value, bool action){

	/*-----------------------------------------------------------------------------
	 * configure mux pin in control module
	 *-----------------------------------------------------------------------------*/
	if(action){
   		HWREG(SOC_CONTROL_REGS+pin) |= value;
	}else{
		HWREG(SOC_CONTROL_REGS+pin) &= ~(value);
	}

}/* -----  end of function configMux  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  initModuleClockGpio0
 *  Description:  Configura o clock de um determinado modulo(utilizado para o GPIO0)
 *    Parameter:  Módulo do clock, valor a ser colocado no registrador,
 *    			  ação de habilitar ou desabilitar
 * =====================================================================================
 */
void initModuleClockGpio0(int module, int value, bool action){

	/*-----------------------------------------------------------------------------
	 * configure clock in control module
	 *-----------------------------------------------------------------------------*/
	if(action){
		HWREG(SOC_CM_WKUP_REGS+module) |= (value);
	}else{
		HWREG(SOC_CM_WKUP_REGS+module) &= ~(value);
	}

}/* -----  end of function initModuleClock  ----- */


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  watchdog
 *  Description:  Habilita ou desabilita o watchdog
 *    Parameter:  Ação de habilitar ou desabilitar
 * =====================================================================================
 */
void watchdog(bool action){

	if(action){
		HWREG(SOC_WDT_1_REGS+WDT_WSPR) = WDT_WSPR_UP_VALUE_TEST;
		delay(3);
		HWREG(SOC_WDT_1_REGS+WDT_WSPR) = WDT_WSPR_UP_VALUE;
	}else{
		HWREG(SOC_WDT_1_REGS+WDT_WSPR) = WDT_WSPR_DOWN_VALUE_TEST;
		delay(3);
		HWREG(SOC_WDT_1_REGS+WDT_WSPR) = WDT_WSPR_DOWN_VALUE;
	}

}/* -----  end of function watchdog  ----- */