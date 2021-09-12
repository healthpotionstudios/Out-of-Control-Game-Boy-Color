#include "Banks/SetBank2.h"
#include "main.h"

#include "SpriteManager.h"

extern const UINT8 anim_wave2[];

void Start_SpriteTitleWaveRed() {
	SetSpriteAnim(THIS, anim_wave2, 6u);
}

void Update_SpriteTitleWaveRed() {
}

void Destroy_SpriteTitleWaveRed() {
}