#include	"hw_types.h"
#include	"soc_AM335x.h"
#include 	"internalMacros.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  pinMode
 *  Description:  Seta a direção do pino
 *    Parameter:  Módulo do pino, número do GPIO do pino, modo de entrada ou saída
 * =====================================================================================
 */

void pinMode(int module, int pin, bool mode){

	/*-----------------------------------------------------------------------------
	 *  Seleciona a função do pino: Entrada ou Saída. Isto é definido pelo parametro
	 *  mode, se(mode == 1 ){ pin é de entrada } senao{ pin é de saída }
	 *-----------------------------------------------------------------------------*/
    if(mode){
        HWREG(module+GPIO_OE) |= (1<<pin);
    }else{
        HWREG(module+GPIO_OE) &= ~(1<<pin);
    }
}/* -----  end of function pinMode  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  digitalWrite
 *  Description:  Envia um sinal digital para determinado pino
 *    Parameter:  Módulo do pino, número do GPIO do pino, nível lógico alto ou baixo
 * =====================================================================================
 */
void digitalWrite(int module, int pin, bool value){

	/*-----------------------------------------------------------------------------
	 *  O sinal digital do pino passado é definido por value.
	 *  se(value == 1 ){ pin configurado para nível lógico alto }
	 *  senao{ pin configurado para nível lógico baixo }
	 *-----------------------------------------------------------------------------*/

	if(value){
		HWREG(module+GPIO_SETDATAOUT) = (1<<pin);
	}else{
		HWREG(module+GPIO_CLEARDATAOUT) = (1<<pin);
	}

}/* -----  end of function digitalWrite  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  digitalRead
 *  Description:  Lê um sinal digital de um determinado pino
 *    Parameter:  Módulo do pino, número do GPIO do pino
 *       Return:  Nível lógico alto ou baixo
 * =====================================================================================
 */
bool digitalRead(int module, int pin){

    return  ((HWREG((module+GPIO_DATAIN)) >> pin) & 1);

}/* -----  end of function digitalRead  ----- */

