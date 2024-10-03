#pragma once
#ifndef _8CC_CPP_HH
#define _8CC_CPP_HH
#include "8cc/8cc_structs.h"

void read_from_string(char *buf);
bool is_ident(Token *tok, char *s);
void expect_newline(void);
void add_include_path(char *path);
void init_now(void);
void cpp_init(void);
Token *peek_token(void);
Token *read_token(void);


#endif  // _CPP_H_
