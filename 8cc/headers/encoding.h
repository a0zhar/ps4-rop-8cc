#pragma once
#ifndef _8CC_ENCODING_HH
#define _8CC_ENCODING_HH
#include "8cc/8cc_structs.h"
#include <stdint.h>
Buffer *to_utf16(char *p, int len);
Buffer *to_utf32(char *p, int len);
void write_utf8(Buffer *b, uint32_t rune);


#endif