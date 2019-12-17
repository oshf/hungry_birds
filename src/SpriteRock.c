#pragma bank 2
#include "main.h"
UINT8 bank_SPRITE_ROCK = 2;

#include "SpriteManager.h"
#include "ZGBMain.h"

extern UINT8 objectCount;
extern UINT8 score;

UINT8 rockTop; // To keep track if the rock reached maximum height
const UINT8 rockSprite[] = { 1, 1 }; // 1 frame of animation, at position 1

void Start_SPRITE_ROCK() {
	NR10_REG = 0x14; // Play sound
	NR11_REG = 0x3F;
	NR12_REG = 0xF7;
	NR13_REG = 0x46;
	NR14_REG = 0x85;
	rockTop = 0;
}

void Update_SPRITE_ROCK() {

	if (score < 50) { // Slower rock speed
		THIS->x--;
		THIS->x--;

		if (THIS->x <= 138) {
			SetSpriteAnim(THIS, rockSprite, 15);
		}

		if (THIS->y > 40 && rockTop == 0) {
			THIS->y--;
			if (THIS->y <= 59)
				rockTop = 1; // Rock has reached the top
		}

		if (THIS->y >= 56 && rockTop == 1) {
			THIS->y++;
		}
	}

	if (score > 49 && score < 100) { // Medium rock speed
			THIS->x--;
			THIS->x--;
			THIS->x--;

			if (THIS->x <= 138) {
				SetSpriteAnim(THIS, rockSprite, 15);
			}

			if (THIS->y > 40 && rockTop == 0) {
				THIS->y--;
				THIS->y--;
				if (THIS->y <= 50)
					rockTop = 1; // Rock has reached the top
			}

			if (THIS->y >= 50 && rockTop == 1) {
				THIS->y++;
				THIS->y++;
			}
	}

	if (score > 99) { // Faster rock speed
		THIS->x--;
		THIS->x--;

		if (THIS->x <= 138) {
			SetSpriteAnim(THIS, rockSprite, 15);
		}

		THIS->x--;
		THIS->x--;

		if (THIS->y > 40 && rockTop == 0) {
			THIS->y--;
			THIS->y--;
			if (THIS->y <= 59)
				rockTop = 1; // Rock has reached the top
		}
		if (THIS->y >= 56 && rockTop == 1) {
			THIS->y++;
			THIS->y++;
		}
	}

	if (THIS->x <= 1) { // Remove rock if it reaches end of screen, set count to 0
		SpriteManagerRemove(THIS_IDX);
		objectCount = 0;
		}
	}

void Destroy_SPRITE_ROCK() {
}