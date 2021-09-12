#include "Banks/SetBank7.h"
#include "SpriteManager.h"
#include "Scroll.h"
#include "Sprite.h"
#include "ZGBMain.h" // get access to sprite types, delta_time
#include "Palette.h"
#include "Sound.h"

//#include "Print.h"


#include "Keys.h"

void RefreshLifeBar();
void BossHurt();
UINT8 GetGridPosX(UINT16 x);
UINT8 GetPlayerY();
void InitLaser();
void InitBouncyNuts();
void InitScrews();
void SetRand();
void SetAttack();
void Attack();


struct Sprite* bodyU_sprite;
struct Sprite* bodyUL_sprite;
struct Sprite* bodyL_sprite;

struct Sprite* player_sprite;


UINT8 bossHealth;
UINT8 bossHealthMax = 20; //20

UINT8 bossinvincible = 0;

const unsigned char doorTiles[] = {65,66,67,68,69,70};

INT8 r = 0;
INT8 attackID = 0;
BYTE attackPrep;
INT8 attackDelay=0;
UINT8 attacksLeft=0;
UINT8 lastAttack = 0;

const UINT8 leftBarEmptyTile = 3;
const UINT8 midBarEmptyTile = 4;
const UINT8 rightBarEmptyTile = 5;
const UINT8 leftBarFullTile = 6;
const UINT8 midBarFullTile = 7;
const UINT8 rightBarFullTile = 8;

extern void BossPaletteSwap(BYTE);



//const UINT8 anim_hedgehog_walk[] = {2, 0, 1};
struct EnemyInfo
{
    UINT8 wait;
};

struct LaserInfo
{
    INT8 x;
    INT8 y;
};

struct NutInfo
{
    BYTE wait, jumping, jumpingUp;
    UINT8 timer;
    INT8 accel_y;
};


void Start_SpriteBossFace() {
    struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
    data->wait = 0;
    THIS->lim_y = 120u;
    //SetSpriteAnim(THIS, anim_hedgehog_walk, 15u);

    attacksLeft=0;
    lastAttack = 0;
    attackDelay=0;
    attackPrep = 0;

    bodyU_sprite = SpriteManagerAdd(SpriteBossBody, THIS->x, THIS->y);
    SET_FRAME(bodyU_sprite, (UINT8)0u);

    bodyUL_sprite = SpriteManagerAdd(SpriteBossBody, THIS->x, THIS->y);
    SET_FRAME(bodyUL_sprite, (UINT8)1u);

    bodyL_sprite = SpriteManagerAdd(SpriteBossBody, THIS->x, THIS->y);
    SET_FRAME(bodyL_sprite, (UINT8)2u);

    bossHealth = bossHealthMax;
    RefreshLifeBar();

    SetRand();

    SPRITE_SET_VMIRROR(THIS);


    UINT8 i;
	struct Sprite* spr;

	SPRITEMANAGER_ITERATE(i, spr) {
		if(spr->type == SpritePlayerBody) {
			player_sprite = spr;
		}
	}
}

