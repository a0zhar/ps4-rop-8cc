#pragma once
#ifndef _8CC_FILE_HH
#define _8CC_FILE_HH
#include "8cc/8cc_structs.h"

File *make_file(FILE *file, char *name);
File *make_file_string(char *s);
int readc(void);
void unreadc(int c);
File *current_file(void);
void stream_push(File *file);
int stream_depth(void);
char *input_position(void);
void stream_stash(File *f);
void stream_unstash(void);

#endif  // _FILE_H_
