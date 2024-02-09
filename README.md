
# The Lunar Kernel (32-Bit)
This is made by me following along through the osdev wiki as a learning experience for fun, love it. the code isn't fully copied obviously

A basic kernel with a simple tty and library (of sorts), you can write to the screen and change the color of the background and foreground

currently colors are indexed 0-15
```
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
```

### commands
./buildboot - Builds an `.iso` along with the grub config

./build:    - Runs all of the make files in the project

./clean:    - removes all of the build things and runs the clean operation in all the make files

./default-host  - I personally use `i386` if you use `i686` just change it

./headers   - creates all of the system headers

./qemu      - builds the project and opens it in qemu (i call this script babes sometimes its so useful)




## Building and running the project
**you must have a cross compiler such as i386elfgcc and you must specifiy its path in the `default-host.sh`**

then you can make ur changes, build and run it in whichever vm software that tickles your fancy
