#ifndef _FUNCTIONS_LCD_
#define _FUNCTIONS_LCD_

void start_lcd(int module);
void write_lcd(int module, char string[]);
void lcd_comand(int module, int comando);
void ShowLCDEnd(bool value, unsigned int sizeMusic, unsigned int points, unsigned int errors, unsigned int max);
void startGame(bool *status);
void limparLCD(void);
void playStatusLCD(int combo, int points);
void write_number_lcd(unsigned int module, unsigned int number);
void CountDown(void);
void ShowPause(void);
void SetMusicLCD(int number);

#endif //_FUNCTIONS_LCD_