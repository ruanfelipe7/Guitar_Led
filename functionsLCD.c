#include	"hw_types.h"
#include	"soc_AM335x.h"
#include    "consoleUtils.h"
#include 	"functionsTimer.h"
#include 	"functionsIO.h"
#include 	"functionsLCD.h"
#include 	"functionsInterrupt.h"
#include 	"internalMacros.h"
#include    "functionsMatrixSongs.h"
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  start_lcd
 *  Description:  Configuração inicial do LCD
 *    Parameter:  Módulo utilizado
 * =====================================================================================
 */


void start_lcd(int module){
	//Coloca o lcd no modo de comando
	digitalWrite(module, RS, LOW);

	//configura modo 8bits -  0x80 => 10000000b
	digitalWrite(module, DO, LOW);
	digitalWrite(module, D1, LOW);
	digitalWrite(module, D2, LOW);
	digitalWrite(module, D3, LOW);
	digitalWrite(module, D4, LOW);
	digitalWrite(module, D5, LOW);
	digitalWrite(module, D6, LOW);
	digitalWrite(module, D7, HIGH);
	//------------------------------

	//pulso
	digitalWrite(module, ENABLE_LCD, HIGH);
	digitalWrite(module, ENABLE_LCD, LOW);
	delay(4);

	//Configuração 0x30
	digitalWrite(module, DO, LOW);
	digitalWrite(module, D1, LOW);
	digitalWrite(module, D2, LOW);
	digitalWrite(module, D3, LOW);
	digitalWrite(module, D4, HIGH);
	digitalWrite(module, D5, HIGH);
	digitalWrite(module, D6, LOW);
	digitalWrite(module, D7, LOW);
	//------------------------------

	//pulso
	digitalWrite(module, ENABLE_LCD, HIGH);
	digitalWrite(module, ENABLE_LCD, LOW);

	//0X38
	digitalWrite(module, DO, LOW);
	digitalWrite(module, D1, LOW);
	digitalWrite(module, D2, LOW);
	digitalWrite(module, D3, HIGH);
	digitalWrite(module, D4, HIGH);
	digitalWrite(module, D5, HIGH);
	digitalWrite(module, D6, LOW);
	digitalWrite(module, D7, LOW);
	//------------------------------

	//pulso
	digitalWrite(module, ENABLE_LCD, HIGH);
	digitalWrite(module, ENABLE_LCD, LOW);

	//0X0C
	digitalWrite(module, DO, LOW);
	digitalWrite(module, D1, LOW);
	digitalWrite(module, D2, HIGH);
	digitalWrite(module, D3, HIGH);
	digitalWrite(module, D4, LOW);
	digitalWrite(module, D5, LOW);
	digitalWrite(module, D6, LOW);
	digitalWrite(module, D7, LOW);
	//------------------------------

	//pulso
	digitalWrite(module, ENABLE_LCD, HIGH);
	delay(5);
	digitalWrite(module, ENABLE_LCD, LOW);



}/* -----  end of function start_lcd  ----- */
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  write_lcd
 *  Description:  Faz a escrita no display de uma string
 *    Parameter:  Módulo utilizado, string a ser escrita
 * =====================================================================================
 */
void write_lcd(int module, char *string){
	for (int i = 0; string[i] ; ++i)
	{
		digitalWrite(module, RS, HIGH);
		//coloca o caractere na entrada de dados
		digitalWrite(module, DO, string[i]&1);
		digitalWrite(module, D1, SHIFT(string[i],1));
		digitalWrite(module, D2, SHIFT(string[i],2));
		digitalWrite(module, D3, SHIFT(string[i],3));
		digitalWrite(module, D4, SHIFT(string[i],4));
		digitalWrite(module, D5, SHIFT(string[i],5));
		digitalWrite(module, D6, SHIFT(string[i],6));
		digitalWrite(module, D7, SHIFT(string[i],7));

		//pulso
		digitalWrite(module, ENABLE_LCD, HIGH);
		delay(3);
		digitalWrite(module, ENABLE_LCD, LOW);
	}

}/* -----  end of function write_lcd  ----- */
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  lcd_comand
 *  Description:  Envia uma instrução para o LCD
 *    Parameter:  Módulo utilizado, número do comando
 * =====================================================================================
 */
void lcd_comand(int module, int comando){

	//modo de comando
	digitalWrite(module, RS, LOW);
	//coloca o comando na entradas de dados
	digitalWrite(module, DO, comando&1);
	digitalWrite(module, D1, SHIFT(comando,1));
	digitalWrite(module, D2, SHIFT(comando,2));
	digitalWrite(module, D3, SHIFT(comando,3));
	digitalWrite(module, D4, SHIFT(comando,4));
	digitalWrite(module, D5, SHIFT(comando,5));
	digitalWrite(module, D6, SHIFT(comando,6));
	digitalWrite(module, D7, SHIFT(comando,7));

	digitalWrite(module, ENABLE_LCD, HIGH);
	delay(3);
	digitalWrite(module, ENABLE_LCD, LOW);
}/* -----  end of function lcd_comand  ----- */


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ShowLCDEnd
 *  Description:  Mostra a Msg e as informações referentes ao jogo que se encerrou
 *    Parameter:  Valor lógico se ganhou ou perdeu, tamanho da música, numero de pontos,
 *                número de erros, combo máximo
 * =====================================================================================
 */

