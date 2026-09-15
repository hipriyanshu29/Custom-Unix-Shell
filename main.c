#include "my_shell.h"



int shell_builtin (char** argv , char** env , char* initial_dir) {



	if (argv == NULL || argv [0] == NULL ) {
		return 0;
	}


	if (my_strcmp (argv[0] , "cd") == 0) {
		return command_cd (argv , env ,  initial_dir);
	} else if (my_strcmp (argv[0] , "pwd") == 0) {
		return command_pwd();
	} else if (my_strcmp (argv[0] , "which") == 0) {
		return command_which (argv , env );
	} else if (my_strcmp (argv[0] , "echo") == 0) {
		return command_echo (argv ,  env);
	} else if (my_strcmp (argv[0] , "env") == 0) {
		int i = 0;
		while (env [i] != NULL) {
			printf ("%s\n", env [i]);
			i++;
		}
		return 1;
	} else if (my_strcmp (argv[0] , "exit") == 0 || my_strcmp (argv[0] , "quit") == 0) {
		exit (EXIT_SUCCESS);
	} else {
		return  executor(argv , env);
	}

}


void shell_loop (char** env) {

	char* input = NULL;
	size_t input_size = 0;
	char** argv;
	char initial_dir[MAX_PATH];

	while (1) {
		getcwd(initial_dir, MAX_PATH);

		printf ("my-shell-[%s]> " , initial_dir);
		getline (&input , &input_size , stdin);
		argv = input_parser (input);


		// for (int i = 0 ; argv[i] ; i++) {
		// 	printf ("argv %d : %s ",i , argv[i]);
		// }

		if (argv[0] == NULL) {
			printf ("\n");
		} else if (strcmp(argv[0] , "setenv") == 0) {
			env = set_env (argv , env);

		} else if (strcmp(argv[0] , "unsetenv") == 0) {
			env = un_setenv (argv , env);
			// int i = 0;
			// while (env[i] != NULL) {
			// 	printf ("%s\n", env [i]);
			// 	i++;
			// }
		} else {
			shell_builtin (argv , env , initial_dir);
		}
		free_allocation (argv);
	}
	free (input);
}

int main (int argc , char** argv , char** env) {

	(void) argv;
	shell_loop (env);
	return 0;
}
