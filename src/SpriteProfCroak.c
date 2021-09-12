#include "Banks/SetBank2.h"
// #include "Keys.h"
#include "SpriteManager.h"
// #include "ZGBMain.h" // get access to sprite types, delta_time

const UINT8 anim_croak[] = {2, 0, 1};

void Start_SpriteProfCroak() {
SetSpriteAnim(THIS, anim_croak, 4u);   
}

void Update_SpriteProfCroak() {

} 

void Destroy_SpriteProfCroak() {
}
