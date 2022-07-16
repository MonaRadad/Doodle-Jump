/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f3xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "LiquidCrystal.h"
#include "string.h"
#include "time.h"
#include <time.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */


extern char * main_field[4][20];
extern char * field[4][20];
char * randfield[4][10] = {NULL};

int doodle_col=18;
int doodle_row=2;
int x=0;

int shoot=0;
int dart_col;
int dart_row;
int change=0;

char player[20]="doodler";

//char * mem[1]={"N"};

int temp=0;
char * side[1]={"U"};
int started=0;
int lost=0;
int monster_lost =0;
int broken_stair =0;
int y1,y2,y3,y4;

int move=0;


int offset=0;
int score=0;
int melody_start=1;
int volval=0;
extern UART_HandleTypeDef huart2;


extern RTC_HandleTypeDef hrtc;
RTC_TimeTypeDef mytime;
RTC_DateTypeDef  myDate;

char str[20];
char str2[20];
char str3[20];


extern void PWM_Start();
extern void PWM_Stop();

extern void PWM_Change_Tone(uint16_t pwm_freq, uint16_t volume);
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/*void melody(){
	// change this to make the song slower or faster
	int tempo = 144;

	// change this to whichever pin you want to use
	int buzzer = 11;

	// notes of the moledy followed by the duration.
	// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
	// !!negative numbers are used to represent dotted notes,
	// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
	const PROGMEM int melody[] = {


	  // Bloody Tears, from Castlevania II
	  // Arranged by Bobby Lee. THe flute part was used
	  // https://musescore.com/user/263171/scores/883296

	  //B-flat major Bb Eb
	  REST, 4, NOTE_G5, 4,
	  NOTE_A5, 4, NOTE_AS5, 4,
	  NOTE_A5, 4, NOTE_F5, 4,
	  NOTE_A5, 4, NOTE_G5, 4,
	  REST, 4, NOTE_G5, 4,
	  NOTE_A5, 4, NOTE_AS5, 4,
	  NOTE_C6, 4, NOTE_AS5, 4,

	  NOTE_A5, 4, NOTE_G5, 4, //8
	  REST, 4, NOTE_G5, 4,
	  NOTE_A5, 4, NOTE_AS5, 4,
	  NOTE_A5, 4, NOTE_F5, 4,
	  NOTE_A5, 4, NOTE_G5, 4,
	  NOTE_D6, 4, REST, 8, NOTE_C6, 8,
	  REST, 4, NOTE_AS5, 4,

	  NOTE_A5, 4, NOTE_AS5, 8, NOTE_C6, 8, //15
	  NOTE_F6, 8, REST, 8, REST, 4,
	  NOTE_G5, 16, NOTE_D5, 16, NOTE_D6, 16, NOTE_D5, 16, NOTE_C6, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16,
	  NOTE_A5, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16, NOTE_A5, 16, NOTE_D5, 16, NOTE_G5, 16, NOTE_D5, 16,
	  NOTE_A5, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16, NOTE_C6, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16,

	  NOTE_A5, 16, NOTE_D5, 16, NOTE_F5, 16, NOTE_D5, 16, NOTE_A5, 16, NOTE_D5, 16, NOTE_G5, 16, NOTE_D5, 16, //20
	  NOTE_G5, 16, NOTE_D5, 16, NOTE_D6, 16, NOTE_D5, 16, NOTE_C6, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16,
	  NOTE_A5, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16, NOTE_A5, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16,
	  NOTE_A5, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16, NOTE_C6, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16,
	  NOTE_A5, 16, NOTE_D5, 16, NOTE_F5, 16, NOTE_D5, 16, NOTE_A5, 16, NOTE_D5, 16, NOTE_G5, 16, NOTE_D5, 16,

	  NOTE_G5, 16, NOTE_D5, 16, NOTE_D6, 16, NOTE_D5, 16, NOTE_C6, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16, //25
	  NOTE_A5, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16, NOTE_A5, 16, NOTE_D5, 16, NOTE_G5, 16, NOTE_D5, 16,
	  NOTE_A5, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16, NOTE_C6, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16,
	  NOTE_A5, 16, NOTE_D5, 16, NOTE_F5, 16, NOTE_D5, 16, NOTE_A5, 16, NOTE_D5, 16, NOTE_G5, 16, NOTE_D5, 16,
	  NOTE_AS5, 16, NOTE_D5, 16, NOTE_D6, 16, NOTE_D5, 16, NOTE_C6, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16,

	  NOTE_A5, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16, NOTE_A5, 16, NOTE_D5, 16, NOTE_G5, 16, NOTE_D5, 16,
	  NOTE_A5, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16, NOTE_C6, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16,
	  NOTE_A5, 16, NOTE_D5, 16, NOTE_F5, 16, NOTE_D5, 16, NOTE_A5, 16, NOTE_D5, 16, NOTE_G5, 16, NOTE_D5, 16,
	  NOTE_C6, 16, NOTE_C6, 16, NOTE_F6, 16, NOTE_D6, 8, REST, 16, REST, 8,
	  REST, 4, NOTE_C6, 16, NOTE_AS5, 16,

	  NOTE_C6, -8,  NOTE_F6, -8, NOTE_D6, -4, //35
	  NOTE_C6, 8, NOTE_AS5, 8,
	  NOTE_C6, 8, NOTE_F6, 16, NOTE_D6, 8, REST, 16, REST, 8,
	  REST, 4, NOTE_C6, 8, NOTE_D6, 8,
	  NOTE_DS6, -8, NOTE_F6, -8,

	  NOTE_D6, -8, REST, 16, NOTE_DS6, 8, REST, 8, //40
	  NOTE_C6, 8, NOTE_F6, 16, NOTE_D6, 8, REST, 16, REST, 8,
	  REST, 4, NOTE_C6, 8, NOTE_AS5, 8,
	  NOTE_C6, -8,  NOTE_F6, -8, NOTE_D6, -4,
	  NOTE_C6, 8, NOTE_AS5, 8,

	  NOTE_C6, 8, NOTE_F6, 16, NOTE_D6, 8, REST, 16, REST, 8, //45
	  REST, 4, NOTE_C6, 8, NOTE_D6, 8,
	  NOTE_DS6, -8, NOTE_F6, -8,
	  NOTE_D5, 8, NOTE_FS5, 8, NOTE_F5, 8, NOTE_A5, 8,
	  NOTE_A5, -8, NOTE_G5, -4,

	  NOTE_A5, -8, NOTE_G5, -4, //50
	  NOTE_A5, -8, NOTE_G5, -4,
	  NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
	  NOTE_A5, -8, NOTE_G5, -8, NOTE_D5, 8,
	  NOTE_A5, -8, NOTE_G5, -8, NOTE_D5, 8,
	  NOTE_A5, -8, NOTE_G5, -8, NOTE_D5, 8,

	  NOTE_AS5, 4, NOTE_C6, 4, NOTE_A5, 4, NOTE_AS5, 4,
	  NOTE_G5,16, NOTE_D5,16, NOTE_D6,16, NOTE_D5,16, NOTE_C6,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16,//56 //r
	  NOTE_A5,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16, NOTE_A5,16, NOTE_D5,16, NOTE_G5,16, NOTE_D5,16,
	  NOTE_A5,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16, NOTE_C6,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16,
	  NOTE_A5,16, NOTE_D5,16, NOTE_F5,16, NOTE_D5,16, NOTE_A5,16, NOTE_D5,16, NOTE_G5,16, NOTE_D5,16,

	  NOTE_G5,16, NOTE_D5,16, NOTE_D6,16, NOTE_D5,16, NOTE_C6,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16,//61
	  NOTE_A5,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16, NOTE_A5,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16,
	  NOTE_A5,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16, NOTE_C6,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16,
	  NOTE_A5,16, NOTE_D5,16, NOTE_F5,16, NOTE_D5,16, NOTE_A5,16, NOTE_D5,16, NOTE_G5,16, NOTE_D5,16,
	  NOTE_G5,16, NOTE_D5,16, NOTE_D6,16, NOTE_D5,16, NOTE_C6,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16,

	  NOTE_A5,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16, NOTE_A5,16, NOTE_D5,16, NOTE_G5,16, NOTE_D5,16,//66
	  NOTE_A5,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16, NOTE_C6,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16,
	  NOTE_A5,16, NOTE_D5,16, NOTE_F5,16, NOTE_D5,16, NOTE_A5,16, NOTE_D5,16, NOTE_G5,16, NOTE_D5,16,
	  NOTE_AS5,16, NOTE_D5,16, NOTE_D6,16, NOTE_D5,16, NOTE_C6,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16,
	  NOTE_A5,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16, NOTE_A5,16, NOTE_D5,16, NOTE_G5,16, NOTE_D5,16,

	  NOTE_A5,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16, NOTE_C6,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16,//71 //
	  NOTE_A5, 16, NOTE_D5, 16, NOTE_F5, 16, NOTE_D5, 16, NOTE_A5, 8, NOTE_G5, 32, NOTE_A5, 32, NOTE_AS5, 32, NOTE_C6, 32,
	  NOTE_D6, 16, NOTE_G5, 16, NOTE_AS5, 16, NOTE_G5, 16, NOTE_C6, 16, NOTE_G5, 16, NOTE_D6, 16, NOTE_G5, 16,
	  NOTE_C6, 16, NOTE_G5, 16, NOTE_A5, 16, NOTE_G5, 16, NOTE_F6, 16, NOTE_G5, 16, NOTE_D6, 16, NOTE_DS5, 16,
	  NOTE_D6, 4, REST, 4,

	  NOTE_C5, 8, REST, 8, NOTE_A4, -16, NOTE_AS4, -16, NOTE_C5, 16, //76
	  NOTE_D6, 16, NOTE_G4, 16, NOTE_AS4, 16, NOTE_G4, 16, NOTE_C5, 16, NOTE_G4, 16, NOTE_D6, 16, NOTE_G4, 16,
	  NOTE_C6, 16, NOTE_F4, 16, NOTE_A4, 16, NOTE_F4, 16, NOTE_F5, 16, NOTE_F4, 16, NOTE_D6, 16, NOTE_DS4, 16,
	  NOTE_D6, 16, REST, 8, NOTE_E4, 16, NOTE_F4, 16,

	  //change of key B Major A# C# D# F# G#
	  NOTE_GS4, 8, REST, 8, NOTE_AS4, 8, REST, 8,

	  NOTE_DS5, 16, NOTE_GS4, 16, NOTE_B4, 16, NOTE_GS4, 16, NOTE_CS5, 16, NOTE_GS4, 16, NOTE_DS5, 16, NOTE_GS4, 16, //81
	  NOTE_CS5, 16, NOTE_FS4, 16, NOTE_AS4, 16, NOTE_FS4, 16, NOTE_FS5, 16, NOTE_FS4, 16, NOTE_DS5, 16, NOTE_E5, 16,
	  NOTE_D5, 4, REST, 4,
	  NOTE_CS5, 8, REST, 8, NOTE_AS4, -16,  NOTE_B4, -16, NOTE_CS5, 16,
	  NOTE_DS5, 16, NOTE_GS4, 16, NOTE_B4, 16, NOTE_GS4, 16, NOTE_CS5, 16, NOTE_GS4, 16, NOTE_DS5, 16, NOTE_GS4, 16,

	  NOTE_CS5, 16, NOTE_FS4, 16, NOTE_AS4, 16, NOTE_FS4, 16, NOTE_FS5, 16, NOTE_FS4, 16, NOTE_DS5, 16, NOTE_E5, 16,
	  NOTE_DS5, 4, REST, 8, NOTE_DS5, 16,  NOTE_E5, 16,
	  NOTE_FS5, 16, NOTE_CS5, 16, NOTE_E5, 16, NOTE_CS4, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_G5, 16, NOTE_AS5, 16,
	  NOTE_GS5, 16, NOTE_DS5, 16, NOTE_DS6, 16, NOTE_DS5, 16, NOTE_CS6, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16,

	  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16, NOTE_AS5, 16, NOTE_DS5, 16, NOTE_GS5, 16, NOTE_DS5, 16, //90
	  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16, NOTE_CS6, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16,
	  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_FS5, 16, NOTE_DS5, 16, NOTE_AS5, 16, NOTE_DS5, 16, NOTE_GS5, 16, NOTE_DS5, 16,
	  NOTE_GS5, 16, NOTE_DS5, 16, NOTE_DS6, 16, NOTE_DS5, 16, NOTE_CS6, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16,

	  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16, NOTE_AS5, 16, NOTE_DS5, 16, NOTE_GS5, 16, NOTE_DS5, 16,//94
	  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16, NOTE_CS6, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16,
	  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_FS5, 16, NOTE_DS5, 16, NOTE_AS5, 16, NOTE_DS5, 16, NOTE_GS5, 16, NOTE_DS5, 16,
	  NOTE_GS5, 16, NOTE_DS5, 16, NOTE_DS6, 16, NOTE_DS5, 16, NOTE_CS6, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16,

	  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16, NOTE_AS5, 16, NOTE_DS5, 16, NOTE_GS5, 16, NOTE_DS5, 16,//98
	  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16, NOTE_CS6, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16,
	  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_FS5, 16, NOTE_DS5, 16, NOTE_AS5, 16, NOTE_DS5, 16, NOTE_GS5, 16, NOTE_DS5, 16,
	  NOTE_GS5, 16, NOTE_DS5, 16, NOTE_DS6, 16, NOTE_DS5, 16, NOTE_CS6, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16,

	  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16, NOTE_AS5, 16, NOTE_DS5, 16, NOTE_GS5, 16, NOTE_DS5, 16,//102
	  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16, NOTE_CS6, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16,
	  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_FS5, 16, NOTE_DS5, 16, NOTE_AS5, 16, NOTE_DS5, 16, NOTE_GS5, 16, NOTE_DS5, 16,

	  NOTE_CS6, 8, NOTE_FS6, 16, NOTE_DS6, 8, REST,16, REST,8, //107
	  REST,4, NOTE_CS6, 8, NOTE_B5, 8,
	  NOTE_CS6,-8, NOTE_FS6, -8, NOTE_DS6, -4,
	  NOTE_CS6, 8, NOTE_B5, 8,
	  NOTE_CS6, 8, NOTE_FS6, 16, NOTE_DS6, 8, REST,16, REST,8,
	  REST,4, NOTE_CS6, 8, NOTE_B5, 8,
	  NOTE_E6, -8, NOTE_F6, -8,

	  NOTE_DS6,-8, REST,16, NOTE_E6,8, REST,16, REST,16, //112
	  NOTE_CS6, 8, NOTE_FS6, 16, NOTE_DS6, 8, REST,16, REST,8,
	  REST,4, NOTE_CS6, 8, NOTE_B5, 8,
	  NOTE_CS6,-8, NOTE_FS6, -8, NOTE_DS6, -4,
	  NOTE_CS6, 8, NOTE_B5, 8,

	  NOTE_CS6, 8, NOTE_FS6, 16, NOTE_DS6, 8, REST,16, REST,8, //117
	  REST,4, NOTE_CS5, 8, NOTE_DS5, 8,
	  NOTE_E5, -8, NOTE_F5, -8,
	  NOTE_DS5, 8, NOTE_G5, 8, NOTE_GS5, 8, NOTE_AS5, 8,
	  NOTE_AS5, -8, NOTE_GS5, -8,

	  NOTE_AS5, -8, NOTE_GS5, -8,//122
	  NOTE_AS5, -8, NOTE_GS5, -8,
	  NOTE_B6, 8, NOTE_AS5, 8, NOTE_GS5, 8, NOTE_FS5, 8,
	  NOTE_AS5,-8, NOTE_GS6, -8, NOTE_DS5, 8,
	  NOTE_AS5,-8, NOTE_GS6, -8, NOTE_DS5, 8,
	  NOTE_AS5,-8, NOTE_GS6, -8, NOTE_DS5, 8,

	  NOTE_B5,8, NOTE_CS6, 8, NOTE_AS5, 8, NOTE_B5, 8,//128
	  NOTE_GS5,8, REST,8, REST, 16

	};

	// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
	// there are two values per note (pitch and duration), so for each note there are four bytes
	int notes = sizeof(melody) / sizeof(melody[0]) / 2;

	// this calculates the duration of a whole note in ms (60s/tempo)*4 beats
	int wholenote = (60000 * 4) / tempo;

	int divider = 0, noteDuration = 0;

	void setup() {
	  // iterate over the notes of the melody.
	  // Remember, the array is twice the number of notes (notes + durations)
	  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

	    // calculates the duration of each note
	    divider = pgm_read_word_near(melody+thisNote + 1);
	    if (divider > 0) {
	      // regular note, just proceed
	      noteDuration = (wholenote) / divider;
	    } else if (divider < 0) {
	      // dotted notes are represented with negative durations!!
	      noteDuration = (wholenote) / abs(divider);
	      noteDuration *= 1.5; // increases the duration in half for dotted notes
	    }

	    // we only play the note for 90% of the duration, leaving 10% as a pause
	    tone(buzzer, pgm_read_word_near(melody+thisNote ), noteDuration * 0.9);

	    // Wait for the specief duration before playing the next note.
	    delay(noteDuration);

	    // stop the waveform generation before the next note.
	    noTone(buzzer);
	  }
	}

	void loop() {
	  // no need to repeat the melody.
	}
}
*/
void randlevels(int volumevalue){
	volval = volumevalue;
	int rr, cr;
	int sr = rand()%3+1;
	int br = rand()%2+1;
	int mr = rand()%1+1;
	int hr = rand()%1+1;
	int fr = rand()%2+1;
	for(int col=0; col <20; col++){
	  for(int row=0; row<4; row++){
		  main_field[row][col]="N";
	  }
	}
	if(volumevalue==0){
		for(int i=1; i<=sr+10; i++){ //stair
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "S";
			setCursor(cr-1, rr-1);
			write(2);
		}
		for(int i=1; i<=br+3; i++){ //brokenstair
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "B";
			setCursor(cr-1, rr-1);
			write(3);
		}
		for(int i=1; i<=mr+1; i++){ //monster
			cr = rand()%16 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "M";
			setCursor(cr-1, rr-1);
			write(4);
		}
		for(int i=1; i<=hr+1; i++){ //hole
			cr = rand()%16 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "H";
			setCursor(cr-1, rr-1);
			write(5);
		}
		for(int i=1; i<=fr+1; i++){ //spring fanar
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "F";
			setCursor(cr-1, rr-1);
			write(6);
		}
	} else if(volumevalue==1){
		for(int i=1; i<=sr+8; i++){ //stair
					cr = rand()%20 + 1;
					rr = rand()%4 + 1;
					main_field[rr-1][cr-1] = "S";
					setCursor(cr-1, rr-1);
					write(2);
		}
		for(int i=1; i<=br+4; i++){ //brokenstair
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "B";
			setCursor(cr-1, rr-1);
			write(3);
		}
		for(int i=1; i<=mr+1; i++){ //monster
			cr = rand()%16 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "M";
			setCursor(cr-1, rr-1);
			write(4);
		}
		for(int i=1; i<=hr+1; i++){ //hole
			cr = rand()%16 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "H";
			setCursor(cr-1, rr-1);
			write(5);
		}
		for(int i=1; i<=fr+2; i++){ //spring fanar
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "F";
			setCursor(cr-1, rr-1);
			write(6);
		}
	} else if(volumevalue==2){
		for(int i=1; i<=sr+8; i++){ //stair
					cr = rand()%20 + 1;
					rr = rand()%4 + 1;
					main_field[rr-1][cr-1] = "S";
					setCursor(cr-1, rr-1);
					write(2);
		}
		for(int i=1; i<=br+4; i++){ //brokenstair
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "B";
			setCursor(cr-1, rr-1);
			write(3);
		}
		for(int i=1; i<=mr+2; i++){ //monster
			cr = rand()%16 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "M";
			setCursor(cr-1, rr-1);
			write(4);
		}
		for(int i=1; i<=hr+1; i++){ //hole
			cr = rand()%16 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "H";
			setCursor(cr-1, rr-1);
			write(5);
		}
		for(int i=1; i<=fr+2; i++){ //spring fanar
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "F";
			setCursor(cr-1, rr-1);
			write(6);
		}
	} else if(volumevalue==3){
		for(int i=1; i<=sr+7; i++){ //stair
					cr = rand()%20 + 1;
					rr = rand()%4 + 1;
					main_field[rr-1][cr-1] = "S";
					setCursor(cr-1, rr-1);
					write(2);
		}
		for(int i=1; i<=br+4; i++){ //brokenstair
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "B";
			setCursor(cr-1, rr-1);
			write(3);
		}
		for(int i=1; i<=mr+2; i++){ //monster
			cr = rand()%16 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "M";
			setCursor(cr-1, rr-1);
			write(4);
		}
		for(int i=1; i<=hr+1; i++){ //hole
			cr = rand()%16 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "H";
			setCursor(cr-1, rr-1);
			write(5);
		}
		for(int i=1; i<=fr+2; i++){ //spring fanar
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "F";
			setCursor(cr-1, rr-1);
			write(6);
		}
	} else if(volumevalue==4){
		for(int i=1; i<=sr+6; i++){ //stair
					cr = rand()%20 + 1;
					rr = rand()%4 + 1;
					main_field[rr-1][cr-1] = "S";
					setCursor(cr-1, rr-1);
					write(2);
		}
		for(int i=1; i<=br+5; i++){ //brokenstair
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "B";
			setCursor(cr-1, rr-1);
			write(3);
		}
		for(int i=1; i<=mr+2; i++){ //monster
			cr = rand()%16 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "M";
			setCursor(cr-1, rr-1);
			write(4);
		}
		for(int i=1; i<=hr+2; i++){ //hole
			cr = rand()%16 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "H";
			setCursor(cr-1, rr-1);
			write(5);
		}
		for(int i=1; i<=fr+2; i++){ //spring fanar
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "F";
			setCursor(cr-1, rr-1);
			write(6);
		}
	} else if(volumevalue==5){
		for(int i=1; i<=sr+6; i++){ //stair
					cr = rand()%20 + 1;
					rr = rand()%4 + 1;
					main_field[rr-1][cr-1] = "S";
					setCursor(cr-1, rr-1);
					write(2);
		}
		for(int i=1; i<=br+3; i++){ //brokenstair
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "B";
			setCursor(cr-1, rr-1);
			write(3);
		}
		for(int i=1; i<=mr+2; i++){ //monster
			cr = rand()%16 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "M";
			setCursor(cr-1, rr-1);
			write(4);
		}
		for(int i=1; i<=hr+3; i++){ //hole
			cr = rand()%16 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "H";
			setCursor(cr-1, rr-1);
			write(5);
		}
		for(int i=1; i<=fr+1; i++){ //spring fanar
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "F";
			setCursor(cr-1, rr-1);
			write(6);
		}
	}else if(volumevalue==6){
		for(int i=1; i<=sr+5; i++){ //stair
					cr = rand()%20 + 1;
					rr = rand()%4 + 1;
					main_field[rr-1][cr-1] = "S";
					setCursor(cr-1, rr-1);
					write(2);
		}
		for(int i=1; i<=br+4; i++){ //brokenstair
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "B";
			setCursor(cr-1, rr-1);
			write(3);
		}
		for(int i=1; i<=mr+3; i++){ //monster
			cr = rand()%16 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "M";
			if(strcmp(main_field[rr-1][cr],"S")){
				main_field[rr-1][cr-1] = "N";
			}
			setCursor(cr-1, rr-1);
			write(4);
		}
		for(int i=1; i<=hr+2; i++){ //hole
			cr = rand()%16 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "H";
			if(strcmp(main_field[rr-1][cr],"S")){
			   main_field[rr-1][cr-1] = "N";
			}
			setCursor(cr-1, rr-1);
			write(5);
		}
		for(int i=1; i<=fr+2; i++){ //spring fanar
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "F";
			setCursor(cr-1, rr-1);
			write(6);
		}
	} else if(volumevalue==7){
		for(int i=1; i<=sr+5; i++){ //stair
					cr = rand()%20 + 1;
					rr = rand()%4 + 1;
					main_field[rr-1][cr-1] = "S";
					setCursor(cr-1, rr-1);
					write(2);
		}
		for(int i=1; i<=br+3; i++){ //brokenstair
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "B";
			setCursor(cr-1, rr-1);
			write(3);
		}
		for(int i=1; i<=mr+3; i++){ //monster
			cr = rand()%16 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "M";
			if(strcmp(main_field[rr-1][cr],"S")){
			   main_field[rr-1][cr-1] = "N";
			}
			setCursor(cr-1, rr-1);
			write(4);
		}
		for(int i=1; i<=hr+3; i++){ //hole
			cr = rand()%16 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "H";
			if(strcmp(main_field[rr-1][cr],"S")){
				main_field[rr-1][cr-1] = "N";
			}
			setCursor(cr-1, rr-1);
			write(5);
		}
		for(int i=1; i<=fr+2; i++){ //spring fanar
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "F";
			setCursor(cr-1, rr-1);
			write(6);
		}
	} else if(volumevalue==8){
		for(int i=1; i<=sr+5; i++){ //stair
					cr = rand()%20 + 1;
					rr = rand()%4 + 1;
					main_field[rr-1][cr-1] = "S";
					setCursor(cr-1, rr-1);
					write(2);
		}
		for(int i=1; i<=br+4; i++){ //brokenstair
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "B";
			setCursor(cr-1, rr-1);
			write(3);
		}
		for(int i=1; i<=mr+4; i++){ //monster
			cr = rand()%16 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "M";
			if(strcmp(main_field[rr-1][cr],"S")){
				main_field[rr-1][cr-1] = "N";
			}
			setCursor(cr-1, rr-1);
			write(4);
		}
		for(int i=1; i<=hr+3; i++){ //hole
			cr = rand()%16 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "H";
			if(strcmp(main_field[rr-1][cr],"S")){
				main_field[rr-1][cr-1] = "N";
			}
			setCursor(cr-1, rr-1);
			write(5);
		}
		for(int i=1; i<=fr+1; i++){ //spring fanar
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "F";
			setCursor(cr-1, rr-1);
			write(6);
		}
	} else if(volumevalue==9){
		for(int i=1; i<=sr+4; i++){ //stair
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "S";
			setCursor(cr-1, rr-1);
			write(2);
		}
		for(int i=1; i<=br+5; i++){ //brokenstair
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "B";
			setCursor(cr-1, rr-1);
			write(3);
		}
		for(int i=1; i<=mr+3; i++){ //monster
			cr = rand()%16 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "M";
			if(strcmp(main_field[rr-1][cr],"S")){
				main_field[rr-1][cr-1] = "N";
			}
			setCursor(cr-1, rr-1);
			write(4);
		}
		for(int i=1; i<=hr+4; i++){ //hole
			cr = rand()%16 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "H";
			if(strcmp(main_field[rr-1][cr],"S")){
				main_field[rr-1][cr-1] = "N";
			}
			setCursor(cr-1, rr-1);
			write(5);
		}
		for(int i=1; i<=fr+2; i++){ //spring fanar
			cr = rand()%20 + 1;
			rr = rand()%4 + 1;
			main_field[rr-1][cr-1] = "F";
			setCursor(cr-1, rr-1);
			write(6);
		}
	}
	setCursor(19,2);
	main_field[2][19]="S";
	write(2);

	setCursor(18,2);
	main_field[2][18]="D";
	write(1);
}

