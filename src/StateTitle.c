#pragma bank 2
#include "main.h"
UINT8 bank_STATE_TITLE = 2;

#include "..\res\src\mtiles.h"
#include "..\res\src\title.h"
#include "..\res\src\font.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Print.h"
#include "Keys.h"

UINT8 printCount; // Counter variable to flash PUSH START

void Start_STATE_TITLE() {

	InitScrollTiles(0, 45, tiles1, 3); // Load background tiles
	InitScroll(map1Width, map1Height, map1, 0, 0, 3); // Load background

	// Initialize Registers for sounds

	NR52_REG = 0x80;  // POWER SOUNDS
	NR50_REG = 0x7f;  // MASTER VOLUME
	NR51_REG = 0xff;   // L/R ENABLES

	INIT_FONT(font, 3, PRINT_BKG); // Load font from bank 3 and print on the background

	PRINT(4, 0, "Made by oshf");
	PRINT(4, 1, "FOR #ZGBJAM2");

	printCount = 0;

	SHOW_BKG; // Show the background
}

void Update_STATE_TITLE() {

	if (printCount < 45) { // Flash PUSH START
		PRINT(5, 13, "PUSH START");
		printCount++;
	}
	else {
		PRINT(5, 13, "          "); // Erase PUSH START
		printCount++;
		if (printCount >= 75) {
			printCount = 0;
		}
	}
	
	if (KEY_TICKED(J_START)) {

		NR10_REG = 0x75; // Play sound
		NR11_REG = 0xBF;
		NR12_REG = 0xF7;
		NR13_REG = 0xDE;
		NR14_REG = 0x84;
		SetState(STATE_GAME); // Change to game state
	}
}