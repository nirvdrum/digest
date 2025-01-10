#ifndef BLAKE3_INCLUDED
#define BLAKE3_INCLUDED

#include "vendor/blake3.h"

typedef struct blake3_state_s {
    blake3_hasher hasher;
} BLAKE3_CTX;

#ifdef RUBY
/* avoid name clash */
#define BLAKE3_Init   rb_Digest_BLAKE3_Init
#define BLAKE3_Update rb_Digest_BLAKE3_Update
#define BLAKE3_Finish rb_Digest_BLAKE3_Finish
#endif

int  BLAKE3_Init _((BLAKE3_CTX *pms));
void BLAKE3_Update _((BLAKE3_CTX *pms, const uint8_t *data, size_t nbytes));
int  BLAKE3_Finish _((BLAKE3_CTX *pms, uint8_t *digest));

#endif /* BLAKE3_INCLUDED */
