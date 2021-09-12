#include "Banks/SetBank7.h"

#include "..\res\src\tiles.h"
#include "..\res\src\maptiles.h"
#include "..\res\src\level1.h"
#include "..\res\src\level2.h"
#include "..\res\src\level3.h"
#include "..\res\src\level4.h"
#include "..\res\src\level5.h"
#include "..\res\src\level6.h"
#include "..\res\src\level7.h"
#include "..\res\src\level8.h"
#include "..\res\src\level9.h"
#include "..\res\src\worldMap.h"
#include "..\res\src\levelBoss.h"

#include "../res/src/font.h"
#include "../res/src/windowTextBox.h"
#include "Print.h"
#include "string.h"
#include "Sound.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Keys.h"

#include "../res/src/playerBody.h" //used for palettes
#include "../res/src/playerHead.h" //used for palettes

#include "../res/src/profcroak.h"

#include "../res/src/hedgehog.h"
#include "../res/src/skunk.h"
#include "../res/src/slime.h"
#include "../res/src/bee.h"
#include "../res/src/stars.h"

#include "../res/src/crab.h"
#include "../res/src/fish.h"
#include "../res/src/squid.h"
#include "../res/src/waterslime.h"

#include "../res/src/bossFace.h"
#include "../res/src/bossLaser.h"
#include "../res/src/bossNut.h"
#include "../res/src/bossScrew.h"

#include "../res/src/playerMap.h"

#include "Palette.h"

extern UINT8 Level;

UINT8 printLimit = 0;
BYTE usePrintLimit = 0;
UINT8 lineNum = 1;
UINT8 charPos = 0;
const char* currentLine;
UINT8 wait;
BYTE textOnScreen;
const BYTE whoIsTalking[] = {0,0,0,1,1,1,1,1,0,0,0,0,1,0,0};
const char roscoe[] = "Roscoe";    //1
const char croak[] = "Prof Croak"; //0
const char line1[] = "Welcome to out\nof control";
const char line2[] = "for gameboy\ncolor.";
const char line3[] = "I don't want to\nseem ungrateful";
const char line4[] = "but you took out\nsome of the";
const char line5[] = "best features.\nthe controls";
const char line6[] = "aren't random\nand i can't";
const char line7[] = "even wall jump.";
const char line8[] = "Roscoe you\nunderstand that";
const char line9[] = "i am not working\nwith much";
const char line10[] = "power here\nright?";
const char line11[] = "gameboy is hard";
const char line12[] = "Sorry...";
const char line13[] = "anyways go\nfight the boss";
const char line14[] = "also 'select'\nwill quit levels";


const UINT16 bg_palette[] = {PALETTE_FROM_HEADER(tiles)}; //file name
const UINT16 map_bg_palette[] = {PALETTE_FROM_HEADER(maptiles)}; //file name

const UINT16 grass_story_palette[] = {
	PALETTE_INDEX(playerBody, 0), //body
	PALETTE_INDEX(playerHead, 1), //head
	PALETTE_INDEX(playerBody, 2), //body - punch
	PALETTE_INDEX(hedgehog, 3),
	PALETTE_INDEX(profcroak, 4),
	PALETTE_INDEX(slime, 5),
    PALETTE_INDEX(slime, 5),
	PALETTE_INDEX(stars, 7),
};

const UINT16 grass_sprites_palette[] = {
	PALETTE_INDEX(playerBody, 0), //body
	PALETTE_INDEX(playerHead, 1), //head
	PALETTE_INDEX(playerBody, 2), //body - punch
	PALETTE_INDEX(hedgehog, 3),
	PALETTE_INDEX(skunk, 4),
	PALETTE_INDEX(slime, 5),
	PALETTE_INDEX(bee, 6),
	PALETTE_INDEX(stars, 7),
};

const UINT16 beach_palette[] = {
	PALETTE_INDEX(playerBody, 0), //body
	PALETTE_INDEX(playerHead, 1), //head
	PALETTE_INDEX(playerBody, 2), //body - punch
	PALETTE_INDEX(hedgehog, 3),
	PALETTE_INDEX(fish, 4),
	PALETTE_INDEX(slime, 5),
	PALETTE_INDEX(squid, 6),
	PALETTE_INDEX(stars, 7),
};

