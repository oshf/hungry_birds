#pragma bank 2
#include "main.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
UINT8 bank_SPRITE_PLAYER = 2;

extern UINT8 lives;
extern UINT8 canJump;
extern UINT8 objectCount;

const UINT8 birdIdle[] = { 1, 0 };  // 1 frame of animation, at position 0
const UINT8 birdJump[] = { 1, 1 }; // 1 frame of animation, at position 1
const UINT8 birdDeath[] = { 2, 2, 3 }; // 2 frames of animation, at position 2 then 3

void doJump();

UINT8 jump; // Track if bird is jumping
UINT8 active; // Track is bird is alive (0 = alive, 1 = not alive)
UWORD jumpState; // 'u' for up, 'd' for down

void Start_SPRITE_PLAYER() {
	jump = 0;
	jumpState = 'u'; // Bird will need to start with an upward jump
	active = 0;
}

void Update_SPRITE_PLAYER() {
	UINT8 i;
	struct Sprite* spr;

	// Collision check

	SPRITEMANAGER_ITERATE(i, spr) {
		if (spr->type == SPRITE_ROCK && jump == 1) { // If bird is hit by a rock and jumping
			if (CheckCollision(THIS, spr)) {
				SetSpriteAnim(THIS, birdDeath, 15); // Play animation
				SpriteManagerRemove(THIS_IDX); // Remove bird
				NR10_REG = 0x1E; // Play sound
				NR11_REG = 0x7F;
				NR12_REG = 0xF3;
				NR13_REG = 0xFF;
				NR14_REG = 0x85;
				jump = 0; // Reset jump
				active = 1; // 1 = bird not alive
				lives--;
				if (canJump == 1)
					canJump = 0;
			}
		}
	}

	if (jump == 1) {
		doJump();
	}
	if (KEY_PRESSED(J_A) && jump == 0 && canJump == 0 && active == 0) { // If A is pressed and can jump and is alive
		jump = 1;
		canJump = 1;
		NR10_REG = 0x17; // Play sound
		NR11_REG = 0x3F;
		NR12_REG = 0xF3;
		NR13_REG = 0xFF;
		NR14_REG = 0x85;
		SetSpriteAnim(THIS, birdJump, 15); // Play animation
	}
}

void Destroy_SPRITE_PLAYER() {
}

void doJump() {
	if (jump == 1) {
		if (THIS->y > 60 && jumpState == 'u') {
			THIS->y--;
			THIS->y--;
			THIS->y--;
			THIS->y--;
			if (THIS->y == 80)
				canJump = 0;
			if (THIS->y == 60) // Reached the top, go down
				jumpState = 'd';
		}
		if (THIS->y < 112 && jumpState == 'd') {
			THIS->y++;
			THIS->y++;
			THIS->y++;
			THIS->y++;
			if (THIS->y == 112) { // Back to starting position
				jump = 0;
				jumpState = 'u';
				SetSpriteAnim(THIS, birdIdle, 15); // Play Idle animation
			}
		}
	}
}