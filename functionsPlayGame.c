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
#include    "functionsMatrixSongs.h"
#include    "functionsPlayGame.h"

//Mapeia os leds das trilhas
int rows[5][3] = {
    {GPIO1_LED01, GPIO1_LED06, GPIO1_LED11},
    {GPIO1_LED02, GPIO1_LED07, GPIO1_LED12},
    {GPIO1_LED03, GPIO1_LED08, GPIO1_LED13},
    {GPIO1_LED04, GPIO1_LED09, GPIO1_LED14},
    {GPIO1_LED05, GPIO1_LED10, GPIO1_LED15}
};
//Mapeia os leds do semaforo
int LedsSemaphore[9] = {GPIO3_LEDSEMAPHORE1, GPIO3_LEDSEMAPHORE2, GPIO3_LEDSEMAPHORE3, GPIO3_LEDSEMAPHORE4,
                        GPIO3_LEDSEMAPHORE5, GPIO3_LEDSEMAPHORE6, GPIO1_LEDSEMAPHORE7, GPIO1_LEDSEMAPHORE8,
                        GPIO1_LEDSEMAPHORE9};

//Mapeia os botoes de jogar
int buttons[3] = {GPIO1_BUTTON1, GPIO1_BUTTON2, GPIO2_BUTTON3};

/*
* scores        = Variável que controla o semáforo representando o status de acertos e erros do jogador
* error         = Variável que representa a quantidade de qualquer erro cometido pelo jogador
* hit           = Variável que representa a quantidade notas acertadas pelo jogador
* mutexButton   = Vetor que sinaliza se alguns dos botões está disponivel para ser apertado
* combo         = Variável que representa se o usuário foi capaz de realizar acertos sucessivos
* bigCombo      = Variável que representa se o usuário foi capaz de realizar combos sucessivos
* (lock & start)= Variáveis que irá bloquear algumas funções do jogo se ainda não estiver iniciado
* numberMusic   = Variável que representa a música que o usuário escolheu
* trailFinaly   = Vetor que representa o nível lógico dos últimos leds de cada trilha
* buttonfinally = Vetor que representa o nível lógico dos botões principais do jogo
* notBuzzer = Indica o momento em que o buzzer deve tocar
*/

unsigned int scores = 5, error = 0, hit = 0, notas = 0, combo = 0, bigCombo=0;
static bool start = 0, win = 0;
static bool trailFinaly[3] = {0,0,0};
static bool buttonfinally[3] = {0,0,0};
bool mutexButton[3] = {TRUE, TRUE, TRUE};
bool lock = FALSE;
static bool pause = FALSE;
int numberMusic = 1;
bool notBuzzer = TRUE;


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  GameBegin
 *  Description:  Realiza todos os passos durante o jogo
 * =====================================================================================
 */

void GameBegin(void){

    MUSIC gameMusic;
    Background();
    delay(TIME*4);
    Playlist();
    while(TRUE){

            diplay7Segments(SOC_GPIO_2_REGS, numberMusic);
            startGame(&start);
            if(start){
                //Desabilita as interrupções dos botões para quando apertado pelo usuário durante
                //a inicialização do jogo não ocorrer alterações indevidas.
                DisableInterrupt();
                DisableInterrupt7Seg();
                DisableInterruptPause();
                ClearMutexButton();
                //Contagem regressiva para iniciar jogo
                CountDown();
                //Reabilita as interrupções dos botões
                EnableInterrupt();
                EnableInterruptPause();
                if(!mutexButton[0])
                    mutexButton[0] = TRUE;
                if(!mutexButton[1])
                    mutexButton[1] = TRUE;
                if(!mutexButton[2])
                    mutexButton[2] = TRUE;
                lock = TRUE;
                break;
            }

    }

    Background();
    gameMusic = GetMusic(numberMusic);
    notas = countNotes(gameMusic.size, gameMusic.notes);
    Semaphore(scores);
    playStatusLCD(combo, hit);
    win = writeBlinkLeds(SOC_GPIO_1_REGS,5,3, gameMusic);
    GameOver(5,3);
    ShowLCDEnd(win,notas,hit,error,bigCombo);
    NewGame();

}/* -----  end of function CountNotes ----- */


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  writeBlinkLeds
 *  Description:  Faz com que os leds pisquem de acordo com a matriz da música
 *    Parameter:  Módulo utilizado para as trilhas de leds, número de leds por trilhas,
 *                número de trilhas, música a ser lida
 *       Return:  Retorna TRUE se finalizar a musica ou FALSE se não conseguir finalizar
 * =====================================================================================
 */
