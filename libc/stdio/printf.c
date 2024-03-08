#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static bool print(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i]) == '\0')
			return false;
	return true;
}

int printf(const char* restrict formatchar, ...) {
	va_list parameters;
	va_start(parameters, formatchar);

	int written = 0;

	while (*formatchar != '\0') {
		size_t maxrem = INT_MAX - written;

		if (formatchar[0] != '%' || formatchar[1] == '%') {
			size_t amount = 1;
			if (formatchar[0] == '%'){
				formatchar++;
			}

			while (formatchar[amount] && formatchar[amount] != '%'){
				amount++;
			}

			// error checks (we repeat this alot)
			if (maxrem < amount) {
				return -1;
			}else if(!print(formatchar, amount)){
				return -1;
			}
			// =====

			formatchar += amount;
			written += amount;
			continue;
		}

		const char* format_begun_at = formatchar++;

		if (*formatchar == 'c') {

			formatchar++;
			char c = (char) va_arg(parameters, int);
			if (!maxrem) {
				return -1;
			}

			if (!print(&c, sizeof(c))){
				return -1;
			}
			written++;

		} else if (*formatchar == 's') {
			
			formatchar++;
			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);
			if (maxrem < len) {
				return -1;
			}
			
			if (!print(str, len)){
				return -1;
			}
			written += len;
			
		} else {
			formatchar = format_begun_at;
			size_t len = strlen(formatchar);
			if (maxrem < len) {
				return -1;
			}

			if (!print(formatchar, len)){
				return -1;
			}
			written += len;
			formatchar += len;
		}
	}

	va_end(parameters);
	return written;
	
}