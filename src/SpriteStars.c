#include "Banks/SetBank2.h"
#include "main.h"

#include "SpriteManager.h"

const UINT8 anim_explosion[] = {8, 0, 1, 2, 3, 4, 5, 5, 5};

void Start_SpriteStars() {
	SetSpriteAnim(THIS, anim_explosion, 12u);
}

void Update_SpriteStars() {
	if(THIS->anim_frame == 7) {
		SpriteManagerRemove(THIS_IDX);
	}
}

void Destroy_SpriteStars() {
}