bool writeBlinkLeds(int module, int numberLedsToTrail, int numberTrail, MUSIC gameMusic){

    bool trails[numberLedsToTrail][numberTrail];

    for (int i = 0; i < numberLedsToTrail; i++){
        for (int j = 0; j < numberTrail; ++j)
        {
            trails[i][j] = 0;
        }
    }

    for (int i = 0; i < gameMusic.size; i++){
        if(scores){
            for (int j = numberLedsToTrail-1; j>=0; j--){
                for (int k = 0; k < numberTrail; ++k){
                    if(j!=0){
                        trails[j][k] = trails[j-1][k];
                    }else{

                        trails[j][k] = gameMusic.notes[i][k];
                    }
                }
            }
            for (int j = 0; j < numberLedsToTrail; j++){
                for (int k = 0; k < numberTrail; ++k){
                    if (trails[j][k]){
                        digitalWrite(module,rows[j][k],HIGH);
                    }else{
                        digitalWrite(module,rows[j][k],LOW);
                    }
                    if(j == (numberLedsToTrail-1)){
                        trailFinaly[k] = trails[j][k];
                    }
                }
            }


            delay(TIME);

            //Quando o botão 0 não é apertado e o último led da primeira coluna
            //está aceso, ocoore um erro do jogador, zerando seu combo
            //e realizado alterações no display
            if((trailFinaly[0]) && (!(buttonfinally[0]))){
                Check(FALSE);
            }
            //Quando o botão 1 não é apertado e o último led da segunda coluna
            //está aceso, ocoore um erro do jogador, zerando seu combo
            //e realizado alterações no display
            if((trailFinaly[1]) && (!(buttonfinally[1]))){
                Check(FALSE);
            }
            //Quando o botão 2 não é apertado e o último led da terceira coluna
            //está aceso, ocoore um erro do jogador, zerando seu combo
            //e realizado alterações no display
            if((trailFinaly[2]) && (!(buttonfinally[2]))){
                Check(FALSE);
            }

            PlayBuzzer(notBuzzer);
            //ConsoleUtilsPrintf("{%d,%d,%d}, \n",buttonfinally[0],buttonfinally[1],buttonfinally[2]);
            
            buttonfinally[0] = FALSE;
            buttonfinally[1] = FALSE;
            buttonfinally[2] = FALSE;
            notBuzzer = TRUE;
            //ConsoleUtilsPrintf("\n Linha - %d \n", i);
            if(pause){
                DisableInterrupt();
                ClearMutexButton();
                ShowPause();
                while(pause);
                CountDown();
                EnableInterrupt();
                SetMutexButton();
                playStatusLCD(combo, hit);
            }

        }else{
            return FALSE;
        }

    }
    return TRUE;
}/* -----  end of function writeBlinkLeds  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  Check
 *  Description:  Verifica se ocorreu um acerto ou um erro do jogador
 *    Parameter:  Valor booleano se acertou ou se errou
 * =====================================================================================
 */
void Check(bool value){
    if(value){
        if(scores < 9)  scores++;
        hit++;
        combo++;
        notBuzzer = TRUE;
        if(combo > bigCombo)bigCombo = combo;
    }else{
        if(scores > 0) scores--;
        error++;
        combo = 0;
        notBuzzer = FALSE;        
    }
    Semaphore(scores);
    playStatusLCD(combo, hit);

} /* -----  end of function Check  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  Semaphore
 *  Description:  Muda o estado do semaforo que controla o status do jogador durante 
 *                a partida
 *    Parameter:  Qual led deve está aceso no semaforo
 * =====================================================================================
 */

