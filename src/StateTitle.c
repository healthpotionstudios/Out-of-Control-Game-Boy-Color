#include "Banks/SetBank2.h"

#include "..\res\src\titleBG.h"
#include "..\res\src\titleScreenMap.h"

#include "ZGBMain.h"
#include "Scroll.h"

#include "Palette.h"
#include "Keys.h"
#include "SpriteManager.h"

#include "../res/src/wavePurple.h" //used for palettes
#include "../res/src/waveOrange.h" //used for palettes
#include "../res/src/waveRed.h" //used for palettes
#include "../res/src/waveGreen.h" //used for palettes
#include "../res/src/waveBlue.h" //used for palettes
#include "../res/src/waveYellow.h" //used for palettes


const UINT16 title_bg_palette[] = {PALETTE_FROM_HEADER(titleBG)}; //file name
UINT16 wave_palette[] = {
	PALETTE_INDEX(wavePurple, 0),
    PALETTE_INDEX(waveOrange, 0),
    PALETTE_INDEX(waveRed, 0),
    PALETTE_INDEX(waveGreen, 0),
};


extern UINT8* title_mod_Data[];

void Start_StateTitle() {

    NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
    
    InitScroll(&titleScreenMap, NULL, 0);

    SetPalette(BG_PALETTE, 0, 8, title_bg_palette, bank_StateTitle);
    SetPalette(SPRITES_PALETTE, 0, 8, wave_palette, bank_StateTitle);

	SHOW_BKG;


    SPRITES_8x8;
    SpriteManagerLoad(8); //purple
    SpriteManagerLoad(9); //orange
    SpriteManagerLoad(10); //red
    SpriteManagerLoad(11); //green
    SpriteManagerLoad(12); //blue
    SpriteManagerLoad(13); //yellow


    SHOW_SPRITES;


    SpriteManagerAdd(SpriteTitleWavePurple, 64, 96);
    SpriteManagerAdd(SpriteTitleWaveOrange, 72, 103);
    SpriteManagerAdd(SpriteTitleWaveRed, 112, 112);
    SpriteManagerAdd(SpriteTitleWaveGreen, 112, 104);
    SpriteManagerAdd(SpriteTitleWaveBlue, 104, 112);
    SpriteManagerAdd(SpriteTitleWaveYellow, 96, 112);

    PlayMusic(title_mod_Data,3,1);
}

void Update_StateTitle() {
    if (KEY_PRESSED(J_START))
    {
        SetState(StateGame);
    }
}