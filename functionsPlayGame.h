#ifndef _FUNCTIONS_PLAYGAME_
#define _FUNCTIONS_PLAYGAME_

#include "functionsMatrixSongs.h"

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
bool writeBlinkLeds(int module, int numberLedsToTrail, int numberTrail, MUSIC gameMusic);
void Check(bool value);
void Semaphore(int value);
void GameOver(int numberLedsToTrail, int numberTrail);
void NewGame(void);
void ClearMutexButton(void);
void SetMutexButton(void);
void SetMusic();
void GameBegin(void);
void PlayBuzzer(bool action);
void Playlist(void);
void Background(void);

/*********    FUNCTIONS ISR INTERRUPTS  **********/
void GPIO1AIsr(void);
void GPIO1BIsr(void);
void GPIO2AIsr(void);
void GPIO2BIsr(void);
void GPIO0AIsr(void);
void GPIO0BIsr(void);





#endif  //_FUNCTIONS_PLAYGAME_