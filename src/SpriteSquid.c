#include "Banks/SetBank2.h"
// #include "Keys.h"
#include "SpriteManager.h"
// #include "ZGBMain.h" // get access to sprite types, delta_time

const UINT8 anim_squid_up[] = {2, 0, 1};
const UINT8 anim_squid_down[] = {1, 1};

const INT8 squidDist = 64u;


struct EnemyInfo
{
    UINT8 wait;
    BYTE goingUp;
    INT8 dist;
};

void Start_SpriteSquid() {
    struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;

    data->wait = 0;
    data->goingUp = 1;
    data->dist = squidDist;

    THIS->coll_y = 2;
    THIS->coll_h = 14;
    THIS->coll_x = 3;
    THIS->coll_w = 13;

    SetSpriteAnim(THIS, anim_squid_up, 10u);
}

void Update_SpriteSquid() {
    struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
    
    if (data->wait == 2)
    {
        data->wait = 0;
        data->dist--;

        if (data->dist == 0)
        {
            data->goingUp = !data->goingUp;
            data->dist = squidDist;
        }

        if (data->goingUp)
        {
            SetSpriteAnim(THIS, anim_squid_up, 10u);
            if (TranslateSprite(THIS,0,-1))
            {
                data->goingUp = !data->goingUp;
                data->dist = squidDist;
            }
        }
        else
        {
            SetSpriteAnim(THIS, anim_squid_down, 15u);
            if (TranslateSprite(THIS,0,1))
            {
                data->goingUp = !data->goingUp;
                data->dist = squidDist;
            }
        }
    }
            

        data->wait ++;
} 

void Destroy_SpriteSquid() {
}