void rancol0(){
	int exist = rand()%2 +1;
	int rr = rand()%4 + 1;
	if (exist==2){
		int randnum =  rand()%11 + 1;
		if(randnum>=1 && randnum<=6)
		{
			main_field[rr-1][0] = "S";
			setCursor(0, rr-1);
			write(2);
		} else if(randnum==7){
			main_field[rr-1][0] = "B";
			setCursor(0, rr-1);
			write(3);
		} else if(randnum==8 || randnum==9){
			main_field[rr-1][0] = "M";
			setCursor(0, rr-1);
			write(4);
		}else if(randnum==10){
			main_field[rr-1][0] = "H";
			setCursor(0, rr-1);
			write(5);
		}else if(randnum==11){
			main_field[rr-1][0] = "F";
			setCursor(0, rr-1);
			write(6);
		}
	}

}

void randgen(){

	for(int col=0; col <20; col++){
						  for(int row=0; row<4; row++){
							  main_field[row][col]="N";
						  }
						  }

	int cr,rr;

	int sr = rand()%3+1;
	for(int i=1; i<=sr+10; i++){ //stair
		cr = rand()%20 + 1;
		rr = rand()%4 + 1;
		main_field[rr-1][cr-1] = "S";
		setCursor(cr-1, rr-1);
		write(2);
	}

	int br = rand()%2+1;
	for(int i=1; i<=br+3; i++){ //brokenstair
		cr = rand()%20 + 1;
		rr = rand()%4 + 1;
		main_field[rr-1][cr-1] = "B";
		setCursor(cr-1, rr-1);
		write(3);
	}

	int mr = rand()%1+1;
	for(int i=1; i<=mr+1; i++){ //monster
		cr = rand()%16 + 1;
		rr = rand()%4 + 1;
		main_field[rr-1][cr-1] = "M";
		setCursor(cr-1, rr-1);
		write(4);
	}

	int hr = rand()%1+1;
	for(int i=1; i<=hr+1; i++){ //hole
		cr = rand()%16 + 1;
		rr = rand()%4 + 1;
		main_field[rr-1][cr-1] = "H";
		setCursor(cr-1, rr-1);
		write(5);
	}

	int fr = rand()%2+1;
	for(int i=1; i<=fr+1; i++){ //spring fanar
		cr = rand()%20 + 1;
		rr = rand()%4 + 1;
		main_field[rr-1][cr-1] = "F";
		setCursor(cr-1, rr-1);
		write(6);
	}
	setCursor(19,2);
	main_field[2][19]="S";
	write(2);

	setCursor(18,2);
	main_field[2][18]="D";
	write(1);


}

