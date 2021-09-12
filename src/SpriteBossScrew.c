#include "Banks/SetBank2.h"
#include "Sound.h"
#include "SpriteManager.h"
#include "ZGBMain.h" //sprite types

// void UpdateInfo(INT8 mx, INT8 my);

struct ScrewInfo
{
    UINT8 wait;
    BYTE falling; 
    UINT8 timer;
};


void Start_SpriteBossScrew() {
    struct ScrewInfo* data = (struct ScrewInfo*)THIS->custom_data;
    data->wait = 0;
    data->falling = 0;
    data->timer = 0;

    THIS->coll_x = 4;
    THIS->coll_y = 4;
    THIS->coll_w = 8;
    THIS->coll_h = 8;

    THIS->lim_x = 100u;
    THIS->lim_y = 400u;
    

    SPRITE_SET_HMIRROR(THIS);
}

void Update_SpriteBossScrew() {
    struct ScrewInfo* data = (struct ScrewInfo*)THIS->custom_data;
    if (data->wait == 0)
    {
        //THIS->x += data->x;
        if (!data->falling)
        {
            THIS->y -= 5;
        }
        else
        {
            THIS->y += 2;
        }
        
        data->wait = 1;
        
        if (THIS->y > 240 && !data->falling)
        {
            data->timer++;
        }

        if (THIS->y > 150 && THIS->y < 160)
        {
            THIS->x = 240;
        }

        if (data->timer == 30)
        {
            THIS->x = (rand()&176) + 8;
            data->timer = 35;
            data->falling = 1;
            SPRITE_UNSET_HMIRROR(THIS);
        }
        
        
    }
    else
    {
        data->wait--;
    }
    
}

void Destroy_SpriteBossScrew() {
}
