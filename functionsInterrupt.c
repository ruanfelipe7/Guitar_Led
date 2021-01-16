#include    "soc_AM335x.h"
#include    "interrupt.h"
#include    "board.h"
#include    "beaglebone.h"
#include    "gpio_v2.h"
#include    "consoleUtils.h"
#include 	"internalMacros.h"
#include    "functionsInterrupt.h"

extern void GPIO1AIsr(void);
extern void GPIO1BIsr(void);
extern void GPIO2AIsr(void);
extern void GPIO2BIsr(void);
extern void GPIO0AIsr(void);
extern void GPIO0BIsr(void);

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  gpioAintConf
 *  Description:  Registra quais funções serão chamadas se cocorrer uma interrupção,
 *                configura e Habilita as interrupção
 * =====================================================================================
 */


 void gpioAintcConf(void){

    /* Initialize the ARM interrupt control */
    IntAINTCInit();

    /* Registering os ISRs de cada interrupção */
    IntRegister(SYS_INT_GPIOINT1A, GPIO1AIsr);
    IntRegister(SYS_INT_GPIOINT1B, GPIO1BIsr);
    IntRegister(SYS_INT_GPIOINT2A, GPIO2AIsr);
    IntRegister(SYS_INT_GPIOINT2B, GPIO2BIsr);
    IntRegister(SYS_INT_GPIOINT0A, GPIO0AIsr);
    IntRegister(SYS_INT_GPIOINT0B, GPIO0BIsr);

    /* Set the priority */
    IntPrioritySet(SYS_INT_GPIOINT1A, 0, AINTC_HOSTINT_ROUTE_IRQ);
    IntPrioritySet(SYS_INT_GPIOINT1B, 0, AINTC_HOSTINT_ROUTE_IRQ);
    IntPrioritySet(SYS_INT_GPIOINT2A, 0, AINTC_HOSTINT_ROUTE_IRQ);
    IntPrioritySet(SYS_INT_GPIOINT2B, 0, AINTC_HOSTINT_ROUTE_IRQ);
    IntPrioritySet(SYS_INT_GPIOINT0A, 0, AINTC_HOSTINT_ROUTE_IRQ);
    IntPrioritySet(SYS_INT_GPIOINT0B, 0, AINTC_HOSTINT_ROUTE_IRQ);


    /* Enable the system interrupt of buttons of the game and display*/
    EnableInterrupt();
    EnableInterrupt7Seg();


}/* -----  end of function gpioAintConf  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ClearInterrupt
 *  Description:  Limpa a interrupção de acordo com a linha, pino e modulo utilizado
 *    Parameter:  Módulo do pino, Linha da interrupção, número do pino
 * =====================================================================================
 */

void ClearInterrupt(unsigned int module, unsigned int line, unsigned int pin){
    if(line)
        HWREG(module + GPIO_IRQ_STATUS1) = (1 << pin);
    else
        HWREG(module + GPIO_IRQ_STATUS0) = (1 << pin);
}/* -----  end of function ClearInterrupt  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  EnableInterrupt
 *  Description:  Habilita as interrupções dos botões do jogo
 * =====================================================================================
 */

void EnableInterrupt(void){

    IntSystemEnable(SYS_INT_GPIOINT1A);
    IntSystemEnable(SYS_INT_GPIOINT1B);
    IntSystemEnable(SYS_INT_GPIOINT2A);
}/* -----  end of function EnableInterrupt  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  DisbaleInterrupt
 *  Description:  Desabilita as interrupções dos botões do jogo
 * =====================================================================================
 */

void DisableInterrupt(void){

    IntSystemDisable(SYS_INT_GPIOINT1A);
    IntSystemDisable(SYS_INT_GPIOINT1B);
    IntSystemDisable(SYS_INT_GPIOINT2A);
}/* -----  end of function DisbaleInterrupt  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  EnableInterruptPause
 *  Description:  Habilita a interrupção do botão pause
 * =====================================================================================
 */

void EnableInterruptPause(void){
    IntSystemEnable(SYS_INT_GPIOINT2B);
}/* -----  end of function EnableInterruptPause  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  DisableInterruptPause
 *  Description:  Desabilita a interrupção do botão pause
 * =====================================================================================
 */

