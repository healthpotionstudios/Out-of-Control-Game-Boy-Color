#include "Banks/SetBank2.h"
#include "Sound.h"
#include "SpriteManager.h"
//#include "ZGBMain.h" //sprite types

// void UpdateInfo(INT8 mx, INT8 my);

struct LaserInfo
{
    INT8 x;
    INT8 y;
    UINT8 wait;
    UINT8 wait2;
    BYTE flip;  
};

void Start_SpriteBossLaser() {
    struct LaserInfo* data = (struct LaserInfo*)THIS->custom_data;
    data->wait = 0;
    data->wait2 = 0;
    data->flip = 0;

    THIS->coll_x = 4;
    THIS->coll_y = 4;
    THIS->coll_w = 8;
    THIS->coll_h = 8;
}

void Update_SpriteBossLaser() {
    struct LaserInfo* data = (struct LaserInfo*)THIS->custom_data;
    if (data->wait == 0)
    {
        THIS->x += data->x;
        THIS->y += data->y;
        data->wait = 1;
        data->flip = !data->flip;
        if (data->wait2 == 0)
        {
            if (data->flip)
            {
                SPRITE_SET_VMIRROR(THIS);
            }
            else
            {
                SPRITE_UNSET_VMIRROR(THIS);
            }
            data->wait2 = 2;
        }
        else
        {
            data->wait2--;
        }
        
        
    }
    else
    {
        data->wait--;
    }
    
}

void Destroy_SpriteBossLaser() {
}


// void UpdateInfo(INT8 mx, INT8 my)
// {
//     struct LaserInfo* data = (struct LaserInfo*)THIS->custom_data;
//     data->x = mx;
//     data->y = my;

// }