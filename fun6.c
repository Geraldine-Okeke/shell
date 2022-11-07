#include "main.h"

/**
 * func_printenv - prints the current environment
 * @environ: environment variable
 */
void func_printenv(char **environ)
{
	int i = 0;

	for (; environ[i] ; i++)
		_puts(environ[i]);
}
/**
 *_puts - prints a string
 *@str: A pointer to an int that will be updated
 *
 *Return: void
 */
void _puts(char *str)
{
	int n;

	for (n = 0 ; str[n] != '\0' ; n++)
	{
		_putchar(str[n]);
	}
	_putchar('\n');
}
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
