#pragma bank 2
#include "main.h"
UINT8 bank_SPRITE_WORM = 2;

#include "SpriteManager.h"
#include "ZGBMain.h"

extern UINT8 score;
extern UINT8 objectCount;

UINT8 wormTop; // To keep track if the worm reached maximum height
const UINT8 wormSprite[] = { 1, 1 }; // 1 frame of animation, at position 1

void Start_SPRITE_WORM(){
	NR10_REG = 0x14; // Play sound
	NR11_REG = 0x3F;
	NR12_REG = 0xF7;
	NR13_REG = 0x46;
	NR14_REG = 0x85;
	wormTop = 0;
}

void Update_SPRITE_WORM() {
	UINT8 i;
	struct Sprite* spr;

	// Collision check

	SPRITEMANAGER_ITERATE(i, spr) {
		if (spr->type == SPRITE_PLAYER) { // Bird 1
			if (CheckCollision(THIS, spr)) {
				SpriteManagerRemove(THIS_IDX); // Remove this sprite
				objectCount = 0;
				NR10_REG = 0x15; // Play sound
				NR11_REG = 0x7F;
				NR12_REG = 0xF3;
				NR13_REG = 0xA0;
				NR14_REG = 0x85;
				score += 3;
			}
		}
		if (spr->type == SPRITE_PLAYER2) { // Bird 2
			if (CheckCollision(THIS, spr)) {
				SpriteManagerRemove(THIS_IDX); // Remove this sprite
				objectCount = 0;
				NR10_REG = 0x15; // Play sound
				NR11_REG = 0x7F;
				NR12_REG = 0xF3;
				NR13_REG = 0xA0;
				NR14_REG = 0x85;
				score += 2;
		}
			}
		if (spr->type == SPRITE_PLAYER3) { // Bird 3
			if (CheckCollision(THIS, spr)) {
				SpriteManagerRemove(THIS_IDX);
				objectCount = 0;
				NR10_REG = 0x15; // Play sound
				NR11_REG = 0x7F;
				NR12_REG = 0xF3;
				NR13_REG = 0xA0;
				NR14_REG = 0x85;
				score++;
			}
		}
	}

	if (score < 26) { // Slower worm speed
		THIS->x--;
		THIS->x--;

		if (THIS->x <= 138) {
			SetSpriteAnim(THIS, wormSprite, 15);
		}

		if (THIS->y > 40 && wormTop == 0) {
			THIS->y--;
			if (THIS->y <= 59)
				wormTop = 1; // Worm has reached the top
		}

		if (THIS->y >= 56 && wormTop == 1) {
			THIS->y++;
		}
	}

	if (score > 25) { // Faster worm speed
			THIS->x--;
			THIS->x--;
			THIS->x--;

			if (THIS->x <= 138) {
				SetSpriteAnim(THIS, wormSprite, 15);
			}

			if (THIS->y > 40 && wormTop == 0) {
				THIS->y--;
				THIS->y--;
				if (THIS->y <= 50)
					wormTop = 1; // Worm has reached the top
			}

			if (THIS->y >= 50 && wormTop == 1) {
				THIS->y++;
				THIS->y++;
			}
	}

	if (THIS->x <= 1) { // Remove worm if it reaches end of screen, set count to 0
		SpriteManagerRemove(THIS_IDX);
		objectCount = 0;
	}


}

void Destroy_SPRITE_WORM() {
}