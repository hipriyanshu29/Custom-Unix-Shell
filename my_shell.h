#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_INPUT 1024
#define MAX_PATH 256

// main.c file content.
void shell_loop (char** env);
int shell_builtin (char** argv , char** env , char *initial_dir);

// input_parser.c file content.
char** input_parser (char* input);
void free_allocation (char** argv);

//helper_functions.c file content.
int my_strcmp (const char* str1 , const char* str2);
int my_strncmp (const char* str1 , const char* str2 , int n);
int my_strlen (const char* str);
char* my_getenv (const char* value , char** env);
char* my_strdup (const char* str);
char* my_strcpy (char* dest , char* src);
int my_strchr (char* str , char c);
char* my_strtok (char* token , const char* delimiter);
int is_delim (char c , const char* str);
char* find_command_in_path (char** env , char* command);

//builtin.c file content
int command_cd (char** argv ,char** env , char* initial_dir);
int command_pwd ();
int command_which(char** argv , char** env);
int command_echo (char** argv , char** env);
int command_env (char** env);

//executor.c file content
int executor (char** argv , char** env);
int child_process (char** argv , char** env );
void handle_redirection (char** argv );
int pipeline_present (char** argv);
void handle_pipeline (char** argv , char** env , int pipeline_count);

char** set_env (char** argv , char** env);
char** un_setenv (char** argv , char** env);
