#pragma once
#ifndef _8CC_DICT_HH
#define _8CC_DICT_HH
#include "8cc/8cc_structs.h"

Dict *make_dict(void);
void *dict_get(Dict *dict, char *key);
void dict_put(Dict *dict, char *key, void *val);
Vector *dict_keys(Dict *dict);


#endif