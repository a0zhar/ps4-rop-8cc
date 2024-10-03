#pragma once
#ifndef _8CC_MAPPER_HH
#define _8CC_MAPPER_HH
#include "8cc/8cc_structs.h"

Map *make_map(void);
Map *make_map_parent(Map *parent);
void *map_get(Map *m, char *key);
void map_put(Map *m, char *key, void *val);
void map_remove(Map *m, char *key);
size_t map_len(Map *m);

#endif  // _MAP_H_
