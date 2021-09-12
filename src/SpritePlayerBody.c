#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "Scroll.h"
#include "ZGBMain.h" // get access to sprite types, delta_time
#include "Sound.h"

#include "../res/src/font.h"
#include "../res/src/window.h"
#include "Print.h"


void RestartLevel();
void QuitLevel();
BYTE PlayerDidNotDie;
void GetHurt();
void RefreshLife();

const UINT8 anim_playerBody_idle[] = {1, 0};   //first number is the number of animation frames
const UINT8 anim_playerBody_walk[] = {4, 1, 0, 2, 0};
const UINT8 anim_playerBody_jump[] = {1, 5};
const UINT8 anim_playerBody_attack[] = {2, 3, 3};

const UINT8 anim_playerHead_idle[] = {1, 0};   //first number is the number of animation frames
const UINT8 anim_playerHead_walk[] = {4, 0, 1, 2, 3};
const UINT8 anim_playerHead_attack[] = {1, 4}; 
const UINT8 anim_playerHead_jump[] = {1, 5}; 

struct Sprite* head_sprite;
struct Sprite* punch_sprite;

typedef enum  {
	PLAYER_STATE_NORMAL,
	PLAYER_STATE_JUMPING,
	PLAYER_STATE_ATTACK,
    PLAYER_STATE_STUNNED
}PLAYER_STATE;
PLAYER_STATE player_state;
INT16 player_accel_y;
UINT8 player_move_speed = 1;
UINT8 maxPlayerHealth = 2;
UINT8 playerHealth = 2;
BYTE collectKey;
UINT8 invincible = 0;
BYTE playerFacingRight = 0;
UINT8 punchDelay = 0;
extern BYTE textOnScreen;
//UINT8 jumpDelay = 0;

const UINT8 HEART_TILE = 2;
const UINT8 EMPTY_HEART_TILE = 1;

UINT8 tile_collision;
extern UINT8 Level;
extern UINT16 scroll_w;

void Start_SpritePlayerBody() {
    THIS->coll_x = 2;
    THIS->coll_y = -8;
    THIS->coll_w = 12;
    THIS->coll_h = 24;
    THIS->lim_y = 120u;

    //scroll_target = THIS;


    head_sprite = SpriteManagerAdd(SpritePlayerHead, THIS->x,THIS->y-16);
    punch_sprite = 0;

    player_accel_y = -1;
    player_state = PLAYER_STATE_NORMAL;

    if (Level == 10)
    {
        maxPlayerHealth = 4;
        playerHealth = maxPlayerHealth;
    }
    else
    {
        maxPlayerHealth = 2;
        playerHealth = 1;
    }
    

    if (Level != 0)
    {
        WX_REG = 7;
        WY_REG = 144-8;
        scroll_h_border = 2 << 2;
        InitWindow(0, 0, &window);
        SHOW_WIN;
        INIT_FONT(font, PRINT_WIN);

        RefreshLife();
    }

    PlayerDidNotDie = 0;
}

void CheckCollisionTile(struct Sprite* sprite, UINT8 idx) {
	if(tile_collision == 67u || tile_collision == 68u) {
		QuitLevel();
	} 
    else if (tile_collision == 90u) //spikes
    {
        RestartLevel();
    }
    else if (tile_collision == 88u)//extra heart
    {
        if (collectKey == 0)
        {
            collectKey = 1;
            playerHealth++;
            PlayFx(CHANNEL_1, 10, 0x4f, 0xc7, 0xf3, 0x73, 0x86);
            RefreshLife();
        }
    }
    // else if(tile_collision == 53u) {
	// 	if(level == 1) {
	// 		SetState(StateWin);
	// 	} else {
	// 		level ++;
	// 		reset_x = 32;
	// 		reset_y = 112;
	// 		SetState(StateGame);
	// 	}
	// }
}


