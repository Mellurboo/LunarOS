#include <string.h>

/// @brief finds the size of a string and returns it
/// @param str target string
/// @return size of a string
size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
