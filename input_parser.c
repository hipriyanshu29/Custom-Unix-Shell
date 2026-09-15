#include "my_shell.h"

char** input_parser (char* input) {
	if (!input) return NULL;
	char** argv = malloc (sizeof(char*)*MAX_INPUT);
	char* token;
	size_t i = 0;
	size_t position = 0;


	while (input[i] != '\0' && position < MAX_INPUT - 1) {


		while (input[i] == ' ' || input[i] == '\t' || input[i] == '\n' || input[i] == '\r') {
			i++;
		}
		if (input[i] == '\0') {
			break;
		}

		token = &input[i];
		size_t token_length = 0;

		while (input[i]  != '\0' && input[i] != ' ' && input[i] != '\t' && input[i] != '\n' && input[i] != '\r') {
			token_length++;
			i++;
		}

		argv[position] = malloc(sizeof(char)*token_length+1);


		for (size_t j = 0 ; j < token_length ; j++) {
			argv[position][j] = token[j];
		}
		argv[position][token_length] = '\0';
		position++;
	}
	argv[position] = NULL;
	return argv;
}

void free_allocation (char** argv) {
	if (!argv) {
		return;
	}
	for (size_t i = 0 ; argv[i] ; i++) {
		free (argv[i]);
	}
	free (argv);
}