const UINT16 underwater_palette[] = {
	PALETTE_INDEX(playerBody, 0), //body
	PALETTE_INDEX(playerHead, 1), //head
	PALETTE_INDEX(playerBody, 2), //body - punch
	PALETTE_INDEX(crab, 3),
	PALETTE_INDEX(fish, 4),
	PALETTE_INDEX(waterslime, 5),
	PALETTE_INDEX(squid, 6),
	PALETTE_INDEX(stars, 7),
};

const UINT16 boss_palette[] = {
	PALETTE_INDEX(playerBody, 0), //body
	PALETTE_INDEX(playerHead, 1), //head
	PALETTE_INDEX(playerBody, 2), //body - punch
    PALETTE_INDEX(bossFace, 3),
    PALETTE_INDEX(bossLaser, 4),
    PALETTE_INDEX(bossNut, 5),
    PALETTE_INDEX(bossScrew, 5),
    PALETTE_INDEX(stars, 7),
};

const UINT16 boss_hurt_palette[] = {
	PALETTE_INDEX(playerBody, 0), //body
	PALETTE_INDEX(playerHead, 1), //head
	PALETTE_INDEX(playerBody, 2), //body - punch
    PALETTE_INDEX(bossFace, 2), //use red palette
    PALETTE_INDEX(bossLaser, 4),
    PALETTE_INDEX(bossNut, 5),
    PALETTE_INDEX(bossScrew, 5),
    PALETTE_INDEX(stars, 7),
};

const UINT16 map_palette[] = {
	PALETTE_INDEX(playerMap, 0), //player
};

const UINT8 collision_tiles[] = {1,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,67,78,79,80,81,88,90, 0}; //collides with tile 1 - MUST END IN ZERO
const UINT8 bottom_collision_tiles[] = {91,92,93,94,95,96,97,98,99, 0}; //collides with tile 1 - MUST END IN ZERO
const UINT8 map_collision_tiles[] = {0};

//                               0    1     2     3     4     5     6     7     8      9    10
const UINT8 startPositions[] = {0,0, 4,13, 2,14, 1,13, 1,11, 1,17, 1,16, 1,18, 4,47, 10,6, 5,15};

extern UINT8* level_mod_Data[];
extern UINT8* boss_mod_Data[];
extern UINT8* map_mod_Data[];

void InitTextBox();
void CloseTextBox();
void ClearTextBoxAndAddName(char name[]);
void ShowTextInBox(const char text[]);
void Custom_Printf(const char* txt, ...);


