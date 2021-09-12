#include "Banks/SetBank2.h"
#include "SpriteManager.h"
#include "Scroll.h"
// #include "ZGBMain.h" // get access to sprite types, delta_time


//const UINT8 anim_skunk_walk[] = {4, 0, 1, 2, 3};
const UINT8 anim_fish[] = {2, 0, 1};

struct EnemyInfo
{
    BYTE wait;
};


void Start_SpriteFish() {
    struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;

    THIS->coll_y = 1;
    THIS->coll_h = 12;

    data->wait = 0;
    SetSpriteAnim(THIS, anim_fish, 15u);

    SPRITE_SET_VMIRROR(THIS);
    
}

void Update_SpriteFish() {
    struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;

    if (!data->wait)
    {
        if(SPRITE_GET_VMIRROR(THIS)) {
            //moving left
            if(TranslateSprite(THIS, -1, 0)) {
                SPRITE_UNSET_VMIRROR(THIS);
            } 
        } else {
            //moving right
            if(TranslateSprite(THIS, +1, 0)) {
                SPRITE_SET_VMIRROR(THIS);
            } 
        }
        data->wait = 1;
        
    }
    else
    {
        data->wait = 0;
    }
    
} 

void Destroy_SpriteFish() {
}