void ShowLCDEnd(bool value, unsigned int sizeMusic, unsigned int points, unsigned int errors, unsigned int max){

	unsigned int percent = 0;
	percent = (points * 100) / sizeMusic;

	for(int i = 0; i < 3; i++){
		limparLCD();
		delay(TIME_1SEC);
		if(value){
			lcd_comand(SOC_GPIO_2_REGS, LINHA_1);
			write_lcd(SOC_GPIO_2_REGS, "Voce eh Fera!");
			delay(TIME_1SEC);
			lcd_comand(SOC_GPIO_2_REGS, CLEAR_LCD);
			delay(TIME_1SEC);

		}else{
			lcd_comand(SOC_GPIO_2_REGS, LINHA_1);
			write_lcd(SOC_GPIO_2_REGS, "Voce Perdeu!");
			delay(TIME_1SEC);
			lcd_comand(SOC_GPIO_2_REGS, CLEAR_LCD);
			delay(TIME_1SEC);

		}


		ConsoleUtilsPrintf("\nFim de Jogo\n");

		write_lcd(SOC_GPIO_2_REGS, "Pts:");
		write_number_lcd(SOC_GPIO_2_REGS, points);

		write_lcd(SOC_GPIO_2_REGS, " Max:");
		write_number_lcd(SOC_GPIO_2_REGS, max);

		lcd_comand(SOC_GPIO_2_REGS, LINHA_2);

		write_lcd(SOC_GPIO_2_REGS, "Pct:");

		//Cálculo do percentual
		if(percent > 100 && errors == 0){
			percent = 100;
		}else if(percent > 100 && errors > 0){
			percent = 95;
		}else{
			percent = percent;
		}

		write_number_lcd(SOC_GPIO_2_REGS, percent);
		write_lcd(SOC_GPIO_2_REGS, "%");

		write_lcd(SOC_GPIO_2_REGS, " Err:");
		write_number_lcd(SOC_GPIO_2_REGS, errors);
		delay(TIME_1SEC);

	}

	limparLCD();
	lcd_comand(SOC_GPIO_2_REGS, LINHA_1);
	write_lcd(SOC_GPIO_2_REGS, "     FIM DE");
	lcd_comand(SOC_GPIO_2_REGS, LINHA_2);
	write_lcd(SOC_GPIO_2_REGS, "      JOGO");
	delay(TIME_1SEC);
}/* -----  end of function ShowLCDEnd  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  limparLCD
 *  Description:  Limpa o conteúdo exibido no display LCD
 * =====================================================================================
 */

void limparLCD(void){
	lcd_comand(SOC_GPIO_2_REGS, LINHA_1);
	lcd_comand(SOC_GPIO_2_REGS, CLEAR_LCD);
	lcd_comand(SOC_GPIO_2_REGS, LINHA_2);
	lcd_comand(SOC_GPIO_2_REGS, CLEAR_LCD);
}/* -----  end of function limparLCD  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  startGame
 *  Description:  Mostra a Msg GuitarLed esperando a inicialização do jogo
 *    Parameter:  Status do jogo, se foi iniciado ou não
 * =====================================================================================
 */

void startGame(bool *status){

	/*-----------------------------------------------------------------------------
	 *  Quando a variavél status for alterada pela interrupção para TRUE ele sairá
	 *  desta função
	 *-----------------------------------------------------------------------------*/

	limparLCD();
	lcd_comand(SOC_GPIO_2_REGS, LINHA_2);
	write_lcd(SOC_GPIO_2_REGS, "Botoes --> Start");

	for(int i = 1; i <= 7; i++){
		lcd_comand(SOC_GPIO_2_REGS, LINHA_1);
		write_lcd(SOC_GPIO_2_REGS, "                ");
		lcd_comand(SOC_GPIO_2_REGS, LINHA_1);
		for(int j = 1; j < i; j++){
			write_lcd(SOC_GPIO_2_REGS, " ");
		}
		if((*status))
			break;
		write_lcd(SOC_GPIO_2_REGS, "GUITAR_LED");
		delay(250);

	}

	if(*status)
		return;

	for(int i = 6; i >= 1; i--){
		lcd_comand(SOC_GPIO_2_REGS, LINHA_1);
		write_lcd(SOC_GPIO_2_REGS, "                ");
		lcd_comand(SOC_GPIO_2_REGS, LINHA_1);
		for(int j = 1; j < i; j++){
			write_lcd(SOC_GPIO_2_REGS, " ");
		}
		if(*status)
			break;
		write_lcd(SOC_GPIO_2_REGS, "GUITAR_LED");
		delay(250);

	}


}/* -----  end of function startGame  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name: CountDown
 *  Description: Mostra a contagem regressiva para o inicio do jogo
 * =====================================================================================
 */