void Semaphore(int value){
    switch(value){
        case SemaphoreState1:
            digitalWrite(SOC_GPIO_3_REGS, LedsSemaphore[1], LOW);
            digitalWrite(SOC_GPIO_3_REGS, LedsSemaphore[0], HIGH);
            break;
        case SemaphoreState2:
            digitalWrite(SOC_GPIO_3_REGS, LedsSemaphore[0], LOW);
            digitalWrite(SOC_GPIO_3_REGS, LedsSemaphore[1], HIGH);
            digitalWrite(SOC_GPIO_3_REGS, LedsSemaphore[2], LOW);
            break;
        case SemaphoreState3:
            digitalWrite(SOC_GPIO_3_REGS, LedsSemaphore[1], LOW);
            digitalWrite(SOC_GPIO_3_REGS, LedsSemaphore[2], HIGH);
            digitalWrite(SOC_GPIO_3_REGS, LedsSemaphore[3], LOW);
            break;
        case SemaphoreState4:
            digitalWrite(SOC_GPIO_3_REGS, LedsSemaphore[2], LOW);
            digitalWrite(SOC_GPIO_3_REGS, LedsSemaphore[3], HIGH);
            digitalWrite(SOC_GPIO_3_REGS, LedsSemaphore[4], LOW);
            break;
        case SemaphoreState5:
            digitalWrite(SOC_GPIO_3_REGS, LedsSemaphore[3], LOW);
            digitalWrite(SOC_GPIO_3_REGS, LedsSemaphore[4], HIGH);
            digitalWrite(SOC_GPIO_3_REGS, LedsSemaphore[5], LOW);
            break;
        case SemaphoreState6:
            digitalWrite(SOC_GPIO_3_REGS, LedsSemaphore[4], LOW);
            digitalWrite(SOC_GPIO_3_REGS, LedsSemaphore[5], HIGH);
            digitalWrite(SOC_GPIO_1_REGS, LedsSemaphore[6], LOW);
            break;
        case SemaphoreState7:
            digitalWrite(SOC_GPIO_3_REGS, LedsSemaphore[5], LOW);
            digitalWrite(SOC_GPIO_1_REGS, LedsSemaphore[6], HIGH);
            digitalWrite(SOC_GPIO_1_REGS, LedsSemaphore[7], LOW);
            break;
        case SemaphoreState8:
            digitalWrite(SOC_GPIO_1_REGS, LedsSemaphore[6], LOW);
            digitalWrite(SOC_GPIO_1_REGS, LedsSemaphore[7], HIGH);
            digitalWrite(SOC_GPIO_1_REGS, LedsSemaphore[8], LOW);
            break;
        case SemaphoreState9:
            digitalWrite(SOC_GPIO_1_REGS, LedsSemaphore[7], LOW);
            digitalWrite(SOC_GPIO_1_REGS, LedsSemaphore[8], HIGH);
            break;
        default:
            digitalWrite(SOC_GPIO_1_REGS, LedsSemaphore[8], LOW);

    }
}/* -----  end of function Semaphore ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  GameOver
 *  Description:  Realiza as preparações quando o jogo se encerra
 *    Parameter:  Número de leds por trilha, número de trilhas
 * =====================================================================================
 */

void GameOver(int numberLedsToTrail, int numberTrail){
    DisableInterrupt();
    DisableInterruptPause();
    ClearMutexButton();
    for(int i = 0; i < 9; i++){
        if(i >= 6)
            digitalWrite(SOC_GPIO_1_REGS, LedsSemaphore[i], LOW);
        else
            digitalWrite(SOC_GPIO_3_REGS, LedsSemaphore[i], LOW);
    }

    for(int i = 0; i < numberLedsToTrail; i++){
        for(int j = 0; j < numberTrail; j++){
            digitalWrite(SOC_GPIO_1_REGS, rows[i][j], LOW);
        }
    }
}/* -----  end of function GameOver ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  NewGame
 *  Description:  Realiza as preparações para se iniciar um novo jogo
 * =====================================================================================
 */

