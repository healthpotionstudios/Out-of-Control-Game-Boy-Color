#include "Banks/SetBank2.h"
#include "main.h"

#include "SpriteManager.h"

extern const UINT8 anim_wave1[];

void Start_SpriteTitleWaveOrange() {
	SetSpriteAnim(THIS, anim_wave1, 5u);
}

void Update_SpriteTitleWaveOrange() {
}

void Destroy_SpriteTitleWaveOrange() {
}