void Start_StateGame() {
	//UINT8 i;
    // for(i = 0; i != N_SPRITE_TYPES; ++ i) {
    //     SpriteManagerLoad(i);
    // }

    NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
    NR50_REG = 0x77; //Max volume


    if (Level == 0) //map
    {
        SPRITES_8x16;

        SpriteManagerLoad(20); //map player

        

        SetPalette(BG_PALETTE, 0, 8, map_bg_palette, bank_StateGame);
        SetPalette(SPRITES_PALETTE, 0, 8, map_palette, bank_StateGame);

        scroll_target = SpriteManagerAdd(SpriteMapPlayer, 6*8, 10*8); //add player at specific position

        InitScroll(&worldMap, map_collision_tiles, 0); ///first argument is the level to load

        SHOW_BKG;
        SHOW_SPRITES;
        HIDE_WIN;

        PlayMusic(map_mod_Data,4,1);    //level music
    }
    else if (Level == 1) //intro story
    {
		SPRITES_8x16;
        SpriteManagerLoad(0); //playerBody
        SpriteManagerLoad(1); //playerHead
        SpriteManagerLoad(2); //Punch

        SpriteManagerLoad(3); //Hedgehog
        SpriteManagerLoad(5); //Slime
        
        SpriteManagerLoad(21); //prof croak
        
        SpriteManagerLoad(7); //stars

        SHOW_SPRITES;

        scroll_target = SpriteManagerAdd(SpritePlayerBody, startPositions[2 * Level]*8, startPositions[2 * Level + 1]*8); //add player at specific position
        InitScroll(&level1, collision_tiles, bottom_collision_tiles); ///first argument is the level to load

        SetPalette(BG_PALETTE, 0, 8, bg_palette, bank_StateGame);
        SetPalette(SPRITES_PALETTE, 0, 8, grass_story_palette, bank_StateGame);

        SHOW_BKG;

        PlayMusic(level_mod_Data,4,1);    //level music


        //run text boxes
        lineNum = 1;
        charPos = 0;
        textOnScreen = 1;
        currentLine = line1;
        InitTextBox();
        usePrintLimit = 1;
        printLimit = 0;
        ClearTextBoxAndAddName(croak);
	}
    else if (Level == 2)
    {
		SPRITES_8x16;
        SpriteManagerLoad(0); //playerBody
        SpriteManagerLoad(1); //playerHead
        SpriteManagerLoad(2); //Punch

        SpriteManagerLoad(3); //Hedgehog
        SpriteManagerLoad(4); //Skunk
        SpriteManagerLoad(5); //Slime
        SpriteManagerLoad(6); //bee

        SpriteManagerLoad(7); //stars

        SHOW_SPRITES;

scroll_target = SpriteManagerAdd(SpritePlayerBody, startPositions[2 * Level]*8, startPositions[2 * Level + 1]*8); //add player at specific position
        InitScroll(&level2, collision_tiles, bottom_collision_tiles); ///first argument is the level to load

        SetPalette(BG_PALETTE, 0, 8, bg_palette, bank_StateGame);
        SetPalette(SPRITES_PALETTE, 0, 8, grass_sprites_palette, bank_StateGame);

        SHOW_BKG;

        PlayMusic(level_mod_Data,4,1);    //level music
	}
    else if (Level == 3)
    {
		SPRITES_8x16;
        SpriteManagerLoad(0); //playerBody
        SpriteManagerLoad(1); //playerHead
        SpriteManagerLoad(2); //Punch

        SpriteManagerLoad(3); //Hedgehog
        SpriteManagerLoad(4); //Skunk
        SpriteManagerLoad(5); //Slime
        SpriteManagerLoad(6); //bee

        SpriteManagerLoad(7); //stars

        SHOW_SPRITES;

scroll_target = SpriteManagerAdd(SpritePlayerBody, startPositions[2 * Level]*8, startPositions[2 * Level + 1]*8); //add player at specific position
        InitScroll(&level3, collision_tiles, bottom_collision_tiles); ///first argument is the level to load

        SetPalette(BG_PALETTE, 0, 8, bg_palette, bank_StateGame);
        SetPalette(SPRITES_PALETTE, 0, 8, grass_sprites_palette, bank_StateGame);

        SHOW_BKG;

        PlayMusic(level_mod_Data,4,1);    //level music
	}
    else if (Level == 4)
    {
		SPRITES_8x16;
        SpriteManagerLoad(0); //playerBody
        SpriteManagerLoad(1); //playerHead
        SpriteManagerLoad(2); //Punch

        SpriteManagerLoad(3); //Hedgehog
        SpriteManagerLoad(23); //fish
        SpriteManagerLoad(24); //squid
        SpriteManagerLoad(5); //slime

        SpriteManagerLoad(7); //stars

        SHOW_SPRITES;

scroll_target = SpriteManagerAdd(SpritePlayerBody, startPositions[2 * Level]*8, startPositions[2 * Level + 1]*8); //add player at specific position
        InitScroll(&level4, collision_tiles, bottom_collision_tiles); ///first argument is the level to load

        SetPalette(BG_PALETTE, 0, 8, bg_palette, bank_StateGame);
        SetPalette(SPRITES_PALETTE, 0, 8, beach_palette, bank_StateGame);

        SHOW_BKG;

        PlayMusic(level_mod_Data,4,1);    //level music
	}
    else if (Level == 5)
    {
		SPRITES_8x16;
        SpriteManagerLoad(0); //playerBody
        SpriteManagerLoad(1); //playerHead
        SpriteManagerLoad(2); //Punch

        SpriteManagerLoad(22); //crab
        SpriteManagerLoad(23); //fish
        SpriteManagerLoad(24); //squid
        SpriteManagerLoad(25); //water slime

        SpriteManagerLoad(7); //stars

        SHOW_SPRITES;

scroll_target = SpriteManagerAdd(SpritePlayerBody, startPositions[2 * Level]*8, startPositions[2 * Level + 1]*8); //add player at specific position
        InitScroll(&level5, collision_tiles, bottom_collision_tiles); ///first argument is the level to load

        SetPalette(BG_PALETTE, 0, 8, bg_palette, bank_StateGame);
        SetPalette(SPRITES_PALETTE, 0, 8, underwater_palette, bank_StateGame);

        SHOW_BKG;

        PlayMusic(level_mod_Data,4,1);    //level music
	}
    else if (Level == 6)
    {
		SPRITES_8x16;
        SpriteManagerLoad(0); //playerBody
        SpriteManagerLoad(1); //playerHead
        SpriteManagerLoad(2); //Punch

        SpriteManagerLoad(3); //Hedgehog
        SpriteManagerLoad(4); //Skunk
        SpriteManagerLoad(5); //Slime
        SpriteManagerLoad(6); //bee

        SpriteManagerLoad(7); //stars

        SHOW_SPRITES;

scroll_target = SpriteManagerAdd(SpritePlayerBody, startPositions[2 * Level]*8, startPositions[2 * Level + 1]*8); //add player at specific position
        InitScroll(&level6, collision_tiles, bottom_collision_tiles); ///first argument is the level to load

        SetPalette(BG_PALETTE, 0, 8, bg_palette, bank_StateGame);
        SetPalette(SPRITES_PALETTE, 0, 8, grass_sprites_palette, bank_StateGame);

        SHOW_BKG;

        PlayMusic(level_mod_Data,4,1);    //level music
	}
    else if (Level == 7)
    {
		SPRITES_8x16;
        SpriteManagerLoad(0); //playerBody
        SpriteManagerLoad(1); //playerHead
        SpriteManagerLoad(2); //Punch

        SpriteManagerLoad(3); //Hedgehog
        SpriteManagerLoad(4); //Skunk
        SpriteManagerLoad(5); //Slime
        SpriteManagerLoad(6); //bee

        SpriteManagerLoad(7); //stars

        SHOW_SPRITES;

scroll_target = SpriteManagerAdd(SpritePlayerBody, startPositions[2 * Level]*8, startPositions[2 * Level + 1]*8); //add player at specific position
        InitScroll(&level7, collision_tiles, bottom_collision_tiles); ///first argument is the level to load

        SetPalette(BG_PALETTE, 0, 8, bg_palette, bank_StateGame);
        SetPalette(SPRITES_PALETTE, 0, 8, grass_sprites_palette, bank_StateGame);

        SHOW_BKG;

        PlayMusic(level_mod_Data,4,1);    //level music
	}
    else if (Level == 8)
    {
		SPRITES_8x16;
        SpriteManagerLoad(0); //playerBody
        SpriteManagerLoad(1); //playerHead
        SpriteManagerLoad(2); //Punch

        SpriteManagerLoad(3); //Hedgehog
        SpriteManagerLoad(4); //Skunk
        SpriteManagerLoad(5); //Slime
        SpriteManagerLoad(6); //bee

        SpriteManagerLoad(7); //stars

        SHOW_SPRITES;

scroll_target = SpriteManagerAdd(SpritePlayerBody, startPositions[2 * Level]*8, startPositions[2 * Level + 1]*8); //add player at specific position
        InitScroll(&level8, collision_tiles, bottom_collision_tiles); ///first argument is the level to load

        SetPalette(BG_PALETTE, 0, 8, bg_palette, bank_StateGame);
        SetPalette(SPRITES_PALETTE, 0, 8, grass_sprites_palette, bank_StateGame);

        SHOW_BKG;

        PlayMusic(level_mod_Data,4,1);    //level music
	}
    else if (Level == 9)
    {
		SPRITES_8x16;
        SpriteManagerLoad(0); //playerBody
        SpriteManagerLoad(1); //playerHead
        SpriteManagerLoad(2); //Punch

        SpriteManagerLoad(3); //Hedgehog
        SpriteManagerLoad(4); //Skunk
        SpriteManagerLoad(5); //Slime
        SpriteManagerLoad(6); //bee

        SpriteManagerLoad(7); //stars

        SHOW_SPRITES;

scroll_target = SpriteManagerAdd(SpritePlayerBody, startPositions[2 * Level]*8, startPositions[2 * Level + 1]*8); //add player at specific position
        InitScroll(&level9, collision_tiles, bottom_collision_tiles); ///first argument is the level to load

        SetPalette(BG_PALETTE, 0, 8, bg_palette, bank_StateGame);
        SetPalette(SPRITES_PALETTE, 0, 8, grass_sprites_palette, bank_StateGame);

        SHOW_BKG;

        PlayMusic(level_mod_Data,4,1);    //level music
	}
    else if (Level == 10) //boss
    {
		SPRITES_8x16;
        SpriteManagerLoad(0); //playerBody
        SpriteManagerLoad(1); //playerHead
        SpriteManagerLoad(2); //Punch

        SpriteManagerLoad(14); //boss face
        SpriteManagerLoad(15); //boss body
        SpriteManagerLoad(16); //boss laser
        SpriteManagerLoad(17); //boss bouncy nut
        SpriteManagerLoad(18); //boss bouncy nut
        SpriteManagerLoad(19); //boss win sprite
        

        SpriteManagerLoad(7); //stars

        SHOW_SPRITES;

scroll_target = SpriteManagerAdd(SpritePlayerBody, startPositions[2 * Level]*8, startPositions[2 * Level + 1]*8); //add player at specific position
        InitScroll(&levelBoss, collision_tiles, 0); ///first argument is the level to load

        SetPalette(BG_PALETTE, 0, 8, bg_palette, bank_StateGame);
        SetPalette(SPRITES_PALETTE, 0, 8, boss_palette, bank_StateGame);

        SHOW_BKG;

        SpriteManagerAdd(SpriteBossFace, 140, 120);


        PlayMusic(boss_mod_Data,1,1);    //boss music

	}
	


	

//now set from player
//	scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);

	

    //SpriteManagerAdd(SpriteSlime, 400, 100); //add enemy at specific position

    

    
}


