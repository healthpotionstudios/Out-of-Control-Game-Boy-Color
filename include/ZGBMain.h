#ifndef ZGBMAIN_H
#define ZGBMAIN_H


#define SPRITE_SET_HMIRROR(SPRITE)   (SPRITE->flags |= 64)
#define SPRITE_UNSET_HMIRROR(SPRITE) (SPRITE->flags &= ~64)
#define SPRITE_GET_HMIRROR(SPRITE)   (SPRITE->flags & 64)


#define STATES \
_STATE(StateTitle)\
_STATE(StateGame)\
STATE_DEF_END

//associate .c sprite file with art (file name without .b3.gbr)
#define SPRITES \
_SPRITE_DMG(SpritePlayerBody, playerBody)\
_SPRITE_DMG(SpritePlayerHead, playerHead)\
_SPRITE_DMG(SpritePunch, playerBody)\
_SPRITE_DMG(SpriteHedgehog, hedgehog)\
_SPRITE_DMG(SpriteSkunk, skunk)\
_SPRITE_DMG(SpriteSlime, slime)\
_SPRITE_DMG(SpriteBee, bee)\
_SPRITE_DMG(SpriteStars, stars)\
_SPRITE_DMG(SpriteTitleWavePurple, wavePurple)\
_SPRITE_DMG(SpriteTitleWaveOrange, waveOrange)\
_SPRITE_DMG(SpriteTitleWaveRed, waveRed)\
_SPRITE_DMG(SpriteTitleWaveGreen, waveGreen)\
_SPRITE_DMG(SpriteTitleWaveBlue, waveBlue)\
_SPRITE_DMG(SpriteTitleWaveYellow, waveYellow)\
_SPRITE_DMG(SpriteBossFace, bossFace)\
_SPRITE_DMG(SpriteBossBody, bossBody)\
_SPRITE_DMG(SpriteBossLaser, bossLaser)\
_SPRITE_DMG(SpriteBossBouncyNut, bossNut)\
_SPRITE_DMG(SpriteBossScrew, bossScrew)\
_SPRITE_DMG(SpriteBossWin, bossWin)\
_SPRITE_DMG(SpriteMapPlayer, playerMap)\
_SPRITE_DMG(SpriteProfCroak, profcroak)\
_SPRITE_DMG(SpriteCrab, crab)\
_SPRITE_DMG(SpriteFish, fish)\
_SPRITE_DMG(SpriteSquid, squid)\
_SPRITE_DMG(SpriteWaterSlime, waterslime)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif