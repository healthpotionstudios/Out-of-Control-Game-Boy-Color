#include "Banks/SetBank2.h"
// #include "Keys.h"
#include "SpriteManager.h"
// #include "ZGBMain.h" // get access to sprite types, delta_time

const UINT8 anim_nut_idle[] = {2, 0, 1};

const UINT8 nutWaitBetweenJump = 1;
const UINT8 nutJumpUpTime = 5u;
const UINT8 nutSpeed = 2;

struct NutInfo
{
    BYTE wait, jumping, jumpingUp;
    UINT8 timer;
    INT8 accel_y;
};


void Start_SpriteBossBouncyNut() {
    struct NutInfo* data = (struct NutInfo*)THIS->custom_data;
    THIS->coll_y = 1;
    THIS->coll_h = 15;

    data->wait = 0;
    data->jumping = 0;
    data->timer = nutWaitBetweenJump;
    //SPRITE_SET_VMIRROR(THIS);
    SetSpriteAnim(THIS,anim_nut_idle,13u);
}

void Update_SpriteBossBouncyNut() {
    struct NutInfo* data = (struct NutInfo*)THIS->custom_data;

    if (data->wait)
    {
        data->wait = 0;
        return;
    }

    data->timer--;
    if (data->timer == 0 && data->jumping == 0)
    {
        data->accel_y = -1;
        data->jumping = 1;
        data->jumpingUp = 1;
        data->timer = nutJumpUpTime;
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
            data->timer = nutWaitBetweenJump;
        }
        
    }
    if (data->jumping)
    {
        if(SPRITE_GET_VMIRROR(THIS)) {
            //moving left
            if(TranslateSprite(THIS, -nutSpeed, 0)) {
                THIS->x = 210;
            } 
        } else {
            //moving right
            if(TranslateSprite(THIS, nutSpeed, 0)) {
                THIS->x = 210;
            } 
        }
    }
    data->wait = 1;
} 

void Destroy_SpriteBossBouncyNut() {
}
