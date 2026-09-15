#include "my_shell.h"

int command_cd (char** argv , char** env , char* initial_dir) {
    (void) initial_dir;
    if (argv[1] == NULL) {
        char* target = my_getenv ("HOME" , env);
        chdir (target);
        return 1;
    }
    else if (strcmp (argv[1] , "~") == 0) {
        char* target = my_getenv ("HOME" , env);
        chdir (target);
        return 0;
    }
    else if (chdir (argv[1]) == 0) {
        return 0;
    } else {
        printf ("chdir failed\n");
    }
    return 1;
}

int command_pwd () {
    char pwd[MAX_PATH];
    getcwd (pwd, sizeof(pwd));
    printf ("%s\n", pwd);
    return 0;
}

int command_echo (char** argv , char** env) {
    int new_line = 1;
    int i = 1;
    if (argv[i] == NULL) {
        printf("\n");
        return 0;
    }
    if (my_strcmp(argv[1] , "-n") == 0) {
        new_line = 0;
        i++;
    }

    for (; argv[i]; i++) {


        if (argv[i][0] == '$') {
            char* value = my_getenv(argv[i]+1 , env);
            if (value) {
                printf ("%s\n", value);
            } else {
                printf ("nothing found\n");
            }
        } else {
            printf ("%s", argv[i]);
        }
        if (argv[i+1] != NULL) {
            printf (" ");
        }
    }
    if (new_line) {
        printf ("\n");
    }

    return 0;

}

int command_which(char** argv , char** env) {
    if (argv[1] == NULL) {
        printf ("expected a argumenr\n");
        return 1;
    }
    char* builtin_commands[] = {"cd", "pwd", "which" , "exit" , "echo" , "env" , NULL};
    for (int i = 0; builtin_commands[i]; i++) {
        if (my_strcmp (builtin_commands[i] , argv[1]) == 0) {
            printf ("%s is builtin command\n", builtin_commands[i]);
            return 0;
        }
    }
    char* path = find_command_in_path(env , argv[1]);

    if (path == NULL) {
        printf ("command not found\n");
        return 1;
    } else {
        printf ("%s\n", path);
        free (path);
        return 0;
    }
    return 0;
}

char** set_env (char** argv , char** env) {
    if (argv[1] == NULL) {
        printf ("expected a argument \n");
        return NULL;
    }

    int env_count = 0;
    while (env[env_count] != NULL) {
        env_count++;
    }
    char** new_env = (char**) malloc ((env_count+2) * sizeof(char*));
    for (int i = 0; i < env_count; i++) {
        new_env[i] = strdup (env[i]);
    }
    // free_allocation(env);

    new_env[env_count] = strdup(argv[1]);
    new_env[env_count+1] = NULL;
    return new_env;
}


char** un_setenv (char** argv , char** env) {
    if (argv[1] == NULL) {
        printf ("expected a argument \n");
        return NULL;
    }
    int env_count = 0;
    while (env[env_count] != NULL) {
        env_count++;
    }
    char** new_env = (char**) malloc ((env_count) * sizeof(char*));
    for (int i = 0; i < env_count; i++) {
        if (strncmp (env[i] , argv[1] , strlen(argv[1]) ) == 0) {
            continue;
        }
        new_env[i] = strdup (env[i]);
    }
    new_env[env_count] = NULL;
    return new_env;
}