void NewGame(){
    start = FALSE;
    scores = 5;
    error = 0;
    hit = 0;
    combo = 0;
    bigCombo = 0;
    trailFinaly[0] = 0;
    trailFinaly[1] = 0;
    trailFinaly[2] = 0;
    EnableInterrupt();
    for(int i = 0; i < 3; i++){
        if(!mutexButton[i])
            mutexButton[i] = TRUE;
    }
    lock = FALSE;
    pause = FALSE;
    EnableInterrupt7Seg();

}/* -----  end of function NewGame ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  GPIO1AIsr
 *  Description:  Função CallBack que será chamada quando o botão 0 for apertado
 * =====================================================================================
 */
 void GPIO1AIsr(void) {

    IntSystemDisable(SYS_INT_GPIOINT1A);
    if(mutexButton[0]){
        if(!start){
            start = TRUE;
        }

        if(lock){

            if(trailFinaly[0])
                Check(TRUE);
            else
                Check(FALSE);


            buttonfinally[0] = TRUE;

        }

    }else{
        mutexButton[0] = TRUE;
    }
    IntSystemEnable(SYS_INT_GPIOINT1A);

    ClearInterrupt(SOC_GPIO_1_REGS, GPIO_INT_LINE_1, buttons[0]);

}/* -----  end of function GPIO1AIsr ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  GPIO1BIsr
 *  Description:  Função CallBack que será chamada quando o botão 1 for apertado
 * =====================================================================================
 */

 void GPIO1BIsr(void) {

    IntSystemDisable(SYS_INT_GPIOINT1B);
    if(mutexButton[1]){

        if(!start){
            start = TRUE;
        }

        if(lock){
            if(trailFinaly[1])
                Check(TRUE);
            else
                Check(FALSE);
                /*  Clear wake interrupt    */
            buttonfinally[1] = TRUE;


        }


    }else{
        mutexButton[1] = TRUE;
    }
    IntSystemEnable(SYS_INT_GPIOINT1B);
    ClearInterrupt(SOC_GPIO_1_REGS, GPIO_INT_LINE_2, buttons[1]);

}/* -----  end of function GPIO1BIsr ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  GPIO2AIsr
 *  Description:  Função CallBack que será chamada quando o botão 2 for apertado
 * =====================================================================================
 */

 void GPIO2AIsr(void) {
    IntSystemDisable(SYS_INT_GPIOINT2A);
    if(mutexButton[2]){

        if(!start){
            start = TRUE;
        }

        if(lock){

            if(trailFinaly[2])
                Check(TRUE);
            else
                Check(FALSE);
            buttonfinally[2] = TRUE;

        }


    }else{
        mutexButton[2] = TRUE;
    }
    IntSystemEnable(SYS_INT_GPIOINT2A);
    ClearInterrupt(SOC_GPIO_2_REGS, GPIO_INT_LINE_1, buttons[2]);

}/* -----  end of function GPIO2AIsr ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  GPIO2BIsr
 *  Description:  Função CallBack que será chamada quando o botão pause for apertado
 * =====================================================================================
 */

void GPIO2BIsr(void){
    //Realiza a inversão da variável pause quando o botão de pause é apertado
    pause ^= 1;
    //Limpa a interrupção
    ClearInterrupt(SOC_GPIO_2_REGS, GPIO_INT_LINE_2, GPIO2_BUTTONPAUSE);
}/* -----  end of function GPIO2BIsr ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  GPIO0AIsr
 *  Description:  Função CallBack que será chamada quando o botão de incremento for apertado
 * =====================================================================================
 */

void GPIO0AIsr(void){
    //Realiza o incremento da variavel numberMusic que representa a música que será escolhida
    if(numberMusic<5)
        numberMusic++;
    diplay7Segments(SOC_GPIO_2_REGS, numberMusic);
    SetMusicLCD(numberMusic);
    ClearInterrupt(SOC_GPIO_0_REGS, GPIO_INT_LINE_1, GPIO0_BUTTONPLUS);
}/* -----  end of function GPIO0AIsr ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  GPIO0BIsr
 *  Description:  Função CallBack que será chamada quando o botão de decremento for apertado
 * =====================================================================================
 */

void GPIO0BIsr(void){
    //Realiza o decremento da variavel numberMusic que representa a música que será escolhida
    if(numberMusic>1)
        numberMusic--;
    diplay7Segments(SOC_GPIO_2_REGS, numberMusic);
    SetMusicLCD(numberMusic);
    ClearInterrupt(SOC_GPIO_0_REGS, GPIO_INT_LINE_2, GPIO0_BUTTONLESS);
}/* -----  end of function GPIO0BIsr ----- */


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ClearMutexButton
 *  Description:  Limpa o vetor de mutex dos botões do jogo
 * =====================================================================================
 */

void ClearMutexButton(void){
    for(int i = 0; i < 3; i++){
        mutexButton[i] = FALSE;
    }
}/* -----  end of function ClearMutexButton ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  SetMutexButton
 *  Description:  Seta como TRUE o vetor de mutex dos botões do jogo
 * =====================================================================================
 */

void SetMutexButton(void){
    for (int i = 0; i < 3; ++i)
    {
        mutexButton[i] = TRUE;
    }
}/* -----  end of function SetMutexButton ----- */


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  PlayBuzzer
 *  Description:  Envia um sinal ao buzzer caso tenha ocorrido algum erro do jogador
 *    Parameter:  Variavél booleana que indica se deve ou não tocar o buzzer
 * =====================================================================================
 */

