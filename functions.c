#include "main.h"

/*printing characters*/

/**
 * print_char - Print char
 * @types: List of arguments
 * @buffer: Array buffer to handle print
 * @flags: Calculates active flags
 * @width: To call Width
 * @precision: Specification of precision
 * @size: Specify the size
 * Return: Number of char to be printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/*printing a string*/
/**
 * print_string - Print string
 * @types: List of arguments
 * @buffer: Array buffer to handle print
 * @flags: Calculates active flags
 * @width: To call width.
 * @precision: Specification of precision
 * @size: Specify the size
 * Return: Number of char to be printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0;
	int a;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (a = width - length; a > 0; a--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (a = width - length; a > 0; a--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}
	return (write(1, str, length));
}

/*printing percentage sign*/

/**
 * print_percent - Print a percentage sign
 * @types: List of arguments
 * @buffer: Array buffer to handle print
 * @flags: Calculates active flags
 * @width: To call width.
 * @precision: Specification of precision
 * @size: Specify the size
 * Return: Number of char to be printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/*printing an integer*/

/**
 * print_int - Print an integer
 * @types: List of arguments
 * @buffer: Array buffer to handle print
 * @flags: Calculates active flags
 * @width: To call width.
 * @precision: Specification of precision
 * @size: Specify the size
 * Return: Number of char to be printed
 */

int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	int is_negative = 0;
	long int l = va_arg(types, long int);
	unsigned long int num;

	l = convert_size_number(l, size);

	if (l == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)l;

	if (l < 0)
	{
		num = (unsigned long int)((-1) * l);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[a--] = (num % 10) + '0';
		num /= 10;
	}

	a++;

	return (write_number(is_negative, a, buffer, flags, width, precision, size));
}

/*printing binary*/

/**
 * print_binary - Print an unsigned number
 * @types: List of arguments
 * @buffer: Array buffer to handle print
 * @flags: Calculates active flags
 * @width: To call width.
 * @precision: Specification of precision
 * @size: Specify the size
 * Return: Number of char to be printed.
 */

int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int i, j, k, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	i = va_arg(types, unsigned int);
	j = 2147483648; /* (2 ^ 31) */
	a[0] = i / j;
	for (k = 1; k < 32; k++)
	{
		j /= 2;
		a[k] = (i / j) % 2;
	}
	for (k = 0, sum = 0, count = 0; k < 32; k++)
	{
		sum += a[k];
		if (sum || k == 31)
		{
			char z = '0' + a[k];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