void Update_StateGame() {
    if (textOnScreen == 0)
    {
        return;
    }
    if (KEY_TICKED(J_A))
    {
        if (usePrintLimit && printLimit != (unsigned)strlen(currentLine))
        {
            printLimit = (unsigned)strlen(currentLine);
            //PlayFx(CHANNEL_1, 10, 0x4f, 0xc7, 0xf3, 0x73, 0x86); //skipped text
        }
        else
        {
            PlayFx(CHANNEL_1, 3, 0x8f, 0xc7, 0xf3, 0x73, 0xdd); //confirm box
            wait = 251;
            lineNum++;
            switch (lineNum)
            {
            case 2:
                currentLine = line2;
                usePrintLimit = 1;
                printLimit = 0;
                ClearTextBoxAndAddName(whoIsTalking[lineNum]?roscoe:croak);
                break;
            case 3:
                currentLine = line3;
                usePrintLimit = 1;
                printLimit = 0;
                ClearTextBoxAndAddName(whoIsTalking[lineNum]?roscoe:croak);
                break;
            case 4:
                currentLine = line4;
                usePrintLimit = 1;
                printLimit = 0;
                ClearTextBoxAndAddName(whoIsTalking[lineNum]?roscoe:croak);
                break;
            case 5:
                currentLine = line5;
                usePrintLimit = 1;
                printLimit = 0;
                ClearTextBoxAndAddName(whoIsTalking[lineNum]?roscoe:croak);
                break;
            case 6:
                currentLine = line6;
                usePrintLimit = 1;
                printLimit = 0;
                ClearTextBoxAndAddName(whoIsTalking[lineNum]?roscoe:croak);
                break;
            case 7:
                currentLine = line7;
                usePrintLimit = 1;
                printLimit = 0;
                ClearTextBoxAndAddName(whoIsTalking[lineNum]?roscoe:croak);
                break;
            case 8:
                currentLine = line8;
                usePrintLimit = 1;
                printLimit = 0;
                ClearTextBoxAndAddName(whoIsTalking[lineNum]?roscoe:croak);
                break;
            case 9:
                currentLine = line9;
                usePrintLimit = 1;
                printLimit = 0;
                ClearTextBoxAndAddName(whoIsTalking[lineNum]?roscoe:croak);
                break;
            case 10:
                currentLine = line10;
                usePrintLimit = 1;
                printLimit = 0;
                ClearTextBoxAndAddName(whoIsTalking[lineNum]?roscoe:croak);
                break;
            case 11:
                currentLine = line11;
                usePrintLimit = 1;
                printLimit = 0;
                ClearTextBoxAndAddName(whoIsTalking[lineNum]?roscoe:croak);
                break;
            case 12:
                currentLine = line12;
                usePrintLimit = 1;
                printLimit = 0;
                ClearTextBoxAndAddName(whoIsTalking[lineNum]?roscoe:croak);
                break;
            case 13:
                currentLine = line13;
                usePrintLimit = 1;
                printLimit = 0;
                ClearTextBoxAndAddName(whoIsTalking[lineNum]?roscoe:croak);
                break;
            case 14:
                currentLine = line14;
                usePrintLimit = 1;
                printLimit = 0;
                ClearTextBoxAndAddName(whoIsTalking[lineNum]?roscoe:croak);
                break;
                
            
            default:
            textOnScreen = 0;
            CloseTextBox();
                break;
            }
        }

    }

    if (usePrintLimit)
    {
        if (wait != 3)
        {
            wait++;
            return;
        }
        if (printLimit == (unsigned)strlen(currentLine))
        {
            usePrintLimit = 0;
            ShowTextInBox(currentLine);
        }
        else
        {
            printLimit++;
            ShowTextInBox(currentLine);
            PlayFx(CHANNEL_4, 4, 0x0c, 0x41, 0x30, 0xc0); //text tick
        }
        wait = 0;
    }

} 

