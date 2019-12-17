#pragma bank 2
#include "main.h"
UINT8 bank_SPRITE_GOM = 2;

#include "SpriteManager.h"
#include "ZGBMain.h"

const UINT8 gameOverMadSpr[] = { 1, 0 }; // 1 frame of animation, at position 0
const UINT8 gameOverMadSpr2[] = { 1, 1 }; // 1 frame of animation, at position 1
 
UINT8 moveCount; // Counter variable to time sprite moves


void Start_SPRITE_GOM() {
	moveCount = 0;
}

void Update_SPRITE_GOM() {
	if (moveCount < 11) { // Move sprite
		THIS->x = 63; 
		THIS->y = 105;
		SetSpriteAnim(THIS, gameOverMadSpr, 1); // Change sprite
		moveCount++;
	}
	else {
		THIS->x = 83; // Move sprite
		THIS->y = 101;
		SetSpriteAnim(THIS, gameOverMadSpr2, 1); // Change sprite
		moveCount++;
		if (moveCount > 20) {
			moveCount = 0;
		}
	}
}

void Destroy_SPRITE_GOM() {
}