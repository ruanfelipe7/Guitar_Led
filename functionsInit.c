#include	"hw_types.h"
#include	"soc_AM335x.h"
#include 	"functionsIO.h"
#include 	"internalMacros.h"
#include 	"functionsConfig.h"
#include    "uart_irda_cir.h"
#include    "consoleUtils.h"
#include    "functionsInterrupt.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  InitGPIOClock
 *  Description:  Inicializa os clocks dos gpios utilizados
 * =====================================================================================
 */

void InitGPIOClock(void){

	initModuleClock(CM_PER_GPIO1, CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK, UP);
	initModuleClock(CM_PER_GPIO1, CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE, UP);
	initModuleClock(CM_PER_GPIO2, CM_PER_GPIO2_CLKCTRL_OPTFCLKEN_GPIO_2_GDBCLK, UP);
	initModuleClock(CM_PER_GPIO2, CM_PER_GPIO2_CLKCTRL_MODULEMODE_ENABLE, UP);
	initModuleClock(CM_PER_GPIO3, CM_PER_GPIO3_CLKCTRL_OPTFCLKEN_GPIO_3_GDBCLK, UP);
	initModuleClock(CM_PER_GPIO3, CM_PER_GPIO3_CLKCTRL_MODULEMODE_ENABLE, UP);
	initModuleClockGpio0(CM_WKUP_GPIO0, CM_WKUP_GPIO0_CLKCTRL_OPTFCLKEN_GPIO_0_GDBCLK, UP);
	initModuleClockGpio0(CM_WKUP_GPIO0, CM_WKUP_GPIO0_CLKCTRL_MODULEMODE_ENABLE, UP);

}/* -----  end of function InitGPIOClock  ----- */


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  InitMUXGpio
 *  Description:  Realiza a configuração dos mux dos pinos utilizados
 * =====================================================================================
 */

