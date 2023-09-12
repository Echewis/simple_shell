#ifndef WEM_KARL_H
#define WEM_KARL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

void printit(const char *okwu);
void show_prompt(void);
void run_command(const char *instruct);
void recieve_command(char *st_c, size_t how_big);
void split_string(char *string, const char *delimiter);

#endif