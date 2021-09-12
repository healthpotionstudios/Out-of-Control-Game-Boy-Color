#include "Banks/SetBank2.h"
#include "Sound.h"
#include "SpriteManager.h"
#include "ZGBMain.h" //sprite types

void Start_SpritePunch() {
	SET_FRAME(THIS, (UINT8)4u);
    THIS->coll_x = 3;
    THIS->coll_y = 3;
    THIS->coll_w = 10;
    THIS->coll_h = 10;
}

void Update_SpritePunch() {
	UINT8 i;
	struct Sprite* spr;
	struct Sprite* spr2;

	for(i = 0u; i != sprite_manager_updatables[0]; ++i) {
		spr = sprite_manager_sprites[sprite_manager_updatables[i + 1u]];
		if(spr->type == SpriteHedgehog || spr->type == SpriteSkunk || spr->type == SpriteSlime || spr->type == SpriteCrab || spr->type == SpriteWaterSlime || spr->type == SpriteFish) {
			if(CheckCollision(THIS, spr)) {
				spr2 = SpriteManagerAdd(SpriteStars, spr->x, spr->y);
                PlayFx(CHANNEL_1, 10, 0x4f, 0xc7, 0xf3, 0x73, 0x86);
				SpriteManagerRemove(i);
			}
		}
	}
}

void Destroy_SpritePunch() {
}