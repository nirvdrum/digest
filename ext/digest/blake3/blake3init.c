/* $RoughId: sha2init.c,v 1.3 2001/07/13 20:00:43 knu Exp $ */
/* $Id$ */

#include <ruby/ruby.h>
#include "../digest.h"
#include "vendor/blake3.h"
#include "blake3.h"

#include <stdio.h>

static const rb_digest_metadata_t blake3 = {
    RUBY_DIGEST_API_VERSION,
    BLAKE3_OUT_LEN,
    BLAKE3_BLOCK_LEN,
    sizeof(BLAKE3_CTX),
    (rb_digest_hash_init_func_t)BLAKE3_Init,
    (rb_digest_hash_update_func_t)BLAKE3_Update,
    (rb_digest_hash_finish_func_t)BLAKE3_Finish,
};

int BLAKE3_Init(BLAKE3_CTX *ctx) {
    blake3_hasher_init(&ctx->hasher);

    return 1;
}

void BLAKE3_Update(BLAKE3_CTX *ctx, const uint8_t *data, size_t nbytes) {
    blake3_hasher_update(&ctx->hasher, data, nbytes);
}

int BLAKE3_Finish(BLAKE3_CTX *ctx, uint8_t *digest) {
    blake3_hasher_finalize(&ctx->hasher, digest, BLAKE3_OUT_LEN);

    return 1;
}

void
Init_blake3(void)
{
    VALUE mDigest, cDigest_Base, cDigest_BLAKE3;
    ID id_metadata = rb_id_metadata();

#if 0
    mDigest = rb_define_module("Digest"); /* let rdoc know */
#endif
    mDigest = rb_digest_namespace();
    cDigest_Base = rb_const_get(mDigest, rb_intern_const("Base"));

    cDigest_BLAKE3 = rb_define_class_under(mDigest, "BLAKE3", cDigest_Base);
    rb_ivar_set(cDigest_BLAKE3, id_metadata, rb_digest_make_metadata(&blake3));
}