void InitMUXGpio(void){
	//pinos das Trilhas de Leds do jogo

	/*****************************************************
	**               TRILHA 1 - LEDS VERDES             **
	******************************************************/

	configMux(GPIO_CTRL_MODULE_ARRAY[6][1], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[2][1], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[13][1], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[15][1], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[30][1], conf_module_mmode, UP);

	/*****************************************************
	**            TRILHA 2 - LEDS VERMELHOS             **
	******************************************************/

	configMux(GPIO_CTRL_MODULE_ARRAY[7][1], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[3][1], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[12][1], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[14][1], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[31][1], conf_module_mmode, UP);

	/*****************************************************
	**               TRILHA 3 - AMARELOS                **
	******************************************************/

	configMux(GPIO_CTRL_MODULE_ARRAY[4][1], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[5][1], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[1][1], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[0][1], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[29][1], conf_module_mmode, UP);

	//pino do Buzzer
	configMux(GPIO_CTRL_MODULE_ARRAY[2][2], conf_module_mmode, UP);

	//pinos do 7 segmentos
	configMux(GPIO_CTRL_MODULE_ARRAY[22][2], conf_module_mmode, UP); //SEG A
	configMux(GPIO_CTRL_MODULE_ARRAY[23][2], conf_module_mmode, UP); //SEG B
	configMux(GPIO_CTRL_MODULE_ARRAY[24][2], conf_module_mmode, UP); //SEG C
	configMux(GPIO_CTRL_MODULE_ARRAY[25][2], conf_module_mmode, UP); //SEG D
	configMux(GPIO_CTRL_MODULE_ARRAY[5][2], conf_module_mmode, UP); //SEG E
	configMux(GPIO_CTRL_MODULE_ARRAY[3][2], conf_module_mmode, UP); //SEG F
	configMux(GPIO_CTRL_MODULE_ARRAY[4][2], conf_module_mmode, UP); //SEG G


	//botões do jogo
	/*****************************************************
	**              BOTÃO 1 - TRILHA VERDE              **
	******************************************************/
	configMux(GPIO_CTRL_MODULE_ARRAY[16][1], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[16][1], conf_module_puden, DOWN);
	configMux(GPIO_CTRL_MODULE_ARRAY[16][1], conf_module_typesel, DOWN);
	configMux(GPIO_CTRL_MODULE_ARRAY[16][1], conf_module_rxactive, UP);

	/*****************************************************
	**            BOTÃO 2 - TRILHA VERMELHO             **
	******************************************************/
	configMux(GPIO_CTRL_MODULE_ARRAY[17][1], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[17][1], conf_module_puden, DOWN);
	configMux(GPIO_CTRL_MODULE_ARRAY[17][1], conf_module_typesel, DOWN);
	configMux(GPIO_CTRL_MODULE_ARRAY[17][1], conf_module_rxactive, UP);

	/*****************************************************
	**             BOTÃO 3 - TRILHA AMARELO             **
	******************************************************/
	configMux(GPIO_CTRL_MODULE_ARRAY[17][2], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[17][2], conf_module_puden, DOWN);
	configMux(GPIO_CTRL_MODULE_ARRAY[17][2], conf_module_typesel, DOWN);
	configMux(GPIO_CTRL_MODULE_ARRAY[17][2], conf_module_rxactive, UP);

	/*****************************************************
	**                  BOTÃO PAUSE                     **
	******************************************************/
	configMux(GPIO_CTRL_MODULE_ARRAY[16][2], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[16][2], conf_module_puden, DOWN);
	configMux(GPIO_CTRL_MODULE_ARRAY[16][2], conf_module_typesel, DOWN);
	configMux(GPIO_CTRL_MODULE_ARRAY[16][2], conf_module_rxactive, UP);

	//botões de escolha de musica
	configMux(GPIO_CTRL_MODULE_ARRAY[27][0], conf_module_mmode, UP); //Button Plus
	configMux(GPIO_CTRL_MODULE_ARRAY[26][0], conf_module_mmode, UP); //Button Less

	//pinos do Semáforo
	configMux(GPIO_CTRL_MODULE_ARRAY[21][3], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[19][3], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[15][3], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[17][3], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[16][3], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[14][3], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[19][1], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[18][1], conf_module_mmode, UP);
	configMux(GPIO_CTRL_MODULE_ARRAY[28][1], conf_module_mmode, UP);



}/* -----  end of function InitMUXGpio  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  InitMUXLCD
 *  Description:  Realiza a configuração dos mux dos pinos utilizados no display LCD
 * =====================================================================================
 */

void InitMUXLCD(void){

	//pins LCD
	configMux(GPIO_CTRL_MODULE_ARRAY[6][2], conf_module_mmode, UP); //DO
	configMux(GPIO_CTRL_MODULE_ARRAY[7][2], conf_module_mmode, UP); //D1
	configMux(GPIO_CTRL_MODULE_ARRAY[8][2], conf_module_mmode, UP); //D2
	configMux(GPIO_CTRL_MODULE_ARRAY[9][2], conf_module_mmode, UP); //D3
	configMux(GPIO_CTRL_MODULE_ARRAY[10][2], conf_module_mmode, UP); //D4

	configMux(GPIO_CTRL_MODULE_ARRAY[11][2], conf_module_mmode, UP); // D5
	configMux(GPIO_CTRL_MODULE_ARRAY[12][2], conf_module_mmode, UP); // D6
	configMux(GPIO_CTRL_MODULE_ARRAY[13][2], conf_module_mmode, UP); //D7
	configMux(GPIO_CTRL_MODULE_ARRAY[14][2], conf_module_mmode, UP); //RS

	configMux(GPIO_CTRL_MODULE_ARRAY[15][2], conf_module_mmode, UP); //enable

}/* -----  end of function InitMUXLCD  ----- */


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  InitConfigPin
 *  Description:  Configura a direção dos pinos utilizados
 * =====================================================================================
 */

