#include "Banks/SetBank2.h"
// #include "Keys.h"
#include "SpriteManager.h"
// #include "ZGBMain.h" // get access to sprite types, delta_time

const UINT8 anim_bee_idle[] = {2, 0, 1};

const INT8 beeDist = 8u * 6u;


struct EnemyInfo
{
    UINT8 wait;
    BYTE goingUp;
    INT8 dist;
};

void Start_SpriteBee() {
    struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;

    data->wait = 0;
    data->goingUp = 1;
    data->dist = beeDist;

    THIS->coll_x = 2;
    THIS->coll_w = 12;
    THIS->lim_y = 64u;

    SetSpriteAnim(THIS, anim_bee_idle, 15u);
}

void Update_SpriteBee() {
    struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
    
    if (data->wait == 2)
    {
        data->wait = 0;
        data->dist--;

        if (data->dist == 0)
        {
            data->goingUp = !data->goingUp;
            data->dist = beeDist;
        }

        if (data->goingUp)
        {
            if (TranslateSprite(THIS,0,-1))
            {
                data->goingUp = !data->goingUp;
                data->dist = beeDist;
            }
        }
        else
        {
            if (TranslateSprite(THIS,0,1))
            {
                data->goingUp = !data->goingUp;
                data->dist = beeDist;
            }
        }
    }
            

        data->wait ++;
} 

void Destroy_SpriteBee() {
}