void PlayBuzzer(bool action){
    
    if(action){
        delay(50);
    }else{
        digitalWrite(SOC_GPIO_2_REGS, BUZZER, HIGH);
        delay(50);
        digitalWrite(SOC_GPIO_2_REGS, BUZZER, LOW);     
    }               
        
}/* -----  end of function PlayBuzzer ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  Playlist
 *  Description:  Imprime a playlist do jogo
 * =====================================================================================
 */

void Playlist(void){
   
        ConsoleUtilsPrintf("********************************************************************************************************************************************\n");  
        ConsoleUtilsPrintf("*                                 _____   _           ___   _    __  _       _   _____   _____                                             *\n");
        ConsoleUtilsPrintf("*                                |  _  | | |         /   | | |  / / | |     | | /  ___/ |_   _|                                            *\n");                          
        ConsoleUtilsPrintf("*                                | |_| | | |        / /| |  | || /  | |     | | | |___    | |                                              *\n");
        ConsoleUtilsPrintf("*                                |  ___/ | |       / / | |   |  /   | |     | | |___  |   | |                                              *\n"); 
        ConsoleUtilsPrintf("*                                | |     | |___   / /  | |   / /    | |___  | |  ___| |   | |                                              *\n");
        ConsoleUtilsPrintf("*                                |_|     |_____| /_/   |_|  /_/     |_____| |_| /_____/   |_|                                              *\n");
        ConsoleUtilsPrintf("********************************************************************************************************************************************\n");  
        ConsoleUtilsPrintf("*  ___        _   _  _____  _____   _____  _____  _____     _____  _____     _____  _   _  _____     _____  _      ___  ___  _____         *\n");       
        ConsoleUtilsPrintf("* |_  |      | | | || ____||  _  | |  _  || ____|/  ___/   |  _  ||  ___|   |  _  || | | ||  _  |   |_   _|| |    /   |/   || ____|        *\n");
        ConsoleUtilsPrintf("*   | |  __  | |_| || |__  | |_| | | | | || |__  | |___    | | | || |__     | | | || | | || |_| |     | |  | |   / /|   /| || |__          *\n");
        ConsoleUtilsPrintf("*   | | |__| |  _  ||  __| |  _  / | | | ||  __| |___  |   | | | ||  __|    | | | || | | ||  _  /     | |  | |  / / |__/ | ||  __|         *\n");
        ConsoleUtilsPrintf("*   | |      | | | || |___ | | | | | |_| || |___  ___| |   | |_| || |       | |_| || |_| || | | |     | |  | | / /       | || |___         *\n");
        ConsoleUtilsPrintf("*   |_|      |_| |_||_____||_| |_| |_____||_____|/_____/   |_____||_|       |_____||_____||_| |_|     |_|  |_|/_/        |_||_____|        *\n");
        ConsoleUtilsPrintf("*                                                                                                                                          *\n");
        ConsoleUtilsPrintf("********************************************************************************************************************************************\n"); 
        ConsoleUtilsPrintf("*  _____        _   _  _____  _____  _____  _         _____      ___  _      _  _____  _____  _____   __   _  _      ___                   *\n");
        ConsoleUtilsPrintf("* /___  |      | | | ||  _  ||_   _|| ____|| |       |  ___|    /   || |    | ||  ___||  _  ||  _  | |  | | || |    /   |                  *\n");
        ConsoleUtilsPrintf("*  ___| |  __  | |_| || | | |  | |  | |__  | |       | |       / /| || |    | || |__  | | | || |_| | |   || || |   / /| |                  *\n");
        ConsoleUtilsPrintf("* /  ___| |__| |  _  || | | |  | |  |  __| | |       | |      / / | || |    | ||  __| | | | ||  _  / | ||   || |  / / | |                  *\n");
        ConsoleUtilsPrintf("* | |___       | | | || |_| |  | |  | |___ | |___    | |___  / /  | || |___ | || |    | |_| || | | | | | |  || | / /  | |                  *\n");
        ConsoleUtilsPrintf("* |_____|      |_| |_||_____|  |_|  |_____||_____|   |_____|/_/   |_||_____||_||_|    |_____||_| |_| |_|  |_||_|/_/   |_|                  *\n");
        ConsoleUtilsPrintf("*                                                                                                                                          *\n");
        ConsoleUtilsPrintf("********************************************************************************************************************************************\n"); 
        ConsoleUtilsPrintf("*  _____        _____  _____  _____      ___  _    _  _____  _   _  _____  _____  _   _  _____  _   _                                      *\n");
        ConsoleUtilsPrintf("* |___  |      |  _  ||  _  || ____|    /   || |  | ||_   _|| | | ||  _  ||  _  || | | |/  ___|| | | |                                     *\n");
        ConsoleUtilsPrintf("*    _| |  __  | |_| || |_| || |__     / /| || | | |   | |  | |_| || |_| || | | || | | || |    | |_| |                                     *\n");
        ConsoleUtilsPrintf("*   |_  { |__| |  _  {|  _  /|  __|   / / | || || |    | |  |  _  ||  _  /| | | || | | || |  _ |  _  |                                     *\n");
        ConsoleUtilsPrintf("*  ___| |      | |_| || | | || |___  / /  | || | | |   | |  | | | || | | || |_| || |_| || |_| || | | |                                     *\n");
        ConsoleUtilsPrintf("* |_____/      |_____/|_| |_||_____|/_/   |_||_|  |_|  |_|  |_| |_||_| |_||_____||_____||_____/|_| |_|                                     *\n");
        ConsoleUtilsPrintf("*                                                                                                                                          *\n");
        ConsoleUtilsPrintf("********************************************************************************************************************************************\n"); 
        ConsoleUtilsPrintf("*  _   _         _____  _          __ _____  _____  _____     _____  _   _  _  _      _____      _____   _    ___  ___  _  __   _  _____   *\n");
        ConsoleUtilsPrintf("* | | | |       /  ___/| |        / /| ____|| ____||_   _|   |  ___|| | | || || |    |  _  |    |  _  | |_|  /   |/   || ||  | | || ____|  *\n");
        ConsoleUtilsPrintf("* | |_| |   __  | |___ | |  __   / / | |__  | |__    | |     | |    | |_| || || |    | | |  |   | | | |     / /|   /| || ||   || || |__    *\n");
        ConsoleUtilsPrintf("* |___  |  |__| |___  || | /  | / /  |  __| |  __|   | |     | |    |  _  || || |    | | |  |   | | | |    / / |__/ | || || ||   ||  __|   *\n");
        ConsoleUtilsPrintf("*     | |        ___| || |/   |/ /   | |___ | |___   | |     | |___ | | | || || |___ | |_|  |   | |_| |   / /       | || || | |  || |___   *\n");
        ConsoleUtilsPrintf("*     |_|       /_____/|___/|___/    |_____||_____|  |_|     |_____||_| |_||_||_____||_____|    |_____|  /_/        |_||_||_|  |_||_____|  *\n");
        ConsoleUtilsPrintf("*                                                                                                                                          *\n");
        ConsoleUtilsPrintf("********************************************************************************************************************************************\n"); 
        ConsoleUtilsPrintf("*  _____        _     __   _  _____  _____  _____       _    __ _____  _   _  _____     _____  _      _____  _____  _   _  _____  _____    *\n");
        ConsoleUtilsPrintf("* |  ___|      | |   |  | | || ____|| ____||  _  |     | |  / /|  _  || | | ||  _  |   |  ___|| |    |  _  ||_   _|| | | || ____|/  ___/   *\n");
        ConsoleUtilsPrintf("* | |___   __  | |   |   || || |__  | |__  | | |  |     | || / | | | || | | || |_| |   | |    | |    | | | |  | |  | |_| || |__  | |___    *\n");
        ConsoleUtilsPrintf("* |___  | |__| | |   | ||   ||  __| |  __| | | |  |      |  /  | | | || | | ||  _  /   | |    | |    | | | |  | |  |  _  ||  __| |___  |   *\n");
        ConsoleUtilsPrintf("*  ___| |      | |   | | |  || |___ | |___ | |_|  |      / /   | |_| || |_| || | | |   | |___ | |___ | |_| |  | |  | | | || |___  ___| |   *\n");
        ConsoleUtilsPrintf("* |_____|      |_|   |_|  |_||_____||_____||_____|      /_/    |_____||_____||_| |_|   |_____||_____||_____|  |_|  |_| |_||_____|/_____/   *\n"); 
        ConsoleUtilsPrintf("*                                                                                                                                          *\n");         
        ConsoleUtilsPrintf("********************************************************************************************************************************************\n");

   



}/* -----  end of function Playlist ----- */    

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  Background
 *  Description:  Imprime o background do jogo
 * =====================================================================================
 */

