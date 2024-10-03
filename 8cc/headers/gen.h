#pragma once
#ifndef _8CC_GEN_HH
#define _8CC_GEN_HH
#include "8cc/8cc_structs.h"

void set_output_file(FILE *fp);
void close_output_file(void);
void emit_toplevel(Node *v);

#endif  // _GEN_H_
