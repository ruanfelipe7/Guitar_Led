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
#include    "soc_AM335x.h"
#include    "interrupt.h"
#include    "board.h"
#include    "beaglebone.h"
#include    "gpio_v2.h"
#include    "consoleUtils.h"
#include    "dmtimer.h"
#include    "delay.h"
#include    "functionsInterrupt.h"

/*
 * Mapeia os seguimentos do display
 */
int segmentos[7] = {GPIO2_SEGMENTOA,
 					GPIO2_SEGMENTOB,
 					GPIO2_SEGMENTOC,
 					GPIO2_SEGMENTOD,
 					GPIO2_SEGMENTOE,
 					GPIO2_SEGMENTOF,
 					GPIO2_SEGMENTOG};

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  display7Segments
 *  Description:  Imprime em um display de 7 segmentos um determinado valor
 *    Parameter:  modulo do GPIO dos pinos utilizados, número a ser imprimido
 * =====================================================================================
 */

void diplay7Segments(int module, int value){
	switch(value){
		case SegState1:
			digitalWrite(module, segmentos[0], LOW);
			digitalWrite(module, segmentos[1], HIGH);
			digitalWrite(module, segmentos[2], HIGH);
			digitalWrite(module, segmentos[3], LOW);
			digitalWrite(module, segmentos[4], LOW);
			digitalWrite(module, segmentos[5], LOW);
			digitalWrite(module, segmentos[6], LOW);
			break;
		case SegState2:
			digitalWrite(module, segmentos[0], HIGH);
			digitalWrite(module, segmentos[1], HIGH);
			digitalWrite(module, segmentos[2], LOW);
			digitalWrite(module, segmentos[3], HIGH);
			digitalWrite(module, segmentos[4], HIGH);
			digitalWrite(module, segmentos[5], LOW);
			digitalWrite(module, segmentos[6], HIGH);
			break;
		case SegState3:
			digitalWrite(module, segmentos[0], HIGH);
			digitalWrite(module, segmentos[1], HIGH);
			digitalWrite(module, segmentos[2], HIGH);
			digitalWrite(module, segmentos[3], HIGH);
			digitalWrite(module, segmentos[4], LOW);
			digitalWrite(module, segmentos[5], LOW);
			digitalWrite(module, segmentos[6], HIGH);
			break;
		case SegState4:
			digitalWrite(module, segmentos[0], LOW);
			digitalWrite(module, segmentos[1], HIGH);
			digitalWrite(module, segmentos[2], HIGH);
			digitalWrite(module, segmentos[3], LOW);
			digitalWrite(module, segmentos[4], LOW);
			digitalWrite(module, segmentos[5], HIGH);
			digitalWrite(module, segmentos[6], HIGH);
			break;
		case SegState5:
			digitalWrite(module, segmentos[0], HIGH);
			digitalWrite(module, segmentos[1], LOW);
			digitalWrite(module, segmentos[2], HIGH);
			digitalWrite(module, segmentos[3], HIGH);
			digitalWrite(module, segmentos[4], LOW);
			digitalWrite(module, segmentos[5], HIGH);
			digitalWrite(module, segmentos[6], HIGH);
			break;
		case SegState6:
			digitalWrite(module, segmentos[0], HIGH);
			digitalWrite(module, segmentos[1], LOW);
			digitalWrite(module, segmentos[2], HIGH);
			digitalWrite(module, segmentos[3], HIGH);
			digitalWrite(module, segmentos[4], HIGH);
			digitalWrite(module, segmentos[5], HIGH);
			digitalWrite(module, segmentos[6], HIGH);
			break;
		case SegState7:
			digitalWrite(module, segmentos[0], HIGH);
			digitalWrite(module, segmentos[1], HIGH);
			digitalWrite(module, segmentos[2], HIGH);
			digitalWrite(module, segmentos[3], LOW);
			digitalWrite(module, segmentos[4], LOW);
			digitalWrite(module, segmentos[5], LOW);
			digitalWrite(module, segmentos[6], LOW);
			break;
		case SegState8:
			digitalWrite(module, segmentos[0], HIGH);
			digitalWrite(module, segmentos[1], HIGH);
			digitalWrite(module, segmentos[2], HIGH);
			digitalWrite(module, segmentos[3], HIGH);
			digitalWrite(module, segmentos[4], HIGH);
			digitalWrite(module, segmentos[5], HIGH);
			digitalWrite(module, segmentos[6], HIGH);
			break;
		case SegState9:
			digitalWrite(module, segmentos[0], HIGH);
			digitalWrite(module, segmentos[1], HIGH);
			digitalWrite(module, segmentos[2], HIGH);
			digitalWrite(module, segmentos[3], HIGH);
			digitalWrite(module, segmentos[4], LOW);
			digitalWrite(module, segmentos[5], HIGH);
			digitalWrite(module, segmentos[6], HIGH);
			break;
		default:
			digitalWrite(module, segmentos[0], LOW);
			digitalWrite(module, segmentos[1], LOW);
			digitalWrite(module, segmentos[2], LOW);
			digitalWrite(module, segmentos[3], LOW);
			digitalWrite(module, segmentos[4], LOW);
			digitalWrite(module, segmentos[5], LOW);
			digitalWrite(module, segmentos[6], LOW);

	}
} /* ----------  end of function display7Segments  ---------- */