void InitConfigPin(void){

	//Pinos das trilhas
	//Trilha - Verde
	pinMode(SOC_GPIO_1_REGS, GPIO1_LED05, OUTPUT);
	pinMode(SOC_GPIO_1_REGS, GPIO1_LED04, OUTPUT);
	pinMode(SOC_GPIO_1_REGS, GPIO1_LED03, OUTPUT);
	pinMode(SOC_GPIO_1_REGS, GPIO1_LED02, OUTPUT);
	pinMode(SOC_GPIO_1_REGS, GPIO1_LED01, OUTPUT);

	//Trilha - Vermelho
	pinMode(SOC_GPIO_1_REGS, GPIO1_LED06, OUTPUT);
	pinMode(SOC_GPIO_1_REGS, GPIO1_LED07, OUTPUT);
	pinMode(SOC_GPIO_1_REGS, GPIO1_LED08, OUTPUT);
	pinMode(SOC_GPIO_1_REGS, GPIO1_LED09, OUTPUT);
	pinMode(SOC_GPIO_1_REGS, GPIO1_LED10, OUTPUT);

	//Trilha - Amarelo
	pinMode(SOC_GPIO_1_REGS, GPIO1_LED11, OUTPUT);
	pinMode(SOC_GPIO_1_REGS, GPIO1_LED12, OUTPUT);
	pinMode(SOC_GPIO_1_REGS, GPIO1_LED13, OUTPUT);
	pinMode(SOC_GPIO_1_REGS, GPIO1_LED14, OUTPUT);
	pinMode(SOC_GPIO_1_REGS, GPIO1_LED15, OUTPUT);

	//Pino do Buzzer
	pinMode(SOC_GPIO_2_REGS, BUZZER, OUTPUT);

	//Pinos dos Botões
	//Botão 1
	pinMode(SOC_GPIO_1_REGS, GPIO1_BUTTON1, INPUT);
	//Botão 2
	pinMode(SOC_GPIO_1_REGS, GPIO1_BUTTON2, INPUT);
	//Botão 3
	pinMode(SOC_GPIO_2_REGS, GPIO2_BUTTON3, INPUT);
	//Botão Pause
	pinMode(SOC_GPIO_2_REGS, GPIO2_BUTTONPAUSE, INPUT);
	//Botão de alteração de música - incrementa
	pinMode(SOC_GPIO_0_REGS, GPIO0_BUTTONPLUS, OUTPUT);
	//Botão de alteração de música - decrementa
	pinMode(SOC_GPIO_0_REGS, GPIO0_BUTTONLESS, OUTPUT);

	//Pinos do display de 7 segmentos
	pinMode(SOC_GPIO_2_REGS,  GPIO2_SEGMENTOA , OUTPUT);
	pinMode(SOC_GPIO_2_REGS,  GPIO2_SEGMENTOB, OUTPUT);
	pinMode(SOC_GPIO_2_REGS,  GPIO2_SEGMENTOC, OUTPUT);
	pinMode(SOC_GPIO_2_REGS,  GPIO2_SEGMENTOD, OUTPUT);
	pinMode(SOC_GPIO_2_REGS,  GPIO2_SEGMENTOE, OUTPUT);
	pinMode(SOC_GPIO_2_REGS,  GPIO2_SEGMENTOF, OUTPUT);
	pinMode(SOC_GPIO_2_REGS,  GPIO2_SEGMENTOG, OUTPUT);

	//Pinos dos semáforo de status
	pinMode(SOC_GPIO_3_REGS, GPIO3_LEDSEMAPHORE1, OUTPUT);
	pinMode(SOC_GPIO_3_REGS, GPIO3_LEDSEMAPHORE2, OUTPUT);
	pinMode(SOC_GPIO_3_REGS, GPIO3_LEDSEMAPHORE3, OUTPUT);
	pinMode(SOC_GPIO_3_REGS, GPIO3_LEDSEMAPHORE4, OUTPUT);
	pinMode(SOC_GPIO_3_REGS, GPIO3_LEDSEMAPHORE5, OUTPUT);
	pinMode(SOC_GPIO_3_REGS, GPIO3_LEDSEMAPHORE6, OUTPUT);
	pinMode(SOC_GPIO_1_REGS, GPIO1_LEDSEMAPHORE7, OUTPUT);
	pinMode(SOC_GPIO_1_REGS, GPIO1_LEDSEMAPHORE8, OUTPUT);
	pinMode(SOC_GPIO_1_REGS, GPIO1_LEDSEMAPHORE9, OUTPUT);



}/* -----  end of function InitConfigPin  ----- */
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  InitConfigPinLCD
 *  Description:  Configura a direção dos pinos utilizados no display LCD
 * =====================================================================================
 */