void updateScreen(){
//	doodle_col+=1;

//	randgen10();

	for(int col=18; col >=0; col--){
						  for(int row=0; row<4; row++){

//							  main_field[row][col+1]= main_field[row][col];
//
//							  if(row==doodle_row && doodle_col==col){
//								  doodle_col+=1;
//							  							  setCursor(col+1, row);
//							  									  write(1);}

							if(strcmp(main_field[row][col],"H")==0){
								  setCursor(col,row);
								          print(" ");
								  setCursor(col+1, row);
										  write(5);

							  }else if(strcmp(main_field[row][col],"M")==0){
								  setCursor(col,row);
								  	  	  print(" ");
								  setCursor(col+1, row);
										  write(4);
							  }
							  else if(strcmp(main_field[row][col],"S")==0){
								  setCursor(col,row);
								  	          print(" ");
								  setCursor(col+1, row);
							  					  write(2);
							  		  }
							  else if(strcmp(main_field[row][col],"B")==0){
								  setCursor(col,row);
								  			   print(" ");
							  			  setCursor(col+1, row);
							  					  write(3);
							  		  }
							  else if(strcmp(main_field[row][col],"F")==0){
								       setCursor(col,row);
								  			   print(" ");
							  			  setCursor(col+1, row);
							  					  write(6);
							  		  }
							  else if(strcmp(main_field[row][col],"N")==0){
								  	  	  setCursor(col,row);
								  		print(" ");
										  setCursor(col+1, row);
												  print(" ");
									  }

						  }
					  }
	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);


	rancol0();
	for(int col=19; col >0; col--){
							  for(int row=0; row<4; row++){
								  field[row][col] = main_field[row][col-1];
							  }
							  }
	for(int col=0; col <20; col++){
							  for(int row=0; row<4; row++){
								  main_field[row][col]="N";
							  }
							  }

	for(int col=19; col >=0; col--){
								  for(int row=0; row<4; row++){
									  main_field[row][col] = field[row][col] ;
								  }
								  }
