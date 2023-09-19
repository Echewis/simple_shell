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


extern char **environ;
void printit(const char *okwu);
void show_prompt(void);
void run_command(char *instruct);
void recieve_command(char *buffer, size_t buffer_size);
char **split_string(char *string);
void exe_file(char *instruct);
char *get_path(char *command);
char *our_getenv(char *env_name);
char *our_strdup(char *str);
void *our_strcpy(char *dest, const char *src);
int our_strncmp(char *str1, char *str2, size_t n); 
int our_strlen(char *s);
void exit_shell(char *inst);
void env(const char *instruct);/* I'm working on this environment as well */


#endif
