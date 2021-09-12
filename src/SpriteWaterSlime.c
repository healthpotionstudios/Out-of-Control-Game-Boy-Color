#include "Banks/SetBank2.h"
// #include "Keys.h"
#include "SpriteManager.h"
// #include "ZGBMain.h" // get access to sprite types, delta_time

extern const UINT8 anim_slime_idle[];
extern const UINT8 anim_slime_jump[];

extern const UINT8 waitBetweenJump;
extern const UINT8 jumpUpTime;
extern const UINT8 slimeSpeed;

struct EnemyInfo
{
    BYTE wait, jumping, jumpingUp;
    UINT8 timer;
    INT8 accel_y;
};


void Start_SpriteWaterSlime() {
    struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
    THIS->coll_y = 1;
    THIS->coll_h = 15;

    data->wait = 0;
    data->jumping = 0;
    data->timer = waitBetweenJump;
    SPRITE_SET_VMIRROR(THIS);
    SetSpriteAnim(THIS,anim_slime_idle,3u);
}

void Update_SpriteWaterSlime() {
    struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;

    if (data->wait)
    {
        data->wait = 0;
        return;
    }

    data->timer--;
    if (data->timer == 10 && data->jumping == 0)
    {
        SetSpriteAnim(THIS,anim_slime_jump,2u);
    }
    if (data->timer == 0 && data->jumping == 0)
    {
        SetSpriteAnim(THIS,anim_slime_idle,3u);
        data->accel_y = -1;
        data->jumping = 1;
        data->jumpingUp = 1;
        data->timer = jumpUpTime;
    }
    if (data->timer == 0 && data->jumping && data->jumpingUp)
    {
        data->jumpingUp = 0;
        data->accel_y = 0;
    }
    if (data->jumping && data->jumpingUp)
    {
        if (TranslateSprite(THIS,0,data->accel_y)) //hits anything
        {
            data->jumpingUp = 0;
            data->accel_y = 0;
        }
        else if (data->accel_y != -4)
        {
            data->accel_y--;
        }
    }
    if (data->jumping && data->jumpingUp == 0)
    {
        
        if (TranslateSprite(THIS,0,data->accel_y) == 0)
        {
            if (data->accel_y != 4)
            {
                data->accel_y++;
            }
        }
        else
        {
            data->jumping = 0;
            data->accel_y = 0;
            data->timer = waitBetweenJump;
        }
        
    }
    if (data->jumping)
    {
        if(SPRITE_GET_VMIRROR(THIS)) {
            //moving left
            if(TranslateSprite(THIS, -slimeSpeed, 0)) {
                SPRITE_UNSET_VMIRROR(THIS);
            } 
        } else {
            //moving right
            if(TranslateSprite(THIS, slimeSpeed, 0)) {
                SPRITE_SET_VMIRROR(THIS);
            } 
        }
    }
    data->wait = 1;
} 

void Destroy_SpriteWaterSlime() {
}