void CountDown(void){
	limparLCD();
	lcd_comand(SOC_GPIO_2_REGS, LINHA_1);
	write_lcd(SOC_GPIO_2_REGS, "       3");
	digitalWrite(SOC_GPIO_2_REGS, BUZZER, HIGH);
    delay(100);
    digitalWrite(SOC_GPIO_2_REGS, BUZZER, LOW);
    delay(900);
	lcd_comand(SOC_GPIO_2_REGS, LINHA_1);
	write_lcd(SOC_GPIO_2_REGS, "       2");
	digitalWrite(SOC_GPIO_2_REGS, BUZZER, HIGH);
    delay(100);
    digitalWrite(SOC_GPIO_2_REGS, BUZZER, LOW);
    delay(900);
    lcd_comand(SOC_GPIO_2_REGS, LINHA_1);
	write_lcd(SOC_GPIO_2_REGS, "       1");
	digitalWrite(SOC_GPIO_2_REGS, BUZZER, HIGH);
    delay(100);
    digitalWrite(SOC_GPIO_2_REGS, BUZZER, LOW);
    delay(900);

}/* -----  end of function CountDown  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ShowPause
 *  Description:  Mostra a mensagem PAUSE
 * =====================================================================================
 */

void ShowPause(void){
	limparLCD();
	lcd_comand(SOC_GPIO_2_REGS, LINHA_1);
	write_lcd(SOC_GPIO_2_REGS, "     PAUSE");
	delay(100);
}/* -----  end of function ShowPause  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  write_number_lcd
 *  Description:  Faz a escrita de um numero no display
 *    Parameter:  Módulo utilizdo, número a ser escrito
 * =====================================================================================
 */
void write_number_lcd(unsigned int module, unsigned int number){

	//separa os algarismos do numero
	int resto = (number % 10);
	number /= 10;
	if(number > 0){
		write_number_lcd(module, number);
	}

	digitalWrite(module, RS, HIGH);
	//coloca o caractere na entrada de dados
	digitalWrite(module, DO, SHIFT(resto,0));
	digitalWrite(module, D1, SHIFT(resto,1));
	digitalWrite(module, D2, SHIFT(resto,2));
	digitalWrite(module, D3, SHIFT(resto,3));
	digitalWrite(module, D4, HIGH);
	digitalWrite(module, D5, HIGH);
	digitalWrite(module, D6, LOW);
	digitalWrite(module, D7, LOW);

	//pulso
	digitalWrite(module, ENABLE_LCD, HIGH);
	delay(2);
	digitalWrite(module, ENABLE_LCD, LOW);

}/* -----  end of function write_number_lcd  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  playStatusLCD
 *  Description:  Mostra o status da pontuação e combo durante o jogo
 *    Parameter:  Valor do combo atual, numero de pontos
 * =====================================================================================
 */

void playStatusLCD(int combo, int points){
	limparLCD();
	lcd_comand(SOC_GPIO_2_REGS, LINHA_1);
	write_lcd(SOC_GPIO_2_REGS, "Pontuacao:");
	write_number_lcd(SOC_GPIO_2_REGS, points);
	lcd_comand(SOC_GPIO_2_REGS, LINHA_2);
	write_lcd(SOC_GPIO_2_REGS, "Combo:");
	write_number_lcd(SOC_GPIO_2_REGS, combo);
}/* -----  end of function playStatusLCD  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  SetMusicLCD
 *  Description:  Mostra qual música foi escolhida de acordo com o numero do
 *                display 7 segmentos
 *    Parameter:  Número da música
 * =====================================================================================
 */


void SetMusicLCD(int number){

	char strline1[12], strline2[17];
	limparLCD();
	lcd_comand(SOC_GPIO_2_REGS, LINHA_1);

	write_number_lcd(SOC_GPIO_2_REGS, number);
	write_lcd(SOC_GPIO_2_REGS, " - ");

	MUSIC playMusic = GetMusic(number);

	if(sizeString(playMusic.name) > 12){
		breakString(playMusic.name, strline1, strline2);
		write_lcd(SOC_GPIO_2_REGS, strline1);
		lcd_comand(SOC_GPIO_2_REGS, LINHA_2);
		write_lcd(SOC_GPIO_2_REGS, "   ");
		write_lcd(SOC_GPIO_2_REGS, strline2);

	}else{
		write_lcd(SOC_GPIO_2_REGS, playMusic.name);
	}



	delay(TIME);
	lcd_comand(SOC_GPIO_2_REGS, LINHA_2);
	write_lcd(SOC_GPIO_2_REGS, "Botoes --> Start");

}/* -----  end of function SetMusicLCD  ----- */