void Background(void){

    ConsoleUtilsPrintf("````````````````1111111`````````````\n");
    ConsoleUtilsPrintf("````````````````1`11`11`````````````\n");
    ConsoleUtilsPrintf("````````````````111111``````````````\n");
    ConsoleUtilsPrintf("```````````````1111`1```````````````\n");
    ConsoleUtilsPrintf("```````````````111``11``````````````\n");
    ConsoleUtilsPrintf("``````````````11111111``````````````\n");
    ConsoleUtilsPrintf("``````````````111111111`````````````\n");
    ConsoleUtilsPrintf("`````````````1111`1111``````````````\n");
    ConsoleUtilsPrintf("```````````````1`1`11```````````````\n");
    ConsoleUtilsPrintf("````````````````1111````````````````\n");
    ConsoleUtilsPrintf("````````````````1111````````````````\n");
    ConsoleUtilsPrintf("````````````````1111````````````````\n");
    ConsoleUtilsPrintf("````````````````1111````````````````\n");
    ConsoleUtilsPrintf("````````````````1111````````````````\n");
    ConsoleUtilsPrintf("````````````````1111````````````````\n");
    ConsoleUtilsPrintf("````````````````1111````````````````\n");
    ConsoleUtilsPrintf("````````````````1111````````````````                /  ___| | | | | | | |_   _|     /   | |  _  \\       | |     | ____| |  _  \\  \n");
    ConsoleUtilsPrintf("````````````````1111````````````````                | |     | | | | | |   | |      / /| | | |_| |       | |     | |__   | | | | \n");
    ConsoleUtilsPrintf("````````````````1111````````````````                | |  _  | | | | | |   | |     / / | | |  _  /       | |     |  __|  | | | | \n");
    ConsoleUtilsPrintf("```````````````11111````````````````                | |_| | | |_| | | |   | |    / /  | | | | \\ \\       | |___  | |___  | |_| | \n");
    ConsoleUtilsPrintf("```````````````11111````````````````                \\_____/ \\_____/ |_|   |_|   /_/   |_| |_|  \\_\\      |_____| |_____| |_____/ \n");
    ConsoleUtilsPrintf("```````````````111111```````````````\n");
    ConsoleUtilsPrintf("```````````````111111```````````````\n");
    ConsoleUtilsPrintf("``````111``````111111```````````````\n");
    ConsoleUtilsPrintf("`````1111``````111111```````````````\n");
    ConsoleUtilsPrintf("`````1111``````111111```````````````\n");
    ConsoleUtilsPrintf("`````11111`````111111```````````````\n");
    ConsoleUtilsPrintf("`````1111111``1111111``````1111`````\n");
    ConsoleUtilsPrintf("`````1111111111111111``````1`11`````\n");
    ConsoleUtilsPrintf("``````1111111``111111````111`11`````\n");
    ConsoleUtilsPrintf("``````1111111``11111111111```11`````\n");
    ConsoleUtilsPrintf("```````1111111```````````````1``````\n");
    ConsoleUtilsPrintf("```````1111111`1111111`1````11``````\n");
    ConsoleUtilsPrintf("```````111111``1```````````11```````\n");
    ConsoleUtilsPrintf("```````111111``1```````1```11```````\n");
    ConsoleUtilsPrintf("```````11111``11111111```1`11```````\n");
    ConsoleUtilsPrintf("``````11111```1111````1``1``1```````\n");
    ConsoleUtilsPrintf("`````111111```````````1``11`11``````\n");
    ConsoleUtilsPrintf("````1111111``111111111`````1`11`````\n");
    ConsoleUtilsPrintf("````1111111``````````````1````11````\n");
    ConsoleUtilsPrintf("```111111111``11111111``````1``1````\n");
    ConsoleUtilsPrintf("```1111111111111`1`1``11111````11```\n");
    ConsoleUtilsPrintf("```11111111111111111111111111``11```\n");
    ConsoleUtilsPrintf("```111111111111111111111``1111111```\n");
    ConsoleUtilsPrintf("```1111111111111111111111111`1111```\n");
    ConsoleUtilsPrintf("````111111111111111111111111`111````\n");
    ConsoleUtilsPrintf("`````11111111111111111111111111`````\n");
    ConsoleUtilsPrintf("```````11111111111111111111111``````\n");

}/* -----  end of function Background ----- */