//	for(int col=0; col <20; col++){
//							  for(int row=0; row<4; row++){
//								  field[row][col+1]= main_field[row][col];
//							  }
//
//							  }
}

void lose(){
	clear();

//	score=+temp;

	int strScore[20];

	setCursor(0,3);
	sprintf(strScore,"%d",score);
	print(strScore);

	setCursor(8,3);
	print(player);

	sprintf(strScore,"\t%d\t",score);
	strcat(player,strScore);
	HAL_UART_Transmit(&huart2, &player, sizeof(unsigned char)*60,1000);
//	player[20]="doodler";

			started=0;
			lost=1;
			setCursor(2, 1);
			print("You Lose!");
			temp=0;
			score = 0;
			side[0]="U";
			  PWM_Start();
			  PWM_Change_Tone(800, 1000);
			  HAL_Delay(1000);
			  PWM_Stop();

}

void check(){
	if(strcmp(field[doodle_row][doodle_col],"H")==0){
	lose();

	}else if(strcmp(field[doodle_row][doodle_col],"M")==0){
//		lose();

		started=0;
		lost=1;
		monster_lost=1;

		  PWM_Start();
					  PWM_Change_Tone(800, 1000);
					  HAL_Delay(1000);
					  PWM_Stop();



	}else if(strcmp(field[doodle_row][doodle_col],"F")==0){
//		setCursor(doodle_col, doodle_row);
//		print(" ");
		setCursor(doodle_col, doodle_row);
		write(6);
		setCursor(doodle_col-1, doodle_row);
		write(1);
//		main_field[doodle_row][doodle_col]="N";

//		if(side[0]=="U"){
//			temp-=7;
//		}else{
//			side[0]="U";
//		}
		side[0]="U";
		temp=-12;




	}
//	else if(strcmp(field[doodle_row][doodle_col],"B")==0){
//
//		broken_stair=1;
//	}
}

