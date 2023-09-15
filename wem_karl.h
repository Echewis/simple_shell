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
void run_command(char *instruct);
void recieve_command(char *buffer, size_t buffer_size);
char **split_string(char *string);
void exe_file(char *instruct);

#endif