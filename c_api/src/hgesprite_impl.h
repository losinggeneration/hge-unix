#ifndef HGE_SPRITE_IMPL_H
#define HGE_SPRITE_IMPL_H

#include "hgesprite.h"

extern "C" {

typedef struct HGE_Sprite_s {
	hgeSprite *s;
} HGE_Sprite_t;

HGE_Sprite_t *HGE_Sprite_Empty();

}

#endif