void movescreen(){
				updateScreen();
				setCursor(10, doodle_row);
				write(1);
				check();
//				move = 7 - temp;
				move++;
				score++;
				if((move+temp)>=7){
					side[0]="D";
					move=0;
					jump();
				}

}

void jump(){

if(started==1){

	if(side[0]=="U"){

		if(temp==0 || temp==-12){

			  PWM_Start();
					  PWM_Change_Tone(500, 1000);
					  HAL_Delay(100);
					  PWM_Stop();
		}
		score++;
		temp++;

		setCursor(doodle_col, doodle_row);
		print(" ");
		if(strcmp(field[doodle_row][doodle_col-1],"S")==0){
			setCursor(doodle_col-2, doodle_row);
					doodle_col-=2;
					temp++;
					score++;

		}else{
			setCursor(doodle_col-1, doodle_row);
					doodle_col--;
		                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          }

		check();
		write(1);
		if(temp == 7){
			side[0]="D";
		}

//		if(doodle_col<=10 && change==0){
//
//			updateScreen();
//			change=1;
//
//		}else{
//			change=0;
//		}


	}else if (strcmp(side[0],"D")==0){
		temp--;
		score--;

		setCursor(doodle_col, doodle_row);
		print(" ");


		if(strcmp(field[doodle_row][doodle_col+1],"S")==0){
			side[0]="U";
			temp=0;
				}else{
					setCursor(doodle_col+1, doodle_row);
							doodle_col++;
							write(1);
				}

		check();
		if(doodle_col==19){
			lose();
		}
	}
}


}