void UpdatePunchPos() {
	punch_sprite->flags = THIS->flags;
	if(SPRITE_GET_VMIRROR(THIS)) 
    {
		punch_sprite->x = THIS->x - 16u;
    }
	else
    {
		punch_sprite->x = THIS->x + 16u; 
    }
	punch_sprite->y = THIS->y;
}


void Update_SpritePlayerBody() {
    UINT8 i;
    struct Sprite* spr;

    if (textOnScreen == 1)
    {
        return;
    }

    if (punchDelay != 0)
    {
        punchDelay--;
    }

    //delta time is used to prevent lag - if there's lag, speed will be multiplied by 2
	if (KEY_PRESSED(J_LEFT)) 
    {
        if (THIS->x > 0)
        {
            tile_collision = TranslateSprite(THIS, -player_move_speed, 0 << delta_time);
            CheckCollisionTile(THIS, THIS_IDX);
            SPRITE_SET_VMIRROR(THIS);
            //SetSpriteAnim(THIS, anim_playerBody_walk, 15);
        }
	}
	if (KEY_PRESSED(J_RIGHT)) 
    {
        if (THIS->x < scroll_w - 16)
        {
            tile_collision = TranslateSprite(THIS, player_move_speed, 0 << delta_time);
            CheckCollisionTile(THIS, THIS_IDX);
            SPRITE_UNSET_VMIRROR(THIS);
            //SetSpriteAnim(THIS, anim_playerBody_walk, 15);
        }
	}
    if(KEY_TICKED(J_B) && player_state != PLAYER_STATE_ATTACK) 
    {
        if (punchDelay == 0)
        {
            punchDelay = 30;
            SetSpriteAnim(THIS, anim_playerBody_attack, 10u);
            SetSpriteAnim(head_sprite,anim_playerHead_attack, 10u);
            player_state = PLAYER_STATE_ATTACK;

            punch_sprite = SpriteManagerAdd(SpritePunch, THIS->x, THIS->y);
            UpdatePunchPos();
        }
	}

    if(KEY_TICKED(J_SELECT))
    {
        QuitLevel();
    }


    switch (player_state)
    {
        case PLAYER_STATE_NORMAL:
// PRINT_POS(1, 0);
// Printf("norm");
            if(KEY_PRESSED(J_RIGHT) || KEY_PRESSED(J_LEFT) ) 
            {
				SetSpriteAnim(THIS, anim_playerBody_walk, 15u);
                SetSpriteAnim(head_sprite,anim_playerHead_walk, 15u);
			} 
            else 
            {
				SetSpriteAnim(THIS, anim_playerBody_idle, 15u);
                SetSpriteAnim(head_sprite,anim_playerHead_idle, 15u);
			}
// PRINT_POS(1, 0);
//Printf("GEMS:%d  ", (int) player_accel_y);

                if(KEY_TICKED(J_A)) 
                {
                    player_accel_y = -50;
                    player_state = PLAYER_STATE_JUMPING;
                } 

            

            //Check falling
            if((player_accel_y >> 4) > 1) 
            {
                player_state = PLAYER_STATE_JUMPING;
            }
            break;
        case PLAYER_STATE_JUMPING:
// PRINT_POS(1, 0);
// Printf("jump");
			SetSpriteAnim(THIS, anim_playerBody_jump, 33u);
            SetSpriteAnim(head_sprite,anim_playerHead_jump, 15u);
			//MovePrincess(THIS, THIS_IDX);
			break;
        case PLAYER_STATE_ATTACK:
// PRINT_POS(1, 0);
// Printf("attk");
			if(THIS->anim_frame == 1) {
				player_state = PLAYER_STATE_NORMAL;
				SpriteManagerRemoveSprite(punch_sprite);
			} else {
				//MovePrincess(THIS, THIS_IDX);
				UpdatePunchPos();
			}
			break;
        case PLAYER_STATE_STUNNED:
// PRINT_POS(1, 0);
// Printf("stun");
            
            if((player_accel_y) > 1 || TranslateSprite(THIS,(playerFacingRight?4:-4), player_accel_y)) 
            {
                player_state = PLAYER_STATE_JUMPING;
                player_accel_y = 0;
            }
            if (invincible == 0)
            {
                player_state =PLAYER_STATE_NORMAL;
            }
            break;
    
    default:
        break;
    }

    //Simple gravity physics 
	if(player_accel_y < 40) {
        player_accel_y += 2;
	}
	
    tile_collision = TranslateSprite(THIS, 0, player_accel_y >> 4);
	if(!tile_collision && delta_time != 0 && player_accel_y < 40) { //Do another iteration if there is no collision
			player_accel_y += 2;
			tile_collision = TranslateSprite(THIS, 0, player_accel_y >> 4);
	}
	if(tile_collision) {
		player_accel_y = 0;
		if(player_state == PLAYER_STATE_JUMPING) {
			player_state = PLAYER_STATE_NORMAL;
		}

		CheckCollisionTile(THIS, THIS_IDX);
	}

    

    head_sprite->flags = THIS->flags;
    head_sprite-> x = THIS->x;
    head_sprite-> y = THIS->y-16;

    if(invincible != 0)
    {
		invincible -= 1;
		if(invincible < 1) {
			invincible = 0;
//            SPRITE_SET_PALETTE(head_sprite, 1);
        }
    }
    else
    {
        //check for sprite collisions if not invincible
        SPRITEMANAGER_ITERATE(i,spr) //iterates over active sprites
        {
            if (spr->type == SpriteHedgehog || spr->type == SpriteSkunk || spr->type == SpriteSlime || spr->type == SpriteBee || spr->type == SpriteBossBody || spr->type == SpriteBossLaser || spr->type == SpriteBossBouncyNut || spr->type == SpriteBossScrew || spr->type == SpriteCrab || spr->type == SpriteFish || spr->type == SpriteSquid || spr->type == SpriteWaterSlime)
            {
                if (CheckCollision(THIS,spr))
                {
                    GetHurt();
                }
            }
            else if (spr->type == SpriteBossWin)
            {
                if (CheckCollision(THIS,spr))
                {
                    QuitLevel();
                }
            }

        }
    }
} 

