#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/dir.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

// TODO: YOUR CODE HERE
// INITIALIZE DATA STRUCTURE TO STORE PIDS OF PROCESSES TO KILL LATER

/* Splits the string by space and returns the array of tokens
 *
 */
char **tokenize(char *line)
{

	// tokenizer variables
	char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
	char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
	int i, tokenIndex = 0, tokenNo = 0;

	// loop on length of line
	for (i = 0; i < strlen(line); i++)
	{

		char readChar = line[i];

		// tokenize on any kind of space
		if (readChar == ' ' || readChar == '\n' || readChar == '\t')
		{
			token[tokenIndex] = '\0';
			if (tokenIndex != 0)
			{
				tokens[tokenNo] = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
				strcpy(tokens[tokenNo++], token);
				tokenIndex = 0;
			}
		}
		else
		{
			token[tokenIndex++] = readChar;
		}
	}

	free(token);
	tokens[tokenNo] = NULL;
	return tokens;
}

// TODO
// MAKE FUNCTIONS AS REQUIRED TO AVOID REPETITIVE WORK
void catFunc(char *fileName)
{
	int fd2 = open(fileName, O_RDONLY);
	if (fd2 == -1)
	{
		// printf("%s: ", tokens[0]);
		perror(fileName);
		return;
	}
	char c;
	while (read(fd2, &c, 1))
	{
		write(STDOUT_FILENO, &c, 1);
	}
}

void echoFunc(char **words)
{
	int i = 0;
	for (; words[i] != NULL; i++)
	{
		char space = ' ';
		write(STDOUT_FILENO, words[i], strlen(words[i]));
		write(STDOUT_FILENO, &space, 1);
	}
	write(STDOUT_FILENO, "\n", 1);
}

void sleepFunc(int time)
{
	sleep(time);
}
void pwdFunc()
{
	char *reqPwd;
	long n = pathconf(".", _PC_PATH_MAX);
	reqPwd = malloc(n * sizeof(*reqPwd));
	getcwd(reqPwd, n);
	printf("%s", reqPwd);
}
void cdFunc(char *path)
{
	if (chdir(path) != 0)
	{
		perror(path);
	}
}
extern int alphasort();
void lsFunc(char *path)
{
	struct dirent **files;
	// if (chdir(path) == NULL)
	// {
	// 	perror(path);
	// }
	int count = scandir(path, &files, NULL, alphasort);
	if (count <= 1)
	{
		printf("There is some erro \n");
		return;
	}

	for (int i = 3; i < count; i++)
	{
		write(STDOUT_FILENO, files[i - 1]->d_name, strlen(files[i - 1]->d_name));
		write(STDOUT_FILENO, "  ", 1);
	}
	write(STDOUT_FILENO, "\n", 1);
}

int main(int argc, char *argv[])
{

	char line[MAX_INPUT_SIZE];
	char **tokens;

	// TODO: YOUR CODE HERE
	// INITIALIZE GLOBAL DATA STRUCTURE OF PIDS TO SOME DEFAULT VALUE
	// INITIALIZE OTHER VARIABLES AS NEEDED

	while (1)
	{

		/* BEGIN: TAKING INPUT */
		bzero(line, sizeof(line));
		printf("$ ");
		scanf("%[^\n]", line);
		getchar();
		/* END: TAKING INPUT */

		line[strlen(line)] = '\n'; // terminate with new line
		tokens = tokenize(line);   // this creates string array of input.

		// You can maintain boolean variables to check which type of command is given by user and then
		// conditionally execute depending on them

		// TODO: YOUR CODE HERE
		// ls, cat, echo, sleep, pwd, ps, man, touch, mkdir, rm, rmdir, kill, diff, clear
		if (tokens[0] != NULL)
		{

			if (strcmp(tokens[0], "cat") == 0)
				catFunc(tokens[1]);
			if (strcmp(tokens[0], "echo") == 0)
				echoFunc(tokens + 1);
			if (strcmp(tokens[0], "sleep") == 0)
				sleepFunc(atoi(tokens[1]));
			if (strcmp(tokens[0], "pwd") == 0)
				pwdFunc();
			if (strcmp(tokens[0], "cd") == 0)
				cdFunc(tokens[1]);
			if (strcmp(tokens[0], "ls") == 0)
			{
				if (tokens[1])
					lsFunc(tokens[1]);
				else
					lsFunc(".");
			}
		}
		// TODO: YOUR CODE HERE

		// freeing the memory
		int i;
		for (i = 0; tokens[i] != NULL; i++)
		{
			// printf("Value of token : %s \n", tokens[i]);
			free(tokens[i]);
		}

		free(tokens);
	}
	return 0;
}