void start(){

	started = 1;
	lost==0;
	monster_lost=0;

	doodle_col=18;
	doodle_row=2;



	for(int col=19; col >0; col--){
						  for(int row=0; row<4; row++){
							  field[row][col] = main_field[row][col];
						  }
						  }


}



/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim15;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F3xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f3xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */
//	menu();
  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */

	unsigned char name[40]="";
	unsigned char username[40];
//						  strcat(data,strTime);

	setCursor(0, 3);
	print("Player name: Doodler");
	HAL_UART_Receive(&huart2, name, sizeof(unsigned char)*1000,1000);

			 sprintf(username,"%p",name);
			 setCursor(12, 3);
		     print(name);

  /* USER CODE END EXTI0_IRQn 1 */
}

/**
  * @brief This function handles EXTI line1 interrupt.
  */
void EXTI1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI1_IRQn 0 */







  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI1_IRQn 1 */


  for(int i=0; i<4; i++){
 	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET);
 	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);
 	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
 	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);


  	if(i==2){
  		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
  				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1)){


  				clear();
  				  				setCursor(0, 1);
  				  				print("Mona Radad");
  				  				setCursor(0, 2);
  				  				print("Zahra Tarvij");

  				  			  int strTime[20];
  				  			  int strDate[20];

  				  			  HAL_RTC_GetTime(&hrtc, &mytime, RTC_FORMAT_BIN);
  				  			  HAL_RTC_GetDate(&hrtc, &myDate, RTC_FORMAT_BIN);


  				  			  setCursor(0,3);
  				  			  sprintf(strTime,"%2d:%2d:%2d",mytime.Hours,mytime.Minutes,mytime.Seconds);
  				  			  print(strTime);

  				  			  setCursor(8,3);
  				  			  sprintf(strDate,"  %d//%d//%d",myDate.Year,myDate.Month,myDate.Date);
  				  			  print(strDate);


  				  }

  	  }else if(i==1){
  		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET);
  				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1)){
clear();


//int volume;
//
//  int y = HAL_ADC_GetValue(&hadc1);
//  float fy = ((float)y*100/4095);
//  volume = (fy/10);
//  volume *= 10;
//	randlevels(volume/10-1);

		randgen();
	//randlevels(9);
		start();

  				  }

  	  }else if(i==0){
  		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
  				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1)){
// left side
  					  if(!(strcmp(main_field[(doodle_row+1)%4][doodle_col],"S")==0)){
  						 setCursor(doodle_col, doodle_row);
  						  					  print(" ");
  						  					doodle_row++;
  						  					  doodle_row = (doodle_row)%4;
  						  					  check();
  						  					 setCursor(doodle_col, doodle_row);
  						  					 write(1);



  							  			time_t t;
  				  						  time(&t);
  						  			     int strTime[20];
										  int strDate[20];

										  HAL_RTC_GetTime(&hrtc, &mytime, RTC_FORMAT_BIN);
										  HAL_RTC_GetDate(&hrtc, &myDate, RTC_FORMAT_BIN);


										  sprintf(strTime,"%2d:%2d:%2d\t",mytime.Hours,mytime.Minutes,mytime.Seconds);
										  sprintf(strDate,"  %d//%d//%d\n",myDate.Year,myDate.Month,myDate.Date);
										  strcat(strTime,strDate);


										  unsigned char data[40]="Doodler\tLeft\n";
										  strcat(data,strTime);
										  HAL_UART_Transmit(&huart2, &data, sizeof(unsigned char)*60,1000);






  					  }
  				  }
 // right side
  	  }else if(i==3){
  		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);
  				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1)){

  					if(!(strcmp(main_field[(doodle_row-1+4)%4][doodle_col],"S")==0)){
  						setCursor(doodle_col, doodle_row);
  						  					print(" ");
  						  					doodle_row--;
  						  					if(doodle_row==-1){
  						  						doodle_row=3;
  						  					}else{
  						  						 doodle_row = abs((doodle_row)%4);
  						  					}
  						  				  check();
  						  					 setCursor(doodle_col, doodle_row);
  						  					 write(1);



  	  							  			time_t t;
  	  				  						  time(&t);
  	  						  			     int strTime[20];
  											  int strDate[20];

  											  HAL_RTC_GetTime(&hrtc, &mytime, RTC_FORMAT_BIN);
  											  HAL_RTC_GetDate(&hrtc, &myDate, RTC_FORMAT_BIN);


  											  sprintf(strTime,"%2d:%2d:%2d\t",mytime.Hours,mytime.Minutes,mytime.Seconds);
  											  sprintf(strDate,"  %d//%d//%d\n",myDate.Year,myDate.Month,myDate.Date);
  											  strcat(strTime,strDate);


  											  unsigned char data[40]="Doodler\tRight\n";
  											  strcat(data,strTime);
  											  HAL_UART_Transmit(&huart2, &data, sizeof(unsigned char)*60,1000);





  					}

  				  }
  	  }

    }
   HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);
   while(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1));

  /* USER CODE END EXTI1_IRQn 1 */
}

