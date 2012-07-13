#include "hgestrings.h"
#include "hgestrings_c.h"
#include "hgestrings_impl.h"

#include <malloc.h>

extern "C" {

HGE_StringTable_t *HGE_StringTable_New(const char *filename) {
	HGE_StringTable_t *st = (HGE_StringTable_t *)malloc(sizeof(HGE_StringTable_t));

	st->st = new hgeStringTable(filename);

	return st;
}

void HGE_StringTable_Free(HGE_StringTable_t *st) {
	delete st->st;
	free(st);
}

char *HGE_StringTable_GetString(HGE_StringTable_t *st, const char *name) {
	return st->st->GetString(name);
}

}
