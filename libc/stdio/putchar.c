// a nice implementation of putchar that doesnt rely on the tty (it does rely on the tty)

#include <stdio.h>

#if defined(__is_libk)
#include <kernel/tty.h>
#endif

int putchar(int ic) {
#if defined(__is_libk)
	char c = (char) ic;
	tty_write(&c, sizeof(c));
#endif
	return ic;
}
