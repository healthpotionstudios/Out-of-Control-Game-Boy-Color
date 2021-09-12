#include "Banks/SetBank2.h"
#include "SpriteManager.h"
#include "ZGBMain.h" //delta_time
#include "Sound.h"

struct EnemyInfo
{
    INT8 vy;
};


void Start_SpriteEnemy() {  
    struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
    data->vy = 1;
}

void Update_SpriteEnemy() {
    struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	if (TranslateSprite(THIS, 0, data->vy << delta_time))
    {
		data->vy = -data->vy;
        PlayFx(CHANNEL_4, 4, 0x0c, 0x41, 0x30, 0xc0);
	}
}

void Destroy_SpriteEnemy() {
}