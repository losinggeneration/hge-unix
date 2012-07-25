#ifndef HGE_RECT_IMPL_H
#define HGE_RECT_IMPL_H

#include "hgerect.h"

extern "C" {

typedef struct HGE_Rect_s {
	HGE_Rect_s() {};
	HGE_Rect_s(hgeRect *r) : r(r) {};
	hgeRect *r;
} HGE_Rect_t;

}

#endif