void DisableInterruptPause(void){
    IntSystemDisable(SYS_INT_GPIOINT2B);
}/* -----  end of function DisableInterruptPause  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  EnableInterrupt7Seg
 *  Description:  Habilita as interrupções dos botões que controlam o número exibido
 *                no display de 7 segmentos
 * =====================================================================================
 */

void EnableInterrupt7Seg(void){
    IntSystemEnable(SYS_INT_GPIOINT0A);
    IntSystemEnable(SYS_INT_GPIOINT0B);
}/* -----  end of function EnableInterrupt7Seg  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  DisableInterrupt7Seg
 *  Description:  Desabilita as interrupções dos botões - Display de 7 segmentos
 * =====================================================================================
 */

void DisableInterrupt7Seg(void){
    IntSystemDisable(SYS_INT_GPIOINT0A);
    IntSystemDisable(SYS_INT_GPIOINT0B);

}/* -----  end of function DisableInterrupt7Seg  ----- */



/*FUNCTION*-------------------------------------------------------
*
* Function Name : gpioPinIntConfig
* Comments      :
*END*-----------------------------------------------------------*/
 int gpioPinIntConf(unsigned int baseAdd, unsigned int intLine,
                  unsigned int pinNumber){

        /* Setting interrupt GPIO pin. */
        gpioPinIntEnable(baseAdd,
               intLine,
               pinNumber);

        return(0);
}

/*FUNCTION*-------------------------------------------------------
*
* Function Name : GPIOPinIntEnable
* Comments      : This API enables the configured interrupt event on a specified input
* GPIO pin to trigger an interrupt request.
*
* \param  baseAdd     The memory address of the GPIO instance being used
* \param  intLine     This specifies the interrupt request line on which the
*                     interrupt request due to the transitions on a specified
*                     pin be propagated
* \param  pinNumber   The number of the pin in the GPIO instance
*
* 'intLine' can take one of the following two values:
* - GPIO_INT_LINE_1 - interrupt request be propagated over interrupt line 1\n
* - GPIO_INT_LINE_2 - interrupt request be propagated over interrupt line 2\n
*
* 'pinNumber' can take one of the following values:
* (0 <= pinNumber <= 31)\n
*
* \return None
*
*END*-----------------------------------------------------------*/
 void gpioPinIntEnable(unsigned int baseAdd,
                      unsigned int intLine,
                      unsigned int pinNumber){
    if(GPIO_INTC_LINE_1 == intLine){
        HWREG(baseAdd + GPIO_IRQSTATUS_SET(0)) = (1 << pinNumber);
    }else{
        HWREG(baseAdd + GPIO_IRQSTATUS_SET(1)) = (1 << pinNumber);
    }
}