void Update_SpriteBossFace() {

    if (KEY_TICKED(J_START))
    {
        InitLaser();
    }

    struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
    UINT8 i;
    struct Sprite* spr;

    if (bossHealth == 0)
    {
        SpriteManagerAdd(SpriteStars, THIS->x, THIS->y);
        SpriteManagerAdd(SpriteStars, bodyU_sprite->x, bodyU_sprite->y);
        SpriteManagerAdd(SpriteStars, bodyUL_sprite->x, bodyUL_sprite->y);
        SpriteManagerAdd(SpriteStars, bodyL_sprite->x, bodyL_sprite->y);
        PlayFx(CHANNEL_1, 10, 0x4f, 0xc7, 0xf3, 0x73, 0x86);
        set_bkg_tiles(5,9,2,3,doorTiles);
        SpriteManagerAdd(SpriteBossWin, 5*8, 10*8);

        THIS->x = 240;
        bodyU_sprite->x = THIS->x;
        bodyUL_sprite->x = THIS->x;
        bodyL_sprite->x = THIS->x;
    }

    if (attackPrep == 0)
    {
        if (data->wait == 0)
        {
            if(SPRITE_GET_VMIRROR(THIS)) {
                //moving left
                if(TranslateSprite(THIS, -1, 0)) {
                    SPRITE_UNSET_VMIRROR(THIS);
                    THIS->x = THIS->x + 16;
                } 
            } else {
                //moving right
                if(TranslateSprite(THIS, +1, 0)) {
                    SPRITE_SET_VMIRROR(THIS);
                    THIS->x = THIS->x - 16;
                } 
            }
            if(!SPRITE_GET_VMIRROR(THIS))
            {
                bodyU_sprite->flags = THIS->flags;
                bodyU_sprite->x = THIS->x;
                bodyU_sprite->y = THIS->y - 16;
                
                bodyUL_sprite->flags = THIS->flags;
                bodyUL_sprite->x = THIS->x - 16;
                bodyUL_sprite->y = THIS->y - 16;
                
                bodyL_sprite->flags = THIS->flags;
                bodyL_sprite->x = THIS->x - 16;
                bodyL_sprite->y = THIS->y;
            }
            else
            {
                bodyU_sprite->flags = THIS->flags;
                bodyU_sprite->x = THIS->x;
                bodyU_sprite->y = THIS->y - 16;
                
                bodyUL_sprite->flags = THIS->flags;
                bodyUL_sprite->x = THIS->x + 16;
                bodyUL_sprite->y = THIS->y - 16;
                
                bodyL_sprite->flags = THIS->flags;
                bodyL_sprite->x = THIS->x + 16;
                bodyL_sprite->y = THIS->y;
            }
            
            if (r == 0)
            {
                attackPrep = 1;
                attackDelay = 30;
                SetAttack();
            }
            else
            {
                r--;
            }
            

            data->wait = 2;
        }
        else
        {
            data->wait--;
        }
    }
    else //is preping attack
    {
        attackDelay--;
        if (attackDelay == 0)
        {
            attackPrep = 0;
            Attack();
        }

    }
    

    if(bossinvincible != 0)
    {
		bossinvincible -= 1;
		if(bossinvincible < 1) {
			bossinvincible = 0;
            BossPaletteSwap(0);

        }
    }
    else
    {
        //check for sprite collisions if not invincible
        SPRITEMANAGER_ITERATE(i,spr) //iterates over active sprites
        {
            if (spr->type == SpritePunch)
            {
                if (CheckCollision(THIS,spr))
                {
                    BossHurt();
                }
            }

        }
    }
    

    //PRINT_POS(8, 0);
    //Printf("P%d,%d B%d", GetGridPosX(player_sprite->x), GetPlayerY(), GetGridPosX(THIS->x));
    //Printf("r:%d  ",r);


} 

void Destroy_SpriteBossFace() {
}

void BossHurt()
{
    bossHealth--;
    BossPaletteSwap(1);
    bossinvincible = 30;
    RefreshLifeBar();
}


void RefreshLifeBar() {
	UINT8 i;
    
    //3-5 empty bar
    //6-8 filled bar

    if (bossHealth == 0)
    {
        set_win_tiles(10, 0, 1, 1, &leftBarEmptyTile);
    }
    else
    {
        set_win_tiles(10, 0, 1, 1, &leftBarFullTile);
    }
    for(i = 1; i != 7; ++i)
    {
        if (bossHealthMax/8*i >= bossHealth )
        {
            set_win_tiles(10+i, 0, 1, 1, &midBarEmptyTile);
        }
        else
        {
            set_win_tiles(10+i, 0, 1, 1, &midBarFullTile);
        }
    }
    if (bossHealthMax/8*7 >= bossHealth )
    {
        set_win_tiles(17, 0, 1, 1, &rightBarEmptyTile);
    }
    else
    {
        set_win_tiles(17, 0, 1, 1, &rightBarFullTile);
    }

}

UINT8 GetGridPosX(UINT16 x)
{
    if (0 < x && x <= 48)
    {
        return 1;
    }
    if (48 < x && x <= 96)
    {
        return 2;
    }
    if (96 < x && x <= 144)
    {
        return 3;
    }
    if (144 < x && x <= 240)
    {
        return 4;
    }
    return 0;
}