/**
  * @brief This function handles EXTI line2 and Touch Sense controller.
  */
void EXTI2_TSC_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI2_TSC_IRQn 0 */

  /* USER CODE END EXTI2_TSC_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
  /* USER CODE BEGIN EXTI2_TSC_IRQn 1 */
  for(int i=0; i<4; i++){
  	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET);
  	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);
  	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
  	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);

// shoot
   	if(i==2){
   		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
   				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2)){

   					  dart_col=doodle_col-1;
   					  dart_row=doodle_row;
   					  shoot=1;


				  			time_t t;
	  						  time(&t);
			  			     int strTime[20];
						  int strDate[20];

						  HAL_RTC_GetTime(&hrtc, &mytime, RTC_FORMAT_BIN);
						  HAL_RTC_GetDate(&hrtc, &myDate, RTC_FORMAT_BIN);


						  sprintf(strTime,"%2d:%2d:%2d\t",mytime.Hours,mytime.Minutes,mytime.Seconds);
						  sprintf(strDate,"  %d//%d//%d\n",myDate.Year,myDate.Month,myDate.Date);
						  strcat(strTime,strDate);


						  unsigned char data[40]="Doodler\tShoot\n";
						  strcat(data,strTime);
						  HAL_UART_Transmit(&huart2, &data, sizeof(unsigned char)*60,1000);

   				  }

   	  }else if(i==1){
   		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET);
   		   				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2)){

   		   					  clear();
   		   					  started=0;
   		   					  lost=0;

   		   				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9,0);
   		   			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10,0);
   		   		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11,0);
   		   	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8,0);
   		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12,0);
   		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13,0);
   		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14,0);
   		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15,0);
   		   					  menu();

   	  }
  }
  }

     HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
     HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET);
     HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
     HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);
     while(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2));

  /* USER CODE END EXTI2_TSC_IRQn 1 */
}