/*FUNCTION*-------------------------------------------------------
*
* Function Name : gpioAintcconfigure
*
* Comments      : Essa API configura o tipo de evento para um
* entrada GPIO pin. Sempre que o evento selecionado ocorrer nesse pino GPIO
* e se a geração de interrupção estiver habilitada para esse pino, o módulo GPIO
* irá enviar uma interrupção para a CPU.
*
* \param  baseAdd    O endereço de memória da instância do GPIO sendo usada
*
* \param  pinNumber  O número do pin na instância do GPIO
*
* \param  eventType  Isso especifica o tipo de evento em cuja detecção,
*                    o módulo GPIO enviará uma interrupção para a CPU,
*                    desde que a geração de interrupções para esse pino esteja habilitada.
*
*
* 'pinNumber' pode ter um dos seguintes valores:
* (0 <= pinNumber <= 31)\n
*
* 'eventType' can take one of the following values:
* - GPIO_INT_TYPE_NO_LEVEL - nenhum pedido de interrupção na ocorrência de um níve
*                            lógico BAIXO ou de um nível lógico ALTO no pino GPIO de entrada \ n
* - GPIO_INT_TYPE_LEVEL_LOW - pedido de interrupção na ocorrência de um nível LOW (lógica 0)
*                             no pino GPIO de entrada \ n
* - GPIO_INT_TYPE_LEVEL_HIGH - pedido de interrupção na ocorrência de um nível HIGH (lógica 1)
*                              no pino GPIO de entrada \ n
* - GPIO_INT_TYPE_BOTH_LEVEL - interromper a solicitação na ocorrência dos níveis LOW e HIGH
*                              no pino GPIO de entrada \ n
* - GPIO_INT_TYPE_NO_EDGE -  nenhum pedido de interrupção em bordas crescentes ou decrescentes no pino \ n
* - GPIO_INT_TYPE_RISE_EDGE - solicitação de interrupção na ocorrência de uma borda de subida no
*                             pino GPIO de entrada \ n
* - GPIO_INT_TYPE_FALL_EDGE - solicitação de interrupção na ocorrência de uma borda descendente
*                             no pino GPIO de entrada \ n
* - GPIO_INT_TYPE_BOTH_EDGE - interromper a solicitação na ocorrência de uma borda ascendente e uma borda
*                             descendente no pino \ n
*
* \return  None
*
* \note  Um caso de uso típico desta API é explicado abaixo:
*
* Se for requerido inicialmente que a interrupção seja gerada em um
* Apenas o nível LOW, então esta API pode ser chamada com
* 'GPIO_INT_TYPE_LEVEL_LOW' como o parâmetro.
* Em um momento posterior, se o nível lógico HIGH só deve ser feito como
* o evento de geração de interrupções, então esta API tem que ser chamada primeiro
* com 'GPIO_INT_TYPE_NO_LEVEL' como o parâmetro e depois com
* 'GPIO_INT_TYPE_LEVEL_HIGH' como o parâmetro. Isso garante que
* O gatilho lógico de nível LOW para interrupções está desativado.
*END*-----------------------------------------------------------*/
 void gpioIntTypeSet(unsigned int baseAdd,
                    unsigned int pinNumber,
                    unsigned int eventType){
    eventType &= 0xFF;

    switch(eventType)
    {

        case GPIO_INT_TYPE_NO_LEVEL:

            /* Disabling logic LOW level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinNumber);

            /* Disabling logic HIGH level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinNumber);

        break;

        case GPIO_INT_TYPE_LEVEL_LOW:

            /* Enabling logic LOW level detect interrupt geenration. */
            HWREG(baseAdd + GPIO_LEVELDETECT(0)) |= (1 << pinNumber);

            /* Disabling logic HIGH level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinNumber);

            /* Disabling rising edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinNumber);

            /* Disabling falling edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinNumber);

        break;

        case GPIO_INT_TYPE_LEVEL_HIGH:

            /* Disabling logic LOW level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinNumber);

            /* Enabling logic HIGH level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(1)) |= (1 << pinNumber);

            /* Disabling rising edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinNumber);

            /* Disabling falling edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinNumber);

        break;

        case GPIO_INT_TYPE_BOTH_LEVEL:

            /* Enabling logic LOW level detect interrupt geenration. */
            HWREG(baseAdd + GPIO_LEVELDETECT(0)) |= (1 << pinNumber);

            /* Enabling logic HIGH level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(1)) |= (1 << pinNumber);

            /* Disabling rising edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinNumber);

            /* Disabling falling edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinNumber);

        break;

        case GPIO_INT_TYPE_NO_EDGE:

            /* Disabling rising edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinNumber);

            /* Disabling falling edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinNumber);

        break;

        case GPIO_INT_TYPE_RISE_EDGE:

            /* Enabling rising edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_RISINGDETECT) |= (1 << pinNumber);

            /* Disabling falling edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinNumber);

            /* Disabling logic LOW level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinNumber);

            /* Disabling logic HIGH level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinNumber);

        break;

        case GPIO_INT_TYPE_FALL_EDGE:

            /* Disabling rising edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinNumber);

            /* Enabling falling edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_FALLINGDETECT) |= (1 << pinNumber);

            /* Disabling logic LOW level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinNumber);

            /* Disabling logic HIGH level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinNumber);

        break;

        case GPIO_INT_TYPE_BOTH_EDGE:

            /* Enabling rising edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_RISINGDETECT) |= (1 << pinNumber);

            /* Enabling falling edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_FALLINGDETECT) |= (1 << pinNumber);

            /* Disabling logic LOW level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinNumber);

            /* Disabling logic HIGH level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinNumber);

        break;

        default:
        break;
    }
}
