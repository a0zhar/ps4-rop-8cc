// Copyright 2012 Rui Ueyama. Released under the MIT license.
#pragma once
#ifndef EIGHTCC_H
#define EIGHTCC_H

// System Related Headers
#include <assert.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

// 8CC Compiler Related Headers
#include "headers/8cc/ast_tokens.h"
#include "headers/8cc/encoding_type.h"
#include "headers/8cc/token_type.h"
#include "headers/8cc/type_kind.h"

// (.c) Source Files Related Headers
#include "headers/encoding.h"
#include "headers/buffer.h"
#include "headers/cpp.h"
#include "headers/debug.h"
#include "headers/dict.h"
#include "headers/error.h"
#include "headers/file.h"
#include "headers/gen.h"
#include "headers/lex.h"
#include "headers/map.h"
#include "headers/parse.h"
#include "headers/set.h"
#include "headers/vector.h"

extern Type *type_void;
extern Type *type_bool;
extern Type *type_char;
extern Type *type_short;
extern Type *type_int;
extern Type *type_long;
extern Type *type_llong;
extern Type *type_uchar;
extern Type *type_ushort;
extern Type *type_uint;
extern Type *type_ulong;
extern Type *type_ullong;
extern Type *type_float;
extern Type *type_double;
extern Type *type_ldouble;

#define EMPTY_MAP    ((Map){})
#define EMPTY_VECTOR ((Vector){})


#endif
