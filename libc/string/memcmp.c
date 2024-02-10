#include <string.h>


/// @brief compare 2 blocks of memory
/// @param aptr pointer to the first block
/// @param bptr pointer to the second block
/// @param size number of bytes to compare
/// @return int
int memcmp(const void* aptr, const void* bptr, size_t size) {
	const unsigned char* a = (const unsigned char*) aptr;
	const unsigned char* b = (const unsigned char*) bptr;
	for (size_t i = 0; i < size; i++) {
		if (a[i] < b[i])
			return -1;
		else if (b[i] < a[i])
			return 1;
	}
	return 0;
}