UINT8 GetPlayerY()
{
    if (117 < player_sprite->y)
    {
        return 4;
    }
    if (89 < player_sprite->y && player_sprite->y <= 117)
    {
        return 3;
    }
    if (68 < player_sprite->y && player_sprite->y <= 89)
    {
        return 2;
    }
    if (0 < player_sprite->y && player_sprite->y <= 68)
    {
        return 1;
    }
    return 0;
}

void SetRand()
{
    r = (rand()&40) + 40;
}

void SetAttack()
{
    UINT8 px = GetGridPosX(player_sprite->x);
    UINT8 py = GetPlayerY();
    UINT8 bx = GetGridPosX(THIS->x);

    if (py == 1 || py == 2 && lastAttack != 3)
    {
        attackID = 3; //screw
        attacksLeft = 4;
        lastAttack = 3;
    }
    else if ((SPRITE_GET_VMIRROR(THIS) && bx > 1 || !SPRITE_GET_VMIRROR(THIS) && bx < 4) && lastAttack != 2)
    {
        attackID = 2; //bouncy nuts
        attacksLeft = 3;
        lastAttack = 2;
        SET_FRAME(THIS, (UINT8)1u);
    }
    else
    {
        attackID = 1; //laser
        // if (bossHealthMax/2 < bossHealth)
        // {
        //     attacksLeft = 1; //based on HP?
        // }
        // else
        // {
        //     attacksLeft = 3; //based on HP?
        // }
        if (py == 4) //grounded
        {
            attacksLeft = 2;
        }
        else
        {
            attacksLeft = 3;
        }
        
        lastAttack = 1;
    }
}

void Attack()
{
    SetRand(); //if this gets called 3 times, who cares
    if (attackID == 0) //delay at the end
    {
        attacksLeft = 0;
        attackPrep = 0;
    }
    if (attackID == 1)
    {
        InitLaser();
    }
    else if (attackID == 2)
    {
        InitBouncyNuts();
    }
    else if (attackID == 3)
    {
        InitScrews();
    }

}

void InitLaser()
{
    PlayFx(CHANNEL_1, 10, 0x4f, 0xc7, 0xf3, 0xf3, 0x86);
    struct Sprite* laser = SpriteManagerAdd(SpriteBossLaser, THIS->x, THIS->y);
    struct LaserInfo* laserdata = (struct LaserInfo*)laser->custom_data;

    laserdata->x = GetGridPosX(player_sprite->x) - GetGridPosX(THIS->x);   
    laserdata->y = GetPlayerY() - 4;

    if (laserdata->x == 0 && laserdata->y == 0)
    {
        if (player_sprite->x < THIS->x)
        {
            laserdata->x = -1;
        }
        else
        {
            laserdata->x = 1;
        }
        
        laserdata->y = -1;
    }


    attacksLeft--;
    if (attacksLeft != 0)
    {
        attackDelay = 20;
        attackPrep = 1;
    }
    else
    {
        attackDelay = 45;
        attackPrep = 1;
        attackID = 0;
        attacksLeft = 1;
    }
    
}

void InitBouncyNuts()
{
    PlayFx(CHANNEL_1, 10, 0x4f, 0xc7, 0xf3, 0x33, 0x86);
    struct Sprite* nut = SpriteManagerAdd(SpriteBossBouncyNut, THIS->x, THIS->y);
    // struct NutInfo* nutdata = (struct NutInfo*)laser->custom_data;

    // nutdata->x = 
    // nutdata->y = 

    if (SPRITE_GET_VMIRROR(THIS))
    {
        SPRITE_SET_VMIRROR(nut);
    }


    attacksLeft--;
    if (attacksLeft != 0)
    {
        attackDelay = 80;
        attackPrep = 1;
    }
    else
    {
        SET_FRAME(THIS, (UINT8)0u);
        attackDelay = 65;
        attackPrep = 1;
        attackID = 0;
        attacksLeft = 1;
    }
}

void InitScrews()
{
    PlayFx(CHANNEL_1, 10, 0x4f, 0xc7, 0xf3, 0x23, 0x86);
    SpriteManagerAdd(SpriteBossScrew, THIS->x, THIS->y);

    attacksLeft--;
    if (attacksLeft != 0)
    {
        attackDelay = 60;
        attackPrep = 1;
    }
    else
    {
        attackDelay = 120;
        attackPrep = 1;
        attackID = 0;
        attacksLeft = 1;
    }
}