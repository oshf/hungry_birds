#pragma bank 2
#include "main.h"
UINT8 bank_STATE_GAME = 2;

#include "..\res\src\tiles.h"
#include "..\res\src\map.h"
#include "..\res\src\font.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Print.h"
#include "Keys.h"
#include <rand.h>

UINT8 score; // Keeps track of the player score
UINT8 lives; // Keeps track of the number of active birds
UINT8 canJump; // Only bird bird can jump at a time
UINT8 objectCount; // Only one object thrown at a time (worm or rock)
UINT8 randNum; // Random number

void updateScore();
void objectCheck();
void deathCheck();

void Start_STATE_GAME() {
	UINT8 i;

	SPRITES_8x16;
	for(i = 0; i != N_SPRITE_TYPES; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

	SpriteManagerAdd(SPRITE_PLAYER, 95, 112); // Bird 1 (A)
	SpriteManagerAdd(SPRITE_PLAYER2, 60, 112); // Bird 2 (B)
	SpriteManagerAdd(SPRITE_PLAYER3, 25, 112); // Bird 3 (Up)

	INIT_FONT(font, 3, PRINT_BKG); // Load font from bank 3 and print on the background

	InitScrollTiles(0, 98, tiles, 3); // Load background tiles from bank 3
	InitScroll(mapWidth, mapHeight, map, 0, 0, 3); // Load background from bank 3

	score = 0;
	lives = 3;
	canJump = 0;
	objectCount = 0;

	initrand(DIV_REG); // Initialize random seed

	PRINT(0, 0, "Score ");

	// Initialize Registers for sounds

	NR52_REG = 0x80;  // POWER SOUNDS
	NR50_REG = 0x7f;  // MASTER VOLUME
	NR51_REG = 0xff;   // L/R ENABLES
}

void Update_STATE_GAME() {  // Game loop

	#ifndef NDEBUG // If debug build allow score increments if SELECT button is pressed
		if (KEY_PRESSED(J_SELECT)) {
			score++;
		}
	#endif

	updateScore(); // Update the player score
	objectCheck(); // Throw an object if one doesn't exist
	deathCheck(); // Check how many lives are left
}

void updateScore() {
		PRINT_POS(6, 0); // Print the score on the background
		Printf("%d", score);

		DPRINT_POS(0, 1); // Debug print the value of randNum
		DPrintf("%d", randNum);
}

void objectCheck() {

	if (objectCount == 0) { // One object at a time
		
		randNum = rand() % 2u; // Random number 0 or 1

		if (randNum != 0) { // If not 0 throw out a rock
			SpriteManagerAdd(SPRITE_ROCK, 160, 108);
			objectCount++;
		}
		else { // Throw a worm
				SpriteManagerAdd(SPRITE_WORM, 160, 108);
				objectCount++;
			}
	}

}

void deathCheck() {
	if (lives == 0) { // If no lives then game over
		SetState(STATE_GAMEOVER);
	}
}