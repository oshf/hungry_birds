#pragma bank 2
#include "main.h"
UINT8 bank_SPRITE_GOB = 2;

#include "SpriteManager.h"
#include "ZGBMain.h"

const UINT8 gameOverBirdAnim[] = { 2, 0, 1 }; // 2 frames of animation, at position 0 then 1

void Start_SPRITE_GOB() {
}

void Update_SPRITE_GOB() {
	SetSpriteAnim(THIS, gameOverBirdAnim, 5); // Change sprite
}

void Destroy_SPRITE_GOB() {
}