/**
  * @brief This function handles EXTI line3 interrupt.
  */
void EXTI3_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI3_IRQn 0 */

  /* USER CODE END EXTI3_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
  /* USER CODE BEGIN EXTI3_IRQn 1 */

  /* USER CODE END EXTI3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */

  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  /* USER CODE BEGIN EXTI4_IRQn 1 */

  /* USER CODE END EXTI4_IRQn 1 */
}

/**
  * @brief This function handles TIM1 break and TIM15 interrupts.
  */
void TIM1_BRK_TIM15_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_BRK_TIM15_IRQn 0 */



	if(shoot==1){

		if(strcmp(field[dart_row][dart_col],"M")==0){
			field[dart_row][dart_col]="N";
			main_field[dart_row][dart_col]="N";
			setCursor(dart_col, dart_row);
			print(" ");
			shoot=0;
			score+=3;
		}
		else if(strcmp(field[dart_row][dart_col],"N")==0) {

						setCursor(dart_col, dart_row);
						print("*");
						dart_col--;
						setCursor(dart_col+1, dart_row);
												print(" ");

						if(dart_col==0){
									shoot=0;
									setCursor(dart_col, dart_row);
												print(" ");
								}
			}else if(strcmp(field[dart_row][dart_col],"S")==0){

				dart_col-=1;
				setCursor(dart_col, dart_row);
				print("*");



			}
			else if(strcmp(field[dart_row][dart_col],"F")==0){

							dart_col-=1;
							setCursor(dart_col, dart_row);
							print("*");
		}else if(strcmp(field[dart_row][dart_col],"H")==0){

			dart_col-=1;
			setCursor(dart_col, dart_row);
			print("*");
		}
	}
	if(lost==1){
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_11);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_12);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_13);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_14);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_15);
	}



  /* USER CODE END TIM1_BRK_TIM15_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  HAL_TIM_IRQHandler(&htim15);
  /* USER CODE BEGIN TIM1_BRK_TIM15_IRQn 1 */

  /* USER CODE END TIM1_BRK_TIM15_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */



		if(lost==0 && broken_stair==0){
			if(doodle_col>10)
				jump();
			else if(doodle_col<=10)
				movescreen();
			}
			else if(monster_lost==1){
				setCursor(doodle_col, doodle_row);
						print(" ");
						setCursor(doodle_col+1, doodle_row);
						doodle_col++;
						write(1);
						if(doodle_col==19){
							monster_lost==0;
							clear();

							int strScore[20];

									  setCursor(0,3);
									  sprintf(strScore,"%d",score);
									  print(strScore);

									  setCursor(8,3);
									  print(player);

									  sprintf(strScore,"\t%d\t",score);
									  	strcat(player,strScore);
									  	HAL_UART_Transmit(&huart2, &player, sizeof(unsigned char)*60,1000);
//									  	player[20]="doodler";

							setCursor(0, 1);
							print("You Lose!");
							temp=0;
							score=0;

							side[0]="U";
						}


	}


  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */


  x++;

    	   if(x%4==0){
    		   	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 0);
    		   	 	  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 1);
    		   	 	  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, 1);
    		   	 	  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, 1);
    		   	 	numberTOBCD(volval);
    	   }
    	   if(x%4==1){
    	 	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 1);
    	 	  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0);
    	 	  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, 1);
    	 	  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, 1);
    	 	  	numberTOBCD(0);
    	   }
    	   if(x%4==2){
    	 	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 1);
    	 	 	  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 1);
    	 	 	  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, 0);
    	 	 	  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, 1);
//    	 	 		y2=(score/10)%10;
//    	 	 		y3=(y2/10)%10;
    	 	 	  y1=((score)/10)%10;
    	 	 	  numberTOBCD(y1);


    	   }
    	   if(x%4==3){
    	 	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 1);
    	 	 	  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 1);
    	 	 	  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, 1);
    	 	 	  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, 0);
//    	 	 	  	y4=(y3/10)%10;
    	 	 	  y2=((score)%10);
    	 	 	   numberTOBCD(y2);

    	   }


  /* USER CODE END TIM3_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
