#pragma once
#ifndef _8CC_SET_HH
#define _8CC_SET_HH
#include "8cc/8cc_structs.h"

Set *set_add(Set *s, char *v);
bool set_has(Set *s, char *v);
Set *set_union(Set *a, Set *b);
Set *set_intersection(Set *a, Set *b);

#endif  // _SET_H_
