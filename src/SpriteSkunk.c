#include "Banks/SetBank2.h"
#include "SpriteManager.h"
#include "Scroll.h"
// #include "ZGBMain.h" // get access to sprite types, delta_time


//const UINT8 anim_skunk_walk[] = {4, 0, 1, 2, 3};
const UINT8 anim_skunk_walk[] = {2, 0, 1};

struct EnemyInfo
{
    BYTE wait;
    INT8 accel_y;
};


void Start_SpriteSkunk() {
    struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;

    THIS->coll_y = 1;
    THIS->coll_h = 15;

    data->wait = 0;
    SetSpriteAnim(THIS, anim_skunk_walk, 15u);
    SPRITE_SET_VMIRROR(THIS);
    
}

void Update_SpriteSkunk() {
    struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;

    if (!data->wait)
    {
        if(SPRITE_GET_VMIRROR(THIS)) {
            //moving left
            if(TranslateSprite(THIS, -1, 0)) {
                SPRITE_UNSET_VMIRROR(THIS);
            } 
            // else	if(!scroll_collisions[GetScrollTile(((THIS->x + THIS->coll_x) >> 3), (THIS->y >> 3) + 2u)]) {
            //     SPRITE_UNSET_VMIRROR(THIS);
            // }
        } else {
            //moving right
            if(TranslateSprite(THIS, +1, 0)) {
                SPRITE_SET_VMIRROR(THIS);
            } 
            // else if(!scroll_collisions[GetScrollTile(((THIS->x + THIS->coll_x + THIS->coll_w) >> 3), (THIS->y >> 3) + 2u)]) {
            //     SPRITE_SET_VMIRROR(THIS);
            // }
        }
        data->wait = 1;
        if (TranslateSprite(THIS,0,data->accel_y) == 0)
        {
            if (data->accel_y != 3)
            {
                data->accel_y = data->accel_y + 1;
            }
        }
        else
        {
            data->accel_y = 1;
        }
        
    }
    else
    {
        data->wait = 0;
    }
    
} 

void Destroy_SpriteSkunk() {
}
