#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

// Helper function to convert unsigned integer to string
static size_t uint_to_str(char* buffer, unsigned int value, unsigned int base) {
    if (value == 0) {
        buffer[0] = '0';
        return 1;
    }
    
    size_t len = 0;
    while (value > 0) {
        unsigned int digit = value % base;
        buffer[len] = (digit < 10) ? '0' + digit : 'a' + (digit - 10);
        value /= base;
        len++;
    }
    
    // Reverse the string
    for (size_t i = 0; i < len / 2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[len - 1 - i];
        buffer[len - 1 - i] = temp;
    }
    
    return len;
}

// Helper function to convert signed integer to string
static size_t int_to_str(char* buffer, int value) {
    if (value == 0) {
        buffer[0] = '0';
        return 1;
    }
    
    size_t len = 0;
    unsigned int abs_value;
    
    if (value < 0) {
        buffer[len++] = '-';
        abs_value = (unsigned int)(-value);
    } else {
        abs_value = (unsigned int)value;
    }
    
    // Convert the absolute value
    size_t num_len = uint_to_str(buffer + len, abs_value, 10);
    return len + num_len;
}

static bool print(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i]) == EOF)
			return false;
	return true;
}

int printf(const char* restrict format, ...) {
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while (*format != '\0') {
		size_t maxrem = INT_MAX - written;

		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%')
				format++;
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			if (maxrem < amount) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}

		const char* format_begun_at = format++;

		if (*format == 'c') {
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
		} else if (*format == 's') {
			format++;
			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		} else if (*format == 'd' || *format == 'i') {
			format++;
			int value = va_arg(parameters, int);
			char buffer[32]; // Large enough for any int
			size_t len = int_to_str(buffer, value);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(buffer, len))
				return -1;
			written += len;
		} else if (*format == 'u') {
			format++;
			unsigned int value = va_arg(parameters, unsigned int);
			char buffer[32]; // Large enough for any unsigned int
			size_t len = uint_to_str(buffer, value, 10);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(buffer, len))
				return -1;
			written += len;
		} else if (*format == 'x' || *format == 'X') {
			format++;
			unsigned int value = va_arg(parameters, unsigned int);
			char buffer[32]; // Large enough for any hex value
			size_t len = uint_to_str(buffer, value, 16);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(buffer, len))
				return -1;
			written += len;
		} else if (*format == 'p') {
			format++;
			void* ptr = va_arg(parameters, void*);
			char buffer[32]; // Large enough for pointer
			buffer[0] = '0';
			buffer[1] = 'x';
			size_t len = uint_to_str(buffer + 2, (unsigned int)ptr, 16) + 2;
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(buffer, len))
				return -1;
			written += len;
		} else {
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len))
				return -1;
			written += len;
			format += len;
		}
	}

	va_end(parameters);
	return written;
}
