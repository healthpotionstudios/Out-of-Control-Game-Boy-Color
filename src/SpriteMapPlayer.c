#include "Banks/SetBank2.h"
#include "Keys.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "ZGBMain.h"

extern UINT8 Level;
extern UINT8 mapPos;


const UINT8 anim_playerMap_idle[] = {1, 0};   //first number is the number of animation frames
const UINT8 anim_playerMap_walkDown[] = {4, 0, 1, 0, 2};
const UINT8 anim_playerMap_walkUp[] = {4, 3, 4, 3, 5};
const UINT8 anim_playerMap_walkSide[] = {4, 6, 7, 6, 8};

const UINT8 mapPoints[] = {5,4, 5,12, 15,12, 15,6, 23,6, 29,6, 34,6, 34,10, 40,10, 51,10};
// 0 none   1 up   2 right   3 down   4 left
const UINT8 mapExits[] = {0,3, 1,2, 4,1, 3,2, 4,2, 4,2, 4,3, 1,2, 4,2, 4,0};

INT8 offset = -12;

BYTE isWalking = 0;
UINT8 dir = 0;

void Start_SpriteMapPlayer() {
    SetSpriteAnim(THIS, anim_playerMap_idle, 15u);
    THIS->x = mapPoints[2 * mapPos] * 8;
    THIS->y = mapPoints[2 * mapPos + 1] * 8 + offset;

    
}

void Update_SpriteMapPlayer() {
    
    if (!isWalking)
    {
        if (KEY_TICKED(J_UP))
        {
            if (mapExits[2 * mapPos] == 1) // previous
            {
                mapPos--;
                dir = 1;
                SetSpriteAnim(THIS, anim_playerMap_walkUp, 15u);
            }
            else if (mapExits[2 * mapPos + 1] == 1) //next 
            {
                mapPos++;
                dir = 1;
                SetSpriteAnim(THIS, anim_playerMap_walkUp, 15u);
            }
        }
        else if (KEY_TICKED(J_RIGHT))
        {
            if (mapPos == 9)
            {
                mapPos = 0;
                SetState(StateGame);
            }
            else
            {
                if (mapExits[2 * mapPos] == 2) // previous
                {
                    mapPos--;
                    dir = 2;
                    SPRITE_UNSET_VMIRROR(THIS);
                    SetSpriteAnim(THIS, anim_playerMap_walkSide, 15u);
                }
                else if (mapExits[2 * mapPos + 1] == 2) //next 
                {
                    mapPos++;
                    dir = 2;
                    SPRITE_UNSET_VMIRROR(THIS);
                    SetSpriteAnim(THIS, anim_playerMap_walkSide, 15u);
                }
            }
        }
        else if (KEY_TICKED(J_DOWN))
        {
            if (mapExits[2 * mapPos] == 3) // previous
            {
                mapPos--;
                dir = 3;
                SetSpriteAnim(THIS, anim_playerMap_walkDown, 15u);
            }
            else if (mapExits[2 * mapPos + 1] == 3) //next 
            {
                mapPos++;
                dir = 3;
                SetSpriteAnim(THIS, anim_playerMap_walkDown, 15u);
            }
        }
        else if (KEY_TICKED(J_LEFT))
        {
            if (mapPos == 0)
            {
                mapPos = 9;
                SetState(StateGame);
            }
            else
            {
                if (mapExits[2 * mapPos] == 4) // previous
                {
                    mapPos--;
                    dir = 4;
                    SPRITE_SET_VMIRROR(THIS);
                    SetSpriteAnim(THIS, anim_playerMap_walkSide, 15u);
                }
                else if (mapExits[2 * mapPos + 1] == 4) //next 
                {
                    mapPos++;
                    dir = 4;
                    SPRITE_SET_VMIRROR(THIS);
                    SetSpriteAnim(THIS, anim_playerMap_walkSide, 15u);
                }
            }
        }
        else if (KEY_TICKED(J_A))
        {
            //start a level
            Level = mapPos + 1;
            SetState(StateGame);
        }
    }

    if (dir != 0)
    {
        isWalking = 1;
    }

    if (isWalking)
    {
        if (dir == 1)
        {
            TranslateSprite(THIS,0,-1);
        }
        else if (dir == 2)
        {
            TranslateSprite(THIS,1,0);
        }
        else if (dir == 3)
        {
            TranslateSprite(THIS,0,1);
        }
        else if (dir == 4)
        {
            TranslateSprite(THIS,-1,0);
        }

        if (THIS->x == mapPoints[2 * mapPos] * 8 && THIS->y == mapPoints[2 * mapPos + 1] * 8 + offset)
        {
            isWalking = 0;
            dir = 0;
            SetSpriteAnim(THIS, anim_playerMap_idle, 15u);
        }
        
    }

    //THIS->x = mapPoints[2 * mapPos] * 8;
    //THIS->y = mapPoints[2 * mapPos + 1] * 8 + offset;
    
} 

void Destroy_SpriteMapPlayer() {
    //SetState(StateGame);
}

