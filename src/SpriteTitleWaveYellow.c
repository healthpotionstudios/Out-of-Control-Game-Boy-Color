#include "Banks/SetBank2.h"
#include "main.h"

#include "SpriteManager.h"

extern const UINT8 anim_wave2[];

void Start_SpriteTitleWaveYellow() {
	SetSpriteAnim(THIS, anim_wave2, 6u);
}

void Update_SpriteTitleWaveYellow() {
}

void Destroy_SpriteTitleWaveYellow() {
}