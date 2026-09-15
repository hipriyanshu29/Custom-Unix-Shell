#include "my_shell.h"

int executor (char** argv , char** env) {
    pid_t pid = fork ();
    if (pid == -1) {
        perror ("fork");
    } else if (pid == 0) {
        if (child_process (argv , env)) {
            printf("success\n");
            return 1;
        }
    } else {
        waitpid (pid, NULL, 0);

    }
    return 0;
}

int child_process (char** argv , char** env) {
    if (argv[0] == NULL) {
        printf ("expected a argument \n");
        return -1;
    }
    char* path;
    int pipeline_count = pipeline_present (argv);
    if (pipeline_count ) {
        handle_pipeline(argv , env , pipeline_count);
    }
    else {
        if (my_strchr (argv[0], '/') == 0) {
            path = argv[0];
        } else {
            path = find_command_in_path(env , argv[0]);
        }

        if (path == NULL) {
            printf ("command not found in child\n");
            return 1;
        }
        handle_redirection (argv);
        execvp(path , argv);
        _exit(1);
    }
    return 0;
}

void handle_redirection (char** argv ) {
    for (int i = 0 ; argv[i] != NULL ; i++) {
        if (strcmp (argv[i] , ">") == 0) {
            int fd = open (argv[i+1], O_WRONLY | O_CREAT | O_TRUNC , 0644);
            dup2 (fd, STDOUT_FILENO);
            close (fd);
            argv[i] = NULL;
        } else if (strcmp (argv[i] , ">>") == 0) {
            int fd = open (argv[i+1], O_WRONLY | O_CREAT | O_APPEND ,  0644);
            dup2 (fd , STDOUT_FILENO);
            close (fd);
            argv[i] = NULL;
        } else if (strcmp (argv[i] , "<") == 0) {
            int fd = open (argv[i+1], O_RDONLY , 0644);
            dup2 (fd, STDIN_FILENO);
            close (fd);
            argv[i] = NULL;
        }
    }
}

int pipeline_present (char** argv ) {
    int i = 0;
    int num_pipes = 0;
    while (argv[i] != NULL) {
        if (strcmp (argv[i] , "|") == 0) {

            num_pipes ++;
        }
        i++;
    }
    return num_pipes;
}

void handle_pipeline (char** argv , char** env , int pipeline_count) {


    int j = 0;
    int pipe1[pipeline_count][2];
    for (int i = 0 ; i < pipeline_count ; i++) {
        if (pipe(pipe1[i]) == -1) {
            perror ("pipe()");
        }
    }

    for (int i = 0 ; i <= pipeline_count ; i++) {
        int k = 0;
        char** pipe = malloc (sizeof(char*)*100);
        while (argv[j] != NULL ) {

            if (strcmp (argv[j] , "|") == 0) {
                j++;
                break;
            }
                pipe[k] = strdup (argv[j]);
                k++; j++;

        }
        pipe[k] = NULL;
        char* path = find_command_in_path (env , pipe [0]);
        pid_t pid = fork ();
        if (pid == -1) {
            perror ("fork");
        }
        if (pid == 0) {
            if (i == 0) {
                dup2 (pipe1[0][1], STDOUT_FILENO);

            } else if (i == pipeline_count) {
                dup2 (pipe1[pipeline_count-1][0], STDIN_FILENO);

            } else {
                dup2 (pipe1[i-1][0] , STDIN_FILENO);
                dup2 (pipe1[i][1] , STDOUT_FILENO);
            }
            for (int f = 0 ; f < pipeline_count ; f++) {
                close (pipe1[f][0]);
                close (pipe1[f][1]);
            }
            execvp (path , pipe );
            exit(1);

        }


        free_allocation (pipe);

    }
    for (int i = 0 ; i < pipeline_count ; i++) {
        close (pipe1[i][0]);
        close (pipe1[i][1]);
    }
    for (int i = 0 ; i <= pipeline_count ; i++) {
        wait (NULL);
    }

}