void InitConfigPinLCD(void){

	//pinslcd
	pinMode(SOC_GPIO_2_REGS, DO, OUTPUT);
	pinMode(SOC_GPIO_2_REGS, D1, OUTPUT);
	pinMode(SOC_GPIO_2_REGS, D2, OUTPUT);
	pinMode(SOC_GPIO_2_REGS, D3, OUTPUT);
	pinMode(SOC_GPIO_2_REGS, D4, OUTPUT);

	pinMode(SOC_GPIO_2_REGS, D5, OUTPUT);
	pinMode(SOC_GPIO_2_REGS, D6, OUTPUT);
	pinMode(SOC_GPIO_2_REGS, D7, OUTPUT);
	pinMode(SOC_GPIO_2_REGS, RS, OUTPUT);

	pinMode(SOC_GPIO_2_REGS, ENABLE_LCD, OUTPUT);

}/* -----  end of function InitConfigPinLCD  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  initSerial
 *  Description:
 * =====================================================================================
 */

void initSerial(){
    /* Initialize console for communication with the Host Machine */
        ConsoleUtilsInit();

        /* Select the console type based on compile time check */
        ConsoleUtilsSetType(CONSOLE_UART);

}/* -----  end of function initSerial  ----- */


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  InitGpioPinInterrupt
 *  Description:  Inicializa os pinos referentes a interrupções
 * =====================================================================================
 */

void InitGpioPinInterrupt(void){

	//Configura os pinos dos botões para a utilização de interrupção e configura a
	//ativação da interrupção para a borda de subida

	gpioPinIntConf(SOC_GPIO_1_REGS, GPIO_INTC_LINE_1, GPIO1_BUTTON1);
    gpioIntTypeSet(SOC_GPIO_1_REGS, GPIO1_BUTTON1, GPIO_INTC_TYPE_RISE_EDGE);
    gpioPinIntConf(SOC_GPIO_1_REGS, GPIO_INTC_LINE_2, GPIO1_BUTTON2);
    gpioIntTypeSet(SOC_GPIO_1_REGS, GPIO1_BUTTON2, GPIO_INTC_TYPE_RISE_EDGE);
    gpioPinIntConf(SOC_GPIO_2_REGS, GPIO_INTC_LINE_1, GPIO2_BUTTON3);
    gpioIntTypeSet(SOC_GPIO_2_REGS, GPIO2_BUTTON3, GPIO_INTC_TYPE_RISE_EDGE);

    gpioPinIntConf(SOC_GPIO_2_REGS, GPIO_INTC_LINE_2, GPIO2_BUTTONPAUSE);
    gpioIntTypeSet(SOC_GPIO_2_REGS, GPIO2_BUTTONPAUSE, GPIO_INTC_TYPE_RISE_EDGE);

    gpioPinIntConf(SOC_GPIO_0_REGS, GPIO_INTC_LINE_1, GPIO0_BUTTONPLUS);
    gpioIntTypeSet(SOC_GPIO_0_REGS, GPIO0_BUTTONPLUS, GPIO_INTC_TYPE_RISE_EDGE);
    gpioPinIntConf(SOC_GPIO_0_REGS, GPIO_INTC_LINE_2, GPIO0_BUTTONLESS);
    gpioIntTypeSet(SOC_GPIO_0_REGS, GPIO0_BUTTONLESS, GPIO_INTC_TYPE_RISE_EDGE);

}/* -----  end of function InitGpioPinInterrupt  ----- */