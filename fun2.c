#include "main.h"

/**
 * _which - identifies the path of the command(*args) that is being passed
 * to it
 * @foundpath: the command that is being passed to it
 * Return: the complete path of the command or 0 on failure
 */
char **_which(char *foundpath)
{
	int size = TOK_BUFSIZE, i = 0;
	char *copy_path = NULL, *tokens = NULL, *sparse = ":=";
	char **dir = _calloc(sizeof(char *), size);

	if (foundpath == NULL)
	{
		free(foundpath);
		return (0);
	}
	if (dir == NULL)
		{
			free(foundpath);
			perror("Error allocated memory");
			return (NULL);
		}

	copy_path = _strdup(foundpath); /*copiar el string --> palabra PATH*/
	tokens = strtok(copy_path, sparse); /*separar el string por un separador*/
	while (tokens != NULL)
	{
		dir[i] = tokens;
		i++;
		tokens = strtok(NULL, sparse);
	}

	return (dir);
}


/**
 * child_process - executes a command if the path of it is an executable file
 * @args: the command to be executed
 * @env: environment variable
 * @status_main: status variable
 * @av: name of program
 * @cnt: count of prompt
 * Return: 1
 */
int child_process(char **av, char **args, char **env, int status_main, int cnt)
{
	pid_t pid;
	int status;

	if (args == NULL)
		return (-1);

	pid = fork();
	if (pid  < 0)
	{
		perror("./hsh: ");
		exit(1);
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, env) == -1)
		{
			_error(av[0], cnt, args[0]);
			free(args);
			exit(1);
		}
		exit(0);
	}
	else
	{
		if (status_main == 1)
			free(args[0]);

		free(args);
		waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}

/**
 * search_path - gets the path to execute commands
 * @environ: Environment variable
 * Return: token_path
 *
 */
char **search_path(char **environ)
{
	int position = 0;
	char **token_path;

	for (; environ[position] != NULL ; position++)
	{
		if (environ[position][0] == 'P' && environ[position][2] == 'T')
		{
			token_path = _which(environ[position]);
		}
	}
	return (token_path);
}
/**
 * _strcmp - compare two strings
 * @s1: string one
 * @s2: string two
 * Return: returns an integer less  than,  equal  to,  or
 * greater  than zero if s1 is found, respectively, to be
 * less than, to match, or be greater than s2.
 */
int _strcmp(char *s1, char *s2)
{
	char *p1 = s1;
	char *p2 = s2;

	while (*p1 != '\0' && *p2 != '\0' && *p1 == *p2)
	{
		p1++;
		p2++;
	}
	return (*p1 - *p2);
}

/**
 * read_input - stores whatever is passed to it as standard input
 * Return: string containing the input
 */
char *read_input(void)
{
	char *line = NULL;
	ssize_t signal;
	size_t bufsize = 0;
	int i;

	signal = getline(&line, &bufsize, stdin);
	if (!line)
	{
		perror("Error allocating memory for buffer");
		return (0);
	}
	if (signal == 1)
	{
		free(line);
		return (NULL);
	}
	else if (signal == EOF)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		free(line);
		exit(0);
	}
	else
	{
		for (i = 0; line[i] == ' ' && line[i + 1] == ' '; i++)
			;
		if (!line[i] && line[i + 1] == '\n')
		{
			free(line);
			return (0);
		}
	}
	return (line);
}

/**
 * sparse_str - devides a string into and array of strings
 * @line: the string to be separated
 * @env: environment variable
 * Return: tokens(array of strings) on succes or EXIT_FAILURE if fails
 */
char **sparse_str(char *line, char **env)
{
	int bufsize = TOK_BUFSIZE, posicion = 0;
	char **tokens;
	char *token;

	if (line == NULL)
	{
		return (0);
	}
	tokens = _calloc(sizeof(char *), bufsize);
	if (!tokens)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, TOK_DELIM);
	while (token != NULL)
	{
		tokens[posicion] = token;
		posicion++;
		token = strtok(NULL, TOK_DELIM);
	}
	if (tokens[0] == NULL)
		tokens[posicion] = "\n";

	if ((_strcmp(tokens[0], "exit") == 0) && tokens[1] == NULL)
	{
		free(line);
		free(tokens);
		exit(0);
	}
	if ((_strcmp(tokens[0], "env") == 0) && tokens[1] == NULL)
		func_printenv(env);

	return (tokens);
}

/**
 * prompt - prints '$' and waits for a user's input
 */
void prompt(void)
{
	char *prompt = {"{^_^} "};
	char *buffer = getcwd(NULL, 0);

	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, prompt, _strlen(prompt));
	}
	free(buffer);
}
/**
 * _strlen - returns a string
 * @s: integer to be used
 * Return: length of string
 */
int _strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return ((i + 1));
}