void InitTextBox()
{
    WX_REG = 7;
	WY_REG = 144-(8*4) + 7;
    scroll_h_border = 8*4;
	InitWindow(0, 0, &windowTextBox);
	SHOW_WIN;
	INIT_FONT(font, PRINT_WIN); 
}

void CloseTextBox()
{
    scroll_h_border = 0;
    HIDE_WIN;
}

void ClearTextBoxAndAddName(char name[])
{
    InitWindow(0, 0, &windowTextBox);
    PRINT_POS(1, 0);
    Custom_Printf(name);
}

void ShowTextInBox(const char text[])
{
    PRINT_POS(2, 1);
    Custom_Printf(text);
}


void BossPaletteSwap(BYTE hurt)
{
    if (hurt)
    {
        SetPalette(SPRITES_PALETTE, 0, 8,boss_hurt_palette , bank_StateGame);   
    }
    else
    {
        SetPalette(SPRITES_PALETTE, 0, 8,boss_palette , bank_StateGame);   
    }
    
}




void Custom_Printf(const char* txt, ...){
	UINT8 idx = 0;
    UINT8 firstPrintX = print_x;
    UINT8 charsPrinted = 0;
	unsigned char c;
	unsigned char tmp[10];

	while(*txt) {
        charsPrinted++;
        if (usePrintLimit && charsPrinted == printLimit)
        {
            break;
        }
		if(*txt == ' ') {
			c = font_idx;
		} else if(*txt >= 'A' && *txt <= 'Z'){
			c = font_idx +  1 + *txt - 'A';
		} else if(*txt >= 'a' && *txt <= 'z') {
			c = font_idx +  1 + *txt - 'a';
		} else if(*txt >= '0' && *txt <= '9') {
			c = font_idx + 27 + *txt - '0';
		} else {
			switch(*txt) {
				case  '!': c= font_idx + 37; break;
				case '\'': c= font_idx + 38; break;
				case  '(': c= font_idx + 39; break;
				case  ')': c= font_idx + 40; break;
				case  '-': c= font_idx + 41; break;
				case  '.': c= font_idx + 42; break;
				case  ':': c= font_idx + 43; break;
				case  '?': c= font_idx + 44; break;
			}
		}
        if (*txt == '\n')
        {
            print_x = firstPrintX;
            print_y++;
            txt++;
            continue;
        }
		if(print_target == PRINT_BKG)
			set_bkg_tiles(0x1F & (print_x + scroll_offset_x), 0x1F & (print_y + scroll_offset_y), 1, 1, &c);
		else
			set_win_tiles(print_x, print_y, 1, 1, &c);

		print_x ++;
		txt ++;
	}
}

