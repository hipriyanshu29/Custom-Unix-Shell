#include "my_shell.h"

int my_strcmp (const char* str1 , const char* str2) {
	while (*str1 && (*str1 == *str2)) {
		str1++;
		str2++;
	}
	return *(unsigned char*)str1 - *(unsigned char*)str2;
}

int my_strncmp (const char* str1 , const char* str2 , int n) {

	 while (n > 0 && *str1 && (*str1 == *str2)) {
		str1++;
		str2++;
		n--;
	}
	if (n == 0) return 0;
	return *(unsigned char*)str1 - *(unsigned char*)str2;
}

int my_strlen (const char* str) {
	if (str == NULL) return 0;
	int i = 0;
	while (*str) {
		i++;
		str++;
	}
	return i;
}

char* my_getenv (const char* value , char** env) {
	if (value == NULL || env == NULL) return NULL;
	int val_len = my_strlen(value);
	if (val_len == 0) return NULL;

	for (size_t i = 0; env[i]; i++) {
		if (my_strncmp (env[i], value, val_len) == 0 && env[i][val_len] == '=') {
			return &env[i][val_len+1];
		}
	}
	return NULL;
}

char* my_strcpy (char* dest , char* src) {
	if (src == NULL) return NULL;
	int i = 0;
	char* ret = dest;
	while (src[i] != '\0') {
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return ret;
}

char* my_strdup (const char* src) {
	if (src == NULL) return NULL;

	int src_len = my_strlen(src);
	if (src_len == 0) return NULL;
	char* ret = (char*)malloc (src_len + 1);
	if (ret == NULL) return NULL;
	for (size_t i = 0; src[i]; i++) {
		ret[i] = src[i];
	}
	ret[src_len] = '\0';
	return ret;
}
int is_delim (char c , const char* str) {
	if (str == NULL) return -1;
	while (*str != '\0') {
		if (*str == c) return 1;
		str++;
	}
	return 0;
}

char* my_strtok (char* token , const char* delimiter) {
	static char* last = NULL;

	if (token != NULL) last = token;
	if (last == NULL) return NULL;

	while (*last != '\0' && is_delim (*last , delimiter) == 1) {
		last++;
	}

	if (*last == '\0') {
		last = NULL;
		return NULL;
	}
	char* start_token = last;

	while (last != NULL && is_delim (*last, delimiter) == 0) {
		last++;
	}

	if (*last != '\0') {
		*last = '\0';
		last++;
	} else {
		return NULL;
	}

	return start_token;
}


int my_strchr (char* str , char c) {
	if (str == NULL) return -1;

	while (*str != '\0') {
		if (*str == c) return 0;
		str++;
	}

	if (*str == '\0') return 0;
	return 1;
}

char* find_command_in_path (char** env , char* command) {
	if (env == NULL || command == NULL) return NULL;
	char* path_env = NULL;
	char* path = NULL;
	char* token = NULL;
	char full_path [1024];

	path_env = my_getenv ("PATH" , env );


	path = my_strdup (path_env);

	if (path == NULL) return NULL;

	token = my_strtok (path , ":");


	while (token != NULL) {
		snprintf(full_path , sizeof(full_path) , "%s/%s", token , command);

		if (access (full_path , X_OK) == 0) {


			free(path);
			return strdup (full_path);
		}

		token = my_strtok (NULL , ":");
	}
	printf("command not found\n");
	free (path);

	return NULL;
}