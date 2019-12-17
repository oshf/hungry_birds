#pragma bank 2
#include "main.h"
UINT8 bank_STATE_GAMEOVER = 2;

#include "..\res\src\font.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Print.h"
#include "Keys.h"

extern UINT8 score;

struct Sprite* gOB; // Pointer for the Game Over Bird sprite
struct Sprite* gOM; // Pointer for the Game Over Mad sprite

UINT8 i, j; // Temp counter variables

void Start_STATE_GAMEOVER() {

	// Initialize Registers for sounds

	NR52_REG = 0x80;  // POWER SOUNDS
	NR50_REG = 0x7f;  // MASTER VOLUME
	NR51_REG = 0xff;   // L/R ENABLES

	NR10_REG = 0x7D; // Play sound
	NR11_REG = 0xBF;
	NR12_REG = 0xF7;
	NR13_REG = 0xDE;
	NR14_REG = 0x83;

	INIT_FONT(font, 3, PRINT_BKG); // Load font from bank 3 and print on the background

	for (i = 0; i <= 20; i++) { // Erase background
		for (j = 0; j <= 18; j++) {
			PRINT(i, j, " ");
		}
	}

	PRINT(6, 5, "GAMEOVER");

	PRINT_POS(6, 6);
	Printf("Score %d", score); // Print the player score on the background

	PRINT(5, 10, "PUSH START");

	gOB = SpriteManagerAdd(SPRITE_GOB, 73, 112); // Add 'Game Over Bird' sprite
	gOM = SpriteManagerAdd(SPRITE_GOM, 65, 105); // Add 'Game Over Mad' (Angry) sprite
}

void Update_STATE_GAMEOVER() {
	if (KEY_TICKED(J_START)) { // Checks to see if the Start button is pressed
		for (i = 0; i <= 20; i++) { // Erase background tiles
			for (j = 0; j <= 18; j++) {
				PRINT(i, j, " ");
			}
		}

		SpriteManagerRemoveSprite(gOB); // Remove Game Over Bird sprite
		SpriteManagerRemoveSprite(gOM); // Remove Game Over Mad (Angry) sprite

		SetState(STATE_TITLE); // Go to the title screen
	}
}