#include "main.h"

/**
 * get_width - Print calculation of width
 * @format: Formatted string to print arguments.
 * @a: arguments to be printed.
 * @list: list of arguments.
 * Return: Width.
 */
int get_width(const char *format, int *a, va_list list)
{
	int curr_a;
	int width = 0;

	for (curr_a = *a + 1; format[curr_a] != '\0'; curr_a++)
	{
		if (is_digit(format[curr_a]))
		{
			width *= 10;
			width += format[curr_a] - '0';
		}
		else if (format[curr_a] == '*')
		{
			curr_a++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*a = curr_a - 1;

	return (width);
}