void Destroy_SpritePlayerBody() {
    if (PlayerDidNotDie == 0)
    {
        RestartLevel();
    }
}

void GetHurt()
{
    SpriteManagerRemoveSprite(punch_sprite);
    if (invincible == 0)
    {
        if (playerHealth != 0)
        {
            playerHealth -= 1;
        }
    }
    if (playerHealth == 0)// || playerHealth > 100)
    {
        RestartLevel();
        RefreshLife();
    }
    else
    {
        invincible = 60;
        player_state = PLAYER_STATE_STUNNED;
        playerFacingRight = SPRITE_GET_VMIRROR(THIS); 
        player_accel_y = -6;
        RefreshLife();
        //SPRITE_SET_PALETTE(head_sprite, 2);
        PlayFx(CHANNEL_1, 10, 0x4f, 0xc7, 0xf3, 0x73, 0x86);
    }
}


void RefreshLife() {
	UINT8 i;
    //PRINT_POS(6, 0);
    //Printf("HP:%d  ", (int) playerHealth);

    for(i = 0; i != maxPlayerHealth; ++i) {
		set_win_tiles(2 + i, 0, 1, 1, &EMPTY_HEART_TILE);
	}
	for(i = 0; i != playerHealth; ++i) {
		set_win_tiles(2 + i, 0, 1, 1, &HEART_TILE);
	}
	
}

void RestartLevel()
{
    PlayerDidNotDie = 1;
    PlayFx(CHANNEL_1, 10, 0x4f, 0xc7, 0xf3, 0x73, 0x86);
    collectKey = FALSE;
    SetState(StateGame);
}

void QuitLevel()
{
    PlayerDidNotDie = 1;
    collectKey = FALSE;
    Level = 0; // map
    SetState(StateGame);
}