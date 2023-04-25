#include "main.h"

/**
 * print_unsigned - Print an unsigned number
 * @types: List of arguments
 * @buffer: Buffer to handle print array
 * @flags: Calculates active flags
 * @width: width
 * @precision: Specification of precision
 * @size: Specify the size
 * Return: Number of chars to be printed.
 */

int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = (num % 10) + '0';
		num /= 10;
	}

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}

/**
 * print_octal - Print an unsigned number in octal notation
 * @types: List of arguments
 * @buffer: Array buffer to handle print
 * @flags: Calculates active flags
 * @width: To call width
 * @precision: Specification of precision
 * @size: Specify the size
 * Return: Number of chars to be printed
 */

int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int a = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[a--] = '0';

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}

/**
 * print_hexadecimal - Unsigned number in lower-case hexadecimal notation
 * @types: List of arguments
 * @buffer: Buffer to handle print array
 * @flags: Calculates active flags
 * @width: Width
 * @precision: Specification of precision
 * @size: Specify the size
 * Return: Number of chars to be printed
 */

int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}


/**
 * print_hexa_upper - Print unsigned number in upper-case hexadecimal notation
 * @types: List of arguments
 * @buffer: Array buffer to handle print
 * @flags: Calculates active flags
 * @width: to call width
 * @precision: Specification of precision
 * @size: Specify the size
 * Return: Number of chars to be printed
 */

int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**
 * print_hexa - Print a hexadecimal number in any case
 * @types: List of arguments
 * @map_to: Array values to map the numbers
 * @buffer: Array buffer to handle print
 * @flags: Calculates active flags
 * @flag_ch: Calculates char flags
 * @width: To call Width
 * @precision: Specification of precision
 * @size: Specify size
 * @size: Specification of size
 * Return: Number of char to be printed
 */

int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[a--] = flag_ch;
		buffer[a--] = '0';
	}

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}
