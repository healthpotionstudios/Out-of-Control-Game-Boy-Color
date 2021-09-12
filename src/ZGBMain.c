/**
*  Hello, This contains some notes for running my code with ZGB
*
* REQUIRED
* Modify build_color.bat
* You must append the line with N_BANKS=8
* ex. %ZGB_PATH%\..\env\make-3.81-bin\bin\make run BUILD_TYPE=ReleaseColor N_BANKS=8
*
*
* OPTIONAL
* For state independent looping music,
* toggle off these two lines in ZGB/common/src/main.c
*        gbt_stop();
*		 last_music = 0;
*
* Disabling these lines, will cause music to not restart when a state reloads (such as dying)
*
**/



#include "ZGBMain.h"
#include "Math.h"
 
UINT8 Level = 0;
UINT8 mapPos = 0;

UINT8 next_state = StateTitle;
UINT16 lastTile = 0;

const UINT8 anim_wave1[] = {10, 0,0,1,2,3,4,5,1,0,0};
const UINT8 anim_wave2[] = {11, 0,0,0,1,2,3,4,5,1,0,0};



UINT8 GetTileReplacement(UINT8* tile_ptr, UINT8* tile) {
	if(current_state == StateGame) {
		if(U_LESS_THAN(255 - (UINT16)*tile_ptr, N_SPRITE_TYPES)) {
			*tile = lastTile;
			return 255 - (UINT16)*tile_ptr;
		}

		*tile = *tile_ptr;
	}
    lastTile = (UINT16)*tile_ptr;

	return 255u;
}