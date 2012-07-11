#ifndef HGE_STRINGS_C_H
#define HGE_STRINGS_C_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HGE_StringTable_s HGE_StringTable_t;

HGE_StringTable_t *HGE_StringTable_New(const char *filename);
void HGE_StringTable_Free(HGE_StringTable_t *st);

char *HGE_StringTable_GetString(HGE_StringTable_t *st, const char *name);

#ifdef __cplusplus
}
#endif

#endif
